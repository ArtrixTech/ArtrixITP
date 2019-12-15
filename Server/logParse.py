# coding=utf-8
import sys


for line in sys.stdin:

    if ("NowCommand:U,UPDSENSOR" in line or "##ACKRESPONSE##" in line or "AdHOC" in line or "[SER23333]GET:S,DOWNLINK,SETPWR," in line) and  "REPORTDEVICE" not in line :
        print(line.strip("\n"))

    if ("[Send]:ON\n        [Send]:OFF" in line ) and  "REPORTDEVICE" not in line :
        print(line.strip("\n"))