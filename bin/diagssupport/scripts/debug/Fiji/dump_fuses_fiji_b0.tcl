namespace path ::astris::console::native

package require Tclx

#
# Parse Fiji fuse information
#

# author    'Jake Albert (jake_albert@apple.com)'
# version   '1'
# date      '2013-12-05'
# copyright 'Copyright (c) 2013 Apple Inc.'
# license   'Apple Internal'

global env
if { [info exists env(RACK_OUTPUT_DIR)] } {
    variable outfd [open $env(RACK_OUTPUT_DIR)/dump_fuses.out w]
} else {
    variable outfd [dup stdout]
}

explore -aponly


####################################################################
# Constants
####################################################################

# Power Manager (PMGR) base register addresses
#     c.f. Fiji Micro Architecture Specification, Table 56: Fiji PIO Address Map (p. 119, Rev 1.03)
set ::bPMGR         0x20e000000

#     c.f. PMGR Register Specification, Section 1: PMGR Address Map (Version 5.2.0)
set ::bPMGRFuse     0x2a000

# Fuse register offsets
#     c.f. PMGR Register Specification, Section 1.28: Fuse Register Overview (Version 5.2.0)
set ::oCFG_FUSE0    0x0
set ::oCFG_FUSE1    0x4
set ::oCFG_FUSE2    0x8
set ::oCFG_FUSE3    0xc
set ::oCFG_FUSE4    0x10
set ::oCFG_FUSE5    0x14
set ::oCFG_FUSE6    0x18
set ::oCFG_FUSE7    0x1c
set ::oCFG_FUSE8    0x20
set ::oCFG_FUSE9    0x24
set ::oCFG_FUSE10   0x28
set ::oCFG_FUSE11   0x2c
set ::oCFG_FUSE12   0x30
set ::oCFG_FUSE13   0x34
set ::oCFG_FUSE14   0x38
set ::oCFG_FUSE15   0x3c
set ::oECID_FUSE0   0x80
set ::oECID_FUSE1   0x84
set ::oECID_FUSE2   0x88
set ::oECID_FUSE3   0x8c
set ::oECID_FUSE4   0x90
set ::oECID_FUSE5   0x94
set ::oECID_FUSE6   0x98
set ::oECID_FUSE7   0x9c

# Cyclone Memory-Mapped System Registers (CCC) base register addresses
#     c.f. Fiji Micro Architecture Specification, Table 44: Fiji PIO Address Map (p. 112, Rev 1.03)
set ::bCCC          0x202000000

#     c.f. CCC Register Specification, Section 1: CCC Address Map (Version 772488)
set ::bCCCPwrCtl    0x220000

