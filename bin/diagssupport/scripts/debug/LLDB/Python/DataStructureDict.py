#!/usr/bin/python
#
# Copyright (c) 2011 - 2012 Apple Inc. All rights reserved
#
# Contains data structure mappings and info for EFI LLDB scripts
# The DataStructureDict is only needed when symbols are not
# availible. When symbols are availible sbvalue.variable()
# can be used:
# gMemoryMap = global_to_variable ("gMemoryMap") 
# if gMemoryMap.ForwardLink == gMemoryMap.BackwardLink:
#

import lldb
import classes

gDebugTableGUID = "49152E77-1ADA-4764-B7A2-7AFEFED95E8B"
gHobListGUID = "7739F24C-93D7-11D4-9A3A-0090273FC14D"
gPanicBufferGUID = "8CD9BBFE-E7DE-4620-805B-F4D472B4EF8E"
gStackGUID = "8EBAAD10-CB31-4EAA-AA9C-A56583112B5C"

EFI_STATUS_Dict = {
  (0x8000000000000000 |  1): "Load Error",
  (0x8000000000000000 |  2): "Invalid Parameter",
  (0x8000000000000000 |  3): "Unsupported",
  (0x8000000000000000 |  4): "Bad Buffer Size",
  (0x8000000000000000 |  5): "Buffer Too Small",
  (0x8000000000000000 |  6): "Not Ready",
  (0x8000000000000000 |  7): "Device Error",
  (0x8000000000000000 |  8): "Write Protected",
  (0x8000000000000000 |  9): "Out of Resources",
  (0x8000000000000000 | 10): "Volume Corrupt",
  (0x8000000000000000 | 11): "Volume Full",
  (0x8000000000000000 | 12): "No Media",
  (0x8000000000000000 | 13): "Media changed",
  (0x8000000000000000 | 14): "Not Found",
  (0x8000000000000000 | 15): "Access Denied",
  (0x8000000000000000 | 16): "No Response",
  (0x8000000000000000 | 17): "No mapping",
  (0x8000000000000000 | 18): "Time out",
  (0x8000000000000000 | 19): "Not started",
  (0x8000000000000000 | 20): "Already started",
  (0x8000000000000000 | 21): "Aborted",
  (0x8000000000000000 | 22): "ICMP Error",
  (0x8000000000000000 | 23): "TFTP Error",
  (0x8000000000000000 | 24): "Protocol Error",

                        0 : "Success",
                        1 : "Warning Unknown Glyph",
                        2 : "Warning Delete Failure",
                        3 : "Warning Write Failure",
                        4 : "Warning Buffer Too Small",

  (0x80000000         |  1): "Load Error",
  (0x80000000         |  2): "Invalid Parameter",
  (0x80000000         |  3): "Unsupported",
  (0x80000000         |  4): "Bad Buffer Size",
  (0x80000000         |  5): "Buffer Too Small",
  (0x80000000         |  6): "Not Ready",
  (0x80000000         |  7): "Device Error",
  (0x80000000         |  8): "Write Protected",
  (0x80000000         |  9): "Out of Resources",
  (0x80000000         | 10): "Volume Corrupt",
  (0x80000000         | 11): "Volume Full",
  (0x80000000         | 12): "No Media",
  (0x80000000         | 13): "Media changed",
  (0x80000000         | 14): "Not Found",
  (0x80000000         | 15): "Access Denied",
  (0x80000000         | 16): "No Response",
  (0x80000000         | 17): "No mapping",
  (0x80000000         | 18): "Time out",
  (0x80000000         | 19): "Not started",
  (0x80000000         | 20): "Already started",
  (0x80000000         | 21): "Aborted",
  (0x80000000         | 22): "ICMP Error",
  (0x80000000         | 23): "TFTP Error",
  (0x80000000         | 24): "Protocol Error",
}

HobDict = {
       1: "EFI_HOB_HANDOFF_INFO_TABLE",
       2: "EFI_HOB_MEMORY_ALLOCATION",
       3: "EFI_HOB_RESOURCE_DESCRIPTOR",
       4: "EFI_HOB_GUID_TYPE",
       5: "EFI_HOB_FIRMWARE_VOLUME",
       6: "EFI_HOB_CPU",
       7: "EFI_HOB_MEMORY_POOL",
       8: "EFI_HOB_CV",
       9: "EFI_HOB_BUILD_ID",
       0xA: "EFI_HOB_SYSTEM_TABLE",
       0xB: "EFI_HOB_MEMORY_ALLOCATION_MODULE",
       0xC: "EFI_HOB_CONSOLE_BUFFER",
       0xD: "EFI_HOB_RAMLOG_BUFFER",
       0xE: "EFI_HOB_MEMORY_MAP_INFO",
       0xffff: "EFI_HOB_END_OF_HOB_LIST",
}

EFI_MEMORY_TYPE_Dict = {
   0:  "EfiReservedMemoryType",
   1:  "EfiLoaderCode",
   2:  "EfiLoaderData",
   3:  "EfiBootServicesCode",
   4:  "EfiBootServicesData",
   5:  "EfiRuntimeServicesCode",
   6:  "EfiRuntimeServicesData",
   7:  "EfiConventionalMemory",
   8:  "EfiUnusableMemory",
   9:  "EfiACPIReclaimMemory",
  10:  "EfiACPIMemoryNVS",
  11:  "EfiMemoryMappedIO",
  12:  "EfiMemoryMappedIOPortSpace",
  13:  "EfiPalCode",
}

EFI_RESOURCE_TYPE_Dict = {
  0:  "Memory",
  1:  "MMIO",
  2:  "IO",
  3:  "FD",
  4:  "Mem Map IO Port",
  5:  "Reserved",
  6:  "IO Reserved",
}

DataStructEnumDict = {
  "EFI_STATUS":                 EFI_STATUS_Dict,
  "EFI_MEMORY_TYPE":            EFI_MEMORY_TYPE_Dict,
  "EFI_RESOURCE_TYPE":          EFI_RESOURCE_TYPE_Dict,
}



# Dictionary for EFI_SYSTEM_TABLE_POINTER
# "element", ((32-bit offset, 32-bit size), (64-bit offset, 64-bit, size), "Type"),
EFI_SYSTEM_TABLE_POINTER_Dict = {
#  UINT64                Signature;          ///< A constant UINT64 that has the value EFI_SYSTEM_TABLE_SIGNATURE
  "Signature":           (( 0, 8), ( 0, 8), "UINT64"),
#  EFI_PHYSICAL_ADDRESS  EfiSystemTableBase; ///< The physical address of the EFI system table.
  "EfiSystemTableBase":  (( 8, 8), ( 8, 8), "EFI_PHYSICAL_ADDRESS"),
#  UINT32                Crc32;              ///< A 32-bit CRC value that is used to verify the EFI_SYSTEM_TABLE_POINTER structure is valid.
  "Crc32":               ((16, 4), (16, 4), "UINT32")
}

# Dictionary for EFI_GUID_Dict
# "element", ((32-bit offset, 32-bit size), (64-bit offset, 64-bit, size), "Type"),
EFI_GUID_Dict = {
#  UINT32  Data1;
  "Data1":           ((0, 4), (0, 4), "UINT32"),
#  UINT16  Data2;
  "Data2":           ((4, 2), (4, 2), "UINT16"),
#  UINT16  Data3;
  "Data3":           ((6, 2), (6, 2), "UINT16"),
#  UINT8   Data4[8];
  "Data4[8]":        ((8, 1), (8, 1), "UINT8"),
}

EFI_PANIC_BUFFER_Dict = {
#typedef struct {
#  EFI_PHYSICAL_ADDRESS  MemoryBaseAddress;
   "Hdr":            ((0, 24), (0, 24), "EFI_HOB_GUID_TYPE"),
   "BufferAddr":     ((24, 4), (24, 8), "VOID*"),
#    EFI_PHYSICAL_ADDRESS BufferAddr;
   "BufferSize":     ((28, 4), (32, 8), "UINTN"),
#    UINTN BufferSize;
#} ApplePanicBufferDescriptor_t;
}

