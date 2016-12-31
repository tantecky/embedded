import sys
from machine import Pin, unique_id, Timer, PWM
import network
from time import sleep_ms
import ubinascii
import ujson
from umqtt.simple import MQTTClient


class Messages:
    # commands
    ARM = b'arm'
    DISARM = b'disarm'
    # events
    ARMED = b'armed'
    DISARMED = b'disarmed'
    TRIGGERED = b'triggered'


class DoorAlarm:

    # in seconds
    PING_INTERVAL = 60
    KEEP_ALIVE_INTERVAL = 2 * PING_INTERVAL + 30

    def __init__(self):
        self.config = None
        self.topic = None
        self.armed = False
        self.triggered = False

        #  pins
        self.d4 = Pin(2, Pin.OUT, value=1)
        self.d1 = Pin(5, Pin.IN, Pin.PULL_UP)
        self.d2 = Pin(4, Pin.IN, Pin.PULL_UP)
        self.d5 = Pin(14, Pin.IN, Pin.PULL_UP)
        self.d6 = Pin(12)
        self.piezo = PWM(self.d6)
        self.piezo.freq(980)
        self.piezo.duty(0)

        self.ping_timer = Timer(-1)
        self.ping_requested = False

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

    def arm(self):
        if self.armed:
            return

        self.armed = True
        self.send_msg(Messages.ARMED)
        self.blink(times=4)

    def disarm(self):
        if not self.armed:
            return

        self.armed = False
        self.triggered = False
        self.send_msg(Messages.DISARMED)
        self.blink(times=2)

    def send_msg(self, msg):
        self.mqtt.publish(self.topic, msg)

    def mqtt_callback(self, topic, msg):
        if msg == Messages.ARM:
            self.arm()
        elif msg == Messages.DISARM:
            self.disarm()
        #  else:
            #  print('Unknown message: %r' % msg)

    def mqtt_subscribe(self):
        client_id = b'tom_' + ubinascii.hexlify(unique_id())
        self.mqtt = MQTTClient(client_id, self.config['host'],
                               port=int(self.config['port']),
                               keepalive=self.KEEP_ALIVE_INTERVAL)
        #  keepalive=0)

        self.mqtt.set_callback(self.mqtt_callback)
        self.mqtt.connect(clean_session=True)
        self.mqtt.subscribe(self.topic)

    def setup_irqs(self):
        self.ping_timer.init(period=self.PING_INTERVAL * 1000,
                             mode=Timer.PERIODIC,
                             callback=lambda t: self.request_ping())
        self.d5.irq(trigger=Pin.IRQ_RISING, handler=self.set_trigger)

    def check_numpad(self):
        if self.d1.value() == 0:
            self.disarm()

        if self.d2.value() == 0:
            self.arm()

    def check_trigger(self):
        if self.armed and self.triggered:
            self.send_msg(Messages.TRIGGERED)
            self.beep()
            self.blink(duration=250, times=1)
            self.triggered = False

    def set_trigger(self, pin):
        if self.armed and self.d5.value() == 1:
            self.triggered = True

    def request_ping(self):
        self.ping_requested = True

    def check_ping_request(self):
        if self.ping_requested:
            self.mqtt.ping()
            self.ping_requested = False
            self.blink()

    def reconnect(self):
        while True:
            sleep_ms(10000)
            try:
                self.mqtt_subscribe()
                print('reconnected...')
                return
            except OSError as e:
                print("reconnect(): %r" % e)


def loop(alarm):
    while True:
        sleep_ms(50)
        try:
            alarm.mqtt.check_msg()
            alarm.check_ping_request()
            alarm.check_numpad()
            alarm.check_trigger()
        except OSError as e:
            print("loop(): %r" % e)
            alarm.reconnect()


def main():
    alarm = DoorAlarm()
    alarm.load_config()
    alarm.connect_wifi()
    alarm.mqtt_subscribe()
    alarm.setup_irqs()
    alarm.arm()

    loop(alarm)

    alarm.mqtt.disconnect()

main()
