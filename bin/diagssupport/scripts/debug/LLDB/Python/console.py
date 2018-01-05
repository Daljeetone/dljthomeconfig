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

TEXTPKT_SIGNATURE = 0xaabe7312
COLOR_END = "\033[0m"

LOG_TYPE_PRINT = 0
LOG_TYPE_ERROR = 1
LOG_TYPE_WARNING = 2
LOG_TYPE_ASSERT = 3
LOG_TYPE_DEBUG = 4
LOG_TYPE_TRACE = 5

gConsoleRouterBufferSize = 0
gConsoleRouterDataAddress = 0

TagTypeStart = { LOG_TYPE_PRINT: "", LOG_TYPE_ERROR: "\033[1;31m", LOG_TYPE_WARNING: "\033[1;35m", LOG_TYPE_TRACE: "\033[1;36m", LOG_TYPE_DEBUG: "\033[1;33m", LOG_TYPE_ASSERT: "\033[1;37m"}
AddedMessage = { LOG_TYPE_PRINT: " ", LOG_TYPE_ERROR: " ERROR: ", LOG_TYPE_WARNING: " WARNING: ", LOG_TYPE_TRACE: " TRACE: ", LOG_TYPE_DEBUG: " ", LOG_TYPE_ASSERT: " ASSERT!! "}

def create_console_options():
   usage = "usage: %prog [options]"
   description='''Dumps the console to the screen'''
   parser = optparse.OptionParser(description=description, prog='console', usage=usage)
   parser.add_option('-n', '--no-colors', action='store_true',  dest='nocolors', help="don't format the string with colors", default=False)
   return parser

def console_command(debugger, command, result, unused):
   global gNoColor
   global gConsoleRouterBufferSize
   global gConsoleRouterDataAddress

   # Use the Shell Lexer to properly parse up command options just like a
   # shell would
   command_args = shlex.split(command)
   parser = create_console_options()
   try:
      (options, args) = parser.parse_args(command_args)
      if options.nocolors:
         gNoColor = True
   except:
      result.PutCString ("bad arguments!")
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   BaseAddr = classes.init_command(debugger)

   gConsoleRouterBufferSize,gConsoleRouterDataAddress,Head,Tail,FreeSpace = console_aux.read_console_metadata(BaseAddr,result,debugger)

   if Tail < Head:
      BytesToRead = gConsoleRouterBufferSize - FreeSpace
   else:
      BytesToRead = Tail

   traverse_buffer_on_device(gConsoleRouterDataAddress + Head, BytesToRead)
         
def read_text_pkt_member(TextPkt, Member):
    (Address, Offset, Size) = GetDataStaructureArrayAddress(EFI_TEXT_PKT_TAG_Dict, Member, 0)
    return console_aux.conversion(TextPkt[Offset:Offset+Size])

