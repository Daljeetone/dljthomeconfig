import optparse
import shlex
import classes
import os
import sys
import fnmatch
from DataStructureDict import *

def load_preefi():
  usage = "usage: %prog"
  description='''Load Pre-Efi Symbols'''
  parser = optparse.OptionParser(description=description, prog='preefi',usage=usage)
  parser.add_option('-t', '--target', dest='target', default=None, type="string")
  return parser

def find_preefi_symbols(base_path,Target):

   for root, dirnames, filenames in os.walk(base_path):
      for filename in fnmatch.filter(filenames, '*.lldb'):
          Path = os.path.join(root, filename)
          PathCheck = ["BuildResults", Target]
          if  all([Item in Path for Item in PathCheck]) and not "bootloader" in Path:
             lines = [line.rstrip('\n').split(' ') for line in open(Path)]
             return root + '/' + filename
         
def load_preefi_command(debugger, command, result, unused):

   command_args = shlex.split(command)
   parser = load_preefi()
   parser.set_defaults(target=True)
   try:
      (options, args) = parser.parse_args(command_args)
      Address = 0
      if not (options.target):
         result.PutCString ("bad arguments!")
         result.SetStatus (lldb.eReturnStatusFailed)
         return
 
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   if options.target == True:

     BaseAddr = classes.init_command(debugger)

     HobAddr = classes.get_hob_addrs_by_type(BaseAddr, "EFI_HOB_MEMORY_ALLOCATION_MODULE")

     if len(HobAddr) != 1:
      print "Unable to load any target. Please specify a target"
      sys.exit()

     DxeCoreAddress = HobAddr[0] + 24

     FileNameLoc = ReadDataStructureMember(EFI_HOB_MEMORY_ALLOCATION_MODULE_Dict, "FileName", HobAddr[0])
     FileName = read_string_from_mem(FileNameLoc)

     HexData = bytearray(read_memory_block(DxeCoreAddress, 8))

     DecData = "%s" %  ''.join('%02x ' % byte for byte in HexData)
     DecData = DecData.replace(" ", "")
     StrData = "".join(reversed([DecData[i:i+2] for i in range(0, len(DecData), 2)]))
     Location = int(StrData,16)

     FilePaths = dict()

     FilePaths[Location] = FileName

     AddCommand = ('target modules add %s' % FileName)
     LoadCommand = ('target modules load --file %s --slide 0x%x' % (os.path.basename(FileName), Location))
     debugger.HandleCommand(AddCommand)
     debugger.HandleCommand(LoadCommand)

     Path = FilePaths[Location].split('/')
     for i, val in enumerate(Path):
        if (val.lower() == "buildresults"): break

     LocalSourcePath = '/'.join(Path[:(i+1)])
     #(i),          (i+1),  (i+2)
     #BuildResults/N61diag/release
     Target = Path[i+1]+'/'+Path[i+2]
     print("Finding peisymbols from %s, Target = %s" % (LocalSourcePath, Target))
     FileName = find_preefi_symbols(LocalSourcePath, Target)
     LoadCommand = ('command source --stop-on-error false %s' % (FileName))
     debugger.HandleCommand(LoadCommand)

   else:

     FileName = find_preefi_symbols(os.pardir,options.target)
     LoadCommand = ('command source --stop-on-error false %s' % (FileName))
     debugger.HandleCommand(LoadCommand)
