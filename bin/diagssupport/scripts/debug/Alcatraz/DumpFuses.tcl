namespace path ::astris::console::native

#
# Parse Alcatraz fuse information
#

# author    'Matthew Fong (mattfong@apple.com)'
# version   '5'
# date      '2013-07-11'
# copyright 'Copyright (c) 2013 Apple Inc.'
# license   'Apple Internal'


####################################################################
# Constants
####################################################################

# Power Manager (PMGR) base register addresses
#     c.f. Alcatraz Micro Architecture Specification, Table 44: Alcatraz PIO Address Map (p. 96, Rev 0.62)
set ::bPMGR         0x20e000000

#     c.f. PMGR Register Specification, Section 1: PMGR Address Map (p. 1, Version 6.6.0)
set ::bPMGRFuse     0x2a000

# Fuse register offsets
#     c.f. PMGR Register Specification, Section 1.26: Fuse Register Overview (p. 197, Version 6.60)
set ::oCFG_FUSE0    0x0
set ::oCFG_FUSE1    0x4
set ::oCFG_FUSE2    0x8
set ::oCFG_FUSE3    0xc
set ::oCFG_FUSE4    0x10
set ::oCFG_FUSE5    0x14
set ::oECID_FUSE0   0x20
set ::oECID_FUSE1   0x24

# Cyclone Memory-Mapped System Registers (CCC) base register addresses
#     c.f. Alcatraz Micro Architecture Specification, Table 44: Alcatraz PIO Address Map (p. 89, Rev 0.62)
set ::bCCC          0x202000000

#     c.f. CCC Register Specification, Section 1: CCC Address Map (p. 1, Release 580242)
set ::bCCCPwrCtl    0x220000

# Fuse register offsets
#     c.f. CCC Register Specification, Section 1.17: ccc_PWRCTL Register Overview (p. 215, Release 580242)
set ::oEFUSE_DVFM0  0xa8
set ::oEFUSE_DVFM1  0xb0

# GPIO base register addresse
#     c.f. Alcatraz Micro Architecture Specification, Table 44: Alcatraz PIO Address Map (p. 96)
#     c.f. Table 23 Alcatraz Power Manager Micro Architecture Specification (p.141)
#     c.f. Section 1.1.95 GPIO Registers
set ::bGPIO         0x20e300000


####################################################################
# Functions
####################################################################

#
# read32
# Read a 32-bit register
#
proc read32 {address} {
    set register [mem -memap 4 $address]
    return $register
}


#
# write32
# Write a 32-bit register
#
proc write32 {address value} {
    mem -memap 4 $address $value
}


