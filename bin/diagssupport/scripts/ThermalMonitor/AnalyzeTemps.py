import sys
import time
import numpy
import csv
from optparse import OptionParser

PLOTS_ENABLED = False
try:
    import matplotlib.pyplot as plt
    PLOTS_ENABLED = True
except:
    print >> sys.stderr, "No matplotlib installed. Please install to enable plotting features"


class Record:
    time = 0.0
    device_id = 0
    device_type = ''
    sensor_name = ''
    temp = 0.0
    
    def Print(self):
        print "%.3f, 0x%02x, %s, %s, %.2f" % (self.time, self.device_id, self.device_type, self.sensor_name, self.temp)

def get_min_temp(temp_data):
    min_temp = numpy.uint32.max
    idx = 0
    for i, temp in enumerate(temp_data):
        new_min = min(temp, min_temp)
        if new_min != min_temp:
            min_temp = new_min
            idx = i

    return min_temp, idx 

def get_max_temp(temp_data):
    max_temp = 0
    idx = 0
    for i, temp in enumerate(temp_data):
        new_max = max(temp, max_temp)
        if new_max != max_temp:
            max_temp = new_max
            idx = i

    return max_temp, idx 

def print_info(data_record):
    x_data = dict()
    y_data = dict()
    names = dict()

    for record in data_record:
        device_id = record.device_id
        name = record.device_type + '.' + record.sensor_name

        if device_id not in x_data:
            x_data[device_id] = []
            y_data[device_id] = []
        y_data[device_id].append(record.temp)
        x_data[device_id].append(record.time)
        names[device_id] = name

    for device_id in x_data:
        min_temp, idx = get_min_temp(y_data[device_id])
        print "%s:" % names[device_id]
        print "\tNum samples: %d" % len(y_data[device_id])
        readable_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(x_data[device_id][0]))
        print "\tFirst sample time: %.3f (%s)" % (x_data[device_id][0], readable_time)
        readable_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(x_data[device_id][-1]))
        print "\tLast sample time: %.3f (%s)" % (x_data[device_id][-1], readable_time)
        readable_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(x_data[device_id][idx]))
        print "\tMin temperature: %.2f" % (min_temp)
        print "\tMin temperature time: %.3f (%s)" % (x_data[device_id][idx], readable_time)
        max_temp, idx = get_max_temp(y_data[device_id])
        readable_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(x_data[device_id][idx]))
        print "\tMax temperature: %.2f" % (max_temp)
        print "\tMax temperature time: %.3f (%s)" % (x_data[device_id][idx], readable_time)


def plot_data(data_record):
    x_data = dict()
    y_data = dict()
    names = dict()
    min_time = data_record[0].time
    readable_min_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(min_time))

    for record in data_record:
        device_id = record.device_id
        name = record.device_type + '.' + record.sensor_name

        if device_id not in x_data:
            x_data[device_id] = []
            y_data[device_id] = []
        y_data[device_id].append(record.temp)
        x_data[device_id].append(record.time - min_time)
        names[device_id] = name

    for device_id in x_data:
        plt.plot(x_data[device_id], y_data[device_id], 'o', label=names[device_id])

    plt.title("Device Temperature Over Time")
    plt.xlabel("Seconds Since %.3f (%s)" % (min_time, readable_min_time))
    plt.ylabel("Temperature")
    plt.legend(fontsize='xx-small', numpoints=1)

    plt.show()

def print_data(data_record):
    for record in data_record:
        record.Print()

def findall_records_in_data_range(data_record, start_time=0, end_time=numpy.uint32.max):
    device_data = []
    for record in data_record:
        if record.time >= start_time and record.time <= end_time:
            device_data.append(record)

    return device_data

def findall_records_by_device_id(data_record, device_id):
    device_data = []
    for record in data_record:
        if record.device_id == device_id:
            device_data.append(record)

    return device_data

def findall_records_by_device_type(data_record, device_type):
    device_data = []
    types = device_type.split(',')
    for record in data_record:
        if record.device_type in types:
            device_data.append(record)

    return device_data

def findall_records_by_sensor_name(data_record, sensor_name):
    device_data = []
    names = sensor_name.split(',')
    for record in data_record:
        if record.sensor_name in names:
            device_data.append(record)

    return device_data

# setup:
# Time                 DeviceId Location  SensorName     Temp
# 1418415548.428s	 0x04	 soc	 CCC_THERMAL2	 27.29
def parse_file(fn):
    data = []
    f = open(fn, 'r')
    contents = f.read()
    reader = csv.reader(contents.split("\n"), delimiter=',')
    for row in reader:
        record = Record()
        if (len(row) != 5):
            continue
        #print "\t".join(row)
        try:
            record.time = float(row[0].strip('s'))
        except:
            print >> sys.stderr, "invalid record"
            print >> sys.stderr, row
            continue
        record.device_id = int(row[1], 16)
        record.device_type = row[2].strip()
        record.sensor_name = row[3].strip()
        record.temp = float(row[4])
        data.append(record)

    return data

def parse_cmd_line():
    parser = OptionParser()
    start_time=0
    end_time=numpy.uint32.max

    parser.add_option("-f", "--file",
                      dest="filename",
                      help="File containing the temperature data", metavar="FILE")
    parser.add_option("-o", "--output",
                      dest="output",
                      help="print the temperature data",
                      action="store_true",
                      default=False)
    if PLOTS_ENABLED:
        parser.add_option("-p", "--plot",
                          dest="plot",
                          help="plot the temperature data",
                          action="store_true",
                          default=False)
    parser.add_option("-i", "--info",
                      dest="info",
                      action="store_true",
                      default=False,
                      help="Output info about the data",)
    parser.add_option("-d", "--device_id",
                      type="int",
                      dest="device_id",
                      help="Only use data from this device id", metavar="DEV",)
    parser.add_option("-t", "--device_type",
                      dest="device_type",
                      help="Only use data from these device types. pmu, soc, etc", metavar="TYPE1,TYPE2,...",)
    parser.add_option("-n", "--sensor_name",
                      dest="sensor_name",
                      help="Only use data from these sensor names", metavar="NAME1,NAME2,...",)
    parser.add_option("-s", "--start_time",
                      type="float",
                      dest="start_time",
                      help="Only use data from this start time", metavar="START_TIME",)
    parser.add_option("-e", "--end_time",
                      type="float",
                      dest="end_time",
                      help="Only use data up to this end time", metavar="END_TIME",)

    (options, args) = parser.parse_args()
    if options.filename is None:
        parser.print_help()
    
    if (not options.output) and (PLOTS_ENABLED and not options.plot) and (not options.info):
        print "No action specified (output, plot or info)"
        parser.print_help()
        exit(1)

    data = parse_file(options.filename)

    if options.device_id:
        data = findall_records_by_device_id(data, options.device_id)

    if options.device_type:
        data = findall_records_by_device_type(data, options.device_type)

    if options.sensor_name:
        data = findall_records_by_sensor_name(data, options.sensor_name)

    if options.start_time:
        start_time = options.start_time

    if options.end_time:
        end_time = options.end_time

    if options.start_time or options.end_time:
        data = findall_records_in_data_range(data, start_time, end_time)

    if options.output:
        print_data(data)

    if options.info:
        print_info(data)

    if PLOTS_ENABLED:
        if options.plot:
            plot_data(data)


def main():
    parse_cmd_line()

if __name__ == '__main__':
    main()


