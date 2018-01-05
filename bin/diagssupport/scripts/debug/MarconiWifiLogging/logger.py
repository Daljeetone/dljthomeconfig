#!/usr/bin/env python
__author__ = 'avrigolan'
import re
import os,sys
import traceback as tb
import struct
from datetime import datetime
from collections import namedtuple

class CoreType(object):
    WIFI_MAC = "WIFI MAC"
    WIFI_PHY = "WIFI PHY"
    BT_MAC = "BT MAC"
    BT_PHY = "BT PHY"

class SeverityType(object):
    DEBUG = 0
    INFO = 1
    WARNING = 2
    ERROR = 3
    FATAL = 4


CURRENT_TS = -1

##############################################################################
class FwLoggerParser(object):
    INVALID_LENGTH = -1
    min_length = 1
    FW_LOGGER_MESSAGE_PARSE_OK = 0
    FW_LOGGER_MESSAGE_PARSE_PARTIAL_LENGTH = 1
    FW_LOGGER_MESSAGE_PARSE_INVALID = 2
    FORMAT_DICT = {1: 'B', 2: 'H', 4: 'I'}
    SOURCE_DICT = {0x00: CoreType.WIFI_MAC, 0x40: CoreType.WIFI_PHY, 0x08 : CoreType.BT_MAC, 0x48: CoreType.BT_PHY }

    def __init__(self, parser, is_phy, internal_logger):
        self._logger = internal_logger
        self.timedelta = datetime.utcnow() - datetime.now()
        self.bin_id = 0
        self.parser = parser
        self.is_phy = is_phy


    def get_max_len(self):
        return 35

    def now(self):
        return str(datetime.utcnow() - self.timedelta)

    def get_length(self):
        return 0

    def parse_trace(self, length=None):
        pass

    def unpack_uint(self, stream, length, offset=0):
        '''struct.unpack() for 1,2,3 or 4 byte length big endian value'''
        if length == 3:
            hi, low = struct.unpack('>BH', stream[offset:offset + length])
            result = low | (hi << 16)
        elif length <= 4:
            result, = struct.unpack('>%s' % self.FORMAT_DICT[length],
                                    stream[offset:offset + length])
        else:
            raise ValueError('Unsupported value length(%d). Should be 1-4.' % length)
        return result

    def get_core_type(self, header):
        # mac/phy is bit 6, wifi/bt is bit 3
        # 01001000 = 0x48
        entry = header & 0x48
        return self.SOURCE_DICT[entry]

    def update_stream(self, stream):
        self.stream = stream

    def write_fwlog(self, text, core_type='', timestamp='', line_num='', file_name='', func_name='', group_name='', severity=''):
        self.parser.write_fwlog(ts_pc=self.now(),
                          core_type=core_type,
                          ts_fw=timestamp,
                          line_num=line_num,
                          file_name=file_name,
                          func_name=func_name,
                          group_name=group_name,
                          severity=severity,
                          text=text,
                          lr=self.lr)
    def get_enums(self):
        if self.is_phy:
            return self.parser.phy_enums
        else:
            return self.parser.enums

    def get_symbols(self):
        if self.is_phy:
            return self.parser.phy_symbols
        else:
            return self.parser.symbols

    def enumify(self, fmt_string):
        try:
            pos = fmt_string.find("ENUM(")
            while pos != -1:
                end_pos = fmt_string.find(")", pos)
                fields = fmt_string[pos + 5:end_pos].strip().split(",")
                if (fields[0], int(fields[1])) in self.get_enums():  # symbol_name = fields[0], param_value (integer) = fields[1]
                    param_name = self.get_enums()[(fields[0], int(fields[1]))]
                else:
                    param_name = fields[1]
                fmt_string = fmt_string[:pos] + param_name + fmt_string[end_pos + 1:]
                pos = fmt_string.find("ENUM(")
        except Exception:
            return "Invalid ENUM message format. (%s)" % (fmt_string)  # Do not consider this as invalid trace
        return fmt_string


