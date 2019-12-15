# coding=utf-8

import socket
import threading
import httpLocal as httpProcess
import time

import sys

args = sys.argv[1:]
mode = "REMOTE"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

if "-l" in args:
    s.bind(('127.0.0.1', 48903))
    import run_local

    run_local.run()

elif "-r" in args:
    s.bind(('172.16.25.227', 48903))
    import run_remote

    run_remote.run()

# s.bind(('10.104.152.191', 6652))
s.listen(5)
print('Waiting for connection....')
clients = dict()


class PowerState:
    state = False


pwrState = PowerState()


def process_message(sock, message):
    message = message.rstrip("|")
    global lastState

    if "UPDSENSOR" in message:

        if "HUMANSENSOR" in message:
            if "BOOL,1" in message:
                sock.send("##DOWNLINK##S,DOWNLINK,SETPWR,CLI6E55S,ON,END|".encode())
                print("         [Send]:ON")
            elif "BOOL,1":
                sock.send("##DOWNLINK##S,DOWNLINK,SETPWR,CLI6E55S,OFF,END|".encode())
                print("         [Send]:OFF")

        if "TEMP" in message:

            splitResult = message.split(",")
            temp = splitResult[5]
            deviceName = splitResult[2]

            print("     Got Temp:" + temp + "C")

            httpProcess.temps[deviceName] = temp

            if float(temp) > 30:
                if not pwrState.state:
                    sock.send("##DOWNLINK##S,DOWNLINK,SETPWR,CLI6E55S,ON,END|".encode())
                    print("         [TEMPLIGHT]:ON")

                    pwrState.state = True

            else:
                if pwrState.state:
                    sock.send("##DOWNLINK##S,DOWNLINK,SETPWR,CLI6E55S,OFF,END|".encode())
                    print("         [TEMPLIGHT]:OFF")
                    pwrState.state = False

        if "PRES" in message:
            splitResult = message.split(",")
            presNow = splitResult[5]
            deviceName = splitResult[2]

            print("     Got Pres:" + presNow + "hPa")

            httpProcess.pres[deviceName] = presNow

        if "HUMI" in message:
            splitResult = message.split(",")
            humiNow = splitResult[5]
            deviceName = splitResult[2]

            print("     Got Humi:" + humiNow + "%")

            httpProcess.humi[deviceName] = humiNow

    if "REGDEV" in message:
        res = message.split(",")
        cli = Client()
        cli.DEVICE_ID = res[1]
        cli.connectSock = sock
        clients[cli.DEVICE_ID] = cli
        print("ClientRegistered:" + res[1])

    if "REPORTDEVICE" in message:

        res = message.split(",")  # Client Name
        currentClientName = res[1]
        currentClient = clients[currentClientName]
        assert isinstance(currentClient, Client)

        subDeviceList = []

        for cliName in res[2:]:
            if "CLI" in cliName:
                sDev = SubDevice()  # New Sub Device Object
                sDev.alive = True
                sDev.DEVICE_ID = cliName

                currentClient.subDevices[cliName] = sDev
                subDeviceList.append(cliName)

                print("     [%s]Device:%s" % (currentClient.DEVICE_ID, cliName))

        httpProcess.device[currentClientName] = subDeviceList

        currentClient.updateOnlineState(res[2:])
        currentClient.showOnlineState()


def process_connection(sock, addr):
    try:
        # if not str(addr).find("192.168"):
        print('Accept new connection from %s:%s...' % addr)
        while True:

            assert isinstance(sock, socket.socket)
            data = sock.recv(1024)
            if not data or data.decode('utf-8') == 'exit':
                break

            if data:
                content = bytes(data).decode("utf-8")
                print(content)
                if content and content.endswith("|"):
                    tmpContent = "##ACKRESPONSE##"
                    tmpContent += content
                    sock.send(tmpContent.replace("\n", "").encode())

                    process_message(sock, content)
    except ConnectionAbortedError:
        pass


class SubDevice:
    online = False
    DEVICE_ID = ""


class Client:
    def updateOnlineState(self, list):  # Update the state of devices

        for devKey in self.subDevices:
            sDev = self.subDevices[devKey]
            sDev.online = False
            for input_device in list:

                if sDev.DEVICE_ID == input_device:
                    sDev.online = True

    def showOnlineState(self):

        for devKey in self.subDevices:
            sDev = self.subDevices[devKey]
            print(str("     Device " + sDev.DEVICE_ID) + "-Online:" + str(sDev.online))

    subDevices = {}

    DEVICE_ID = ""
    connectSock = ""
    address = ""


s.settimeout(0.1)
while True:
    # 接受一个新连接:
    time.sleep(0.1)

    try:
        sock, addr = s.accept()
        httpProcess.control_sock = sock
        # 创建新线程来处理TCP连接:
        t = threading.Thread(target=process_connection, args=(sock, addr))
        t.start()
    except socket.timeout:
        pass