APPLE_STACK_DESC_Dict = {
#typedef struct {
   "Hdr":            ((0, 24), (0, 24), "EFI_HOB_GUID_TYPE"),
   "privilege":      ((24, 4), (24, 8), "UINTN"),
#	STACK_PRIVILEGE_LEVEL privilege;
   "mode":           ((28, 4), (32, 8), "UINTN"),
#	STACK_MODE mode;
   "stackTop":       ((32, 8), (40, 8), "EFI_PHYSICAL_ADDRESS"),
#	EFI_PHYSICAL_ADDRESS stackTop;
   "stackBottom":    ((40, 8), (48, 8), "EFI_PHYSICAL_ADDRESS"),
#	EFI_PHYSICAL_ADDRESS stackBottom;
#} AppleStackDescriptor_t;
}

EFI_TABLE_HEADER_Dict = {
#///
#/// Data structure that precedes all of the standard EFI table types.
#/// 
# typedef struct {
#   ///
#   /// A 64-bit signature that identifies the type of table that follows.
#   /// Unique signatures have been generated for the EFI System Table,
#   /// the EFI Boot Services Table, and the EFI Runtime Services Table.
#   ///
#   UINT64  Signature;
  "Signature":                      (( 0, 8), ( 0, 8), "UINT64"),
#   ///
#   /// The revision of the EFI Specification to which this table
#   /// conforms. The upper 16 bits of this field contain the major
#   /// revision value, and the lower 16 bits contain the minor revision
#   /// value. The minor revision values are limited to the range of 00..99.
#   ///
#   UINT32  Revision;
  "Revision":                      (( 8, 4), ( 8, 4), "UINT32"),
#   ///
#   /// The size, in bytes, of the entire table including the EFI_TABLE_HEADER.
#   ///
#   UINT32  HeaderSize;
  "HeaderSize":                   ((12, 4), (12, 4), "UINT32"),
#   ///
#   /// The 32-bit CRC for the entire table. This value is computed by
#   /// setting this field to 0, and computing the 32-bit CRC for HeaderSize bytes.
#   ///
#   UINT32  CRC32;
  "CRC32":                        ((16, 4), (16, 4), "UINT32"),
#   ///
#   /// Reserved field that must be set to 0.
#   ///
#   UINT32  Reserved;
 "Reserved":                     ((20, 4), (20, 4), "UINT32"),
}


# "element", ((32-bit offset, 32-bit size), (64-bit offset, 64-bit, size), "Type"),
EFI_SYSTEM_TABLE_Dict = {
#   ///
#   /// The table header for the EFI System Table.
#   ///
#   EFI_TABLE_HEADER                  Hdr;
  "Hdr":                      (( 0, 24), ( 0, 24), "EFI_TABLE_HEADER"),
#   ///
#   /// A pointer to a null terminated string that identifies the vendor
#   /// that produces the system firmware for the platform.
#   ///
#   CHAR16                            *FirmwareVendor;
  "FirmwareVendor":           ((24,  4), (24,  8), "CHAR16*"),
#   ///
#   /// A firmware vendor specific value that identifies the revision
#   /// of the system firmware for the platform.
#   ///
#   UINT32                            FirmwareRevision;
  "FirmwareRevision":         ((28,  4), (32,   4), "UINT32"),
#   ///
#   /// The handle for the active console input device. This handle must support
#   /// EFI_SIMPLE_TEXT_INPUT_PROTOCOL and EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
#   ///
#   EFI_HANDLE                        ConsoleInHandle;
  "ConsoleInHandle":          ((32,  4), (40,  8), "EFI_HANDLE"),
#   ///
#   /// A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL interface that is
#   /// associated with ConsoleInHandle.
#   ///
#   EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *ConIn;
  "ConIn":                    ((36,  4), (48,  8), "EFI_SIMPLE_TEXT_INPUT_PROTOCOL*"),
#   ///
#   /// The handle for the active console output device.
#   ///
#   EFI_HANDLE                        ConsoleOutHandle;
  "ConsoleOutHandle":         ((40,  4), (56,  8), "EFI_HANDLE"),
#   ///
#   /// A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface
#   /// that is associated with ConsoleOutHandle.
#   ///
#   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *ConOut;
  "ConOut":                   ((44,  4), (64,  8), "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*"),
#   ///
#   /// The handle for the active standard error console device.
#   /// This handle must support the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
#   ///
#   EFI_HANDLE                        StandardErrorHandle;
  "StandardErrorHandle":      ((48,  4), (72,  8), "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL"),
#   ///
#   /// A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface
#   /// that is associated with StandardErrorHandle.
#   ///
#   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *StdErr;
  "StdErr":                   ((52,  4), (80,  8), "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*"),
#   ///
#   /// A pointer to the EFI Runtime Services Table.
#   ///
#   EFI_RUNTIME_SERVICES              *RuntimeServices;
  "RuntimeServices":          ((56,  4), (88,  8), "EFI_RUNTIME_SERVICES*"),
#   ///
#   /// A pointer to the EFI Boot Services Table.
#   ///
#   EFI_BOOT_SERVICES                 *BootServices;
  "BootServices":             ((60,  4), (96,  8), "EFI_BOOT_SERVICES*"),
#   ///
#   /// The number of system configuration tables in the buffer ConfigurationTable.
#   ///
#   UINTN                             NumberOfTableEntries;
  "NumberOfTableEntries":     ((64,  4), (104,  8), "UINTN"),
#   ///
#   /// A pointer to the system configuration tables.
#   /// The number of entries in the table is NumberOfTableEntries.
#   ///
#   EFI_CONFIGURATION_TABLE           *ConfigurationTable;
  "ConfigurationTable":       ((68,  4), (112,  8), "EFI_CONFIGURATION_TABLE*"),
}

EFI_CONFIGURATION_TABLE_Dict = {
#   ///
#   /// The 128-bit GUID value that uniquely identifies the system configuration table.
#   ///
#   EFI_GUID                          VendorGuid;
  "VendorGuid":       ((0,  16), (0,  16), "EFI_GUID"),
#   ///
#   /// A pointer to the table associated with VendorGuid.
#   ///
#   VOID                              *VendorTable;
  "VendorTable":       ((16,  4), (16,  8), "VOID*"),
} ;


EFI_DEBUG_IMAGE_INFO_TABLE_HEADER_Dict = {
#   ///
#   /// A pointer to the first element of an array of EFI_DEBUG_IMAGE_INFO structures.
#   ///
#   EFI_DEBUG_IMAGE_INFO  *EfiDebugImageInfoTable;
  "EfiDebugImageInfoTable":   ((0,  4), (0,  8), "EFI_DEBUG_IMAGE_INFO*"),
#   ///
#   /// UpdateStatus is used by the system to indicate the state of the debug image info table.
#   ///
#   volatile UINT32       UpdateStatus;
  "UpdateStatus":             ((4,  4), (8,  4), "volatile UINT32"),
#   ///
#   /// The number of EFI_DEBUG_IMAGE_INFO elements in the array pointed to by EfiDebugImageInfoTable.
#   ///
#   UINT32                TableSize;
  "TableSize":                ((8,  4), (12,  4), "UINT32"),
}

EFI_DEBUG_IMAGE_INFO_Dict = {
# typedef union {
#   UINT32                      *ImageInfoType;
   "ImageInfoType":              ((0, 4), (0, 8), "UINTN*"),
#   EFI_DEBUG_IMAGE_INFO_NORMAL *NormalImage;
   "NormalImage":                ((4,  4), (8,  8), "EFI_DEBUG_IMAGE_INFO_NORMAL*"),
}

EFI_DEBUG_IMAGE_INFO_NORMAL_Dict = {
#  ///
#  /// Indicates the type of image info structure. For PE32 EFI images,
#  /// this is set to EFI_DEBUG_IMAGE_INFO_TYPE_NORMAL.
#  ///
#  UINT32                     ImageInfoType;
  "ImageInfoType":                ((0,  4), (0,  8), "UINTN"),

#  ///
#  /// A pointer to an instance of the loaded image protocol for the associated image.
#  ///
#  EFI_LOADED_IMAGE_PROTOCOL  *LoadedImageProtocolInstance;
  "LoadedImageProtocolInstance":  ((4,  4), (8,  8), "EFI_LOADED_IMAGE_PROTOCOL*"),

#  ///
#  /// Indicates the image handle of the associated image.
#  ///
#  EFI_HANDLE                 ImageHandle;
 "ImageHandle":                   ((8,  4), (16, 8), "EFI_HANDLE"),
}

EFI_APPLE_IMAGE_RANGE_Dict = {
   "Base":        ((0, 8), (0, 8), "EFI_VIRTUAL_ADDRESS"),
   "Size":        ((8, 8), (8, 8), "UINT64"),

}

