from __future__ import print_function
import optparse
import shlex
import hob
import sys
from DataStructureDict import *
try:
    import __builtin__ as builtins # Python 2
except ImportError:
    import builtins # Python 3

global GTarget 
global GError
global SystemTableLoc 
global HobListPtr
global GDebugger

GTarget = 0
GError = 0
SystemTableLoc = 0
PeiHobLoc = None
HobListPtr = 0

GDebug = False

def debug_print(*args, **kwargs):
   if GDebug:
      builtins.print("DEBUG:", *args, **kwargs)

def get_hob_list(HobAddr):

   global HobListPtr
   gST = get_system_table_location(HobAddr)

   if HobListPtr != 0:
      return HobListPtr

   if not gST:
      print("Cannot get config table list because the gST is not present")
      return None

   NumberOfTableEntries = ReadDataStructureMember (EFI_SYSTEM_TABLE_Dict, "NumberOfTableEntries", gST)
   classes.debug_print("NumberOfTableEntries 0x%x" % NumberOfTableEntries)
   ConfigurationTable = ReadDataStructureMember (EFI_SYSTEM_TABLE_Dict, "ConfigurationTable", gST)
   classes.debug_print("ConfigurationTable 0x%x" % ConfigurationTable)
   for i in range(NumberOfTableEntries):
      guid = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorGuid", ConfigurationTable)
      Ptr  = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorTable", ConfigurationTable)
      guidStr = GuidToStr(guid)
      if guidStr == gHobListGUID :
         HobListPtr = Ptr
         return Ptr

      ConfigurationTable += GetDataStructureSize (EFI_CONFIGURATION_TABLE_Dict, GTarget.addr_size)

   return None

def get_hob_addrs_by_type(HobAddr, Type):
   ret = []
   HobType = 1
   while True:
      HobLength = ReadDataStructureMember(EFI_HOB_GENERIC_HEADER_Dict, "HobLength", HobAddr)
      HobType = ReadDataStructureMember(EFI_HOB_GENERIC_HEADER_Dict, "HobType", HobAddr)
      if ((HobType in HobDict.keys()) == False):
         print("Did not find hob table at 0x%x." % HobAddr)
         return None
      if Type == HobDict[HobType]:
         ret.append(HobAddr)
      HobAddr += HobLength
      if HobDict[HobType] == "EFI_HOB_END_OF_HOB_LIST":
         break

   return ret

def find_correct_hob_location(HobAddrs):
   if not isinstance(HobAddrs, tuple):
       print("Invalid parameter to find_correct_hob_location");
       sys.exit()

   for Addr in HobAddrs:
      addrs = get_hob_addrs_by_type(Addr, "EFI_HOB_END_OF_HOB_LIST")
      if addrs is None or len(addrs) != 1:
         continue
      classes.debug_print("EFI_HOB_SYSTEM_TABLE 0x%x" % addrs[0])
      if len(addrs) == 1:
         break

   if addrs is None or len(addrs) != 1:
      return None

   PeiHobLoc = Addr;

   return Addr;

def get_build_info(BaseAddr):
   BuildInfo = []

   addrs = get_hob_addrs_by_type(BaseAddr, "EFI_HOB_BUILD_ID")
   
   if len(addrs) != 1:
      return (None, None, None, None, None, None, None)

   addr = addrs[0]

   PlatformIDLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "PlatformIDLocation", addr)
   PlatformID = read_string_from_mem(PlatformIDLoc)
   BuildInfo.append(PlatformID)

   BuildTypeLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "BuildTypeLocation", addr)
   BuildType = read_string_from_mem(BuildTypeLoc)
   BuildInfo.append(BuildType)

   BuildTrainLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "BuildTrainLocation", addr)
   BuildTrain = read_string_from_mem(BuildTrainLoc)
   BuildInfo.append(BuildTrain)

   DiagsBuildBranchLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "DiagsBuildBranchLocation", addr)
   DiagsBuildBranch = read_string_from_mem(DiagsBuildBranchLoc)
   BuildInfo.append(DiagsBuildBranch)

   DiagsBuildIDLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "DiagsBuildIDLocation", addr)
   DiagsBuildID = read_string_from_mem(DiagsBuildIDLoc)
   BuildInfo.append(DiagsBuildID)

   BuildNumberLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "BuildNumberLocation", addr)
   BuildNumber = read_string_from_mem(BuildNumberLoc)
   BuildInfo.append(BuildNumber)

   BuildSrcRevLocLoc = ReadDataStructureMember(EFI_HOB_BUILD_ID_Dict , "BuildSrcRevLocation", addr)
   BuildSrcRev = read_string_from_mem(BuildSrcRevLocLoc)
   BuildInfo.append(BuildSrcRev)
   # clear the potential error reading the srcrev because it was added after the other fields
   classes.GError.Clear();

   return (PlatformID, BuildType, BuildTrain, DiagsBuildBranch, DiagsBuildID, BuildNumber, BuildSrcRev)

def get_system_table_location(HobAddr):
   global SystemTableLoc
   if SystemTableLoc != 0:
      return SystemTableLoc

   addrs = get_hob_addrs_by_type(HobAddr, "EFI_HOB_SYSTEM_TABLE")
   classes.debug_print("EFI_HOB_SYSTEM_TABLE 0x%x" % addrs[0])

   if len(addrs) != 1:
      return None
   addr = addrs[0]

   MemoryBase = ReadDataStructureMember(EFI_HOB_HANDOFF_INFO_TABLE_Dict, "EfiMemoryBottom", HobAddr)
   MemoryEnd = ReadDataStructureMember(EFI_HOB_HANDOFF_INFO_TABLE_Dict, "EfiFreeMemoryTop", HobAddr)

   Location = ReadDataStructureMember(EFI_HOB_SYSTEM_TABLE_Dict, "TableLocation", addr)
   classes.debug_print("TableLocation 0x%x" % Location)

   if (Location >= MemoryEnd or Location < MemoryBase):
      print("System table location is either corrupt or not present. Perhaps dxe main has not finshed loading. Supposed location: 0x%x" % Location)
      return 0

   SystemTableLoc = Location
   return Location

def get_pei_hob_addrs():
   #HOB at the start of memory
   if GTarget.addr_size == 8:
      BaseAddrs = (0x800000000, 0x808006000, 0x810006000)
   else:
      BaseAddrs = (0x80000000, 0x88003000, 0x84003000, 0x80010000)

   for Addr in BaseAddrs:
      classes.debug_print("BaseAddr 0x%x" % Addr)

   return BaseAddrs

def init_command(debugger):
   global PeiHobLoc
   global GTarget
   global GError
   global GDebugger

   SBError = lldb.SBError()

   SBTarget  = debugger.GetTargetAtIndex(0)

   GTarget = SBTarget
   GError = SBError
   GDebugger = debugger


   BaseAddrs = get_pei_hob_addrs()

   ValidBaseAddrs = []
   for Addr in BaseAddrs:
       GTarget.process.ReadMemory(Addr, 1, GError)
       if GError.Success():
           ValidBaseAddrs += [Addr]
       else:
           #Could not read memory from this address. Possibly not mapped
           GError.Clear()

   if (len(ValidBaseAddrs) < 1) :
       print ("Could not read any possible Hob Addresses")
       sys.exit()

   ValidBaseAddrs = tuple(ValidBaseAddrs)
   if not PeiHobLoc:
      PeiHobLoc = find_correct_hob_location(ValidBaseAddrs);
      if not PeiHobLoc:
         print("Possibly not in EFI. Please verify the currently running system.\n");
         sys.exit()

   return PeiHobLoc;
