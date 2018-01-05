import optparse
import shlex
import classes
import lldb

def debug_usage():
  usage = "usage: %prog [on|off]"
  description='''Turns on debugging of lldb scripts'''
  parser = optparse.OptionParser(description=description, prog='debug',usage=usage)
  parser.add_option('--on', action='store_true',  dest='on', help="turn on debugging", default=False)
  parser.add_option('--off', action='store_true',  dest='off', help="turn off debugging", default=False)
  return parser


def debug_command(debugger, command, result, unused):
   
   command_args = shlex.split(command)
   parser = debug_usage()
   try:
      (options, args) = parser.parse_args(command_args)
      if options.on == options.off:
         result.PutCString ("bad arguments!")
         result.SetStatus (lldb.eReturnStatusFailed)
         return
      classes.GDebug = options.on
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return