EFI_APPLE_DEBUG_SUPPORT_Dict = {
   #CHAR8 *FilePath;     // Pointer into actual loaded image area.
  "FilePath":             ((0,  4), (0,  8), "CHAR8*"),
   #// Covers whole image in-memory (headers + text + data + symbols, etc)
   #EFI_APPLE_IMAGE_RANGE ImageRange;
  "ImageRange":           ((4,  16), (8,  16), "EFI_APPLE_IMAGE_RANGE"),
   ##// Text segment only
   #EFI_APPLE_IMAGE_RANGE TextRange;
  "TextRange":           ((20,  16), (24,  16), "EFI_APPLE_IMAGE_RANGE"),
   #// Data segment only
   #EFI_APPLE_IMAGE_RANGE DataRange;
  "DataRange":           ((36,  16), (40,  16), "EFI_APPLE_IMAGE_RANGE"),
}

# "element", ((32-bit offset, 32-bit size), (64-bit offset, 64-bit, size), "Type"),
EFI_LOADED_IMAGE_PROTOCOL_Dict = {
#   UINT32            Revision;       ///< Defines the revision of the EFI_LOADED_IMAGE_PROTOCOL structure.
#                                     ///< All future revisions will be backward compatible to the current revision.
  "Revision":                ((0,  4), (0,  4), "UINT32"),
#   EFI_HANDLE        ParentHandle;   ///< Parent image's image handle. NULL if the image is loaded directly from
#                                     ///< the firmware's boot manager.
  "ParentHandle":            ((4,  4), (8,  8), "EFI_HANDLE"),
#   EFI_SYSTEM_TABLE  *SystemTable;   ///< the image's EFI system table pointer.
#
#   //
#   // Source location of image
#   //
  "SystemTable":             ((8,  4), (16,  8), "EFI_SYSTEM_TABLE*"),
#   EFI_HANDLE        DeviceHandle;   ///< The device handle that the EFI Image was loaded from.
  "DeviceHandle":           ((12,  4), (24,  8), "EFI_HANDLE*"),
#   EFI_DEVICE_PATH_PROTOCOL  *FilePath;  ///< A pointer to the file path portion specific to DeviceHandle
#                                         ///< that the EFI Image was loaded from.
  "FilePath":               ((16,  4), (32,  8), "EFI_DEVICE_PATH_PROTOCOL*"),
#   VOID              *Reserved;      ///< Reserved. DO NOT USE.
  "Reserved":               ((20,  4), (40,  8), "VOID*"),
#
#   //
#   // Images load options
#   //
#   UINT32            LoadOptionsSize;///< The size in bytes of LoadOptions.
  "LoadOptionsSize":        ((24,  4), (48,  4), "UINT32"),
#   VOID              *LoadOptions;   ///< A pointer to the image's binary load options.
  "LoadOptions":            ((28,  4), (56,  8), "VOID*"),
#
#   //
#   // Location of where image was loaded
#   //
#   VOID              *ImageBase;     ///< The base address at which the image was loaded.
  "ImageBase":              ((32,  4), (64,  8), "VOID*"),
#   UINT64            ImageSize;      ///< The size in bytes of the loaded image.
  "ImageSize":              ((36,  8), (72,  8), "UINT64"),
#   EFI_MEMORY_TYPE   ImageCodeType;  ///< The memory type that the code sections were loaded as.
  "ImageCodeType":          ((44,  4), (80,  4), "EFI_MEMORY_TYPE"),
#   EFI_MEMORY_TYPE   ImageDataType;  ///< The memory type that the data sections were loaded as.
  "ImageCodeType":          ((48,  4), (84,  4), "EFI_MEMORY_TYPE"),
  "ImageDebugInfo":         ((56,  52), (88, 56), "EFI_APPLE_DEBUG_SUPPORT"),
#   EFI_IMAGE_UNLOAD  Unload;
  "Unload":                 ((104,  4), (144, 8), "EFI_IMAGE_UNLOAD"),
}

#
# PE/COFF Structures
#
EFI_IMAGE_DATA_DIRECTORY_Dict = {
#   UINT32  VirtualAddress;
  "VirtualAddress":        ((0,  4), (0,  4), "UINT32"),
#   UINT32  Size;
  "Size":                  ((4,  4), (4,  4), "UINT32"),
}

# Signature is "VZ" for TE. VZ = Vincent Zimmer
EFI_TE_IMAGE_HEADER_Dict = {
#   UINT16                    Signature;            ///< The signature for TE format = "VZ".
  "Signature":                ((0,  2), (0,  2), "UINT16"),
#   UINT16                    Machine;              ///< From the original file header.
  "Machine":                  ((2,  2), (2,  2), "UINT16"),
#   UINT8                     NumberOfSections;     ///< From the original file header.
  "NumberOfSections":         ((4,  1), (4,  1), "UINT8"),
#   UINT8                     Subsystem;            ///< From original optional header.
  "Subsystem":                ((5,  1), (5,  1), "UINT8"),
#   UINT16                    StrippedSize;         ///< Number of bytes we removed from the header.
  "StrippedSize":             ((6,  2), (6,  2), "UINT16"),
#   UINT32                    AddressOfEntryPoint;  ///< Offset to entry point -- from original optional header.
  "AddressOfEntryPoint":      ((8,  4), (8,  4), "UINT32"),
#   UINT32                    BaseOfCode;           ///< From original image -- required for ITP debug.
  "BaseOfCode":               ((12, 4), (12, 4), "UINT32"),
#   UINT64                    ImageBase;            ///< From original file header.
  "ImageBase":                ((16, 8), (16, 8), "UINT64"),
#   EFI_IMAGE_DATA_DIRECTORY  DataDirectory[2];     ///< Only base relocation and debug directory.
  "DataDirectory[2]":         ((24, 8), (24, 8), "EFI_IMAGE_DATA_DIRECTORY"),
}

# Signature is "MZ" for DOS Header. MZ = Mark Zbikowski
# ///
# /// PE images can start with an optional DOS header, so if an image is run
# /// under DOS it can print an error message.
# ///
EFI_IMAGE_DOS_HEADER_Dict=  {
#   UINT16  e_magic;    ///< Magic number.
  "e_magic":            ((0, 2), (0, 2), "UINT32"),
#   UINT16  e_cblp;     ///< Bytes on last page of file.
#   UINT16  e_cp;       ///< Pages in file.
#   UINT16  e_crlc;     ///< Relocations.
#   UINT16  e_cparhdr;  ///< Size of header in paragraphs.
#   UINT16  e_minalloc; ///< Minimum extra paragraphs needed.
#   UINT16  e_maxalloc; ///< Maximum extra paragraphs needed.
#   UINT16  e_ss;       ///< Initial (relative) SS value.
#   UINT16  e_sp;       ///< Initial SP value.
#   UINT16  e_csum;     ///< Checksum.
#   UINT16  e_ip;       ///< Initial IP value.
#   UINT16  e_cs;       ///< Initial (relative) CS value.
#   UINT16  e_lfarlc;   ///< File address of relocation table.
#   UINT16  e_ovno;     ///< Overlay number.
#   UINT16  e_res[4];   ///< Reserved words.
#   UINT16  e_oemid;    ///< OEM identifier (for e_oeminfo).
#   UINT16  e_oeminfo;  ///< OEM information; e_oemid specific.
#   UINT16  e_res2[10]; ///< Reserved words.
#   UINT32  e_lfanew;   ///< File address of new exe header. 0x3c
  "e_lfanew":           ((60, 4), (60, 4), "UINT32"),
}


