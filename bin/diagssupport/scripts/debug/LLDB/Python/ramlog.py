import optparse
import shlex
from DataStructureDict import *
import hob
from ctypes import *
import binascii
import classes
import console_aux
import sys

gNoColor = False

TAG_PKT_HDR_SIGNATURE = 0xabbd137a
COLOR_END = "\033[0m"

LOG_TYPE_PRINT = 0
LOG_TYPE_ERROR = 1
LOG_TYPE_WARNING = 2
LOG_TYPE_ASSERT = 3
LOG_TYPE_DEBUG = 4
LOG_TYPE_TRACE = 5

ATTRIBUTE_IS_DUMP_PACKET           =     (0x01)
ATTRIBUTE_EXCLUDE_FROM_FORMATTING  =     (0x02)
ATTRIBUTE_APPEND_NEWLINE           =     (0x04)
ATTRIBUTE_SOURCE_IS_LIBRARY        =     (0x08)
ATTRIBUTE_WAS_FILTERED             =     (0x10)

TagTypeStart = { LOG_TYPE_PRINT: "", LOG_TYPE_ERROR: "\033[1;31m", LOG_TYPE_WARNING: "\033[1;35m", LOG_TYPE_TRACE: "\033[1;36m", LOG_TYPE_DEBUG: "\033[1;33m", LOG_TYPE_ASSERT: "\033[1;37m"}
AddedMessage = { LOG_TYPE_PRINT: " ", LOG_TYPE_ERROR: " ERROR: ", LOG_TYPE_WARNING: " WARNING: ", LOG_TYPE_TRACE: " TRACE: ", LOG_TYPE_DEBUG: " ", LOG_TYPE_ASSERT: " ASSERT!! "}

def create_ramlog_options():
   usage = "usage: %prog [options]"
   description='''Dumps the ramlog to the screen'''
   parser = optparse.OptionParser(description=description, prog='ramlog', usage=usage)
   parser.add_option('-n', '--no-colors', action='store_true',  dest='nocolors', help="don't format the string with colors", default=False)
   return parser

def get_size(BufferSize, Head, Tail):
    if Tail >= Head:
        return Tail - Head
    else:
        return (BufferSize - Head) + Tail;

def get_contiguous(MaxDataSize, BufferSizeMask, Data, Head, Tail):
   if Tail < Head:
		return Data + ((Head + MaxDataSize) & BufferSizeMask)
   else: 
		return Data + Head

def ramlog_command(debugger, command, result, unused):
   global gNoColor

   # Use the Shell Lexer to properly parse up command options just like a
   # shell would
   command_args = shlex.split(command)
   parser = create_ramlog_options()
   try:
      (options, args) = parser.parse_args(command_args)
      if options.nocolors:
         gNoColor = True
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   BaseAddr = classes.init_command(debugger)

   BufferSize,BufferSizeMask,MaxDataSize,DataAddress,Head,Tail = console_aux.read_ramlog_metadata(BaseAddr,result,debugger)
   if DataAddress == 0:
       print "Ramlog not initialized"
       return
 
   BufferSize = get_size(BufferSize, Head, Tail)

   BufferAddress = get_contiguous(MaxDataSize, BufferSizeMask, DataAddress, Head, Tail)

   print "Reading 0x%x bytes from 0x%x" % (BufferSize, BufferAddress)

   traverse_buffer_on_device(BufferAddress, BufferSize)

def traverse_buffer_on_device(BufferStart, BytesToRead):
   PreviousTagTime = 0
   BytesRead = 0

   TextPktHdrSize = GetDataStructureSize(EFI_TEXT_PKT_HDR_Dict, classes.GTarget.addr_size)

   TextTagSize = GetDataStructureSize(EFI_TEXT_TAG_Dict, classes.GTarget.addr_size)
   classes.debug_print("TextPktHdrSize = 0x%x, TextTagSize = 0x%x" % (TextPktHdrSize, TextTagSize))

   CollectStr = ""

   while BytesRead < BytesToRead:
      TotalDataLen = ReadDataStructureMember(EFI_TEXT_PKT_HDR_Dict, "TotalDataLen", BufferStart)
      Magic = ReadDataStructureMember(EFI_TEXT_PKT_HDR_Dict, "Magic", BufferStart)
      classes.debug_print("BufferStart = 0x%x, TotalDataLen = 0x%x, Magic = 0x%x" % (BufferStart, TotalDataLen, Magic))
      if Magic != TAG_PKT_HDR_SIGNATURE:
         print "Bad magic!"
         return
      StrLen = ReadDataStructureMember(EFI_TEXT_PKT_HDR_Dict, "StrLen", BufferStart)
      Tag = BufferStart + TextPktHdrSize
      StrLoc = Tag + TextTagSize

      ModuleRefKey = ReadDataStructureMember(EFI_TEXT_TAG_Dict, "SourceRef", Tag)
      SpecialAttributes = ReadDataStructureMember(EFI_TEXT_TAG_Dict, "SpecialAttributes", Tag)
      ExcludeFromFormatting = ReadDataStructureMember(EFI_MODULE_INFO_Dict, "ExcludeFromFormatting", ModuleRefKey)

      BufferStart += TextPktHdrSize + TextTagSize + TotalDataLen
      BytesRead += TextPktHdrSize + TextTagSize + TotalDataLen

      Str = read_string_from_mem(Tag + TextTagSize)

      if (SpecialAttributes & ATTRIBUTE_APPEND_NEWLINE) != 0:
         Str += "\n"
    
      if (SpecialAttributes & ATTRIBUTE_EXCLUDE_FROM_FORMATTING) != 0:
          ExcludeFromFormatting = True

      if not ExcludeFromFormatting:
         CollectStr += Str

         if not Str[-1] in ['\n', '\r']:
            continue

         TimeStamp = ReadDataStructureMember(EFI_TEXT_TAG_Dict, "Timestamp", Tag)
         TagType = ReadDataStructureMember(EFI_TEXT_TAG_Dict, "Type", Tag)
         FuncNameStr = read_string_from_mem(ReadDataStructureMember(EFI_TEXT_TAG_Dict, "FunctionName", Tag))

         DeltaTime = TimeStamp - PreviousTagTime

         sys.stdout.write(TagTypeStart[LOG_TYPE_PRINT if gNoColor else TagType] + "[" + FuncNameStr + "]" + "<" + str(TimeStamp/1000000) + "." + str(TimeStamp%1000000) + "s (+" + str(DeltaTime/1000000) + "." + "%06d" %(DeltaTime%1000000) + ")>" + AddedMessage[TagType] + CollectStr + COLOR_END)
         PreviousTagTime = TimeStamp
         CollectStr = ""
      else:
         sys.stdout.write(Str)

   print CollectStr

