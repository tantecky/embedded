import sys
import machine
import network
import time
import ubinascii
import ujson
from umqtt.robust import MQTTClient


class DoorAlarm(object):

    def __init__(self):
        self.config = None
        self.p0 = machine.Pin(2, machine.Pin.OUT)

    def load_config(self):
        with open('cfg.json', 'r') as cfg:
            self.config = ujson.load(cfg)

    def connect_wifi(self):
        ap_if = network.WLAN(network.AP_IF)
        ap_if.active(False)

        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(True)

        if sta_if.isconnected():
            sta_if.disconnect()

        sta_if.connect(self.config['ssid'], self.config['passwd'])

        for _ in range(20):
            time.sleep(1)

            if sta_if.isconnected():
                return

        print('Unable to connect to AP: {}'.format(ssid))
        sys.exit(1)

    def mqtt_callback(self, topic, msg):
        self.p0.value(not self.p0.value())

    def mqtt_subscribe(self):
        client_id = b'tom_' + ubinascii.hexlify(machine.unique_id())
        self.mqtt = MQTTClient(client_id, self.config['host'],
                               port=int(self.config['port']))

        self.mqtt.set_callback(self.mqtt_callback)
        self.mqtt.connect()
        self.mqtt.subscribe(self.config['topic'])


def main():
    alarm = DoorAlarm()
    alarm.load_config()
    alarm.connect_wifi()
    alarm.mqtt_subscribe()

    while True:
        # Blocking wait for message
        alarm.mqtt.wait_msg()

    alarm.mqtt.disconnect()

main()