# Signature is "PE/0/0"
# Code uses EFI_IMAGE_OPTIONAL_HEADER_UNION
# This data structure is based on EFI_IMAGE_NT_HEADERS64, but
#  EFI_IMAGE_FILE_HEADER (COFF) header and
#  EFI_IMAGE_OPTIONAL_HEADER64 (required for PE/COFF)
#  are converted into a single structure that also supports 32-bits
# PE = 32-bit PE+ = 64-bit
#
# "element", ((32-bit offset, 32-bit size), (64-bit offset, 64-bit, size), "Type"),
EFI_IMAGE_NT_HEADERS_Dict = {
#  UINT32                      Signature;
  "Signature":                ((0,  4), (0,  4), "UINT32"),

# typedef struct {
#   UINT16  Machine;
  "Machine":                        (( 4, 2), (4,  2), "UINT16"),
#   UINT16  NumberOfSections;
  "NumberOfSections":               (( 6, 2), (6,  2), "UINT16"),
#   UINT32  TimeDateStamp;
  "TimeDateStamp":                  (( 8, 4), (8,  4), "UINT32"),
#   UINT32  PointerToSymbolTable;
  "PointerToSymbolTable":           ((12, 4), (12, 4), "UINT32"),
#   UINT32  NumberOfSymbols;
  "NumberOfSymbols":                ((16, 4), (16, 4), "UINT32"),
#   UINT16  SizeOfOptionalHeader;
  "SizeOfOptionalHeader":           ((20, 2), (20, 2), "UINT16"),
#   UINT16  Characteristics;
  "Characteristics":                ((22, 2), (22, 2), "UINT16"),
# } EFI_IMAGE_FILE_HEADER;
#
# typedef struct {
#   ///
#   /// Standard fields. COFF
#   ///
#   UINT16                    Magic; // 0x10b for PE32, 0x20b for PE32+
  "Magic":                      ((24 +  0,  2), (24 +  0, 2), "UINT16"),
#   UINT8                     MajorLinkerVersion;
  "MajorLinkerVersion":         ((24 +  2,  1), (24 +  2, 1), "UINT8"),
#   UINT8                     MinorLinkerVersion;
  "MinorLinkerVersion":         ((24 +  3,  1), (24 +  3, 1), "UINT8"),
#   UINT32                    SizeOfCode;
  "SizeOfCode":                 ((24 +  4,  4), (24 +  4, 4), "UINT32"),
#   UINT32                    SizeOfInitializedData;
  "SizeOfInitializedData":      ((24 +  8,  4), (24 +  8, 4), "UINT32"),
#   UINT32                    SizeOfUninitializedData;
  "SizeOfUninitializedData":    ((24 + 12,  4), (24 + 12, 4), "UINT32"),
#   UINT32                    AddressOfEntryPoint;
  "AddressOfEntryPoint":        ((24 + 16,  4), (24 + 16, 4), "UINT32"),
#   UINT32                    BaseOfCode;
  "BaseOfCode":                 ((24 + 20,  4), (24 + 20, 4), "UINT32"),
#   UINT32                    BaseOfData;  ///< PE32 contains this additional field, which is absent in PE32+.
  "BaseOfData":                 ((24 + 24,  4), (    0, 0  ), "UINT32"),

#   ///
#   /// Optional Header Windows-Specific Fields.
#   ///

#   UINT64                    ImageBase;  /// 32-bit in PE32. Type will be wrong in PE32 dump
  "ImageBase":                  ((24 + 28, 4), (24 + 24, 8), "UINT64"),

#   UINT32                    SectionAlignment;
  "SectionAlignment":           ((24 + 32, 4), (24 + 32, 8), "UINT32"),
#   UINT32                    FileAlignment;
  "FileAlignment":              ((24 + 36, 4), (24 + 36, 4), "UINT16"),
#   UINT16                    MajorOperatingSystemVersion;
  "MajorOperatingSystemVersion":((24 + 40, 2), (24 + 40, 2), "UINT16"),
#   UINT16                    MinorOperatingSystemVersion;
  "MinorOperatingSystemVersion":((24 + 42, 2), (24 +  0, 2), "UINT16"),
#   UINT16                    MajorImageVersion;
  "MajorImageVersion":          ((24 + 44, 2), (24 +  0, 2), "UINT16"),
#   UINT16                    MinorImageVersion;
  "MinorImageVersion":          ((24 + 46, 2), (24 +  0, 2), "UINT16"),
#   UINT16                    MajorSubsystemVersion;
  "MajorSubsystemVersion":      ((24 + 48, 2), (24 +  0, 2), "UINT16"),
#   UINT16                    MinorSubsystemVersion;
  "MinorSubsystemVersion":      ((24 + 50, 2), (24 +  0, 2), "UINT16"),
#   UINT32                    Win32VersionValue;
  "Win32VersionValue":          ((24 + 52, 4), (24 + 52, 4), "UINT32"),
#   UINT32                    SizeOfImage;
  "SizeOfImage":                ((24 + 56, 4), (24 + 56, 4), "UINT32"),
#   UINT32                    SizeOfHeaders;
  "SizeOfHeaders":              ((24 + 60, 4), (24 + 60, 4), "UINT32"),
#   UINT32                    CheckSum;
  "CheckSum":                   ((24 + 64, 4), (24 + 64, 4), "UINT32"),
#   UINT16                    Subsystem;
  "Subsystem":                  ((24 + 68, 2), (24 + 68, 2), "UINT16"),
#   UINT16                    DllCharacteristics;
  "DllCharacteristics":         ((24 + 70, 2), (24 + 70, 2), "UINT16"),
#   UINT64                    SizeOfStackReserve;
  "SizeOfStackReserve":         ((24 + 72, 4), (24 + 72, 8), "UINT64"),
#   UINT64                    SizeOfStackCommit;
  "SizeOfStackCommit":          ((24 + 76, 4), (24 + 80, 8), "UINT64"),
#   UINT64                    SizeOfHeapReserve;
  "SizeOfHeapReserve":          ((24 + 80, 4), (24 + 88, 8), "UINT64"),
#   UINT64                    SizeOfHeapCommit;
  "SizeOfHeapCommit":           ((24 + 84, 4), (24 + 96, 8), "UINT64"),
#   UINT32                    LoaderFlags;
  "LoaderFlags":                ((24 + 88, 4), (24 +104, 4), "UINT32"),
#   UINT32                    NumberOfRvaAndSizes;
  "NumberOfRvaAndSizes":        ((24 + 92, 4), (24 +108, 4), "UINT32"),
#   EFI_IMAGE_DATA_DIRECTORY  DataDirectory[16];
  "DataDirectory[16]":           ((24 + 96, 8), (24 +112, 8), "EFI_IMAGE_DATA_DIRECTORY"),
#} EFI_IMAGE_OPTIONAL_HEADER64;
}

EFI_IMAGE_SECTION_HEADER_Dict = {
# ///
# /// Section Table. This table immediately follows the optional header.
# ///
#   UINT8 Name[8];
  "Name[8]":              (( 0, 8), ( 0, 8), "UINT8"),
#   union {
#     UINT32  PhysicalAddress;
#     UINT32  VirtualSize;
  "VirtualSize":          (( 8, 4), ( 8, 4), "UINT32"),
#   } Misc;
#   UINT32  VirtualAddress;
  "VirtualAddress":       ((12, 4), (12, 4), "UINT32"),
#   UINT32  SizeOfRawData;
  "SizeOfRawData":        ((16, 4), (16, 4), "UINT32"),
#   UINT32  PointerToRawData;
  "PointerToRawData":     ((20, 4), (20, 4), "UINT32"),
#   UINT32  PointerToRelocations;
  "PointerToRelocations": ((24, 4), (24, 4), "UINT32"),
#   UINT32  PointerToLinenumbers;
  "PointerToLinenumbers": ((28, 4), (28, 4), "UINT32"),
#   UINT16  NumberOfRelocations;
  "NumberOfRelocations":  ((32, 4), (32, 4), "UINT16"),
#   UINT16  NumberOfLinenumbers;
  "NumberOfLinenumbers":  ((34, 4), (34, 4), "UINT16"),
#   UINT32  Characteristics;
  "Characteristics":      ((36, 4), (36, 4), "UINT32"),
}


EFI_IMAGE_BASE_RELOCATION_Dict = {
# ///
# /// Based relocation format.
# ///
# typedef struct {
#   UINT32  VirtualAddress;
  "VirtualAddress":     ((0, 4), (0, 4), "UINT32"),
#   UINT32  SizeOfBlock;
  "SizeOfBlock":        ((4, 4), (4, 4), "UINT32"),
}


EFI_IMAGE_DEBUG_DIRECTORY_ENTRY_Dict = {
# ///
# /// Debug Directory Format.
# ///
#   UINT32  Characteristics;
  "Characteristics":   (( 0, 4), ( 0, 4), "UINT32"),
#   UINT32  TimeDateStamp;
  "TimeDateStamp":     (( 4, 4), ( 4, 4), "UINT32"),
#   UINT16  MajorVersion;
  "MajorVersion":      (( 8, 2), ( 8, 2), "UINT16"),
#   UINT16  MinorVersion;
  "MinorVersion":      ((10, 2), (10, 2), "UINT16"),
#   UINT32  Type;
  "Type":              ((12, 4), (12, 4), "UINT32"),
#   UINT32  SizeOfData;
  "SizeOfData":        ((16, 4), (16, 4), "UINT32"),
#   UINT32  RVA;           ///< The address of the debug data when loaded, relative to the image base.
  "RVA":               ((20, 4), (20, 4), "UINT32"),
#   UINT32  FileOffset;    ///< The file pointer to the debug data.
  "FileOffset":        ((24, 4), (24, 4), "UINT32"),
}


