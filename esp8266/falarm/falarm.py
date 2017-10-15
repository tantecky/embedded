import sys
from machine import Pin, unique_id, Timer, PWM
import network
from time import sleep_ms
import ubinascii
import ujson
from umqtt.simple import MQTTClient


class FridgeAlarm:

    def __init__(self):
        self.config = None
        self.topic = None

        #  pins

    def load_config(self):
        with open('cfg.json', 'r') as cfg:
            self.config = ujson.load(cfg)

        # handy shortcut
        self.topic = self.config['topic']

    def connect_wifi(self):
        ap_if = network.WLAN(network.AP_IF)
        ap_if.active(False)

        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(True)

        if sta_if.isconnected():
            sta_if.disconnect()

        sta_if.connect(self.config['ssid'], self.config['passwd'])

        for _ in range(20):
            sleep_ms(1000)

            if sta_if.isconnected():
                return

        print('Unable to connect to AP: %r' % ssid)
        sys.exit(1)

    def blink(self, duration=50, times=1):
        for _ in range(times):
            self.d4.low()
            sleep_ms(duration)
            self.d4.high()
            sleep_ms(duration)

    def beep(self, duration=100, times=3):
        for _ in range(times):
            self.piezo.duty(400)
            sleep_ms(duration)
            self.piezo.duty(0)
            sleep_ms(duration)


def loop(alarm):
    while True:
        sleep_ms(50)


def main():
    alarm = FridgeAlarm()
    alarm.load_config()
    alarm.connect_wifi()
    loop(alarm)


main()
