import sys
import optparse
import shlex
import classes
import os
import re
from DataStructureDict import *

def paniclog_usage():
  usage = "usage: %prog"
  description='''paniclog Script'''
  parser = optparse.OptionParser(description=description, prog='paniclog',usage=usage)
  return parser

def paniclog_command(debugger, command, result, unused):

    panicLogAddr = None;
    baseAddr = classes.init_command(debugger)
    baseAddr = classes.get_hob_list(baseAddr)

    for addr  in classes.get_hob_addrs_by_type(baseAddr, "EFI_HOB_GUID_TYPE"):
        guid = ReadDataStructureMember(EFI_HOB_GUID_TYPE, "Guid", addr)
        guidStr = GuidToStr(guid)
        if guidStr == gPanicBufferGUID:
            panicLogAddr = ReadDataStructureMember(EFI_PANIC_BUFFER_Dict, "BufferAddr", addr)
            panicLogSize = ReadDataStructureMember(EFI_PANIC_BUFFER_Dict, "BufferSize", addr)
            #PrintDataStructure(debugger, result, "EFI_PANIC_BUFFER", addr)
            break

    if not panicLogAddr:
        print "no panic log found"
        return

    panicLog = read_string_from_mem(panicLogAddr, MaxLen=panicLogSize)

    print "Panic log (0x%x):" % panicLogAddr
    print panicLog