class FwLoggerParser_Text(FwLoggerParser):

    min_length = 2
    param_count = 0
    sub_type = ""
    lr = 0
    ts = 0
    KEEP_ALIVE_LR = 0x55555555

    def __init__(self, parser, is_phy, internal_logger):
        FwLoggerParser.__init__(self, parser, is_phy, internal_logger)



    #
    # Create a list of all the param sizes
    #
    def get_param_lengths(self):
        param_lengths = []

        for byte in bytearray(self.sub_type):
            # bits = BitStream("0x" + byte.encode("hex"))
            # params = bits.readlist('uint:2, uint:2, uint:2, uint:2')
            params = (byte & 0b11000000) >> 6, \
                        (byte & 0b00110000) >> 4, \
                        (byte & 0b00001100) >> 2, \
                        byte & 0b00000011

            #
            # We refer to 0 in every field as 1 byte, hence the addition of 1
            #
            param_lengths.append(params[0] + 1)
            param_lengths.append(params[1] + 1)
            param_lengths.append(params[2] + 1)
            param_lengths.append(params[3] + 1)

        return param_lengths

    #
    # Calculate the total length of the parameters
    #
    def get_param_length(self):
        total_param_length = 0
        param_lengths = self.get_param_lengths()

        for i in range(self.param_count):
            total_param_length += param_lengths[i]

        return total_param_length

    #
    # Return the length of the trace
    #
    def get_length(self):
        #
        # Min header length in bytes
        #

        s0 = ord(self.stream[0])
        s1 = ord(self.stream[1])
        lr_len = (s0 & 0b110) >> 1
        ts_len = ((s0 & 1) << 1) | ((s1 & 0b10000000) >> 7)
        self.param_count = (s1 & 0b01111100) >> 2

        self.coreType = self.get_core_type(s0)

        #
        # Add 1 to length fields since the protocol refers to 0 as 8bit (1 byte)
        #
        lr_len += 1
        ts_len += 1

        #
        # Assume calculation is done based on whole numbers
        #
        sub_type_len = (abs(self.param_count - 1) / 4) + 1
        total_trace_length = self.min_length + lr_len + ts_len + sub_type_len

        #
        # We need the sub_type field in order to calculate the exact size of the trace
        #
        if len(self.stream) >= total_trace_length:
            stream = self.stream[self.min_length:]
            self.lr = self.unpack_uint(stream, lr_len)

            if ts_len == 3:
                hi, low, self.sub_type = \
                    struct.unpack('>BH%us' % sub_type_len,
                                  stream[lr_len:lr_len + ts_len + sub_type_len])
                self.ts = low | (hi << 16)
            else:
                self.ts, self.sub_type = \
                    struct.unpack('>%s%us' % (self.FORMAT_DICT[ts_len], sub_type_len),
                                  stream[lr_len:ts_len + lr_len + sub_type_len])

            return total_trace_length + self.get_param_length()

        return total_trace_length

    def get_params(self):
        params = []
        param_lengths = self.get_param_lengths()

        param_stream = self.stream[-self.get_param_length():]
        index = 0
        for i in xrange(self.param_count):
            plen = param_lengths[i]
            param = self.unpack_uint(param_stream, plen, index)
            index += plen
            params.append(param)
        return params

    #
    # TODO: Send trace to the service module for parsing
    #
    def parse_trace(self, length=None):
        #
        # Make sure we have the entire message
        #
        format_string = ""
        file_name = ""
        func_name = ""
        group_name = ""
        line_num = 0

        if length is None:
            length = self.get_length()

        if len(self.stream) >= length:

            self.stream = self.stream[:length]
            params = self.get_params()

            # Due  to compiler optimizations we need to search for
            # the lr for up to at least 50 bytes ahead (possibly more, but very unlikely)
            found_lr = self.lr in self.get_symbols()

            if not found_lr and self.lr != self.KEEP_ALIVE_LR:
                self.write_fwlog(text="Invalid Trace - Unknown LR %d (0x%X) ts=%d %s" % (int(self.lr), self.lr, self.ts, params), timestamp=self.ts)
                self._logger.warning("Invalid Trace - Unknown LR {0} (0x{1:X}) params {2}".format(int(self.lr), self.lr, params))
                return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK

            format_string = ""
            try:
                if self.lr == self.KEEP_ALIVE_LR:
                    # self._logger.info("Got sync, binid=%d 0x%X" % (self.bin_id,self.bin_id))
                    # if self.bin_id == params[0] and self.bin_id != 0:  # Display keep alive message only once
                    #    return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK
                    if len(params) == 1:
                        format_string = "Keep Alive - Bin ID is 0x%X"
                    else:
                        format_string = "Keep Alive - Mac Bin ID is 0x%X, Phy Bin ID is 0x%X"
                    func_name = file_name = "None"
                    line_num = 0
                    self.bin_id = params[0]
                else:
