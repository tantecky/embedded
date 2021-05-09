import serial
from serial.tools.list_ports_windows import comports
import matplotlib.pyplot as plt

PORT = None

for port in comports():
    if 'CP210x' in port.description:
        PORT = port.name
        break

plt.ion()
fig = plt.figure()

ser = serial.Serial(PORT, 115200)
print(PORT)
ser.close()
ser.open()

x = []
y = []

while True:
    try:
        line = ser.readline().decode('ascii').strip(' \r\n')

        if not line:
            continue

        if '++' in line:
            x.clear()
            y.clear()

            while True:
                line = ser.readline().decode('ascii').strip(' \r\n')

                if not line:
                    continue

                if '--' in line:
                    fig.clear()
                    plt.semilogx(x, y, '-o')
                    plt.ylim([0, 1])
                    fig.canvas.draw()
                    fig.canvas.flush_events()
                    break

                idx, freq, val = line.split(' ')
                x.append(float(freq))
                y.append(float(val))

    except:
        continue