#
# GetDeviceData
# c.f. Alcatraz Text Plan Internal, Section 7.2 Alcatraz Configuration Fuses, Table 31: Alcatraz Configuration Fuse Assignment for B0 Discrete (p. 43, Rev 1.18)
# c.f. Alcatraz Text Plan Internal, Section 7.2 Alcatraz Configuration Fuses, Table 33: Detailed fuse assignment of Fuse Revision for B0 from Alcatraz Configuration Fuse ROM (p. 45, Rev 1.18)
# c.f. Alcatraz Text Plan Internal, Section 7.2 Alcatraz Configuration Fuses, Table 34: The Detailed Fuse Assignment of Device Version from Alcatraz Configuration Fuse ROM (p. 45, Rev 1.18)
# c.f. PMGR Register Specification, Section 1.26.1: PMGR_FUSE_CFG_FUSE0 (p. 198, Version 6.6.0)
#
proc GetDeviceData {addrCFGFuse0} {
    set kDeviceVersion {
        0   "A0"
        1   "A1"
        2   "A2"
        3   "A3"
        4   "A4"
        5   "A5"
        8   "B0"
        9   "B1"
        10  "B2"
        11  "B3"
        12  "B4"
        13  "B5"
        16  "C0"
        17  "C1"
    }
    
    set kPartID {
        0 "POP"
        1 "Discrete"
    }
    
    set kSOCFusing {
        POP {
            0   "B06"
            2   "B09"
            3   "B12"
        }
        Discrete {
            0   "B20"
            2   "B22"
            3   "B24"
        }
    }
    
    # Set minimum version for SOC fusing
    set kMinDeviceVersion   8
    
    set cfgFuse0 [read32 $addrCFGFuse0]
    
    set productionMode  [expr {($cfgFuse0 & 0x00000001)}]
    set secureMode      [expr {($cfgFuse0 & 0x00000002) >> 1}]
    set boardID         [expr {($cfgFuse0 & 0x00000030) >> 4}]
    set partID          [expr {($cfgFuse0 & 0x00030000) >> 16}]
    set fuseRevision    [expr {($cfgFuse0 & 0x003C0000) >> 18}]
    set deviceVersion   [expr {($cfgFuse0 & 0x0FC00000) >> 22}]
    
    set socFusing       [expr {($secureMode << 1) | $productionMode}]
    
    puts [format "\n#### Fuse/Device information"]
    puts [format "CFG_FUSE0: 0x%08x" $cfgFuse0]
    
    puts [format "productionMode: 0x%01x" $productionMode]
    puts [format "secureMode    : 0x%01x" $secureMode]
    puts [format "boardID       : 0x%01x" $boardID]
    puts [format "partID        : 0x%01x (%s)" $partID [dict get $kPartID $partID]]
    puts [format "fuseRevision  : 0x%02x" $fuseRevision]
    puts [format "deviceVersion : 0x%02x (%s)" $deviceVersion [dict get $kDeviceVersion $deviceVersion]]
    if {$deviceVersion >= $kMinDeviceVersion} {
        puts [format "socFusing     : 0x%02x (%s)" $socFusing [dict get $kSOCFusing [dict get $kPartID $partID] $socFusing]]
    }
    
    return $partID
}


#
# GetECIDData
# Get the data stored in the ECID
# c.f. Alcatraz Text Plan Internal, Section 7.1 ECID Fuses (p. 39, Rev 1.18)
#
proc GetECIDData {addrECIDFuse0 addrECIDFuse1} {
    set kFabLocation {
        2 "Dresden (GF Fab1)"
        1 "Austin (S2 line)"
        0 "GiHeung (S1 line)"
    }
    
    set ecidFuse0 [read32 $addrECIDFuse0]
    set ecidFuse1 [read32 $addrECIDFuse1]
    
    set rawDEID  [expr {($ecidFuse1 & 0x000003FF) << 32 | $ecidFuse0}]
    set lotID    [expr {($rawDEID & 0x000001FFFFF)}]
    set waferNum [expr {($rawDEID & 0x00003E00000) >> 21}]
    set xPosH    [expr {($rawDEID & 0x000FC000000) >> 26}]
    set xPosL    [expr {($rawDEID & 0x00300000000) >> 32}]
    set yPos     [expr {($rawDEID & 0x3FC00000000) >> 34}]
    
    set fabLocationRaw [expr {($ecidFuse1 & 0x00001C00) >> 10}]
    
    puts [format "\n#### Wafer information"]
    puts [format "ECID_FUSE0: 0x%08x" $ecidFuse0]
    puts [format "ECID_FUSE1: 0x%08x" $ecidFuse1]
    
    puts [format "DEID        : 0x%011x" $rawDEID]
    puts [format "    LotID   : 0x%06x" $lotID]
    puts [format "    WaferNum: 0x%02x" $waferNum]
    puts [format "    XPosH   : 0x%02x" $xPosH]
    puts [format "    XPosL   : 0x%01x" $xPosL]
    puts [format "    YPos    : 0x%02x" $yPos]
    
    puts [format "Fab Location: %s" [dict get $kFabLocation $fabLocationRaw]]
}


