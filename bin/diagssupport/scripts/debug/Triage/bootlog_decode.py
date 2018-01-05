import struct
from collections import namedtuple
import sys

if (len(sys.argv) != 2):
    print "usage: python %s <filename>" % sys.argv[0]
    sys.exit()

TEXTPKT_SIGNATURE = 0xaabe7312
COLOR_END = "\033[0m"

LOG_TYPE_PRINT = 0
LOG_TYPE_ERROR = 1
LOG_TYPE_WARNING = 2
LOG_TYPE_ASSERT = 3
LOG_TYPE_DEBUG = 4
LOG_TYPE_TRACE = 5

TagTypeStart = { LOG_TYPE_PRINT: "", LOG_TYPE_ERROR: "\033[1;31m", LOG_TYPE_WARNING: "\033[1;35m", LOG_TYPE_TRACE: "\033[1;36m", LOG_TYPE_DEBUG: "\033[1;33m", LOG_TYPE_ASSERT: "\033[1;37m"}
AddedMessage = { LOG_TYPE_PRINT: " ", LOG_TYPE_ERROR: " ERROR: ", LOG_TYPE_WARNING: " WARNING: ", LOG_TYPE_TRACE: " TRACE: ", LOG_TYPE_DEBUG: " ", LOG_TYPE_ASSERT: " ASSERT!! "}

def _DumpPkt(Pkt):
    print("PKT:");
    print("\tSignature : 0x%x" % Pkt.Signature)
    print("\tFunctionName : 0x%x" % Pkt.FunctionName)
    print("\tLogType : 0x%x" % Pkt.LogType)
    print("\tMaskValue : 0x%x" % Pkt.MaskValue)
    print("\tModuleRefKey : 0x%x" % Pkt.ModuleRefKey)
    print("\tTimestamp : 0x%x" % Pkt.Timestamp)
    print("\tAppendNewLine : 0x%x" % Pkt.AppendNewLine)
    print("\tStrBytes : 0x%x" % Pkt.StrBytes)

def _DumpHex(buf):
    for i in range(len(buf)):
        if (i % 8 == 0):
            if (i): print("")
            sys.stdout.write("0x%04x: " % i)
        sys.stdout.write("%02x " % ord(buf[i]))
    print("")

def _CheckData(Data):
    if len(Data) == 0:
        print "No more Data"
        sys.exit()

with open(sys.argv[1], 'rb') as f:
    Data = f.read()

FileInfo_T = namedtuple('FileInfo', 'Offset Version WordSize', verbose=False)
FileInfoString = "<QLB"
FileInfoSize = struct.calcsize(FileInfoString)
FileInfo = FileInfo_T._make(struct.unpack(FileInfoString, Data[:FileInfoSize]))

Data = Data[FileInfoSize:FileInfo.Offset]
#                            FileName(0x8, 0x8)
#                           / FunctionName(0xC, 0x10)
#                          | / LineNo(0x10, 0x18)
#                          || / Type(0x14, 0x20)
#                          ||| / MaskValue(0x18, 0x24)
#                          |||| / ModuleRefKey(0x1C, 0x28)
#                          ||||| / Timestamp(0x20, 0x30)
#                       Sig|||||| / AppendNewLine(0x28, 0x38)
#                      /   ||||||| /        StrBytes(0x30, 0x40)
#                     |    ||||||||        /
#                     0    ||||||||       |
SmallStructString = "<LxxxxLLLLLLQBxxxxxxxLxxxx";
LargeStructString = "<LxxxxQQQLLQQBxxxxxxxQ";
SmallWordString = "L"
LargWordString = "Q"
TextPkt = namedtuple('TextPkt', 'Signature FileName FunctionName LineNo LogType MaskValue ModuleRefKey Timestamp AppendNewLine StrBytes', verbose=False)

if (FileInfo.WordSize == 8):
    StructString = LargeStructString
    WordString = LargWordString
else:
    StructString = SmallStructString
    WordString = SmallWordString

TextPktSize = struct.calcsize(StructString)

PreviousTagTime = 0
SawNewLine = False
LastSourceRef = 0
LastType = 0
LastMask = 0
while (len(Data) != 0):
    PrintImplicitNewline = True
    PrintFormatting = True
    #Get the TextPkt structure
    Pkt = TextPkt._make(struct.unpack(StructString, Data[:TextPktSize]))
    if (Pkt.Signature != TEXTPKT_SIGNATURE):
        print "TextPkt corrupted"
        sys.exit()

    #PrintOnNewline intelligently controls newline generation logic by gating the evaluation of the Print* variables to see if we need to prepend anything - this gets set to false only 
    #if we're switching sources, types, debug masks 
    # See Formatter.c
    if Pkt.ModuleRefKey == LastSourceRef and Pkt.LogType == LastType:
        if Pkt.LogType != LOG_TYPE_DEBUG or (Pkt.LogType == LOG_TYPE_DEBUG and LastMask == Pkt.MaskValue):
            if not SawNewLine:
                PrintImplicitNewline = False 
                PrintFormatting = False

    LastSourceRef = Pkt.ModuleRefKey
    LastType = Pkt.LogType
    LastMask = Pkt.MaskValue

    #Get the TextPkt Str Data
    Data = Data[TextPktSize:]
    _CheckData(Data)

    Str = Data[:Pkt.StrBytes]

    if (PrintImplicitNewline and not SawNewLine):
        sys.stdout.write("\n")

    if (Pkt.AppendNewLine):
        SawNewLine = True
        Str = Str + "\n"

    SawNewLine = ('\n' in Str) or ('\r' in Str)
    
    #Get the Function name length
    Data = Data[Pkt.StrBytes:]
    _CheckData(Data)

    FunctionNameLen = struct.unpack("<"+WordString, Data[:FileInfo.WordSize])[0]

    #Get the Function name
    Data = Data[FileInfo.WordSize:]
    _CheckData(Data)

    FunctionName = Data[:FunctionNameLen]

    #Trim the rest of the Data
    Data = Data[FunctionNameLen:]

    DeltaTime = Pkt.Timestamp - PreviousTagTime

    sys.stdout.write(TagTypeStart[Pkt.LogType])

    if PrintFormatting:
        sys.stdout.write( "[" + FunctionName + "]" + "<" + str(Pkt.Timestamp/1000000) + "." + str(Pkt.Timestamp%1000000) + "s (+" + str(DeltaTime/1000000) + "." + "%06d" %(DeltaTime%1000000) + ")>" + AddedMessage[Pkt.LogType])

    sys.stdout.write(Str)

    sys.stdout.write(COLOR_END)

    PreviousTagTime = Pkt.Timestamp

