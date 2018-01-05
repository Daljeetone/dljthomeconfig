import optparse
from DataStructureDict import *
from subprocess import call
import hob
import os
import sys
import shlex
import ssl
import urllib2
import fnmatch
import classes
import shutil
import zipfile

from ArtifactoryConnection import ArtifactoryConnection

def create_load_symbols_options():
  usage = "usage: %prog"
  description='''Load debug symbols'''
  parser = optparse.OptionParser(description=description, prog='symbols',usage=usage)
  parser.add_option('-p', '--history', dest='history', default=None, action="store")
  parser.add_option('-w', '--workspace', dest='workspace', default=None, action="store")
  parser.add_option('-m', '--main', action='store_true', dest='main', help='Just load dxe main', default=False)
  return parser

def find_preefi_symbols(base_path,Target,BuildType):
   print("Finding pei symbols from %s for %s %s" % (base_path, BuildType, Target))
   for root, dirnames, filenames in os.walk(base_path):
      for filename in fnmatch.filter(filenames, '*.lldb'):
         #print "checking", root + str(os.path.sep) + filename
         if all(x in root for x in ["FV", Target, BuildType]):
            # must come from diags
            if not "bootloader" in root:
               print "found", os.path.join(root, filename)
               lines = [line.rstrip('\n').split(' ') for line in open(os.path.join(root, filename))]
               return lines
   print "No PEI symbols found"
   return None

def get_preefi_symbols(PreEfiSymbols):
   i = 0
   FilePaths = dict()

   while i < len(PreEfiSymbols):
      PathIndex = PreEfiSymbols[i].index('add')
      LocIndex = PreEfiSymbols[i+1].index('--slide')
      FilePaths[int(PreEfiSymbols[i+1][LocIndex + 1],16)] = PreEfiSymbols[i][PathIndex + 1]
      i += 2

   return FilePaths

def get_build_number(path, branch):
    path_parts = path.split('/')
    for path_part in path_parts:
       if branch in path_part:
          build_parts = path_part.split('_')
          return build_parts[-1]
    return None

def find_all_symbol_files(base_path, build_type):
   matches = []

   for root, dirnames, filenames in os.walk(base_path):
      if "dSYM" in root:
         continue
      if build_type not in root:
         continue
      for filename in fnmatch.filter(filenames, '*.macho'):
         matches.append(os.path.join(root, filename))

      for filename in fnmatch.filter(filenames, 'VectorJumpIsland.obj'):
         matches.append(os.path.join(root, filename))
   return matches

def find_workspace(FullPath):
   Path = FullPath.split('/')
   Found = False
   for i, val in enumerate(Path):
      if (val.lower() == "buildresults"):
         Found = True
         break

   if not Found:
      print "Could not find original workspace"
      sys.exit()


   return '/'.join(Path[:i])

def change_to_workspace(FullPath, Workspace):
   Path = FullPath.split('/')
   Found = False
   for i, val in enumerate(Path):
      if (val.lower() == "buildresults"):
         Found = True
         break
   if not Found:
      print ("Never found build results in Path %s" % FullPath)
      return None

   return Workspace + '/' + '/'.join(Path[i:])

def get_dxe_main_symbols(Addr):
   print "Getting dxemain from 0x%x" % Addr
   FileNameLoc = ReadDataStructureMember(EFI_HOB_MEMORY_ALLOCATION_MODULE_Dict, "FileName", Addr)
   FileName = read_string_from_mem(FileNameLoc)

   DxeCoreAddress = Addr + 24

   HexData = bytearray(read_memory_block(DxeCoreAddress, 8))

   DecData = "%s" %  ''.join('%02x ' % byte for byte in HexData)
   DecData = DecData.replace(" ", "")
   StrData = "".join(reversed([DecData[i:i+2] for i in range(0, len(DecData), 2)]))
   Location = int(StrData,16)

   print "DxeMain = %s, Loc - 0x%x" % (FileName, Location)
   return FileName, Location