#                     if self.bin_id == 0:  # No keep alive received so far - ignore message
#                         return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_INVALID
                    symb = self.get_symbols()[self.lr]
                    format_string = symb["log_text"]
                    file_name = symb["file_name"]
                    func_name = symb["func_name"]
                    group_name = symb["group_name"]
                    line_num = symb["line_num"]
                log_text = format_string % tuple(params)
                log_text = self.enumify(log_text)
                log_text_lower = log_text.lower()
                log_sevirity_type = SeverityType.INFO
                if log_text_lower.find("err") != -1:
                    log_sevirity_type = SeverityType.ERROR
                elif log_text_lower.find("warn") != -1:
                    log_sevirity_type = SeverityType.WARNING
                elif log_text_lower.find("assert") != -1:
                    log_sevirity_type = SeverityType.FATAL

                self.write_fwlog(log_text, self.coreType, self.ts, line_num, file_name,
                                 func_name, group_name, log_sevirity_type,
                                 )
            except Exception as e:
                print e
                self.write_fwlog("Invalid Trace - LR(%d) Bad Params (%s) (%s)"
                                  % (int(self.lr), format_string, str(params)),
                                    self.coreType, self.ts, line_num, file_name,
                                 func_name, group_name, 0)
                return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK

            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK
        else:
            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_PARTIAL_LENGTH



class FwLoggerParser_NGPIO_NewFormat(FwLoggerParser):

    min_length = 8
    def __init__(self, parser, is_phy, internal_logger):
        FwLoggerParser.__init__(self, parser, is_phy, internal_logger)
        self.msg_length = 0
        self.has_data = 0

    def write_gpio(self, io_id, mode, ts, text):
        event_name = self.enumify(io_id)
        # if self.db:
        #    self.db.write_query("INSERT INTO sigview_fw_events(src_id, dev_id, log_session_id, event_type, event_id, event_name, ts_fw, mode, text) VALUES ('FwLogAccess', ?, '0', '100', ?, ?, ?, ?, ?)", (self.source_device, io_id, event_name, ts, mode, text))
        # TODO - what should we do with GPIO when there is no DB ???
        print "GPIO id={} mode={}".format(io_id, mode)
        pass

    def get_length(self):
        s0 = ord(self.stream[0])
        self.has_data = (s0 >> 2) & 1
        self.mode = s0 & 0x3
        self.msg_length = 12 if self.has_data else 8
        return self.msg_length

    def enumify(self, io_id):
        enums = self.get_enums()
        if ("gTraceIoTextGroups_e", int(io_id)) in enums:
            param_name = enums[("gTraceIoTextGroups_e", int(io_id))]
        else:
            param_name = "Invalid io_id %d" % io_id
        return (param_name)

    def parse_trace(self, length=None):
        global CURRENT_TS
        self.id, ts = struct.unpack("<LL", self.stream[0:8])
        self.id = (self.id >> 8) & 0xFFFF
        data = ""
        if self.has_data:
            data, = struct.unpack("<L", self.stream[8:12])
        self.write_gpio(self.id, self.mode, ts, data)
        # print "GPIO ID={} mode={} ts={} data={}".format(self.id, self.mode, ts, data)
        return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK


