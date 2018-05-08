import sys
from machine import Pin, Timer, PWM
import network
from time import sleep_ms
import ujson

#  PINS:
#  d4 = led do not connect
#  d5 = reed switch
#  d6 = piezo


class FridgeAlarm:

    def __init__(self):
        self.config = None
        self.topic = None
        self.state_changed = False
        self.time_elapsed = False
        #  pins
        self.d4 = Pin(2, Pin.OUT, value=1)
        self.d6 = Pin(12)
        self.reed_pins = []

        self.piezo = PWM(self.d6)
        self.piezo.freq(980)
        self.piezo.duty(0)

        self.timer = Timer(-1)

    def load_config(self):
        with open('cfg.json', 'r') as cfg:
            self.config = ujson.load(cfg)

        # handy shortcut
        self.threshold = int(self.config['threshold'])

    def connect_wifi(self):
        ap_if = network.WLAN(network.AP_IF)
        ap_if.active(False)

        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(False)

    def blink(self, duration=25, times=1):
        for _ in range(times):
            self.d4.value(0)
            sleep_ms(duration)
            self.d4.value(1)
            sleep_ms(duration)

    def beep(self, duration=100):
        self.piezo.duty(400)
        sleep_ms(duration)
        self.piezo.duty(0)
        sleep_ms(duration)

    @property
    def is_opened(self):
        return any(pin.value() == 1 for pin in self.reed_pins)

    def on_elapsed(self):
        while self.is_opened:
            self.blink()
            self.beep()

    def on_open(self):
        self.d4.value(0)
        self.timer.init(period=self.threshold, mode=Timer.ONE_SHOT,
                        callback=lambda t: setattr(self, 'time_elapsed', True))

    def on_close(self):
        self.d4.value(1)
        self.timer.deinit()

    def check_state(self):
        if self.is_opened:
            if not self.state_changed:
                self.state_changed = True
                self.on_open()
        else:
            if self.state_changed:
                self.state_changed = False
                self.on_close()
            #  to avoid an unknown state
            self.state_changed = False
            self.time_elapsed = False

        if self.time_elapsed:
            self.time_elapsed = False
            self.on_elapsed()

    def setup(self):
        self.load_config()
        for pin in self.config['reed_pins']:
            self.reed_pins.append(Pin(int(pin), Pin.IN, Pin.PULL_UP))
        self.connect_wifi()

    def loop(self):
        while True:
            sleep_ms(50)
            self.check_state()


def main():
    alarm = FridgeAlarm()
    alarm.setup()
    alarm.loop()


main()