EFI_IMAGE_DEBUG_CODEVIEW_MTOC_ENTRY_Dict = {
# ///
# /// Debug Data Structure defined by Apple Mach-O to Coff utility.
# ///
# typedef struct {
#   UINT32    Signature;                       ///< "MTOC".
  "Signature":   ((0,  4), (0,  4), "UINT32"),
#   EFI_GUID      MachOUuid;
  "MachOUuid":   ((4, 16), (4, 16), "EFI_GUID"),
#   //
#   //  Filename of .DLL (Mach-O with debug info) goes here
#   //
}

APPLE_DEBUG_INFO_TABLE_Dict = {
# typedef struct {
# EFI_GUID              Guid;
  "Guid":               (( 0, 16), ( 0, 16), "EFI_GUID"),
# VOID                  *ImageBase;
  "ImageBase":          ((16,  4), (16,  8), "VOID *"),
# VOID                  *Pdb;
  "Pdb":                ((20,  4), (24,  8), "VOID *"),
}

EFI_HOB_MEMORY_ALLOCATION_HEADER_Dict = {
#typedef struct {
  #EFI_GUID              Name;
   "Guid":                  ((0, 16), ( 0, 16), "EFI_GUID"),
#  EFI_PHYSICAL_ADDRESS  MemoryBaseAddress;
   "MemoryBaseAddress":     ((16, 8), (16, 8), "EFI_PHYSICAL_ADDRESS"),
#  UINT64                MemoryLength;
   "MemoryLength":          ((24, 8), (24, 8), "UINT64"),
#  EFI_MEMORY_TYPE       MemoryType;
   "MemoryType":            ((32, 4), (32, 4), "UINT32"),
#  UINT8                 Reserved[4];
   "Reserved[4]":           ((36, 1), (36, 1), "UINT8"),
}

EFI_HOB_GENERIC_HEADER_Dict = {
#typedef struct {
#  UINT16  HobType;
   "HobType":           ((0, 2), (0, 2), "UINT16"),
  #UINT16  HobLength;
   "HobLength":         ((2, 2), (2, 2), "UINT16"),
  #UINT32  Reserved;
   "Reserved":          ((4, 4), (4, 4), "UINT32"),
}

EFI_HOB_HANDOFF_INFO_TABLE_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER  Header;
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
  #UINT32                  Version;
   "Version":              ((8, 4), (8, 4), "UINT32"),
  #EFI_BOOT_MODE           BootMode;
   "BootMode":             ((12, 4), (12, 4), "UINT32"),
  #EFI_PHYSICAL_ADDRESS    EfiMemoryTop;
   "EfiMemoryTop":         ((16, 8), (16, 8), "EFI_PHYSICAL_ADDRESS"),
  #EFI_PHYSICAL_ADDRESS    EfiMemoryBottom;
   "EfiMemoryBottom":      ((24, 8), (24, 8), "EFI_PHYSICAL_ADDRESS"),
  #EFI_PHYSICAL_ADDRESS    EfiFreeMemoryTop;
   "EfiFreeMemoryTop":     ((32, 8), (32, 8), "EFI_PHYSICAL_ADDRESS"),
  #EFI_PHYSICAL_ADDRESS    EfiFreeMemoryBottom;
   "EfiFreeMemoryBottom":  ((40, 8), (40, 8), "EFI_PHYSICAL_ADDRESS"),
  #EFI_PHYSICAL_ADDRESS    EfiEndOfHobList;
   "EfiEndOfHobList":      ((48, 8), (48, 8), "EFI_PHYSICAL_ADDRESS"),
}

EFI_HOB_MEMORY_ALLOCATION_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER            Header;
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  EFI_HOB_MEMORY_ALLOCATION_HEADER  AllocDescriptor;
   "AllocDescriptor":      ((8, 40), (8, 40), "EFI_HOB_MEMORY_ALLOCATION_HEADER"),
}

EFI_HOB_RESOURCE_DESCRIPTOR_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER      Header;
   "Header":                ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  EFI_GUID                    Owner;
   "Owner":                 ((8, 16), ( 8, 16), "EFI_GUID"),
#  EFI_RESOURCE_TYPE           ResourceType;
   "ResourceType":          ((24, 4), (24, 4), "UINT32"),
#  EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute;
   "ResourceAttribute":     ((28, 4), (28, 4), "UINT32"),
#  EFI_PHYSICAL_ADDRESS        PhysicalStart;
   "PhysicalStart":         ((32, 8), (32, 8), "EFI_PHYSICAL_ADDRESS"),
#  UINT64                      ResourceLength;
   "ResourceLength":        ((40, 8), (40, 8), "UINT64"),
}

EFI_HOB_GUID_TYPE = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER  Header;
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
   #EFI_GUID                Name;
   "Guid":                  (( 8, 16), ( 8, 16), "EFI_GUID"),
}


EFI_HOB_FIRMWARE_VOLUME_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER  Header;
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  EFI_PHYSICAL_ADDRESS    BaseAddress;
   "BaseAddress":          ((8, 8), (8, 8), "EFI_PHYSICAL_ADDRESS"),
  #UINT64                  Length;
   "Length":               ((16, 8), (16, 8), "UINT64"),
}

EFI_HOB_CPU_Dict = {
#typedef struct {
   #EFI_HOB_GENERIC_HEADER  Header;
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
   #UINT8                   SizeOfMemorySpace;
   "SizeOfMemorySpace":    ((8,  1), (8, 1), "UINT8"),
   #UINT8                   SizeOfIoSpace;
   "SizeOfIoSpace":        ((9,  1), (9, 1), "UINT8"),
   #UINT8                   Reserved[6];
   "Reserved[6]":          ((10, 1), (10, 1), "UINT8"),
}

