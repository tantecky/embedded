class NetAlarm(object):

    def __init__(self):
        pass

    def connect_wifi(self):
        import network
        import time

        ap_if = network.WLAN(network.AP_IF)
        ap_if.active(False)

        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(True)

        if sta_if.isconnected():
            sta_if.disconnect()

        with open('wifi.cfg', 'r') as cfg:
            ssid = cfg.readline().strip(' \r\n')
            passwd = cfg.readline().strip(' \r\n')

        sta_if.connect(ssid, passwd)

        for _ in range(20):
            time.sleep(1)

            if sta_if.isconnected():
                return True

        print('Unable to connect to AP: {}'.format(ssid))
        return False


def main():
    alarm = NetAlarm()
    alarm.connect_wifi()

main()
