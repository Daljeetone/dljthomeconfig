import sys
import optparse
import shlex
import classes
from DataStructureDict import *

def create_build_info_options():
  usage = "usage: %prog"
  description='''Build Information'''
  parser = optparse.OptionParser(description=description, prog='build_info',usage=usage)
  return parser

def build_info_command(debugger, command, result, unused):
   classes.init_command(debugger)

   (PlatformID, BuildType, BuildTrain, DiagsBuildBranch, DiagsBuildID, BuildNumber, SrcRev) = classes.get_build_info(classes.init_command(debugger))
   result.PutCString("PlatformID: %s" % PlatformID)
   result.PutCString("BuildType: %s" % BuildType)
   result.PutCString("BuildTrain: %s" % BuildTrain)
   result.PutCString("DiagsBuildBranch: %s" % DiagsBuildBranch)
   result.PutCString("DiagsBuildID: %s" % DiagsBuildID)
   result.PutCString("BuildNumber: %s" % BuildNumber)
   result.PutCString("SrcRevision: %s" % SrcRev)