class FwLoggerParser_NewFormat(FwLoggerParser):

    min_length = 8
    lr = 0
    ts = 0
    TRACE_DROP_LR = 0x666666


    def __init__(self, parser, is_phy, internal_logger):
        FwLoggerParser.__init__(self, parser, is_phy, internal_logger)
        self.bin_id = 0



    def get_length(self):
        count = ord(self.stream[0]) & 0x7
        return 8 + count * 4


    #
    # TODO: Send trace to the service module for parsing
    #
    def parse_trace(self, length=None):
        #
        # Make sure we have the entire message
        #
        format_string = ""
        file_name = ""
        func_name = ""
        group_name = ""
        line_num = 0
        symbols = self.get_symbols()
        if length is None:
            length = self.get_length()

        if len(self.stream) >= length:
            header = ord(self.stream[0])
            count = header & 0x7
            self.lr, self.ts = struct.unpack("<LL", self.stream[0:8])
            self.lr = self.lr >> 8

            params = []
            self.coreType = self.get_core_type(header)
            found_lr = self.lr in symbols
            
            if not found_lr:
                params = struct.unpack("<" + "L" * count, self.stream[8:8 + count * 4])
                self.write_fwlog("Invalid Trace - Unknown LR %d (0x%X) ts=%d %s" % (int(self.lr), self.lr, self.ts, params),
                                 self.coreType, self.ts, "", "",
                                 "", "", SeverityType.INFO)
                if self.lr == 0:
                    # we shouldn't get zero LR ...
                    return FW_LOGGER_MESSAGE_PARSE_INVALID
                return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK

            format_string = ""
            try:
                if self.lr == self.TRACE_DROP_LR:
                    # in drop, the TS is the amount of dropped frames
                    format_string = "Lost %d traces"
                    params = [self.ts];  # use the ts as the only argument
                    self.ts = 0
                else:
                    symb = symbols[self.lr]
                    format_string, unpack_str, unpack_len = symb["unpack_params"]
                    # print format_string, unpack_str, unpack_len
                    params = struct.unpack(unpack_str, self.stream[8:8 + unpack_len])
                    file_name = symb["file_name"]
                    func_name = symb["func_name"]
                    group_name = symb["group_name"]
                    line_num = symb["line_num"]
                log_text = format_string % tuple(params)
                log_text = self.enumify(log_text)
                log_text_lower = log_text.lower()
                log_sevirity_type = SeverityType.INFO
                if log_text_lower.find("err") != -1:
                    log_sevirity_type = SeverityType.ERROR
                elif log_text_lower.find("warn") != -1:
                    log_sevirity_type = SeverityType.WARNING
                elif log_text_lower.find("assert") != -1:
                    log_sevirity_type = SeverityType.FATAL
                # print "LOG ts={} text={}".format(self.ts, log_text)
                self.write_fwlog(log_text, self.coreType, self.ts, line_num, file_name,
                                 func_name, group_name, log_sevirity_type
                                 )
            except Exception as e:
                print "Exception", e
                try:
                    params = struct.unpack("L%d" % count, self.stream[8:8 + count * 4])
                except Exception as e:
                    print e
                    params = "Failed to parse"
                self.write_fwlog("Format Exception - LR(%d) Bad Params (%s) (%s)"
                              % (int(self.lr), format_string, str(params)),
                                  self.coreType, self.ts, line_num, file_name,
                             func_name, group_name, 0)
                return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK

            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK
        else:
            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_PARTIAL_LENGTH