# Fuse register offsets
#     c.f. CCC Register Specification, Section 1.17: ccc_PWRCTL Register Overview (Release 772488)
set ::oEFUSE_DVFM0  0x0a8
set ::oEFUSE_DVFM1  0x100
set ::oEFUSE_REV    0x0b0


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
# GetDeviceData
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 25: Fiji Configuration Fuse Assignment A (No Secure Storage) (p. 106, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 26: Fiji Configuration Fuse Assignment B (EEPROM) (p. 111, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 27: Fiji Configuration Fuse Assignment C (SE SPI) (p. 116, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 28: Fiji Configuration Fuse Assignment D (Encryted Tunnel) (p. 120, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 29: Detailed fuse assignment of Fuse Revision in Configuration Fuse Block (p. 125, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 30: The Detailed Fuse Assignment of Device Version from Fiji Configuration Fuse ROM (p. 125, Rev 1.0)
# c.f. PMGR Register Specification, Section 1.28.1: PMGR_FUSE_CFG_FUSE0 (Version 5.2.0)
#
proc GetDeviceData {cfgFuse0 cfgFuse4} {
    variable outfd

    set kFuseRevision {
        0   "Default"
        1   "Correct efuse addressing scheme"
        2   "Corners, IDS @ 0.95V"
        3   "SS Corners, 11/04/2013"
        4   "B0 no binning, IDS @ CPU=0.88V"
        5   "B0, IDS @ 0.95V"
        47  "A0, Bring-Up"
    }

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
        47  "A0, Bring-Up"
    }
    set productionMode  [expr {($cfgFuse0 & 0x00000001)}]
    set secureMode      [expr {($cfgFuse0 & 0x00000002) >> 1}]
    set securityDomain  [expr {($cfgFuse0 & 0x0000000c) >> 2}]
    set boardID         [expr {($cfgFuse0 & 0x00000070) >> 4}]
    set secureElement   [expr {($cfgFuse0 & 0x00000180) >> 7}]
    set minimumEpoch    [expr {($cfgFuse0 & 0x0000fe00) >> 9}]
    set partID          [expr {($cfgFuse0 & 0x00030000) >> 16}]

    set fuseRevision    [expr {($cfgFuse4 & 0x0000003f) >> 0}]
    set deviceVersion   [expr {($cfgFuse4 & 0x003f0000) >> 16}]
    
    puts $outfd [format "\n#### Device information"]

    puts $outfd [format "productionMode : 0x%01x" $productionMode]
    puts $outfd [format "secureMode     : 0x%01x" $secureMode]
    puts $outfd [format "securityDomain : 0x%01x" $securityDomain]
    puts $outfd [format "boardID        : 0x%01x" $boardID]
    puts $outfd [format "secureElement  : 0x%01x" $secureElement]
    puts $outfd [format "minimumEpoch   : 0x%02x" $minimumEpoch]
    puts $outfd [format "partID         : 0x%01x" $partID]

    if { [dict exists $kFuseRevision $fuseRevision] == true } {
	set fuseRevisionStr [dict get $kFuseRevision $fuseRevision]
    } else {
	set fuseRevisionStr "unknown revision"
    }
    puts $outfd [format "fuseRevision   : 0x%02x (%s)" $fuseRevision $fuseRevisionStr]

    if { [dict exists $kDeviceVersion $deviceVersion] == true } {
	set deviceVersionStr [dict get $kDeviceVersion $deviceVersion]
    } else {
	set deviceVersionStr "unknown version"
    }
    puts $outfd [format "deviceVersion  : 0x%02x (%s)" $deviceVersion $deviceVersionStr]

    return $fuseRevision
}


#
# GetECIDData
# Get the data stored in the ECID
# c.f. Fiji Text Plan Internal, Section 11.1 ECID Fuses (p.102, Rev 1.0)
#
proc GetECIDData {fuseRevision ecidFuse0 ecidFuse1 ecidFuse2 ecidFuse3 ecidFuse7} {
    variable outfd

    if { $fuseRevision != 47 } {
        set rawDEID  [expr {($ecidFuse1 & 0x001FFFFF) << 32 | $ecidFuse0}]
    } else {
        set ecidFuse0Fixed [expr {($ecidFuse1 & 0xFFFF0000) | ($ecidFuse1 & 0xFFFF) << 16 | ($ecidFuse0 & 0xFFFF0000) >> 16 | ($ecidFuse0 & 0xFFFF)}]
        set ecidFuse1Fixed [expr {($ecidFuse3 & 0xFFFF0000) | ($ecidFuse3 & 0xFFFF) << 16 | ($ecidFuse2 & 0xFFFF0000) >> 16 | ($ecidFuse2 & 0xFFFF)}]
        puts $outfd [format "\n#### Bring-Up ECID"]
        puts $outfd [format "ECID_FUSE0_FIXED: 0x%08x" $ecidFuse0Fixed]
        puts $outfd [format "ECID_FUSE1_FIXED: 0x%08x" $ecidFuse1Fixed]
        set rawDEID  [expr {($ecidFuse1Fixed & 0x001FFFFF) << 32 | $ecidFuse0Fixed}]
    }

    set lotID    [expr {($rawDEID & 0x0000000FFFFFFFFF)}]
    set waferNum [expr {($rawDEID & 0x000001F000000000) >> 36}]
    set xPos     [expr {($rawDEID & 0x00007E0000000000) >> 41}]
    set yPos     [expr {($rawDEID & 0x001F800000000000) >> 47}]

    set platformVersion [expr {(${ecidFuse7} & 0xFFFF0000) >> 16}]

    puts $outfd [format "\n#### Wafer information"]
    puts $outfd [format "DEID        : 0x%011x" $rawDEID]
    puts $outfd [format "    LotID   : 0x%06x" $lotID]
    puts $outfd [format "    WaferNum: 0x%02x" $waferNum]
    puts $outfd [format "    XPos    : 0x%02x" $xPos]
    puts $outfd [format "    YPos    : 0x%02x" $yPos]

    puts $outfd [format "Platform Version : 0x%04x" $platformVersion]
}


#
# GetIdsData
# Get the Ids from the CFG fuses
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 25: Fiji Configuration Fuse Assignment A (No Secure Storage) (p. 106, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 26: Fiji Configuration Fuse Assignment B (EEPROM) (p. 111, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 27: Fiji Configuration Fuse Assignment C (SE SPI) (p. 116, Rev 1.0)
# c.f. Fiji Text Plan Internal, Section 11.3 Fiji Configuration Fuses, Table 28: Fiji Configuration Fuse Assignment D (Encryted Tunnel) (p. 120, Rev 1.0)
#
proc GetIdsData {cfgFuse5 cfgFuse6} {
    variable outfd

    set kIdsCPUFactor 1.0
    set kIdsSOCFactor 1.0
    set kIdsGPUFactor 1.0
    set kIdsFixedFactor 1.0

    set rawIds [expr {($cfgFuse6 & 0x0000001F) << 32 | $cfgFuse5}]
    set IdsCPU     [expr {($rawIds & 0x00000003FF)}]
    set IdsSOC     [expr {($rawIds & 0x000007FC00) >> 10}]
    set IdsGPU     [expr {($rawIds & 0x000FF80000) >> 19}]
    set IdsFixed   [expr {($rawIds & 0x1FF0000000) >> 28}]

    puts $outfd [format "\n#### Ids information"]
    puts $outfd [format "IdsCPU     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%03x)" [expr {$kIdsCPUFactor * ($IdsCPU + 1)}] $IdsCPU]
    puts $outfd [format "IdsSOC     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%02x)" [expr {$kIdsSOCFactor * ($IdsSOC + 1)}] $IdsSOC]
    puts $outfd [format "IdsGPU     @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%02x)" [expr {$kIdsGPUFactor * ($IdsGPU + 1)}] $IdsGPU]
    puts $outfd [format "IdsFixed   @ 25C, 1.1V, 1mA/step: %3.1f mA (0x%1x)" [expr {$kIdsFixedFactor * ($IdsFixed + 1)}] $IdsFixed]
}


#
# GetBinningData
# Get the bin data from the CFG and DVFM fuses
# c.f. Fiji Text Plan Internal, Section 14 Binning Fuse Information (p.161, Rev 1.0)
#
proc GetBinningData {fuseRevision cfgFuse7 cfgFuse8 dvfmFuse0 dvfmFuse1 dvfmFuseRev} {
    variable outfd

    set kBinMapping {
        socP2 {
            "0x46"  "Bin 950"
            "0x41"  "Bin 925"
            "0x3c"  "Bin 900"
            "0x37"  "Bin 875"
        }
        socP1 {
            "0x3c"  "Bin 900"
            "0x37"  "Bin 875"
            "0x32"  "Bin 850"
            "0x2d"  "Bin 825"
        }
        fixed {
            "0x46"  "Bin 950"
            "0x41"  "Bin 925"
            "0x3c"  "Bin 900"
            "0x37"  "Bin 875"
        }
        cpuP9 {
            "speed" "1608 MHz"
            "0x78"  "Bin 1200"
            "0x73"  "Bin 1175"
            "0x6e"  "Bin 1150"
            "0x69"  "Bin 1125"
        }
        cpuP8 {
            "speed" "1512 MHz"
            "0x70"  "Bin 1163"
            "0x6b"  "Bin 1138"
            "0x66"  "Bin 1113"
            "0x61"  "Bin 1088"
        }
        cpuP7 {
            "speed" "1392 MHz"
            "0x69"  "Bin 1125"
            "0x64"  "Bin 1100"
            "0x5f"  "Bin 1075"
            "0x5a"  "Bin 1050"
        }
        cpuP6 {
            "speed" "1296 MHz"
            "0x5c"  "Bin 1060"
            "0x57"  "Bin 1035"
            "0x52"  "Bin 1010"
            "0x4d"  "Bin  985"
        }
        cpuP5 {
            "speed" "1128 MHz"
            "0x4c"  "Bin  980"
            "0x47"  "Bin  955"
            "0x42"  "Bin  930"
            "0x3d"  "Bin  905"
        }
        cpuP4 {
            "speed" " 840 MHz"
            "0x38"  "Bin 880"
            "0x33"  "Bin 855"
            "0x2e"  "Bin 830"
            "0x29"  "Bin 805"
        }
        cpuP3 {
            "speed" " 600 MHz"
            "0x28"  "Bin 800"
            "0x23"  "Bin 775"
            "0x1e"  "Bin 750"
            "0x19"  "Bin 725"
        }
        cpuP1 {
            "speed" " 396 MHz"
            "0x23"  "Bin 775"
            "0x1e"  "Bin 750"
            "0x19"  "Bin 725"
            "0x14"  "Bin 700"
        }
        gpuP2 {
            "speed" " 400 MHz"
            "0x46"  "Bin 950"
            "0x41"  "Bin 925"
            "0x3c"  "Bin 900"
            "0x37"  "Bin 875"
        }
        gpuP1 {
            "speed" " 355 MHz"
            "0x3c"  "Bin 900"
            "0x37"  "Bin 875"
            "0x32"  "Bin 850"
            "0x2d"  "Bin 825"
        }
    }

    if { $fuseRevision != 47 } {
        # <rdar://problem/14787262>
        # according to Fiji Test Plan Int, v. 1.0, page 160,
        #   eFuseDvfm0[27:0] = UDR[32:5]
        #   eFuseDvfm1[27:0] = UDR[60:33]
        # however, eFuseDvfm{0,1} are 32-bit registers
        # and every 8th bit is padding
        set dvfmFuse1_packed [expr { (($dvfmFuse1 & 0x7F000000) >> 3) | (($dvfmFuse1 & 0x7F0000) >> 2) | (($dvfmFuse1 & 0x7F00) >> 1) | ($dvfmFuse1 & 0x7F) }]
        set dvfmFuse0_packed [expr { (($dvfmFuse0 & 0x7F000000) >> 3) | (($dvfmFuse0 & 0x7F0000) >> 2) | (($dvfmFuse0 & 0x7F00) >> 1) | ($dvfmFuse0 & 0x7F) }]

        set rawUDR  [expr { (($dvfmFuseRev & 0xE0000000) << 32) | (($dvfmFuse1_packed & 0x0FFFFFFF) << 33) | (($dvfmFuse0_packed & 0x0FFFFFFF) << 5) | (($dvfmFuseRev & 0x1F000000) >> 24) }]

        # Base voltage and binning fuse revision
        set baseVoltage     [expr {($rawUDR & 0x000000000000001F) >>  0}]
        set binFuseRev      [expr {($rawUDR & 0xE000000000000000) >> 61}]

        # SOC bin, Mode 1
        set socP1ModeBin [expr {($cfgFuse7 & 0x0000007F) >> 0}]

        # SOC bin, Mode 2
        set socP2ModeBin [expr {($cfgFuse7 & 0x00003F80) >> 7}]

        # Fixed bin
        set fixedBin     [expr {(($cfgFuse8 & 0x7) << 4) | (($cfgFuse7 & 0xF0000000) >> 28)}]

        # GPU bin, Mode 1
        set gpuP1ModeBin [expr {($cfgFuse7 & 0x001FC000) >> 14}]

        # GPU bin, Mode 2
        set gpuP2ModeBin [expr {($cfgFuse7 & 0x0FE00000) >> 21}]

        # CPU Bin, Mode 1
        set cpuP1ModeBin [expr {($rawUDR & 0x000000000007F000) >> 12}]

        # CPU Bin, Mode 3
        set cpuP3ModeBin [expr {($rawUDR & 0x00000001FC000000) >> 26}]

        # CPU Bin, Mode 4
        set cpuP4ModeBin [expr {($rawUDR & 0x000000FE00000000) >> 33}]

        # CPU Bin, Mode 5
        set cpuP5ModeBin [expr {($rawUDR & 0x00007F0000000000) >> 40}]

        # CPU Bin, Mode 6
        set cpuP6ModeBin [expr {($rawUDR & 0x003F800000000000) >> 47}]

        # CPU Bin, Mode 7
        set cpuP7ModeBin [expr {($rawUDR & 0x1FC0000000000000) >> 54}]

        # CPU Bin, Mode 8
        set cpuP8ModeBin [expr {($rawUDR & 0x0000000003F80000) >> 19}]

        # CPU Bin, Mode 9
        set cpuP9ModeBin [expr {($rawUDR & 0x0000000000000FE0) >> 5}]
    } else {
        set baseVoltage  0x17
        set binFuseRev   0x00

        set socP1ModeBin 0x3c
        set socP2ModeBin 0x46
        set fixedBin     0x46

        set gpuP1ModeBin 0x3c
        set gpuP2ModeBin 0x46

        set cpuP1ModeBin 0x23
        set cpuP2ModeBin 0x23
        set cpuP3ModeBin 0x2c
        set cpuP4ModeBin 0x3c
        set cpuP5ModeBin 0x50
        set cpuP6ModeBin 0x64
        set cpuP7ModeBin 0x72
        set cpuP8ModeBin 0x70
        set cpuP9ModeBin 0x78
    }

    # Base voltage
    set baseVoltage_mV  [expr {($baseVoltage + 1) * 25}]

    # Compute SOC voltages
    set socP1ModeBin_mV [expr {$baseVoltage_mV + ($socP1ModeBin * 5)}]
    set socP2ModeBin_mV [expr {$baseVoltage_mV + ($socP2ModeBin * 5)}]
    set fixedBin_mV     [expr {$baseVoltage_mV + ($fixedBin * 5)}]

    # Compute GPU voltages
    set gpuP1ModeBin_mV [expr {$baseVoltage_mV + ($gpuP1ModeBin * 5)}]
    set gpuP2ModeBin_mV [expr {$baseVoltage_mV + ($gpuP2ModeBin * 5)}]

    # Compute CPU voltages
    set cpuP1ModeBin_mV [expr {$baseVoltage_mV + ($cpuP1ModeBin * 5)}]
    set cpuP3ModeBin_mV [expr {$baseVoltage_mV + ($cpuP3ModeBin * 5)}]
    set cpuP4ModeBin_mV [expr {$baseVoltage_mV + ($cpuP4ModeBin * 5)}]
    set cpuP5ModeBin_mV [expr {$baseVoltage_mV + ($cpuP5ModeBin * 5)}]
    set cpuP6ModeBin_mV [expr {$baseVoltage_mV + ($cpuP6ModeBin * 5)}]
    set cpuP7ModeBin_mV [expr {$baseVoltage_mV + ($cpuP7ModeBin * 5)}]
    set cpuP8ModeBin_mV [expr {$baseVoltage_mV + ($cpuP8ModeBin * 5)}]
    set cpuP9ModeBin_mV [expr {$baseVoltage_mV + ($cpuP9ModeBin * 5)}]

    # Compute SOC bins
    set socP1ModeMap [format "0x%02x" $socP1ModeBin]
    if { [dict exists $kBinMapping socP1 $socP1ModeMap] } {
        set socP1ModeMap [dict get $kBinMapping socP1 $socP1ModeMap]
    }
    set socP2ModeMap [format "0x%02x" $socP2ModeBin]
    if { [dict exists $kBinMapping socP2 $socP2ModeMap] } {
        set socP2ModeMap [dict get $kBinMapping socP2 $socP2ModeMap]
    }
    set fixedMap [format "0x%02x" $fixedBin]
    if { [dict exists $kBinMapping fixed $fixedMap] } {
        set fixedMap [dict get $kBinMapping fixed $fixedMap]
    }

    # Compute GPU bins
    set gpuP1ModeMap [format "0x%02x" $gpuP1ModeBin]
    if { [dict exists $kBinMapping gpuP1 $gpuP1ModeMap] } {
        set gpuP1ModeMap [dict get $kBinMapping gpuP1 $gpuP1ModeMap]
    }
    set gpuP2ModeMap [format "0x%02x" $gpuP2ModeBin]
    if { [dict exists $kBinMapping gpuP2 $gpuP2ModeMap] } {
        set gpuP2ModeMap [dict get $kBinMapping gpuP2 $gpuP2ModeMap]
    }

    # Compute CPU bins
    set cpuP9ModeMap [format "0x%02x" $cpuP9ModeBin]
    if { [dict exists $kBinMapping cpuP9 $cpuP9ModeMap] } {
        set cpuP9ModeMap [dict get $kBinMapping cpuP9 $cpuP9ModeMap]
    }
    set cpuP8ModeMap [format "0x%02x" $cpuP8ModeBin]
    if { [dict exists $kBinMapping cpuP8 $cpuP8ModeMap] } {
        set cpuP8ModeMap [dict get $kBinMapping cpuP8 $cpuP8ModeMap]
    }
    set cpuP7ModeMap [format "0x%02x" $cpuP7ModeBin]
    if { [dict exists $kBinMapping cpuP7 $cpuP7ModeMap] } {
        set cpuP7ModeMap [dict get $kBinMapping cpuP7 $cpuP7ModeMap]
    }
    set cpuP6ModeMap [format "0x%02x" $cpuP6ModeBin]
    if { [dict exists $kBinMapping cpuP6 $cpuP6ModeMap] } {
        set cpuP6ModeMap [dict get $kBinMapping cpuP6 $cpuP6ModeMap]
    }
    set cpuP5ModeMap [format "0x%02x" $cpuP5ModeBin]
    if { [dict exists $kBinMapping cpuP5 $cpuP5ModeMap] } {
        set cpuP5ModeMap [dict get $kBinMapping cpuP5 $cpuP5ModeMap]
    }
    set cpuP4ModeMap [format "0x%02x" $cpuP4ModeBin]
    if { [dict exists $kBinMapping cpuP4 $cpuP4ModeMap] } {
        set cpuP4ModeMap [dict get $kBinMapping cpuP4 $cpuP4ModeMap]
    }
    set cpuP3ModeMap [format "0x%02x" $cpuP3ModeBin]
    if { [dict exists $kBinMapping cpuP3 $cpuP3ModeMap] } {
        set cpuP3ModeMap [dict get $kBinMapping cpuP3 $cpuP3ModeMap]
    }
    set cpuP1ModeMap [format "0x%02x" $cpuP1ModeBin]
    if { [dict exists $kBinMapping cpuP1 $cpuP1ModeMap] } {
        set cpuP1ModeMap [dict get $kBinMapping cpuP1 $cpuP1ModeMap]
    }

    puts $outfd [format "\n#### Bin information"]

    puts $outfd [format "DVFM fuse revision: %d (0x%01x)" $binFuseRev $binFuseRev]
    puts $outfd [format "Base voltage     : %4.1f mV (0x%02x)" $baseVoltage_mV $baseVoltage]

    puts $outfd [format "SOC P1 bin       : %4.1f mV (Mode 1, 0x%02x, %s)" $socP1ModeBin_mV $socP1ModeBin $socP1ModeMap]
    puts $outfd [format "SOC P2 bin       : %4.1f mV (Mode 2, 0x%02x, %s)" $socP2ModeBin_mV $socP2ModeBin $socP2ModeMap]
    puts $outfd [format "Fixed bin        : %4.1f mV (0x%02x, %s)" $fixedBin_mV $fixedBin $fixedMap]

    puts $outfd [format "GPU bin, %s: %4.1f mV (Mode 1, 0x%02x, %s)" [dict get $kBinMapping gpuP1 "speed"] $gpuP1ModeBin_mV $gpuP1ModeBin $gpuP1ModeMap]
    puts $outfd [format "GPU bin, %s: %4.1f mV (Mode 2, 0x%02x, %s)" [dict get $kBinMapping gpuP2 "speed"] $gpuP2ModeBin_mV $gpuP2ModeBin $gpuP2ModeMap]

    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 9, 0x%02x, %s)" [dict get $kBinMapping cpuP9 "speed"] $cpuP9ModeBin_mV $cpuP9ModeBin $cpuP9ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 8, 0x%02x, %s)" [dict get $kBinMapping cpuP8 "speed"] $cpuP8ModeBin_mV $cpuP8ModeBin $cpuP8ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 7, 0x%02x, %s)" [dict get $kBinMapping cpuP7 "speed"] $cpuP7ModeBin_mV $cpuP7ModeBin $cpuP7ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 6, 0x%02x, %s)" [dict get $kBinMapping cpuP6 "speed"] $cpuP6ModeBin_mV $cpuP6ModeBin $cpuP6ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 5, 0x%02x, %s)" [dict get $kBinMapping cpuP5 "speed"] $cpuP5ModeBin_mV $cpuP5ModeBin $cpuP5ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 4, 0x%02x, %s)" [dict get $kBinMapping cpuP4 "speed"] $cpuP4ModeBin_mV $cpuP4ModeBin $cpuP4ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 3, 0x%02x, %s)" [dict get $kBinMapping cpuP3 "speed"] $cpuP3ModeBin_mV $cpuP3ModeBin $cpuP3ModeMap]
    puts $outfd [format "CPU bin, %s: %4.1f mV (Mode 1, 0x%02x, %s)" [dict get $kBinMapping cpuP1 "speed"] $cpuP1ModeBin_mV $cpuP1ModeBin $cpuP1ModeMap]
}


####################################################################
# main
####################################################################
set rCFG_FUSE0 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE0}]
set rCFG_FUSE1 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE1}]
set rCFG_FUSE2 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE2}]
set rCFG_FUSE3 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE3}]
set rCFG_FUSE4 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE4}]
set rCFG_FUSE5 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE5}]
set rCFG_FUSE6 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE6}]
set rCFG_FUSE7 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE7}]
set rCFG_FUSE8 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE8}]
set rCFG_FUSE9 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE9}]
set rCFG_FUSE10 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE10}]
set rCFG_FUSE11 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE11}]
set rCFG_FUSE12 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE12}]
set rCFG_FUSE13 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE13}]
set rCFG_FUSE14 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE14}]
set rCFG_FUSE15 [expr {$::bPMGR + $::bPMGRFuse + $::oCFG_FUSE15}]