def fixup_filepaths(FilePaths, Workspace):
   FoundWorkspace = None
   NotFoundLocations = []
   # If there is no workspace then just assume it.
   # Only support one workspace so only look at the first path
   if not Workspace:
      Path = FilePaths[FilePaths.keys()[0]]
      Path = Path.split('/');
      Found = False
      for i, val in enumerate(Path):
         if (val.lower() == "buildresults"): 
            Found = True
            break
      FoundWorkspace = '/'.join(Path[:i])
      if not Found or not os.path.isdir('/'.join(Path[:i+1])):
         print("Did not find any workspace")
         return None
      else:
         print "Workspace = ", FoundWorkspace

   else:
      FoundWorkspace = os.path.abspath(Workspace)

   for Location, Path in FilePaths.iteritems():

      NewPath = change_to_workspace(Path, FoundWorkspace)
      if not NewPath or not os.path.isfile(NewPath):
         NotFoundLocations = NotFoundLocations + [Location] 
      else:
         FilePaths[Location] = NewPath

   for Location in NotFoundLocations:
      print "Removing path", FilePaths[Location]
      del FilePaths[Location]

   return FoundWorkspace

def find_source_path():
   path = None
   process = classes.GTarget.GetProcess();
   if not process:
      print "No process"

   thread = process.GetThreadAtIndex(0)

   if not thread:
      print "No thread"

   for i in range(thread.GetNumFrames()):
      frame = thread.GetFrameAtIndex(i)

      if not frame:
         print "No frame", i
         continue


      context = frame.GetSymbolContext(lldb.eSymbolContextEverything)

      if not context:
         print "No context for frame", i
         continue

      lineentry = context.GetLineEntry()

      if not lineentry:
         print "No lineentry for frame", i
         continue

      filespec = str(lineentry.GetFileSpec())

      bootloader = filespec.find("bootloader") 
      diagnostics = filespec.find("diagnostics") 
      if bootloader > 0:
         path = filespec[:bootloader]
         break
      elif diagnostics > 0:
         path = filespec[:diagnostics]
         break

   print "Source path:", path
   return path

def load_file_paths(FilePaths, PlatformID, debugger):
   HistoryFileName = "/tmp/symbols-" + PlatformID + ".lldb"
   HistoryFile = open(HistoryFileName,'wb')
   print "Loading symbol files to LLDB"   
   RestorePathCmd = "cd " + os.getcwd()
   for Location, Path in FilePaths.iteritems():
      if os.path.isfile(Path): 
         Command = ('cd %s' % os.path.dirname(Path))
         classes.debug_print(Command)
         HistoryFile.write(Command+'\n')
         debugger.HandleCommand(Command)

         Command = ('target modules add %s' % os.path.basename(Path))
         classes.debug_print(Command)
         HistoryFile.write(Command+'\n')
         debugger.HandleCommand(Command)

         Command = ('target modules load --file %s --slide 0x%x' % (os.path.basename(Path), Location))
         classes.debug_print(Command)
         HistoryFile.write(Command+'\n')
         debugger.HandleCommand(Command)
      else:
         print "How does this file not exist?", Path

   HistoryFile.write(RestorePathCmd+'\n')
   debugger.HandleCommand(RestorePathCmd)
   HistoryFile.close()


def download_artifactory(output_zip_path, build_id):
   # This should throw ValueError if not found
   try:
      artifactory_user = os.environ['DIAGS_ARTIFACTORY_USER']
      artifactory_token = os.environ['DIAGS_ARTIFACTORY_TOKEN']
   except KeyError as e:
      print e.message, "environment variable missing"
      raise

   artifactory = ArtifactoryConnection('https://artifacts-hwte.apple.com',
                                       'LLD',
                                       artifactory_user,
                                       artifactory_token,
                                       False)

   matching_extras = artifactory.search_artifacts({'shasta.version': build_id,
                                                   'shasta.artifact_type': 'binary_extras'})
   if len(matching_extras) == 0:
      print "No artifacts found for", build_id, "on Artifactory"
      raise KeyError("build not found in Artifactory")

   print "Found symbols in Artifactory"
   with open(output_zip_path, 'wb') as output_zip:
      # Just download the first match
      output_zip.write(matching_extras.items()[0][1].read())