EFI_HOB_BUILD_ID_Dict = {
   "Header":                     ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
   "PlatformIDLocation":         ((8, 8), (8, 8),   "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),#really a EFI_PHYSICAL_ADDRESS but why not print out the string instead
   "BuildTypeLocation":          ((16, 8), (16, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
   "BuildTrainLocation":         ((24, 8), (24, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
   "DiagsBuildBranchLocation":   ((32, 8), (32, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
   "DiagsBuildIDLocation":       ((40, 8), (40, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
   "BuildNumberLocation":        ((48, 8), (48, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
   "BuildSrcRevLocation":        ((56, 8), (56, 8), "CHAR8*"),#"EFI_PHYSICAL_ADDRESS"),
}


EFI_HOB_SYSTEM_TABLE_Dict = {
   "Header":               ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
   "TableLocation":        ((8, 8), (8, 8), "EFI_PHYSICAL_ADDRESS"),
}

EFI_HOB_MEMORY_ALLOCATION_MODULE_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER            Header;
   "Header":                  ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  EFI_HOB_MEMORY_ALLOCATION_HEADER  MemoryAllocationHeader;
   "MemoryAllocationHeader": ((8, 40), (8, 40), "EFI_HOB_MEMORY_ALLOCATION_HEADER"),
#  EFI_GUID                          ModuleName;
   "ModuleName":              ((48, 16), (48, 16), "EFI_GUID"),
#  EFI_PHYSICAL_ADDRESS              EntryPoint;
   "EntryPoint":              ((64, 8), (64, 8), "EFI_PHYSICAL_ADDRESS"),
#  CHAR8								*FileName;
   "FileName":                ((72, 4), (72,  8), "CHAR8*"),
}

EFI_HOB_CONSOLE_BUFFER_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER            Header;
   "Header":                  ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  UINTN                             Version;
   "Version":                 ((8, 4), (8, 8), "UINTN"),
#  EFI_PHYSICAL_ADDRESS              BufferStructAddress;
   "BufferStructAddress":     ((16, 4), (16, 8), "EFI_PHYSICAL_ADDRESS"),
}

EFI_HOB_RAMLOG_BUFFER_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER            Header;
   "Header":                  ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#  UINTN                             Version;
   "Version":                 ((8, 4), (8, 8), "UINTN"),
#  EFI_PHYSICAL_ADDRESS              BufferStructAddress;
   "BufferStructAddress":     ((16, 4), (16, 8), "EFI_PHYSICAL_ADDRESS"),
}

EFI_HOB_END_OF_HOB_LIST_Dict = {
#typedef struct {
#  EFI_HOB_GENERIC_HEADER            Header;
   "Header":                  ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
}

EFI_CONTIG_RING_BUFFER_Dict = {
#typedef struct
#{
	#UINTN BufferSize;
   "BufferSize":                 ((0, 4), (0, 8), "UINTN"),
   #UINTN BufferSizeMask;
   "BufferSizeMask":             ((4, 4), (8, 8), "UINTN"),
	#UINTN MaxDataSize;
   "MaxDataSize":                ((8, 4), (16, 8), "UINTN"),
	#UINTN Head;
   "Head":                       ((12, 4), (24, 8), "UINTN"),
   #UINTN Tail;
   "Tail":                       ((16, 4), (32, 8), "UINTN"),
	#UINT8 *Data;
   "Data":                       ((20, 4), (40,  8), "UINT8*"),
}

EFI_FORENSICS_BUFFER_Dict = {
#typedef struct
#{
  #UINTN BufferSize;
   "Buf":                         ((0, 4), (0, 8), "UINT8*"),
   #UINTN BufferSizeMask;
   "BufSize":                     ((4, 4), (8, 8), "UINTN"),
  #UINTN MaxDataSize;
   "HeadIdx":                      ((8, 4), (16, 8), "UINTN"),
  #UINTN Head;
   "TailIdx":                      ((12, 4), (24, 8), "UINTN"),
   #UINTN Tail;
   "Freespace":                     ((16, 4), (32, 8), "UINTN"),
}


EFI_CORE_LOG_TEXT_TAG_Dict = {
#typedef struct {
#    CHAR8 *FileName;
    "FileName":                     ((0, 4), (0, 8), "CHAR8*"),
#    CHAR8 *FunctionName;
    "FunctionName":                 ((4, 4), (8, 8), "CHAR8*"),
#    UINTN LineNo;
    "LineNo":                       ((8, 4), (16, 8), "UINTN"),
#    LogType Type;
    "Type":                         ((12, 4), (24, 4), "UINT32"),
#
#    union {
#        DebugLogMask MaskValue;
#        TraceType TraceValue;
#    };
    "MaskValue":                    ((16, 4), (28, 4), "UINT32"),
#
#    ConsoleSourceRef ModuleRefKey;
    "ModuleRefKey":                 ((0x14, 4), (32, 8), "ConsoleSourceRef"),
#    UINT64 Timestamp;
    "Timestamp":                    ((0x18, 8), (40, 8), "UINT64"),
#    BOOLEAN AppendNewline;
    "AppendNewline":                ((0x20, 4), (48, 4), "BOOLEAN"),
#} CoreLogTextTag;
}

EFI_TEXT_PKT_Dict = {
#typedef struct {
#    UINT32 Signature;
    "Signature":                    ((0, 4),  (0, 4), "UINT32"),
#    CoreLogTextTag Tag;
    "Tag":                          ((0x8, 36), (8, 56), "CoreLogTextTag"),
#    UINTN StrBytes;
    "StrBytes":                     ((0x30, 4), (64, 8), "UINTN"),
#    CHAR8 Str[];
    "Str":                          ((0x34, 1), (72, 1), "CHAR8 []"),
#} TextPkt;
}

EFI_TEXT_TAG_Dict = {
#typedef struct {
#    UINT64 Timestamp;
    "Timestamp":                    ((0, 8), (0, 8), "UINT64"),
#    CHAR8 *FunctionName;
    "FunctionName":                 ((8, 4), (8, 8), "CHAR8*"),
#    UINTN LineNo;
    "LineNo":                       ((12, 4), (16, 8), "UINTN"),
#    LogType Type;
    "Type":                         ((16, 4), (24, 4), "UINT32"),
#    union {
#        DebugLogMaskInfo MaskInfo;
#        TraceType TraceValue;
#        CHAR8 *AssertFileName;
#    };
#
#    CHAR8 *SourceModuleName;
    "SourceModuleName":             ((30, 4), (38, 8), "CHAR8*"),
#    CHAR8 *ImageName;
#    UINT64 SpecialAttributes;
    "SpecialAttributes":             ((0x28, 8), (0x48, 8), "UINT64"),
#    ConsoleSourceRef SourceRef;                        // Used to allow sinks to 'loosely' track when a source has changed relative to the last print
    "SourceRef":                    ((0x30, 8), (0x50, 8), "ConsoleSourceRef"), 
#} TextTag;
}

EFI_TEXT_PKT_HDR_Dict = {
#typedef struct {
#    UINT32 Magic;
    "Magic":                    ((0, 4),  (0, 4), "UINT32"),
#    UINTN StrLen;
    "StrLen":                   ((4, 4),  (8, 8), "UINTN"),
#    UINTN TotalDataLen;
    "TotalDataLen":             ((8, 4),  (16, 8), "UINTN"),
    "Tag":                      ((12, 0), (24, 0), "CHAR8 []"),
#} TagPktHdr;
}

EFI_TEXT_PKT_TAG_Dict = {
#typedef struct {
#    UINT32 Signature;
    "Signature":                    ((0, 4),  (0, 4), "UINT32"),
#    CoreLogTextTag Tag;
#    "Tag":                          ((4, 36), (8, 56), "CoreLogTextTag"),

    "Tag.FileName":                     ((0x8, 4), (8 + 0, 8), "CHAR8*"),
#    CHAR8 *FunctionName;
    "Tag.FunctionName":                 ((0xC, 4), (8 + 8, 8), "CHAR8*"),
#    UINTN LineNo;
    "Tag.LineNo":                       ((0x10, 4), (8 + 16, 8), "UINTN"),
#    LogType Type;
    "Tag.Type":                         ((0x14, 4), (8 + 24, 4), "UINT32"),
#
#    union {
#        DebugLogMask MaskValue;
#        TraceType TraceValue;
#    };
    "Tag.MaskValue":                    ((0x18, 4), (8 + 28, 4), "UINT32"),
#
#    ConsoleSourceRef ModuleRefKey;
    "Tag.ModuleRefKey":                 ((0x1C, 4), (8 + 32, 8), "ConsoleSourceRef"),
#    UINT64 Timestamp;
    "Tag.Timestamp":                    ((0x20, 8), (8 + 40, 8), "UINT64"),
#    BOOLEAN AppendNewline;
    "Tag.AppendNewline":                ((0x28, 4), (8 + 48, 4), "BOOLEAN"),
#} CoreLogTextTag;


#    UINTN StrBytes;
    "StrBytes":                     ((0x30, 4), (64, 8), "UINTN"),
#    CHAR8 Str[];
    "Str":                          ((0x38, 1), (72, 1), "CHAR8 []"),
#} TextPkt;
}

EFI_MODULE_INFO_Dict = {
#typedef struct _ConsoleSourceInfo {
#    UINTN Signature;
    "Signature":                    ((0, 4),  (0, 8), "UINTN"),
#    SourceType Type;
    "Type":                         ((4, 4),  (8, 8), "UINTN"),
#    ModuleLoggingInfo *Info;
    "Info":                         ((8, 4),  (0x10, 8), "ModuleLoggingInfo *"),
#    DbgLogMaskMap DbgMaskHashTbl[sizeof(DebugLogMask) * 8];
    "DbgMaskHashTbl":               ((0xc, 4),  (0x18, 8), "DbgLogMaskMap **"),
#    ImageInfoEntry *ParentImage;
    "ParentImage":                  ((0x8c, 4),  (0x98, 8), "ImageInfoEntry *"),
#    EFI_LIST_ENTRY Entry;
#    EFI_LIST_ENTRY ModuleEntry;
#    EFI_LIST_ENTRY RouteLists[LOG_TYPE_MAX];
#    BOOLEAN RouteMaskedList[LOG_TYPE_MAX];
#    BOOLEAN AlwaysRoutedModule;
#    BOOLEAN ExcludeFromFormatting;
    "ExcludeFromFormatting":      ((0xF5, 1),  (0x169, 1), "BOOLEAN"),
#    BOOLEAN IsLibrary;
#    SourceType Type;
#    struct _ConsoleSourceInfo *SimilarModule;     /* If NULL, has no similar modules. If == self, then this is the main module in the group of similarly named modules. If != self && !NULL, this is a module in the group of similar named modules */
#} ModuleInfoEntry;
}

EFI_MODULE_LOGGING_INFO_Dict = {
    "ModuleName":                 ((0, 4), (0, 8), "CHAR8*"),
#typedef struct {
#    CHAR8 *ModuleName;              // Name of the module for which verbosity levels are being exported
#    DebugLogMaskInfo *MaskList;     // List of all the different debug masks
#    UINTN NumMasks;                 // Number of debug log masks as pointed to by "MaskList"
#    UINT32 GlobalDebugLevels[NUM_GLOBAL_DEBUG_LEVELS];      // Mapping from debug masks to global debug levels
#} ModuleLoggingInfo;
}

EFI_HOB_MEMORY_MAP_INFO_Dict = {
#typedef struct {
#    EFI_HOB_GENERIC_HEADER          Header;
    "Header":                 ((0, 8), (0, 8), "EFI_HOB_GENERIC_HEADER"),
#    EFI_PHYSICAL_ADDRESS            GcdMemorySpaceMap;
    "GcdMemorySpaceMap":      ((8, 8), (8, 8), "EFI_PHYSICAL_ADDRESS"),
#    EFI_PHYSICAL_ADDRESS            MemoryMap;
    "MemoryMap":              ((16, 8), (16, 8), "EFI_PHYSICAL_ADDRESS"),
#    EFI_PHYSICAL_ADDRESS            GcdMemorySpaceLock;
    "GcdMemorySpaceLock":     ((24, 8), (24, 8), "EFI_PHYSICAL_ADDRESS"),
#    EFI_PHYSICAL_ADDRESS            MemoryLock;
    "MemoryLock":             ((32, 8), (32, 8), "EFI_PHYSICAL_ADDRESS"),
#    UINT8                           PageShift;
    "PageShift":              ((40, 1), (40, 1), "UINT8"),
#} EFI_HOB_MEMORY_MAP_INFO;
}

DataStructureDict = {
   "EFI_TABLE_HEADER":                       EFI_TABLE_HEADER_Dict,
   "EFI_SYSTEM_TABLE_POINTER":               EFI_SYSTEM_TABLE_POINTER_Dict,
   "EFI_GUID":                               EFI_GUID_Dict,
   "EFI_PANIC_BUFFER":                       EFI_PANIC_BUFFER_Dict,
   "APPLE_STACK_DESC":                       APPLE_STACK_DESC_Dict,
   "EFI_SYSTEM_TABLE":                       EFI_SYSTEM_TABLE_Dict,
   "EFI_CONFIGURATION_TABLE":                EFI_CONFIGURATION_TABLE_Dict,
   "EFI_DEBUG_IMAGE_INFO_TABLE_HEADER":      EFI_DEBUG_IMAGE_INFO_TABLE_HEADER_Dict,
   "EFI_DEBUG_IMAGE_INFO_NORMAL":            EFI_DEBUG_IMAGE_INFO_NORMAL_Dict,
   "EFI_LOADED_IMAGE_PROTOCOL":              EFI_LOADED_IMAGE_PROTOCOL_Dict,
   "EFI_IMAGE_DATA_DIRECTORY":               EFI_IMAGE_DATA_DIRECTORY_Dict,
   "EFI_TE_IMAGE_HEADER":                    EFI_TE_IMAGE_HEADER_Dict,
   "EFI_IMAGE_DOS_HEADER":                   EFI_IMAGE_DOS_HEADER_Dict,
   "EFI_IMAGE_NT_HEADERS":                   EFI_IMAGE_NT_HEADERS_Dict,
   "EFI_IMAGE_SECTION_HEADER":               EFI_IMAGE_SECTION_HEADER_Dict,
   "EFI_IMAGE_DEBUG_DIRECTORY_ENTRY":        EFI_IMAGE_DEBUG_DIRECTORY_ENTRY_Dict,
   "EFI_IMAGE_BASE_RELOCATION":              EFI_IMAGE_BASE_RELOCATION_Dict,
   "EFI_IMAGE_DEBUG_CODEVIEW_MTOC_ENTRY":    EFI_IMAGE_DEBUG_CODEVIEW_MTOC_ENTRY_Dict,
   "APPLE_DEBUG_INFO_TABLE":                 APPLE_DEBUG_INFO_TABLE_Dict,
   "EFI_DEBUG_IMAGE_INFO":                   EFI_DEBUG_IMAGE_INFO_Dict,
   "EFI_HOB_GENERIC_HEADER":                 EFI_HOB_GENERIC_HEADER_Dict,
   "EFI_HOB_MEMORY_ALLOCATION_HEADER":       EFI_HOB_MEMORY_ALLOCATION_HEADER_Dict, 
   "EFI_HOB_HANDOFF_INFO_TABLE":             EFI_HOB_HANDOFF_INFO_TABLE_Dict,
   "EFI_HOB_MEMORY_ALLOCATION":              EFI_HOB_MEMORY_ALLOCATION_Dict,
   "EFI_HOB_RESOURCE_DESCRIPTOR":            EFI_HOB_RESOURCE_DESCRIPTOR_Dict,
   "EFI_HOB_GUID_TYPE":                      EFI_HOB_GUID_TYPE,
   "EFI_HOB_FIRMWARE_VOLUME":                EFI_HOB_FIRMWARE_VOLUME_Dict, 
   "EFI_HOB_CPU":                            EFI_HOB_CPU_Dict,
   "EFI_HOB_BUILD_ID":                       EFI_HOB_BUILD_ID_Dict,
   "EFI_HOB_SYSTEM_TABLE":                   EFI_HOB_SYSTEM_TABLE_Dict,
   "EFI_HOB_MEMORY_ALLOCATION_MODULE":       EFI_HOB_MEMORY_ALLOCATION_MODULE_Dict, 
   "EFI_HOB_CONSOLE_BUFFER":                 EFI_HOB_CONSOLE_BUFFER_Dict,
   "EFI_HOB_RAMLOG_BUFFER":                  EFI_HOB_RAMLOG_BUFFER_Dict,
   "EFI_HOB_END_OF_HOB_LIST":                EFI_HOB_END_OF_HOB_LIST_Dict,
   "EFI_APPLE_DEBUG_SUPPORT":                EFI_APPLE_DEBUG_SUPPORT_Dict,
   "EFI_APPLE_IMAGE_RANGE":                  EFI_APPLE_IMAGE_RANGE_Dict,
   "EFI_CONTIG_RING_BUFFER":                 EFI_CONTIG_RING_BUFFER_Dict,
   "EFI_FORENSICS_BUFFER":                   EFI_FORENSICS_BUFFER_Dict,
   "EFI_CORE_LOG_TEXT_TAG":                  EFI_CORE_LOG_TEXT_TAG_Dict,
   "EFI_TEXT_TAG":                           EFI_TEXT_TAG_Dict,
   "EFI_TEXT_PKT":                           EFI_TEXT_PKT_Dict,
   "EFI_TEXT_HDR_PKT":                       EFI_TEXT_PKT_HDR_Dict,
   "EFI_MODULE_INFO":                        EFI_MODULE_INFO_Dict,
   "EFI_MODULE_LOGGING_INFO":                EFI_MODULE_LOGGING_INFO_Dict,
   "EFI_HOB_MEMORY_MAP_INFO":                EFI_HOB_MEMORY_MAP_INFO_Dict,
}


#
# Worker functions for the DataStructureDict dictionaries
#

def BestMatchDataStructDictKey (Dict, Member):
#
# Key for array types look like Array[10]
# Key for other types looks like Name
# Caller will always use Name form so make sure Array matches Array[10]
#
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict

  try:
    if not Member in Dict:
      # test for Member ABC, but key ABC[4]
      for key in Dict:
        if key.startswith(Member):
          ProcessedKey = key
          break
    else:
      ProcessedKey = Member

    return Dict[ProcessedKey]
  except:
    return ((0, 0), (0, 0), "")

def GetDataStructureMemberType (Dict, Member):
  #
  #
  #
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict


  ((Offset32, Size32), (Offset64, Size64), Type) = BestMatchDataStructDictKey (Dict, Member)
  return Type

def GetDataStructureMemberOffset (Dict, Member, Width):
  #
  #
  #
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict

  ((Offset32, Size32), (Offset64, Size64), Type) = BestMatchDataStructDictKey (Dict, Member)
  return Offset64 if Width == 8 else Offset32


def GetDataStructureSize (Dict, Width):
  #
  #
  #
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict

  # dictionaries have no order so put the structure into a list
  StructList = []
  for key, ((Offset32, Size32), (Offset64, Size64), Type) in Dict.items():
    StructList.append (((Offset32, Size32), (Offset64, Size64), Type , key))


  # Offset32 was first to make sort do the right thing
  StructList.sort()

  # grab last item on the list
  ((Offset32, Size32), (Offset64, Size64), Type, key) = StructList[-1]

  # If last element is an array we have some extra math to do
  TypeList = key.replace(']','[').split('[')
  if len(TypeList) > 1:
    ArrayAdjust = int(TypeList[1])
  else:
    ArrayAdjust = 1

  if Width == 8:
    return Offset64 + (Size64 * ArrayAdjust)
  else:
    return Offset32 + (Size32 * ArrayAdjust)


def GetDataStaructureArrayAddress (Dict, Member, Address, Index=0):
  #
  # Return (Address, Offset, Size) of array element
  #
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict
  Width = classes.GTarget.addr_size

  try:
    ((Offset32, Size32), (Offset64, Size64), Type) = BestMatchDataStructDictKey (Dict, Member)

    if Width == 4:
      Offset, Size = Offset32, Size32
    elif Width == 8:
      Offset, Size = Offset64, Size64
    else:
      classes.GError.SetErrorToGenericError()

    if Size == 0:
      # the Dict works like a union for 32/64 bits structs. So a struct may not exist
      # on one side
      return (0, 0, 0)

    Offset += (Index * Size)
    Address += Offset
    return (Address, Offset, Size)
  except:
    return (0, 0, 0)


def ReadDataStructureArrayElement (Dict, Member, Address, Index):
  #
  # duck type return of data from an EFI structure
  #  <= 4 byte int.
  #  <= 8 bytes long.
  #   > 8 bytearray. String where every ascii char is really a byte.
  # return (Data, Offset, SizeofElement)
  #
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict

  try:
    (Address, Offset, Size) = GetDataStaructureArrayAddress (Dict, Member, Address, Index)
    if Address == 0 or classes.GError.Fail():
      return (0, 0, 0)

    if Size > 8:
      Data = bytearray(classes.GTarget.process.ReadMemory (Address, Size, classes.GError))
    else:
      Data = classes.GTarget.process.ReadUnsignedFromMemory (Address, Size, classes.GError)
    return (Data, Offset, Size)

  except:
    classes.GError.SetErrorToGenericError()
    return (0, 0, 0)


def ReadDataStructureMember (Dict, Member, Address):
  #
  # duck type return of data from an EFI structure
  #  <= 4 byte int.
  #  <= 8 bytes long.
  #   > 8 bytearray. String where every ascii char is really a byte.
  # return Data
  assert isinstance(Dict, dict),  "Dict is not a dictionary: %s" % Dict
  
  (Data, Offset, Size) = ReadDataStructureArrayElement (Dict, Member, Address, 0)
  return Data

def DataByteArrayOrUintToString (Data, Size, TypeString="", DefaultHex=True):
  #
  # Output formater to use with ReadDataStructureArrayElement() and ReadDataStructureMember()
  #

  if TypeString == "EFI_GUID" and Size == 16:
    return GuidToCStructStr (Data)
  elif TypeString in DataStructEnumDict:
    return DataStructEnumDict[TypeString].get (Data, "Unknown")
  elif DefaultHex:
    if isinstance (Data, bytearray):
      # bytearray is string where every char is a byte.
      # treat each byte in byte array as int and return a long hex string
      return "%s" %  ''.join('0x%02x ' % byte for byte in Data)
    else:
      return "0x%0*x" %  ((Size*2), Data)

def PrintDataStructure(debugger, result, internal_dict_name, Address, indent=''):
   #
   # dump info on structure
   #
   #

   try:
      Dict = DataStructureDict[internal_dict_name]
   except KeyError:
      result.PutCString("Could not find %s" % internal_dict_name)
      return

   SBError = lldb.SBError()
   KeyWidth  = max(len(key) for key in Dict.keys())
   TypeWidth = max(len(Type) for key, ((Offset32, Size32), (Offset64, Size64), Type)  in Dict.iteritems())

   # dictionaries have no order so put the structure into a list
   StructList = []
   for key, ((Offset32, Size32), (Offset64, Size64), Type) in Dict.items():
      StructList.append (((Offset32, Size32), (Offset64, Size64), Type , key))

   # Offset32 was first to make sort do the right thing
   StructList.sort()
   SBTarget  = debugger.GetTargetAtIndex(0)

   result.PutCString("%s(0x%x):" % (internal_dict_name, Address))
   for (Offset32, Size32), (Offset64, Size64), Type , key in StructList:
      TypeList = key.replace(']','[').split('[')
      if len(TypeList) > 1:
         result.PutCString (indent + "\t%s(%s) {" % (key, Type))
         for i in range(int(TypeList[1])):
            (ArrayData, ArrayOffset, ElementSize) = ReadDataStructureArrayElement (Dict, key, Address, i)
            result.PutCString (indent + "\t\t0x%08x: 0x%x" % (Address + ArrayOffset, ArrayData))
         result.PutCString (indent + "\t}")
      else:
         Offset = Offset64 if SBTarget.addr_size == 8 else Offset32
         #String!!
         if Type in ['CHAR8*', 'STRING']:
            result.PutCString (indent + "\t%s(String): " % key)
            StringLoc = SBTarget.process.ReadPointerFromMemory(Address + Offset, SBError)
            String = read_string_from_mem(StringLoc)

            result.PutCString(indent + "\t\t0x%08x: (0x%08x)%s" % (Address + Offset, StringLoc, String))
         else:
            Offset = Offset64 if SBTarget.addr_size == 8 else Offset32
            #check to see if the type is another dictionary type
            if Type in DataStructureDict.keys():
               result.Print(indent + "\t%s:" % key)
               PrintDataStructure(debugger, result, Type, Address + Offset, indent+'\t')
               continue 
            # straight type
            (Data, Offset, Size) = ReadDataStructureArrayElement (Dict, key, Address, 0)
            DataStr = DataByteArrayOrUintToString (Data, Size, Type)
            result.PutCString(indent + "\t%s(%s):" % (key, Type))
            result.PutCString (indent + "\t\t0x%08x: %s" % (Address + Offset, DataStr))

   return

def ReadDataStructureString(Dict, Key, Addr):
   TypeList = Key.replace(']','[').split('[')
   string = []
   for i in range(int(TypeList[1])):
      (ArrayData, ArrayOffset, ElementSize) = ReadDataStructureArrayElement (Dict, Key, Addr, classes.GTarget.addr_size, i)
      if ArrayData == 0: break
      string.append(chr(ArrayData))
   return ''.join(string)

def read_string_from_mem(Addr, MaxLen=256):
   String = classes.GTarget.process.ReadCStringFromMemory(Addr, MaxLen, classes.GError)
   if classes.GError.Success():
      return String
   else:
      print 'error: ', classes.GError
      return None

def read_memory_block(Addr, Len):
   Contents = classes.GTarget.process.ReadMemory(Addr, Len, classes.GError)
   if classes.GError.Success():
      return Contents
   else:
      print 'error: ', classes.GError
      return None

def GuidToStr (guid, Name=False, OnlyName=False):
  #
  # Convert a 16-byte bytesarry (or bytearray compat object) to GUID string or name
  # B402621F-A940-1E4A-866B-4DC9162B347C
  #
  # Name=True means lookup name in GuidNameDict and us it if you find it
  # OnlyName=Ture means return "" if Name lookup failed.
  #
  global GuidNameDict

  if not isinstance (guid, bytearray):
    # convert guid object to UUID, and UUID to bytearray
    Uuid = uuid.UUID(guid)
    guid = bytearray (Uuid.bytes_le)

  Str = "%02.2X%02.2X%02.2X%02.2X-%02.2X%02.2X-%02.2X%02.2X-%02.2X%02.2X-%02.2X%02.2X%02.2X%02.2X%02.2X%02.2X" % \
        (guid[3], guid[2], guid[1],  guid[0],  guid[5],  guid[4],  guid[7],  guid[6], guid[8], guid[9], guid[10], guid[11], guid[12], guid[13], guid[14], guid[15])

  if Name:
    if Str in GuidNameDict:
      return GuidNameDict[Str]
    if Str in GuidFileNameDict:
      return GuidFileNameDict[Str]

  if OnlyName:
    return ""
  return Str
