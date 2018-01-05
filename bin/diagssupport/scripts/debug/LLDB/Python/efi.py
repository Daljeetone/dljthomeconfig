#!/usr/bin/python -u

import platform
import commands
import os
import inspect
import sys
from subprocess import Popen, PIPE, STDOUT
import lldb
import optparse
import shlex
import subprocess
import binascii
import struct
import textwrap
import uuid
import time
import string
import struct
import sbvalue
import glob
import inspect
import getpass
import urllib2
import datetime
import hob
import symbols
import workspace
import console
import ramlog
import classes
import build_info
import config_table
import triage
import preefi
import deadloop_step
import debug 
import paniclog

# EFI LLDB Script imports
# Makes GuidNameDict.py and DataStructureDict.py act like there were in this file
try:
  from GuidNameDict      import *
except:
  GuidNameDict = {}  

from DataStructureDict import *

#
# optionally import other files 
#
try:
  import BuildSpecific
  BuildSpecificImported = True
except:
  BuildSpecificImported = False

try:
  import UserSpecific
  UserSpecificImported = True
except:
  UserSpecificImported = False

def load_scripts(debugger):
   curr_path = inspect.getfile(inspect.currentframe())
   for root, dirs, files in os.walk(os.path.dirname(curr_path)):
    for file in files:
        if file.endswith(".py"):
            if file == "efi.py":
               continue
            else:
               debugger.HandleCommand('command script import %s' % os.path.join(root, file))

def load_os(debugger):
    debugger.HandleCommand('command script import os')
    debugger.HandleCommand('command alias pwd script print os.getcwd()')
    debugger.HandleCommand('command regex cd "s/^(.*)$/script os.chdir(os.path.expanduser(\'%1\'))/"')