set rECID_FUSE0 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE0}]
set rECID_FUSE1 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE1}]
set rECID_FUSE2 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE2}]
set rECID_FUSE3 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE3}]
set rECID_FUSE4 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE4}]
set rECID_FUSE5 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE5}]
set rECID_FUSE6 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE6}]
set rECID_FUSE7 [expr {$::bPMGR + $::bPMGRFuse + $::oECID_FUSE7}]

set rEFUSE_DVFM0 [expr {$::bCCC + $::bCCCPwrCtl + $::oEFUSE_DVFM0}]
set rEFUSE_DVFM1 [expr {$::bCCC + $::bCCCPwrCtl + $::oEFUSE_DVFM1}]
set rEFUSE_REV   [expr {$::bCCC + $::bCCCPwrCtl + $::oEFUSE_REV}]

set cfgFuse0 [read32 $rCFG_FUSE0]
set cfgFuse1 [read32 $rCFG_FUSE1]
set cfgFuse2 [read32 $rCFG_FUSE2]
set cfgFuse3 [read32 $rCFG_FUSE3]
set cfgFuse4 [read32 $rCFG_FUSE4]
set cfgFuse5 [read32 $rCFG_FUSE5]
set cfgFuse6 [read32 $rCFG_FUSE6]
set cfgFuse7 [read32 $rCFG_FUSE7]
set cfgFuse8 [read32 $rCFG_FUSE8]
set cfgFuse9 [read32 $rCFG_FUSE9]
set cfgFuse10 [read32 $rCFG_FUSE10]
set cfgFuse11 [read32 $rCFG_FUSE11]
set cfgFuse12 [read32 $rCFG_FUSE12]
set cfgFuse13 [read32 $rCFG_FUSE13]
set cfgFuse14 [read32 $rCFG_FUSE14]
set cfgFuse15 [read32 $rCFG_FUSE15]