def load_symbols_command(debugger, command, result, unused):
   command_args = shlex.split(command)
   parser = create_load_symbols_options()
   try:
      (options, args) = parser.parse_args(command_args)
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   if options.history:
      FileName = "/tmp/symbols-" + options.history + ".lldb"
      if os.path.isfile(FileName):
         LoadCommand = ('command source --stop-on-error false %s' % (FileName))
         debugger.HandleCommand(LoadCommand)
      else:
         print "Symbols file does not exist"
         sys.exit()
      return

   if options.workspace and (not os.path.isdir(options.workspace) or not os.path.isdir(options.workspace + '/BuildResults')):
      result.PutCString ("bad workspace or missing build results!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   BaseAddr = classes.init_command(debugger)

   MemoryHobAddr = classes.get_hob_addrs_by_type(BaseAddr, "EFI_HOB_MEMORY_ALLOCATION_MODULE")[0]
   classes.debug_print("MemoryHobAddr: 0x%x" % MemoryHobAddr)
   DxeMainFile, DxeMainLoc = get_dxe_main_symbols(MemoryHobAddr)
   OrigWorkspace = find_workspace(DxeMainFile)

   Type = "release" if "release" in DxeMainFile else "debug"

   (PlatformID, BuildType, _, DiagsBuildBranch, DiagsBuildID, _, _) = classes.get_build_info(BaseAddr)

   FilePaths = dict()

   if options.workspace: 
      DxeMainFile = change_to_workspace(DxeMainFile, options.workspace)

   if DxeMainFile:
      FilePaths[DxeMainLoc] = DxeMainFile;

   if options.main:
      load_file_paths(FilePaths, PlatformID, debugger)
      return

   classes.debug_print("Getting HobList");
   BaseAddr = classes.get_hob_list(BaseAddr)
   if not BaseAddr:
      print "Cannot load symbols. Missing needed hob info"
      sys.exit()

   RemoteFilePaths = dict()
   gST = classes.get_system_table_location(BaseAddr)

   if None in (DiagsBuildBranch, PlatformID, DiagsBuildID, BuildType):
      print "Somehow the build info in the hob is messed up, trying to get it from another location."
      (PlatformID, BuildType, _, DiagsBuildBranch, DiagsBuildID, _, _) = classes.get_build_info(BaseAddr)

   print "Retrieving symbols from HOB"
   NumberOfTableEntries = ReadDataStructureMember(EFI_SYSTEM_TABLE_Dict, "NumberOfTableEntries", gST)
   ConfigurationTable = ReadDataStructureMember(EFI_SYSTEM_TABLE_Dict, "ConfigurationTable", gST)
   classes.debug_print("NumberOfTableEntries = %d, ConfigurationTable = 0x%x" % (NumberOfTableEntries, ConfigurationTable))
   DebugTablePtr = None

   # Find the debug table where the images and their locations are stored
   for i in range(NumberOfTableEntries):
      guid = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorGuid", ConfigurationTable)
      Ptr  = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorTable", ConfigurationTable)
      guidStr = GuidToStr(guid)

      if gDebugTableGUID == guidStr:
         DebugTablePtr = Ptr
         break;

      ConfigurationTable += GetDataStructureSize(EFI_CONFIGURATION_TABLE_Dict, classes.GTarget.addr_size)

   if DebugTablePtr is None:
      result.SetStatus (lldb.eReturnStatusFailed)
      return 

   DebugTableSize = ReadDataStructureMember(EFI_DEBUG_IMAGE_INFO_TABLE_HEADER_Dict, "TableSize", DebugTablePtr)
   ImageLocation = ReadDataStructureMember(EFI_DEBUG_IMAGE_INFO_TABLE_HEADER_Dict, "EfiDebugImageInfoTable", DebugTablePtr)
   classes.debug_print("Found DebugTableGUID = 0x%x, Size = 0x%x, ImageLocation = 0x%x" % (DebugTablePtr, DebugTableSize, ImageLocation))
   for j in range(DebugTableSize):
      NormalImageLocation = ReadDataStructureMember(EFI_DEBUG_IMAGE_INFO_Dict, "NormalImage", ImageLocation + j*classes.GTarget.addr_size)
      if NormalImageLocation  == 0: break;

      ImageProtocolLocation = ReadDataStructureMember(EFI_DEBUG_IMAGE_INFO_NORMAL_Dict, "LoadedImageProtocolInstance", NormalImageLocation)
      if ImageProtocolLocation == 0: break;
      classes.debug_print("ImageProtocolLocation = 0x%x" % (ImageProtocolLocation))

      (_, Offset, _) = ReadDataStructureArrayElement(EFI_LOADED_IMAGE_PROTOCOL_Dict, "ImageDebugInfo", ImageProtocolLocation, 0)
      classes.debug_print("ImageDebugInfo Offset = 0x%x" % (Offset))

      FilePathLocation = ReadDataStructureMember(EFI_APPLE_DEBUG_SUPPORT_Dict , "FilePath", ImageProtocolLocation + Offset)
      if FilePathLocation == 0: break;
      classes.debug_print("FilePathLocation = 0x%x" % (FilePathLocation))

      ImageBaseLocation = ReadDataStructureMember(EFI_LOADED_IMAGE_PROTOCOL_Dict, "ImageBase", ImageProtocolLocation)
      classes.debug_print("ImageBaseLocation = 0x%x" % (ImageBaseLocation))

      if ImageBaseLocation in FilePaths.keys(): print "What the heck? already loaded this image?"
      FilePaths[ImageBaseLocation] = read_string_from_mem(FilePathLocation)

      print("File Path Found:%s @ 0x%x" % (FilePaths[ImageBaseLocation], ImageBaseLocation))

   if len(FilePaths.keys()) == 0:
      print "Symbol files are not present in HOB"
      sys.exit()

   Workspace = fixup_filepaths(FilePaths, options.workspace)

   if Workspace is not None:
      PreEfiSymbols = find_preefi_symbols(Workspace,PlatformID,Type)
      if PreEfiSymbols is not None:
         PeiFilePaths = get_preefi_symbols(PreEfiSymbols)
         fixup_filepaths(PeiFilePaths, Workspace)
         FilePaths.update(PeiFilePaths)

      DxeMainFile = change_to_workspace(DxeMainFile, Workspace)
      if DxeMainFile:
         FilePaths[DxeMainLoc] = DxeMainFile
   else:
      if None in (DiagsBuildBranch, PlatformID, DiagsBuildID, BuildType):
         print "Somehow the build info in the hob is messed up still. Stopping."
         sys.exit()

      if BuildType == "CMKit":
          print ("CMKit builds are never on the build server. Please use the workspace option")
          sys.exit()

      DiagsBuildBranch = DiagsBuildBranch.lower()

      print("PlatformID: %s" % PlatformID)
      print("DiagsBuildID: %s" % DiagsBuildID)

      RemoteSymbols = []

      ZipPath = '/tmp/' + DiagsBuildID + '_extra.zip'
      SymbolsDLDir = '/tmp/' + DiagsBuildID + '_extra'

      if not os.path.isfile(ZipPath):
         try:
            download_artifactory(ZipPath, DiagsBuildID)
         except KeyError:
            print "Symbols not downloaded from Artifactory, falling back to Wendigo"
            # use wendigo to get the diags extras package
            Url = "https://wendigo.apple.com/panic_query.php?user=PanicUser22&passwd=998pu822&version=" + DiagsBuildID
            gcontext = ssl.SSLContext(ssl.PROTOCOL_TLSv1)

            print("Downloading %s" % Url)
            Url = urllib2.urlopen(Url, context=gcontext)
            ZipFile = Url.read()

            with open(ZipPath, 'wb') as SymbolsZipFd:
                SymbolsZipFd.write(ZipFile)

      print("Unpacking symbols zip: %s" % ZipPath)
      with zipfile.ZipFile(ZipPath, 'r') as zipped:
          zipped.extractall('/tmp/')

      RemoteSymbols += find_all_symbol_files(SymbolsDLDir, Type)

      PreEfiSymbols = find_preefi_symbols(SymbolsDLDir,PlatformID,Type)
      if PreEfiSymbols is not None:
         PeiFilePaths = get_preefi_symbols(PreEfiSymbols)
         FilePaths.update(PeiFilePaths)

      FilePaths[DxeMainLoc] = DxeMainFile

      for Location, LocalPath in FilePaths.iteritems():
         Found = False
         for RemoteSymbolFile in RemoteSymbols:
            # print "Checking", LocalPath, "vs", RemoteSymbolFile
            if os.path.basename(LocalPath) == os.path.basename(RemoteSymbolFile):
               Found = True
               RemoteFilePaths[Location] = RemoteSymbolFile
               break
         if not Found:
            print("No replacement found for: %s" % LocalPath)

      FilePaths = RemoteFilePaths

   load_file_paths(FilePaths, PlatformID, debugger)

   path = find_source_path()
   if path and Workspace and path.strip('/') != Workspace.strip('/'):
      print "Mapping sources"
      MapCommand = "settings set target.source-map " + path + " " + Workspace
      print MapCommand
      debugger.HandleCommand(MapCommand)
