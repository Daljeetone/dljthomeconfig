import optparse
import shlex
import classes
from DataStructureDict import *

def create_dump_config_table_options():
  usage = "usage: %prog [options]"
  description='''EFI System Table dump'''
  parser = optparse.OptionParser(description=description, prog='config_table',usage=usage)
  return parser

def dump_config_table_command(debugger, command, result, unused):
   
   BaseAddr = classes.init_command(debugger)

   gST = classes.get_system_table_location(BaseAddr)

   PrintDataStructure(debugger, result, "EFI_SYSTEM_TABLE", gST)
   NumberOfTableEntries = ReadDataStructureMember (EFI_SYSTEM_TABLE_Dict, "NumberOfTableEntries", gST)
   ConfigurationTable = ReadDataStructureMember (EFI_SYSTEM_TABLE_Dict, "ConfigurationTable", gST)
   result.PutCString("NumberOfTableEntries = %x" % NumberOfTableEntries)
   result.PutCString("ConfigurationTable = %x" % ConfigurationTable)
   for i in range(NumberOfTableEntries):
      guid = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorGuid", ConfigurationTable)
      Ptr  = ReadDataStructureMember (EFI_CONFIGURATION_TABLE_Dict, "VendorTable", ConfigurationTable)
      guidStr = GuidToStr(guid)

      result.PutCString("%s  VendorTable = 0x%08x" % (GuidToStr (guid), Ptr))

      ConfigurationTable += GetDataStructureSize (EFI_CONFIGURATION_TABLE_Dict, classes.GTarget.addr_size)

   return