class FwLoggerParser_Extended_NewFormat(FwLoggerParser_NewFormat):

    min_length = 8

    def __init__(self, parser, is_phy, internal_logger):
        FwLoggerParser.__init__(self, parser, is_phy, internal_logger)
        self.subprotocol_parsers = {
                                   1: self._TypeText_Parser
                                   }

        self.subprotocol_length = {
                                  1:self._TypeText_get_length
                                  }

    def get_max_len(self):
        return 255

    def get_length(self):
        header = ord(self.stream[0])
        # subtype for extended header is the lowest 3 bits
        subtype = header & 0x7
        # print "using subtype ", subtype
        if subtype in self.subprotocol_length:
            return self.subprotocol_length[subtype]()
        self._logger.error("ERROR:Unsupported subtype for extended log {}"
                           .format(subtype))
        return -1


    def parse_trace(self, length=None):
        header = ord(self.stream[0])
        # subtype for extended header is the lowest 3 bits
        subtype = header & 0x7
        if subtype in self.subprotocol_parsers:
            return self.subprotocol_parsers[subtype](length)
        self._logger.error("ERROR:Unsupported subtype for extended log {}"
                           .format(subtype))
        return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_INVALID

    def _TypeText_get_length(self):
        count = ord(self.stream[1])
        count = (count + 3) & 0xFC  # add padding
        return 8 + count

    def _TypeText_Parser(self, length=None):
        #
        # Make sure we have the entire message
        #
        file_name = "RtKit"
        func_name = "Printf"
        group_name = ""
        line_num = 0
        log_sevirity_type = SeverityType.INFO
        if length is None:
            length = self.get_length()
        if len(self.stream) >= length:

            header = ord(self.stream[0])
            count = ord(self.stream[1])
            # print "got simple log, count=%d" % (count)
            self.ts, = struct.unpack("<L", self.stream[4:8])
            self.coreType = self.get_core_type(header)
            log_text = self.stream[8:8 + count]
            log_text_lower = log_text.lower()
            if log_text_lower.find("err") != -1:
                log_sevirity_type = SeverityType.ERROR
            elif log_text_lower.find("warn") != -1:
                log_sevirity_type = SeverityType.WARNING
            elif log_text_lower.find("assert") != -1:
                log_sevirity_type = SeverityType.FATAL

            self.write_fwlog(log_text, self.coreType, self.ts, line_num, file_name,
                             func_name, group_name, log_sevirity_type,
                             )
            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK
        else:
            return FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_PARTIAL_LENGTH


class myLogger:
    def warning(self, data):
        print "warning:", data
    def error(self, data):
        print "warning:", data
    def info(self, data):
        print "warning:", data
    def write(self, data):
        print "Log:", data


