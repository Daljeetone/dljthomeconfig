import sys
import optparse
import shlex
import classes
import os
import re
from DataStructureDict import *

gPanicLogSize = 0x20000;

def triage():
  usage = "usage: %prog"
  description='''Triage Script'''
  parser = optparse.OptionParser(description=description, prog='triage',usage=usage)
  return parser

def panic_frame_info(debugger, panicLogAddr=None):
    path = None
    found = False
    frame = None
    i = 0

    if not panicLogAddr:
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

            panic = filespec.find("Panic.c") 
            if panic > 0:
                found = True;
                break

        if not found:
            print "No panic frame found"
            return;

        print "Panic frame:", i

        Command = "frame select %d" % i
        print "Running:", Command
        debugger.HandleCommand(Command)

        _panicLogSBVal = frame.GetValueForVariablePath("_panicLogBuffer", False)
        panicLogAddr = _panicLogSBVal.GetValue()
        panicLogAddr = int(panicLogAddr, 16)

    if not panicLogAddr:
        print "No panic buffer found"
        return

    panicLog = read_string_from_mem(panicLogAddr, MaxLen=gPanicLogSize)

    print "Panic log (0x%x):" % panicLogAddr
    print panicLog
    if not panicLog:
        print "Panic log is empty"
        return

    i = 0
    while True:
        pattern = re.compile(("#%d\s+(0x[0-9a-fA-F]+)" % i))

        match = pattern.search(panicLog);
        if not match:
            print ("Did not find frame %d" % i)
            break

        panic_frame = match.group(1)
        print "Getting panic log frame %d info" % i

        Command = "image lookup -v --address %s" % panic_frame
        print "Running:", Command
        debugger.HandleCommand(Command)
        i = i + 1
     
    return

def triage_command(debugger, command, result, unused):

    global gPanicLogSize

    panicLogAddr = None;
    BaseAddr = classes.init_command(debugger)

    Command = "memory read --binary -c 0x100 0x%x" % BaseAddr
    print "Running:", Command
    debugger.HandleCommand(Command)

    BaseAddr = classes.get_hob_list(BaseAddr)

    for addr  in classes.get_hob_addrs_by_type(BaseAddr, "EFI_HOB_GUID_TYPE"):
        guid = ReadDataStructureMember(EFI_HOB_GUID_TYPE, "Guid", addr)
        guidStr = GuidToStr(guid)
        if guidStr == gPanicBufferGUID:
            panicLogAddr = ReadDataStructureMember(EFI_PANIC_BUFFER_Dict, "BufferAddr", addr)
            gPanicLogSize = ReadDataStructureMember(EFI_PANIC_BUFFER_Dict, "BufferSize", addr)
            #PrintDataStructure(debugger, result, "EFI_PANIC_BUFFER", addr)
            break


    Command = "build_info"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "hob -t stack"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "console --no-colors"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "ramlog --no-colors"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "symbols"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "bt"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "frame select 0"
    print "Running:", Command
    debugger.HandleCommand(Command)

    Command = "register read"
    print "Running:", Command
    debugger.HandleCommand(Command)

    panic_frame_info(debugger, panicLogAddr)