#
# GetIdsData
# Get the Ids from the CFG fuses
# c.f. Alcatraz Text Plan Internal, Section 7.2 Alcatraz Configuration Fuses, Table 30, 31: Alcatraz Configuration Fuse Assignment for B0 {POP, Discrete} (p. 37, Rev 1.18)
#
proc GetIdsData {addrCFGFuse4 addrCFGFuse5} {
    set kIdsCPUFactor 1.0
    set kIdsSOCFactor 1.0
    set kIdsGPUFactor 1.0
    set kIdsCPUSRAMFactor 1.0
    set kIdsSOCSRAMFactor 1.0
    
    set cfgFuse4 [read32 $addrCFGFuse4]
    set cfgFuse5 [read32 $addrCFGFuse5]
    
    set rawIds [expr {($cfgFuse5 << 1) | ($cfgFuse4 & 0x80000000) >> 31}]
    set IdsCPU     [expr {($rawIds & 0x0000001FF)}]
    set IdsSOC     [expr {($rawIds & 0x00001FE00) >> 9}]
    set IdsGPU     [expr {($rawIds & 0x001FE0000) >> 17}]
    set IdsCPUSRAM [expr {($rawIds & 0x01E000000) >> 25}]
    set IdsSOCSRAM [expr {($rawIds & 0x1E0000000) >> 29}]
    
    puts [format "\n#### Ids information"]
    puts [format "CFG_FUSE4: 0x%08x" $cfgFuse4]
    puts [format "CFG_FUSE5: 0x%08x" $cfgFuse5]
    
    puts [format "IdsCPU     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%03x)" [expr {$kIdsCPUFactor * ($IdsCPU + 1)}] $IdsCPU]
    puts [format "IdsSOC     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%02x)" [expr {$kIdsSOCFactor * ($IdsSOC + 1)}] $IdsSOC]
    puts [format "IdsGPU     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%02x)" [expr {$kIdsGPUFactor * ($IdsGPU + 1)}] $IdsGPU]
    puts [format "IdsCPUSRAM @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%1x)" [expr {$kIdsCPUSRAMFactor * ($IdsCPUSRAM + 1)}] $IdsCPUSRAM]
    puts [format "IdsSOCSRAM @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%1x)" [expr {$kIdsSOCSRAMFactor * ($IdsSOCSRAM + 1)}] $IdsSOCSRAM]
}