class BinParser(object):

    LOG_SYMBOL_MARKER = "GTRACE_MARKER_LOG_SYMBOLS\r\n"
    ENUM_SYMBOL_MAKER = "***ENUMS\r\n"

    def __init__(self, bin_file):
        self._logger = myLogger()
        self.bin_file = bin_file
        if self.bin_file:
            self.data = file(bin_file, "rb").read()
        self.symbols = {}
        self.enums = {}
        self.type = "unknown"
        self.bin_id = 0
        # use regular scan

        # format_spec ::=  [[fill]align] [sign] [#] [0] [width] [,] [.precision][length [type]
        # fill        ::=  <any character>
        # align       ::=  "<" | ">" | "=" | "^"
        # sign        ::=  "+" | "-" | " "
        # width       ::=  integer
        # precision   ::=  integer
        # length
        # type        ::=  b|c|d|o|x|X|n|u
        self.print_pattern = re.compile('((%[<>=^]?[+\- ]?#?0?[\d+]?,?(\.\d+)?)(hh|h|l|ll)?(b|c|d|o|x|X|n|u))')


    def get_symbols(self):
        return self.symbols

    def get_enums(self):
        return self.enums

    def get_gpio_symbols(self):
        raise NotImplementedError('no GPIO info in bin')

    def parse_bin(self):
        if not self.bin_file:
            return
        if self.data.find(BinParser.LOG_SYMBOL_MARKER) != -1:
            self.parse_llvm_bin()
            self.read_bin_id()
            self.type = "llvm"
        else:
            self.type = "unknown"
        return self.type

    def read_bin_id(self):
        bin_reg = re.compile('BIN_ID=\s*(\S+)')
        binid = bin_reg.findall(self.data)
        if binid:
            binid = binid[0]
            self.bin_id = int(binid, 0)
            # print "Found binid 0x%X" % self.bin_id

    def parse_llvm_bin(self):

        self.symbols = {}
        self.enums = {}

        # Retrieve the log symbols
        lines = self.data[self.data.find(BinParser.LOG_SYMBOL_MARKER) +
                          len(BinParser.LOG_SYMBOL_MARKER):].split("\r\n")

        try:
            enum_index = lines.index(BinParser.ENUM_SYMBOL_MAKER[0:-2])
            lines = lines[0:enum_index]
        except Exception:
            pass  # no enums in bin file

        lines.sort(key=lambda line: int(line.split("|")[0]), reverse=True)

        for line in lines:
            if line.strip() == "" or line[0] == "*":
                break
            parts = line.strip().split("|")
            lr = int(parts[0].strip())
            line_num = parts[1]
            file_name = parts[2].replace("__S__", "/").replace("__D__", ".")
            func_name = parts[3]
            group_name = parts[4]
            log_text = ''.join(parts[5:])
            self.symbols[lr] = {"log_text": log_text,
                                "file_name": file_name,
                                "func_name": func_name,
                                "group_name": group_name,
                                "line_num": line_num}
        self.update_symbols(self.symbols)

        # Get enums
        if self.data.find(BinParser.ENUM_SYMBOL_MAKER) != -1:
            lines = self.data[self.data.find(BinParser.ENUM_SYMBOL_MAKER) +
                              len(BinParser.ENUM_SYMBOL_MAKER):].split("\r\n")

            for line in lines:
                if line.strip() == "" or line[0] == "*":
                    break
                fields = line.strip().split("|")
                enum_name = fields[0]
                # List of all the enum values
                enumValues = fields[1].split(";")[:-1]
                for value in enumValues:
                    param_name, param_value = value.split(",")
                    self.enums[(enum_name, int(param_value))] = param_name


    # return a touple of unpack string format and length
    def scan_params(self, text):
        try:
            # for full control use:
            # use "@unpack_str:length@string_format"
            # where:
            # unpack_str - string to use in struct.unpack
            # len = number of bytes to take from the data
            # string_format - string to use in the printf format
            if text.startswith("@"):
                vals = text.split('@')
                if len(vals) >= 3:
                    text = vals[2]
                    unpack_str, length = vals[1].split(":")
                    return text, unpack_str, int(length)
        except Exception:
            # tb.print_exc(file=sys.stdout)
            self._logger.warning("failed to parse %s", text)
            None
        res = self.print_pattern.findall(text)
        unpack_str = "<"
        pack_len = 0
        for x in res:
            s_all = x[0]
            s_prefix = x[1]
            s_len = x[3]
            s_type = x[4]
            if  s_len == "hh":
                unpack_str += "b" if s_type == "d" else "B"
                pack_len += 1
                # hh is not supported in python, remove it
                text = text.replace(s_all, s_prefix + s_type)
            elif s_len == "h":
                unpack_str += "h" if s_type == "d" else "H"
                pack_len += 2
            elif s_len == "ll":
                unpack_str += "q" if s_type == "d" else "Q"
                text = text.replace(s_all, s_prefix + s_type)
                pack_len += 8
            elif s_type == "d":
                unpack_str = unpack_str + "l"
                pack_len += 4
            elif s_type == "f":
                unpack_str = unpack_str + "f"
                pack_len += 4
            else :
                unpack_str = unpack_str + "L"
                pack_len += 4
        return text, unpack_str, pack_len

    def update_symbols(self, symbols):
        # we need to change the LR to 24 bit ...
        self.symbols = {}
        try:

            for lr, val in symbols.iteritems():
                new_lr = lr & 0xFFFFFF
                if new_lr in self.symbols:
                    self._logger.error("Found duplicated LR's : {:x} and {:x}".
                                      format(new_lr, lr))
                val["unpack_params"] = self.scan_params(val["log_text"])
                self.symbols[new_lr] = val
        except Exception as e:
             self._logger.warning("Error in update symbols : {}".format(tb.format_exc()))