set ecidFuse0 [read32 $rECID_FUSE0]
set ecidFuse1 [read32 $rECID_FUSE1]
set ecidFuse2 [read32 $rECID_FUSE2]
set ecidFuse3 [read32 $rECID_FUSE3]
set ecidFuse4 [read32 $rECID_FUSE4]
set ecidFuse5 [read32 $rECID_FUSE5]
set ecidFuse6 [read32 $rECID_FUSE6]
set ecidFuse7 [read32 $rECID_FUSE7]

set dvfmFuse0 [read32 $rEFUSE_DVFM0]
set dvfmFuse1 [read32 $rEFUSE_DVFM1]
set dvfmFuseRev [read32 $rEFUSE_REV]

puts $outfd [format "\n#### PMGR Fuses"]
puts $outfd [format "CFG_FUSE0:  0x%08x" $cfgFuse0]
puts $outfd [format "CFG_FUSE1:  0x%08x" $cfgFuse1]
puts $outfd [format "CFG_FUSE2:  0x%08x" $cfgFuse2]
puts $outfd [format "CFG_FUSE3:  0x%08x" $cfgFuse3]
puts $outfd [format "CFG_FUSE4:  0x%08x" $cfgFuse4]
puts $outfd [format "CFG_FUSE5:  0x%08x" $cfgFuse5]
puts $outfd [format "CFG_FUSE6:  0x%08x" $cfgFuse6]
puts $outfd [format "CFG_FUSE7:  0x%08x" $cfgFuse7]
puts $outfd [format "CFG_FUSE8:  0x%08x" $cfgFuse8]
puts $outfd [format "CFG_FUSE9:  0x%08x" $cfgFuse9]
puts $outfd [format "CFG_FUSE10: 0x%08x" $cfgFuse10]
puts $outfd [format "CFG_FUSE11: 0x%08x" $cfgFuse11]
puts $outfd [format "CFG_FUSE12: 0x%08x" $cfgFuse12]
puts $outfd [format "CFG_FUSE13: 0x%08x" $cfgFuse13]
puts $outfd [format "CFG_FUSE14: 0x%08x" $cfgFuse14]
puts $outfd [format "CFG_FUSE15: 0x%08x" $cfgFuse15]