#
# GetBinningData
# Get the bin data from the CFG and DVFM fuses
# c.f. Alcatraz Text Plan Internal, Section 11 Binning Fuse Information (p. 67, Rev 1.18)
#
proc GetBinningData {addrCFGFuse1 addrDVFMFuse0 addrDVFMFuse1 partID} {
    # POP and discrete packages have the same binning tables, but differ in leakage. Will keep separate in case additional information is needed.
    set kBinMapping {
        gpuP3 {
            "speed" " 450 MHz"
            "0x5a"  "Bin 100"
            "0x53"  "Bin 200"
            "0x4c"  "Bin 300"
            "0x46"  "Bin 400"
        }
        gpuP2 {
            "speed" " 390 MHz"
            "0x4b"  "Bin 10"
            "0x45"  "Bin 20"
            "0x3f"  "Bin 30"
            "0x39"  "Bin 40"
        }
        gpuP1 {
            "speed" " 330 MHz"
            "0x3f"  "Bin 1"
            "0x39"  "Bin 2"
            "0x32"  "Bin 3"
            "0x2c"  "Bin 4"
        }
        soc {
            "0x46"  "Bin 1"
            "0x42"  "Bin 2"
            "0x3e"  "Bin 3"
            "0x3a"  "Bin 4"
        }
        cpuP9 {
            "speed" "1392 MHz"
            "0x78"  "Bin 100000"
            "0x72"  "Bin 200000"
            "0x6d"  "Bin 300000"
            "0x69"  "Bin 400000"
        }
        cpuP7 {
            "speed" "1296 MHz"
            "0x73"  "Bin 10000"
            "0x6c"  "Bin 20000"
            "0x68"  "Bin 30000"
            "0x64"  "Bin 40000"
        }
        cpuP4 {
            "speed" "1128 MHz"
            "0x60"  "Bin 1000"
            "0x5a"  "Bin 2000"
            "0x56"  "Bin 3000"
            "0x52"  "Bin 4000"
        }
        cpuP2 {
            "speed" " 840 MHz"
            "0x42"  "Bin 100"
            "0x3c"  "Bin 200"
            "0x38"  "Bin 300"
            "0x34"  "Bin 400"
        }
        cpuP1 {
            "speed" " 600 MHz"
            "0x2d"  "Bin 10"
            "0x27"  "Bin 20"
            "0x23"  "Bin 30"
            "0x1f"  "Bin 40"
        }
        cpuP5 {
            "speed" " 396 MHz"
            "0x1f"  "Bin 1"
            "0x1b"  "Bin 2"
            "0x17"  "Bin 3"
            "0x13"  "Bin 4"
        }
    }
    set cfgFuse1  [read32 $addrCFGFuse1]
    set dvfmFuse0 [read32 $addrDVFMFuse0]
    set dvfmFuse1 [read32 $addrDVFMFuse1]
    
    # Base voltage and binning fuse revision
    set baseVoltage     [expr {($dvfmFuse0 & 0x1F000000) >> 24}]
    set binFuseRev      [expr {($dvfmFuse0 & 0xE0000000) >> 29}]
    
    # CPU Bin, Mode 5
    set cpuP5ModeBin [expr {($dvfmFuse0 & 0x0000007F)}]
    
    # CPU Bin, Mode 6
    set cpuP6ModeBin [expr {($dvfmFuse0 & 0x00003F80) >> 7}]
    
    # CPU Bin, Mode 1
    set cpuP1ModeBin [expr {($dvfmFuse0 & 0x001FC000) >> 14}]
    
    # CPU Bin, Mode 2
    set cpuP2ModeBin [expr {($dvfmFuse1 & 0x0000000F) << 3 | ($dvfmFuse0 & 0x00E00000) >> 21}]
    
    # CPU Bin, Mode 3
    set cpuP3ModeBin [expr {($dvfmFuse1 & 0x000007F0) >> 4}]
    
    # CPU Bin, Mode 4
    set cpuP4ModeBin [expr {($dvfmFuse1 & 0x0003F800) >> 11}]
    
    # CPU Bin, Mode 7
    set cpuP7ModeBin [expr {($dvfmFuse1 & 0x01FC0000) >> 18}]
    
    # CPU Bin, Mode 9
    set cpuP9ModeBin [expr {($dvfmFuse1 & 0xFE000000) >> 25}]
    
    # GPU bin, Mode 1 (LP)
    set gpuP1ModeBin [expr {($cfgFuse1 & 0x0000007F)}]
    
    # GPU bin, Mode 2 (NP)
    set gpuP2ModeBin [expr {($cfgFuse1 & 0x00003F80) >> 7}]
    
    # GPU bin, Mode 3 (HP)
    set gpuP3ModeBin [expr {($cfgFuse1 & 0x001FC000) >> 14}]
    
    # SOC bin
    set socBin       [expr {($cfgFuse1 & 0x0FE00000) >> 21}]
    
    # Base voltage
    set baseVoltage_mV  [expr {($baseVoltage + 1) * 25}]
    
    # Compute SOC voltages
    set socBin_mV       [expr {$baseVoltage_mV + ($socBin * 5)}]
    set gpuP1ModeBin_mV [expr {$baseVoltage_mV + ($gpuP1ModeBin * 5)}]
    set gpuP2ModeBin_mV [expr {$baseVoltage_mV + ($gpuP2ModeBin * 5)}]
    set gpuP3ModeBin_mV [expr {$baseVoltage_mV + ($gpuP3ModeBin * 5)}]
    
    # Compute CPU voltages
    set cpuP1ModeBin_mV [expr {$baseVoltage_mV + ($cpuP1ModeBin * 5)}]
    set cpuP2ModeBin_mV [expr {$baseVoltage_mV + ($cpuP2ModeBin * 5)}]
    set cpuP3ModeBin_mV [expr {$baseVoltage_mV + ($cpuP3ModeBin * 5)}]
    set cpuP4ModeBin_mV [expr {$baseVoltage_mV + ($cpuP4ModeBin * 5)}]
    set cpuP5ModeBin_mV [expr {$baseVoltage_mV + ($cpuP5ModeBin * 5)}]
    set cpuP6ModeBin_mV [expr {$baseVoltage_mV + ($cpuP6ModeBin * 5)}]
    set cpuP7ModeBin_mV [expr {$baseVoltage_mV + ($cpuP7ModeBin * 5)}]
    set cpuP9ModeBin_mV [expr {$baseVoltage_mV + ($cpuP9ModeBin * 5)}]
    
    puts [format "\n#### Bin information"]
    puts [format "CFG_FUSE1:   0x%08x" $cfgFuse1]
    puts [format "EFUSE_DVFM0: 0x%08x" $dvfmFuse0]
    puts [format "EFUSE_DVFM1: 0x%08x" $dvfmFuse1]
    
    if {$partID} {
        puts [format "Discrete package"]
    } else {
        puts [format "POP package"]
    }
    
    if {$baseVoltage} {
        puts [format "DVFM fuse revision: %d (0x%01x)" $binFuseRev $binFuseRev]
        puts [format "Base voltage     : %4.1f mV (0x%02x)" $baseVoltage_mV $baseVoltage]
        
        puts [format "SOC bin          : %4.1f mV (0x%02x, %s)" $socBin_mV $socBin [dict get $kBinMapping soc [format "0x%02x" $socBin]]]
        puts [format "GPU bin, %s: %4.1f mV (Mode 1, 0x%02x, %s)" [dict get $kBinMapping gpuP1 "speed"] $gpuP1ModeBin_mV $gpuP1ModeBin [dict get $kBinMapping gpuP1 [format "0x%02x" $gpuP1ModeBin]]]
        puts [format "GPU bin, %s: %4.1f mV (Mode 2, 0x%02x, %s)" [dict get $kBinMapping gpuP2 "speed"] $gpuP2ModeBin_mV $gpuP2ModeBin [dict get $kBinMapping gpuP2 [format "0x%02x" $gpuP2ModeBin]]]
        puts [format "GPU bin, %s: %4.1f mV (Mode 3, 0x%02x, %s)" [dict get $kBinMapping gpuP3 "speed"] $gpuP3ModeBin_mV $gpuP3ModeBin [dict get $kBinMapping gpuP3 [format "0x%02x" $gpuP3ModeBin]]]
        
        puts [format "CPU bin, %s: %4.1f mV (Mode 5, 0x%02x, %s)" [dict get $kBinMapping cpuP5 "speed"] $cpuP5ModeBin_mV $cpuP5ModeBin [dict get $kBinMapping cpuP5 [format "0x%02x" $cpuP5ModeBin]]]
        puts [format "CPU bin, %s: %4.1f mV (Mode 1, 0x%02x, %s)" [dict get $kBinMapping cpuP1 "speed"] $cpuP1ModeBin_mV $cpuP1ModeBin [dict get $kBinMapping cpuP1 [format "0x%02x" $cpuP1ModeBin]]]
        puts [format "CPU bin, %s: %4.1f mV (Mode 2, 0x%02x, %s)" [dict get $kBinMapping cpuP2 "speed"] $cpuP2ModeBin_mV $cpuP2ModeBin [dict get $kBinMapping cpuP2 [format "0x%02x" $cpuP2ModeBin]]]
        puts [format "CPU bin, %s: %4.1f mV (Mode 4, 0x%02x, %s)" [dict get $kBinMapping cpuP4 "speed"] $cpuP4ModeBin_mV $cpuP4ModeBin [dict get $kBinMapping cpuP4 [format "0x%02x" $cpuP4ModeBin]]]
        puts [format "CPU bin, %s: %4.1f mV (Mode 7, 0x%02x, %s)" [dict get $kBinMapping cpuP7 "speed"] $cpuP7ModeBin_mV $cpuP7ModeBin [dict get $kBinMapping cpuP7 [format "0x%02x" $cpuP7ModeBin]]]
        
        if {$partID} {
            puts [format "CPU bin, %s: %3.1f mV (Mode 9, 0x%02x, %s)" [dict get $kBinMapping cpuP9 "speed"] $cpuP9ModeBin_mV $cpuP9ModeBin [dict get $kBinMapping cpuP9 [format "0x%02x" $cpuP9ModeBin]]]
        }
    } else {
        puts [format "No valid binning fuse information"]
    }
}


