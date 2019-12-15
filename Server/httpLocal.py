# coding=utf-8

from flask import Flask
import threading
from flask import render_template
from flask import Blueprint

iot = Blueprint('iot', __name__, template_folder="templates", static_folder="static")


temps = {}
pres = {}
humi = {}

device = {}

control_sock = None

# [command_RECV] > [command_send] #
reactions = {"SER23333": ["U,UPDSENSOR,CLI5F33Q,HUMANSENSOR,BOOL,1,END|>D,SETPWR,CLI6E55S,ON,END|#",
                          "U,UPDSENSOR,CLI5F33Q,HUMANSENSOR,BOOL,0,END|>D,SETPWR,CLI6E55S,OFF,END|#",
                          "U,UPDSENSOR,CLI6M5E4,HUMANSENSOR,BOOL,1,END|>D,SETPWR,CLI6E55S,ON,END|#",
                          "U,UPDSENSOR,CLI6M5E4,HUMANSENSOR,BOOL,0,END|>D,SETPWR,CLI6E55S,OFF,END|#"]}


@iot.route('/')
def hello2():
    return "1234123123"

@iot.route('/show')
def hello():
    return render_template('module.html')


@iot.route('/tempereature/<DEVICE_ID>')
def get_temp(DEVICE_ID):
    if DEVICE_ID in temps:
        return temps[DEVICE_ID]
    else:
        return "--.--"


@iot.route('/pressure/<DEVICE_ID>')
def get_pres(DEVICE_ID):
    if DEVICE_ID in pres:
        return pres[DEVICE_ID]
    else:
        return "----.--"


@iot.route('/humidity/<DEVICE_ID>')
def get_humi(DEVICE_ID):
    if DEVICE_ID in humi:
        return humi[DEVICE_ID]
    else:
        return "--.--"


@iot.route('/reactions/<DEVICE_ID>')
def get_reactions(DEVICE_ID):
    ret_s = "$"
    for line in reactions[DEVICE_ID]:
        ret_s += line
    return ret_s


@iot.route('/control/<DEVICE_ID>/<command>')
def control(DEVICE_ID, command):
    print(DEVICE_ID + " - " + command)
    if control_sock:
        control_sock.send(command.encode())
        return "OK"
    else:
        return "BAD"


@iot.route('/device_list/<DEVICE_ID>')
def device_list(DEVICE_ID):
    ret_s = ""
    for subDeviceName in device[DEVICE_ID]:
        ret_s += subDeviceName
        ret_s += ","
    ret_s = ret_s[0:len(ret_s) - 1]
    return ret_s
