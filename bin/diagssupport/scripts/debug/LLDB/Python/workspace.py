import optparse
import lldb
import os
import shlex
import classes
import symbols

def create_workspace_options():
  usage = "usage: %prog <path>"
  description= '''Update source location. Way simpler than:                                
              settings set target.source-map <initial_path> <actual_path>'''
  parser = optparse.OptionParser(description=description, prog='workspace',usage=usage)
  return parser

def workspace_command(debugger, command, result, unused):
   """workspace <path>"""
 
   # Use the Shell Lexer to properly parse up command options just like a
   # shell would
   command_args = shlex.split(command)

   parser = create_workspace_options()
   try:
      (options, args) = parser.parse_args(command_args)
   except:
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   if len(command_args) != 1:
       print "invalid command"
       print workspace_command.__doc__ 
       return

   if not os.path.isdir(command_args[0]):
       print "Invalid path", command_args[0]
       return

   _ = classes.init_command(debugger)

   SourcePath = os.path.abspath(command_args[0])
   SymbolSourcePath = symbols.find_source_path()

   print "Mapping sources"
   MapCommand = "settings set target.source-map " + SymbolSourcePath + " " + SourcePath
   print MapCommand
   debugger.HandleCommand(MapCommand)