#
# GetGPIOAddress
# Get the register configuration address of a given GPIO
# [CODE] http://www.linuxforums.org/forum/programming-scripting/76747-tcl-string-variable-conversion.html
#
proc GetGPIOAddress {baseGPIOAddress gpioNumber} {
    return [expr {$baseGPIOAddress + ($gpioNumber * 4)}]
}


#
# GetGPIOData
# Get the register configuration from a given GPIO
#
proc GetGPIOData {baseGPIOAddress gpioNumber} {
    return [read32 [GetGPIOAddress $baseGPIOAddress $gpioNumber]]
}


#
# GetSystemBoardID
# Get the system board ID
#
proc GetSystemBoardID {baseGPIOAddress partID} {
    set kSystemBoardMaping {
        0   "N51AP"
        1   "N51DEV"
        2   "N53AP"
        3   "N53DEV"
        10  "J85AP"
        11  "J85DEV"
        12  "J86AP"
        13  "J86DEV"
        14  "J87AP"
        15  "J87DEV"
        16  "J71AP"
        17  "J71DEV"
        18  "J72AP"
        19  "J72DEV"
        20  "J73AP"
        21  "J73DEV"
        22  "J34AP"
        23  "J34DEV"
    }
    
    set kPullDisableMask    0xFFFFFF7F
    set kInputEnableMask    0x00000200
    
    set shiftBy         0
    set systemBoardID   0
    
    # Board ID bit to SOC GPIOs mapping for all Alcatraz-based products:
    #     Bit 0: GPIO 72
    #     Bit 1: GPIO 73
    #     Bit 2: GPIO 74
    #     Bit 3: GPIO 18
    foreach {i} {72 73 74 18} {
        # Read GPIO, modify, and write
        #     Disable PE bit (bit 7) to prevent pull-up or pull-down from interfering with read
        #     Enable IE bit (bit 9) to enable GPIO input
        write32 [GetGPIOAddress $baseGPIOAddress $i] [expr {[GetGPIOData $baseGPIOAddress $i] & $kPullDisableMask | $kInputEnableMask}]
        set gpioRegister [GetGPIOData $baseGPIOAddress $i]
        
        # GPIO input value in stored in bit 0
        set bit0Value [expr {$gpioRegister & 0x00000001}]
        
        # Shift bit to proper position and OR with current value of systemBoardID
        set systemBoardID [expr {$systemBoardID | ($bit0Value << $shiftBy)}]
        
        # Increment shiftBy
        set shiftBy [expr {$shiftBy + 1}]
    }
    
    # Or the partID (POP or discrete) to get a proper system board ID
    set systemBoardID [expr {$systemBoardID | ($partID << $shiftBy)}]
    
    puts [format "systemBoardID : 0x%02x (%s)" $systemBoardID [dict get $kSystemBoardMaping $systemBoardID]]
}


####################################################################
# main
####################################################################
set rCFG_FUSE0 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE0}]
set partID [GetDeviceData $rCFG_FUSE0]

GetSystemBoardID $::bGPIO $partID

set rECID_FUSE0 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE0}]
set rECID_FUSE1 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE1}]
GetECIDData $rECID_FUSE0 $rECID_FUSE1

set rCFG_FUSE4 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE4}]
set rCFG_FUSE5 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE5}]
GetIdsData $rCFG_FUSE4 $rCFG_FUSE5

set rCFG_FUSE1   [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE1}]
set rEFUSE_DVFM0 [expr {$::bCCC + $::bCCCPwrCtl + $::oEFUSE_DVFM0}]
set rEFUSE_DVFM1 [expr {$::bCCC + $::bCCCPwrCtl + $::oEFUSE_DVFM1}]
GetBinningData $rCFG_FUSE1 $rEFUSE_DVFM0 $rEFUSE_DVFM1 $partID