class FwlogParser():

    def __init__(self, bin_file, phy_bin_file, core_type, logger, internal_logger):

        self.core_type = core_type
        self.bin_file = bin_file
        self.phy_bin_file = phy_bin_file
        self.acilog = logger
        self._logger = internal_logger
        self.log_count = 0
        self.device_connected = False
        self.last_bin_id = 0
        self.source_device = 0  # TBD update this

        self.protocol_parsers = {
                           0: FwLoggerParser_Text,  # Human-Readable Logs
                           1: FwLoggerParser_Text,  # Human-Readable Logs
                           # 2: FwLoggerParser_Event,  # Events
                           # 3: FwLoggerParserBtEvent,  # BT Events
                           # 4: FwLoggerParser_NGPIO,  # Normal GPIO
                           # 5: FwLoggerParserBtEvent,  # BtFwLoggerParserDashboard,
                           # 7: BtFwLoggerParserNGPIOv2,  # BT GPIO version 2.
                           8: FwLoggerParser_NewFormat,  # Logger WIFI PHY
                           9: FwLoggerParser_NewFormat,  # Logger BT PHY
                           # 10: FwLoggerParser_BTProtocolViewer,  # BT Protocol Viewer
                           16: FwLoggerParser_NewFormat,  # Logger WIFI MAC
                           17: FwLoggerParser_NewFormat,  # Logger BT MAC
                           20: FwLoggerParser_NGPIO_NewFormat,  # GPIO WIFI MAC
                           22: FwLoggerParser_Extended_NewFormat,  # Ext WIFI MAC
                           23: FwLoggerParser_Extended_NewFormat,  # Ext BT MAC
                           24: FwLoggerParser_NewFormat,  # Logger WIFI PHY
                           25: FwLoggerParser_NewFormat,  # Logger BT PHY
                           30: FwLoggerParser_Extended_NewFormat,  # Ext Wifi Phy
                           31: FwLoggerParser_Extended_NewFormat,  # Ext BT Phy
        }

        self.legal_protocol_parsers = self.protocol_parsers.keys()
        self.phy_protocol_parsers = [8, 9, 24, 25]
        # Verify we parse messages by relevant core parser

        self.legal_protocol_parsers = [0, 8, 16, 20, 22, 24, 30]
        self.protocol_parser_handlers = [None] * 32  # len(self.protocol_parsers)

        for parser_id, parser in self.protocol_parsers.iteritems():
            if parser_id in self.legal_protocol_parsers:
                is_phy = parser_id in self.phy_protocol_parsers
                self.protocol_parser_handlers[parser_id] = parser(self, is_phy, self._logger)

        self.update_symbols()

    def read_cpf_bin_id(self):
        return 0

    def update_symbols(self):
        self._update_symbols()

    def _update_symbols(self):
        try:
            self.bin = BinParser(self.bin_file)
            self.bin_type = self.bin.parse_bin()
            self.symbols = self.bin.get_symbols()
            self.enums = self.bin.get_enums()
            self.bin_id = self.bin.bin_id
        except Exception as e:
            self.bin_type = 'None'
            self.symbols = {}
            self.enums = {}
            print "Exception:", e
            self.acilog.write("WARNING: Missing or invalid MAC bin file %s" % self.bin_file)
        try:
            self.phy_bin = BinParser(self.phy_bin_file)
            self.phy_bin_type = self.phy_bin.parse_bin()
            self.phy_symbols = self.phy_bin.get_symbols()
            self.phy_enums = self.phy_bin.get_enums()

        except Exception as e:
            self.phy_bin_type = 'None'
            self.phy_symbols = {}
            self.phy_enums = {}
            print "Exception:", e
            self.acilog.write("WARNING: Missing or invalid PHY bin file %s" % self.phy_bin_file)


    def write_fwlog(self, ts_pc, core_type, ts_fw, line_num, file_name, func_name, group_name, severity, text, lr):
        # remove folder name from file

        file_name = os.path.basename(file_name)
        location = "{}:{}".format(file_name, line_num)
        print "FWLOG {:40}{:40} {:,} {}".format(location, func_name, ts_fw, text)


    def parse_error(self):
        if self.device_connected:
            self._logger.info("Lost sync with device %s - searching for keep alive message"
                              " for synchronization. last_bin_id %d" % (self.source_device, self.last_bin_id))
        self.device_connected = False  # Assume we lost sync with device

    def is_data_sync(self,word):
        try:
            data, = struct.unpack("<L", word)
            headr = data & 0xFF
            lr = data >> 8
            # check that header and LR are ok
            hdr_byte = (headr & 0b11111000) >> 3
            if hdr_byte in self.legal_protocol_parsers:
                # header byte is ok, check the LR.
                parser = self.protocol_parser_handlers[hdr_byte]
                symbols = parser.get_symbols()
                if lr in symbols:
                    print "Synced by good data"
                    return True
        except Exception as E:
            print "Error in is_data_sync 0x%X error %s" % (data,repr(E))
        return False

    def search_for_sync(self):
        # for sync, message length must be at least 6 bytes were the [2:5] = 0x55555555
        h1, h2, ka = struct.unpack("<BBL", self.stream[0:6])

        if ka == 0x55555555 and (h1 >> 3) < 2:
            print "Found sync word"
            return True
        # try to sync to data
        return self.is_data_sync(self.stream[0:4])
    
    def parse_synced_stream(self,stream):
        self.device_connected = True
        self.parse_stream(stream)

    def parse_stream(self, stream):
        self.stream = stream
        required_length = 0
        lost_bytes = []
        #
        # Search for all traces inside the stream
        #
        while len(self.stream) > 0:

            # if we are not in sync, search it.
            if not self.device_connected:
                if (len(self.stream) < 6):
                    required_length = 6
                    break
                if not self.search_for_sync():
                    lost_bytes.append(ord(self.stream[0]))
                    self.stream = self.stream[1:]
                    continue
                else:
                    if lost_bytes:
                        print "Lost {} bytes: {}".format(len(lost_bytes), lost_bytes)
                        print lost_bytes
                        lost_bytes = []
                    self.device_connected = True
            #
            # First byte in data represents the trace type
            #
            hdr_byte = (ord(self.stream[0]) & 0b11111000) >> 3
            if hdr_byte in self.legal_protocol_parsers:
                parser = self.protocol_parser_handlers[hdr_byte]
            else:
                if len(self.stream) < 4:
                    required_length = 4
                    break
                first_word, = struct.unpack("<L", self.stream[0:4])

                # self.acilog.write("Invalid header received... hdr %d" % hdr_byte)
                self._logger.error("Got Invalid header- {}".format(hdr_byte))
                # self.print_stream()
                #self.stream = self.stream[1:]
                self.parse_error()  # Assume we lost sync with device
                continue

            if len(self.stream) < parser.min_length:
                required_length = parser.min_length
                break


            parser.update_stream(self.stream)

            length = parser.get_length()
            #
            # TEMP solution to prevent uart garbage from getting us stuck
            #
            if length > parser.get_max_len():
                self._logger.error("Got length {}, assume lost sync".format(length))
                self.stream = self.stream[1:]
                self.parse_error()  # Assume we lost sync with device
                continue

            # Length is Invalid for unknown BT event -> Check the next byte - [1:]
            if length <= 0:
                self._logger.error("Got length {}, assume lost sync".format(length))
                self.stream = self.stream[1:]
                continue

            # Assume we have enough data to parse the trace header
            #
            if len(self.stream) < length:
                required_length = length
                break

            #
            # Do we have at least one full trace? Sometimes we need more data to parse the trace
            #

            parse_result = parser.parse_trace(length)

            if parse_result == FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_INVALID:
                self._logger.info("Got FW_LOGGER_MESSAGE_PARSE_INVALID")
                self.parse_error()  # Assume we lost sync with device
            elif parse_result == FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_PARTIAL_LENGTH:
                break  # we need more data to parse the trace
            elif parse_result == FwLoggerParser.FW_LOGGER_MESSAGE_PARSE_OK:
                self.log_count += 1
          # self.last_msg = self.stream[0:length]
            self.stream = self.stream[length:]

        return required_length


if len(sys.argv) != 3:
    print "Usage:"
    print "logger.py <cpf_file> <binary_logger_file>"
    exit(1)
    
cpf_file = sys.argv[1]
log_file = sys.argv[2]
internal_logger = myLogger()
bin_file = "mac_log_symbols.bin"
phy_bin_file = "phy_log_symbols.bin"
os.system("tar -xvf {} {}".format(cpf_file,bin_file))
os.system("tar -xvf {} {}".format(cpf_file,phy_bin_file))
lgr = FwlogParser(bin_file, phy_bin_file, CoreType.WIFI_MAC, internal_logger, internal_logger)
lgr.device_connected = True  # we should be in sync ...
log_data = open(log_file,"rb").read()
lgr.parse_synced_stream(log_data)


