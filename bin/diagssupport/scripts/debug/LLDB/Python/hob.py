import sys
import optparse
import shlex
import classes
from DataStructureDict import *

def create_hob_options():
  usage = "usage: %prog [options]"
  description='''Dump HOBs'''
  parser = optparse.OptionParser(description=description, prog='hob',usage=usage)
  parser.add_option('-l', '--list', action='store_true', dest='list', help='display summary all the hobs', default=False)
  parser.add_option('-p', '--pei', action='store_true', dest='pei', help='display summary all the hobs in preefi', default=False)
  parser.add_option('-t', '--type', dest='type', default=None, type="string", help=str(HobDict))
  return parser

def hob_command(debugger, command, result, unused):
   """hob <-l|-t <hob_type>>"""
 
   # Use the Shell Lexer to properly parse up command options just like a
   # shell would
   command_args = shlex.split(command)
   parser = create_hob_options()

   stack = False

   try:
      (options, args) = parser.parse_args(command_args)
      Address = 0
      if not (options.type or options.list):
         result.PutCString ("bad arguments!")
         result.SetStatus (lldb.eReturnStatusFailed)
         return
 
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   BaseAddr = classes.init_command(debugger)
   
   if not options.pei:
       BaseAddr = classes.get_hob_list(BaseAddr)

   if not BaseAddr:
      print "Cannot dump the hob. Missing needed hob info"
      sys.exit()

   if options.list:
      HobType = 1
      HobAddr = BaseAddr
      while HobType != 0xFFFF:
         HobLength = ReadDataStructureMember(EFI_HOB_GENERIC_HEADER_Dict, "HobLength", HobAddr)
         HobType = ReadDataStructureMember(EFI_HOB_GENERIC_HEADER_Dict, "HobType", HobAddr)
         classes.debug_print("Hob Type: 0x%x, HobLength: %d" % (HobType, HobLength))
         PrintDataStructure(debugger, result, HobDict[HobType], HobAddr)
         HobAddr += HobLength

   if options.type and options.type == "stack":
      options.type = "EFI_HOB_GUID_TYPE"
      stack = True

   if options.type and options.type in DataStructureDict.keys():
      for addr  in classes.get_hob_addrs_by_type(BaseAddr, options.type):
         if stack:
            guid = ReadDataStructureMember(EFI_HOB_GUID_TYPE, "Guid", addr)
            guidStr = GuidToStr(guid)
            if guidStr == gStackGUID:
               PrintDataStructure(debugger, result, "APPLE_STACK_DESC", addr)
         else:
            PrintDataStructure(debugger, result, options.type, addr)

   return

