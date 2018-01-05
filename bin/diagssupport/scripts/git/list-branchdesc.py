import subprocess, sys, argparse, re, os
from tabulate import tabulate

DEBUG = 0

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

def run_cmd (cmd):
    if (DEBUG == 1):
        print("Running cmd: " + cmd)

    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    output, ret = p.communicate()

    #output = p.communicate()
    #ret = subprocess.call(cmd, stdout=subprocess.PIPE, shell=True);

    #if (p.returncode != 0):
    if (ret):
        print(bcolors.FAIL + "-----------------------------------------------------------------------------------")
        print("ERROR! Cmd '" + cmd + "' returned " + str(ret))
        print(bcolors.FAIL + "-----------------------------------------------------------------------------------" + bcolors.ENDC)
        sys.exit(-1)

    return output

output = run_cmd('git branch -a')
output = output.split("\n")

tbl = []

for line in output:
    line = line.replace(" ", "")
    line_final = line.replace("*", "")

    if (line_final.find("remote") <> 0):
        out = run_cmd("git config branch." + line_final + ".description")
        out = out.replace("\n", " ")
        if (line.find("*") <> -1):
            line = bcolors.OKGREEN + line + bcolors.ENDC

        tbl.append([line, out])

print tabulate(tbl, [bcolors.WARNING + "branch" + bcolors.ENDC, bcolors.WARNING + "description" + bcolors.ENDC])