def TypePrintFormating(debugger):
   #
   # Set the default print formating for EFI types in lldb. 
   # seems lldb defaults to decimal.
   #
   category = debugger.GetDefaultCategory()
   FormatBool = lldb.SBTypeFormat(lldb.eFormatBoolean)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("BOOLEAN"), FormatBool)

   FormatHex  = lldb.SBTypeFormat(lldb.eFormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("UINT64"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("INT64"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("UINT32"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("INT32"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("UINT16"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("INT16"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("UINT8"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("INT8"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("UINTN"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("INTN"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("CHAR8"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("CHAR16"), FormatHex)

   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_PHYSICAL_ADDRESS"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_STATUS"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_TPL"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_LBA"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_BOOT_MODE"), FormatHex)
   category.AddTypeFormat(lldb.SBTypeNameSpecifier("EFI_FV_FILETYPE"), FormatHex)

   #
   # Smart type printing for EFI
   #
   '''debugger.HandleCommand("type summary add EFI_GUID --python-function efi.EFI_GUID_TypeSummary")
   debugger.HandleCommand("type summary add EFI_STATUS --python-function efi.EFI_STATUS_TypeSummary")
   debugger.HandleCommand("type summary add EFI_TPL --python-function efi.EFI_TPL_TypeSummary")
   debugger.HandleCommand("type summary add EFI_DEVICE_PATH_PROTOCOL --python-function efi.EFI_DEVICE_PATH_PROTOCOL_TypeSummary")
   debugger.HandleCommand("type summary add EFI_BOOT_MODE --python-function efi.EFI_BOOT_MODE_TypeSummary")
   debugger.HandleCommand("type summary add EFI_FV_FILETYPE --python-function efi.EFI_FV_FILETYPE_TypeSummary")

   debugger.HandleCommand("type summary add CHAR16 --python-function efi.CHAR16_TypeSummary")
   debugger.HandleCommand('type summary add --regex "CHAR16 \[[0-9]+\]" --python-function efi.CHAR16_TypeSummary')
   debugger.HandleCommand("type summary add CHAR8 --python-function efi.CHAR8_TypeSummary")
   debugger.HandleCommand('type summary add --regex "CHAR8 \[[0-9]+\]" --python-function efi.CHAR8_TypeSummary')'''

   # useful macros for EFI
   # (lldb) offsetof MEMORY_MAP Start
   # Get offset of Start member of the structure MEMORY_MAP
   # command alais print __builtin_offsetof(%1,%2) DOES NOT WORK. This is the only way
   debugger.HandleCommand("command regex offsetof 's/([a-zA-Z_][a-zA-Z0-9_]*) +([a-zA-Z_][a-zA-Z0-9_]*)/print __builtin_offsetof(%1,%2)/'")

#
########## Code that runs when this script is imported into LLDB ###########
#
def __lldb_init_module (debugger, internal_dict):
   # This initializer is being run from LLDB in the embedded command interpreter
   # Make the options so we can generate the help text for the new LLDB
   # command line command prior to registering it with LLDB below
 

   TypePrintFormating (debugger)
   debugger.HandleCommand('setting set frame-format "frame #${frame.index}: ${frame.pc}{ ${module.file.basename}{:${function.name}()${function.pc-offset}}}{ at ${line.file.fullpath}:${line.number}}\n"')
 
   print """For lldb documentation see http://lldb.llvm.org/lldb-gdb.html or
 <http://devpubsu.apple.com/Archive/> for LLDB Spotlight On sessions.
 For help on an lldb command type "help COMMAND" or "COMMAND --help."""
   CommandList = []

   load_scripts(debugger)
   load_os(debugger)
 
   # add hob
   parser = hob.create_hob_options()
   hob.hob_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f hob.hob_command hob')
   CommandList.append("hob")

   #add build_info
   parser = build_info.create_build_info_options()
   build_info.build_info_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f build_info.build_info_command build_info')
   CommandList.append("build_info")

   #add config_table
   parser = config_table.create_dump_config_table_options()
   config_table.dump_config_table_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f config_table.dump_config_table_command config_table')
   CommandList.append("config_table")

   #add symbols
   parser = symbols.create_load_symbols_options()
   symbols.load_symbols_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f symbols.load_symbols_command symbols')
   CommandList.append("symbols")

   #add workspace
   parser = workspace.create_workspace_options()
   workspace.workspace_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f workspace.workspace_command workspace')
   CommandList.append("workspace")

   #add console
   parser = console.create_console_options()
   console.console_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f console.console_command console')
   CommandList.append("console")

   #add ramlog
   parser = ramlog.create_ramlog_options()
   ramlog.ramlog_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f ramlog.ramlog_command ramlog')
   CommandList.append("ramlog")

   parser = triage.triage()
   triage.triage_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f triage.triage_command triage')
   CommandList.append("triage")

   parser = preefi.load_preefi()
   preefi.load_preefi_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f preefi.load_preefi_command loadpei')
   CommandList.append("loadpei")

   parser = deadloop_step.dead_step()
   deadloop_step.deadloop_step_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f deadloop_step.deadloop_step_command deadloop_step')
   CommandList.append("deadloop_step")

   parser = debug.debug_usage()
   debug.debug_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f debug.debug_command debug')
   CommandList.append("debug")

   parser = paniclog.paniclog_usage()
   debug.debug_command.__doc__ = parser.format_help()
   # Add any commands contained in this module to LLDB
   debugger.HandleCommand('command script add -f paniclog.paniclog_command paniclog')
   CommandList.append("paniclog")
 
   # Turn off you will kill the process if you exit prompt. 
   debugger.HandleCommand('settings set auto-confirm true')
 
   # print command list as string with 80 column word wrap
   CommandStr = "EFI lldb commands: " + ", ".join(CommandList)
   print textwrap.fill(CommandStr, initial_indent='', subsequent_indent='  ')
 
   #
   # Init optional files, if they exist
   #
   if BuildSpecificImported:
      BuildSpecific.__lldb_init_module (debugger, internal_dict)
 
   if UserSpecificImported:
      UserSpecific.__lldb_init_module (debugger, internal_dict)
 
   Target = debugger.GetTargetAtIndex(0)

   if Target:
      Breakpoint = Target.BreakpointCreateByName('SecGdbScriptBreak')  

if __name__ == '__main__':
   # Create a new debugger instance in your module if your module 
   # can be run from the command line. When we run a script from
   # the command line, we won't have any debugger object in
   # lldb.debugger, so we can just create it if it will be needed  
   lldb.debugger = lldb.SBDebugger.Create()
   lldb.debugger.SetAsync (False)

