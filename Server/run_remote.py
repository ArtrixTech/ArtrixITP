from gevent import monkey
from gevent.pywsgi import WSGIServer
from geventwebsocket.handler import WebSocketHandler
from flask import Flask

from threading import Thread
from httpLocal import iot
import time

monkey.patch_all()

app = Flask(__name__, static_folder="", static_url_path=None)
app.register_blueprint(iot)

app.config.update({
    'SERVER_NAME': 'iot.rapi.link:30126',
    'DEBUG': 'True'
})
app.debug = True

# app.run(host="45.76.102.168", port=80)

print(app.url_map)

http_server = WSGIServer(('172.16.25.227', 30126), app, handler_class=WebSocketHandler)


def start():
    http_server.serve_forever()


def run():
    tr = Thread(target=start)
    tr.start()

# while 1:
# No delete this part for unknowing reason to keep the program running!!!
# time.sleep(2000)