def get_whole_text_pkt(CurrentAddr):
   TextPktSize = GetDataStructureSize(EFI_TEXT_PKT_TAG_Dict, classes.GTarget.addr_size)
   classes.debug_print("TextPktSize = 0x%x" % (TextPktSize))
   ReadFromAddress = CurrentAddr
   BytesRemaining = TextPktSize

   # Have to do this twice. Once for the TextPkt another for the string
   if ReadFromAddress + BytesRemaining >= gConsoleRouterDataAddress + gConsoleRouterBufferSize:
      BytesToRead = (gConsoleRouterDataAddress+gConsoleRouterBufferSize) - ReadFromAddress
      classes.debug_print("ReadFromAddress = 0x%x, BytesToRead = 0x%x" % (ReadFromAddress, BytesToRead))
      Buffer = read_memory_block(ReadFromAddress, BytesToRead)

      BytesToRead = BytesRemaining - BytesToRead
      classes.debug_print("gConsoleRouterDataAddress = 0x%x, BytesToRead = 0x%x" % (gConsoleRouterDataAddress, BytesToRead))
      Buffer += read_memory_block(gConsoleRouterDataAddress, BytesToRead)

      ReadFromAddress = gConsoleRouterDataAddress + BytesToRead
   else:
      classes.debug_print("ReadFromAddress = 0x%x, BytesRemaining = 0x%x" % (ReadFromAddress, BytesRemaining))
      Buffer = read_memory_block(ReadFromAddress, BytesRemaining)
      ReadFromAddress = ReadFromAddress + BytesRemaining

   (Address, Offset, Size) = GetDataStaructureArrayAddress(EFI_TEXT_PKT_TAG_Dict, "StrBytes", 0)
   StrBytes = console_aux.conversion(Buffer[Offset:Offset+Size])
   classes.debug_print("StrBytes = 0x%x, Offset = 0x%x, Size = 0x%x" % (StrBytes, Offset, Size))

   BytesRemaining = StrBytes + classes.GTarget.addr_size - 1
   classes.debug_print("BytesRemaining = 0x%x, read = 0x%x" % (BytesRemaining, len(Buffer)))

   if ReadFromAddress + BytesRemaining >= gConsoleRouterDataAddress + gConsoleRouterBufferSize:
      BytesToRead = (gConsoleRouterDataAddress+gConsoleRouterBufferSize) - ReadFromAddress
      classes.debug_print("ReadFromAddress2 = 0x%x, BytesToRead = 0x%x" % (ReadFromAddress, BytesToRead))
      Buffer += read_memory_block(ReadFromAddress, BytesToRead)

      BytesToRead = BytesRemaining - BytesToRead
      classes.debug_print("gConsoleRouterDataAddress2 = 0x%x, BytesToRead = 0x%x" % (gConsoleRouterDataAddress, BytesToRead))
      Buffer += read_memory_block(gConsoleRouterDataAddress, BytesToRead)

      ReadFromAddress = gConsoleRouterDataAddress + BytesToRead
   else:
      classes.debug_print("ReadFromAddress2 = 0x%x, BytesRemaining = 0x%x" % (ReadFromAddress, BytesRemaining))
      Buffer += read_memory_block(ReadFromAddress, BytesRemaining)
      ReadFromAddress = ReadFromAddress + BytesRemaining

   return Buffer, len(Buffer), ReadFromAddress
    
      
def traverse_buffer_on_device(BufferStart, BytesToRead):
   PreviousTagTime = 0
   BytesRead = 0

   _, TextStartOffset, _ =  GetDataStaructureArrayAddress(EFI_TEXT_PKT_TAG_Dict, "Str", 0)

   CollectStr = ""

   while BytesRead < BytesToRead:
      classes.debug_print("BytesRead = 0x%x" % (BytesRead))
      (TextPkt, TextPktSize, BufferStart) = get_whole_text_pkt(BufferStart)
      classes.debug_print("TextPktSize = 0x%x, BufferStart = 0x%x" % (TextPktSize, BufferStart))
      BytesRead += TextPktSize
      Sig = read_text_pkt_member(TextPkt, "Signature")
      if Sig != TEXTPKT_SIGNATURE:
          print "bad signature!"
          break
      Size = read_text_pkt_member(TextPkt, "StrBytes")
      ModuleRefKey = read_text_pkt_member(TextPkt, "Tag.ModuleRefKey")
      ExcludeFromFormatting = ReadDataStructureMember(EFI_MODULE_INFO_Dict, "ExcludeFromFormatting", ModuleRefKey)

      ConsoleStr = TextPkt[TextStartOffset:TextStartOffset+Size]
      if ExcludeFromFormatting == 0:
         CollectStr += ConsoleStr
         if not ConsoleStr[-2] in ['\n', '\r']:
            continue
         TimeStamp = read_text_pkt_member(TextPkt, "Tag.Timestamp")
         TagType = read_text_pkt_member(TextPkt, "Tag.Type")
         FuncNameStr = read_string_from_mem(read_text_pkt_member(TextPkt, "Tag.FunctionName"))
         DeltaTime = TimeStamp - PreviousTagTime
         sys.stdout.write(TagTypeStart[LOG_TYPE_PRINT if gNoColor else TagType] + "[" + FuncNameStr + "]" + "<" + str(TimeStamp/1000000) + "." + str(TimeStamp%1000000) + "s (+" + str(DeltaTime/1000000) + "." + "%06d" %(DeltaTime%1000000) + ")>" + AddedMessage[TagType] + CollectStr + COLOR_END)
         PreviousTagTime = TimeStamp
         CollectStr = ""
      else:
         sys.stdout.write(ConsoleStr)

   print CollectStr 

