class NetAlarm(object):

    def __init__(self):
        self.config = None

    def load_config(self):
        from ujson import load
        with open('cfg.json', 'r') as cfg:
            self.config = load(cfg)

    def connect_wifi(self):
        import network
        import time

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
                return True

        print('Unable to connect to AP: {}'.format(ssid))
        return False


def main():
    alarm = NetAlarm()
    alarm.load_config()
    alarm.connect_wifi()

main()
