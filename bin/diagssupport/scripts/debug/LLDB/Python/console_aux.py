import sys
import optparse
import shlex
from DataStructureDict import *
import hob
import classes
from ctypes import *
import binascii

def read_console_metadata(BaseAddr,result,debugger):
   BaseAddr = classes.get_hob_list(BaseAddr)
   if not BaseAddr:
      print "Cannot dump console. Missing needed hob info"
      sys.exit()

   Addrs = classes.get_hob_addrs_by_type(BaseAddr, "EFI_HOB_CONSOLE_BUFFER")

   if len(Addrs) != 1:
      result.PutCString ("Found %d Console Buffers!" % len(Addrs))
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   Addr = Addrs[0]
   print ("EFI_HOB_CONSOLE_BUFFER Location: 0x%x" % Addr)
   ConsoleBufferStructure = ReadDataStructureMember(EFI_HOB_CONSOLE_BUFFER_Dict, "BufferStructAddress", Addr)
   print ("ConsoleBufferStruct Location: 0x%x" % ConsoleBufferStructure)

   Data = ReadDataStructureMember(EFI_FORENSICS_BUFFER_Dict, "Buf", ConsoleBufferStructure)
   BufferSize = ReadDataStructureMember(EFI_FORENSICS_BUFFER_Dict, "BufSize", ConsoleBufferStructure)
   Head = ReadDataStructureMember(EFI_FORENSICS_BUFFER_Dict, "HeadIdx", ConsoleBufferStructure)
   Tail = ReadDataStructureMember(EFI_FORENSICS_BUFFER_Dict, "TailIdx", ConsoleBufferStructure)
   Freespace = ReadDataStructureMember(EFI_FORENSICS_BUFFER_Dict, "Freespace", ConsoleBufferStructure)
   print "BufferSize: 0x%x\nFreespace: 0x%x\nHead: 0x%x\nTail: 0x%x\nData:0x%x" % (BufferSize, Freespace,Head, Tail, Data)

   return (BufferSize,Data,Head,Tail,Freespace)

def read_ramlog_metadata(BaseAddr,result,debugger):
   BaseAddr = classes.get_hob_list(BaseAddr)
   if not BaseAddr:
      print "Cannot dump ramlog. Missing needed hob info"
      sys.exit()

   Addrs = classes.get_hob_addrs_by_type(BaseAddr, "EFI_HOB_RAMLOG_BUFFER")

   if len(Addrs) != 1:
      result.PutCString ("Found %d Ramlog Buffers!" % len(Addrs))
      result.SetStatus (lldb.eReturnStatusFailed)
      return

   Addr = Addrs[0]
   RamlogBufferStructure = ReadDataStructureMember(EFI_HOB_RAMLOG_BUFFER_Dict, "BufferStructAddress", Addr)
   print ("RamlogBuffer Struct Location: 0x%x" % RamlogBufferStructure)

   DataAddress = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "Data", RamlogBufferStructure)
   BufferSize = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "BufferSize", RamlogBufferStructure)
   BufferSizeMask = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "BufferSizeMask", RamlogBufferStructure)
   MaxDataSize = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "MaxDataSize", RamlogBufferStructure)
   Head = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "Head", RamlogBufferStructure)
   Tail = ReadDataStructureMember(EFI_CONTIG_RING_BUFFER_Dict, "Tail", RamlogBufferStructure)
   print "BufferSize: 0x%x\nBufferSizeMask: 0x%x\nMaxDataSize: 0x%x\nHead: 0x%x\nTail: 0x%x\nData:0x%x" % (BufferSize, BufferSizeMask, MaxDataSize, Head, Tail, DataAddress)
   return (BufferSize,BufferSizeMask,MaxDataSize,DataAddress,Head,Tail)

def conversion(HexData):
   DecData = ''.join( [ "%02X " % ord( x ) for x in HexData ] ).strip()
   DecData = DecData.replace(" ", "")
   StrData = "".join(reversed([DecData[i:i+2] for i in range(0, len(DecData), 2)]))
   RetValue = int(StrData,16)
   return RetValue

def convert_bytes_to_numbers(StartAddress,Length):
   HexData = bytearray(read_memory_block(StartAddress, Length), 'hex')
   HexData = str(HexData)
   DecData = ''.join( [ "%02X " % ord( x ) for x in HexData ] ).strip()
   DecData = DecData.replace(" ", "")
   StrData = "".join(reversed([DecData[i:i+2] for i in range(0, len(DecData), 2)]))
   RetValue = int(StrData,16)
   return RetValue