puts $outfd [format "\n#### ECID Fuses"]
puts $outfd [format "ECID_FUSE0: 0x%08x" $ecidFuse0]
puts $outfd [format "ECID_FUSE1: 0x%08x" $ecidFuse1]
puts $outfd [format "ECID_FUSE2: 0x%08x" $ecidFuse2]
puts $outfd [format "ECID_FUSE3: 0x%08x" $ecidFuse3]
puts $outfd [format "ECID_FUSE4: 0x%08x" $ecidFuse4]
puts $outfd [format "ECID_FUSE5: 0x%08x" $ecidFuse5]
puts $outfd [format "ECID_FUSE6: 0x%08x" $ecidFuse6]
puts $outfd [format "ECID_FUSE7: 0x%08x" $ecidFuse7]

puts $outfd [format "\n#### DVFM Fuses"]
puts $outfd [format "EFUSE_DVFM0: 0x%08x" $dvfmFuse0]
puts $outfd [format "EFUSE_DVFM1: 0x%08x" $dvfmFuse1]
puts $outfd [format "EFUSE_REV:   0x%08x" $dvfmFuseRev]

set fuseRevision [GetDeviceData $cfgFuse0 $cfgFuse4]

GetECIDData $fuseRevision $ecidFuse0 $ecidFuse1 $ecidFuse2 $ecidFuse3 $ecidFuse7

GetIdsData $cfgFuse5 $cfgFuse6

GetBinningData $fuseRevision $cfgFuse7 $cfgFuse8 $dvfmFuse0 $dvfmFuse1 $dvfmFuseRev

close $outfd
