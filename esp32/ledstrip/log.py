import serial


ser = serial.Serial('COM4', 115200)
ser.close()
ser.open()

size = 256 * 1024

with open("log.raw", "wb") as f:
    count = 0
    while count < size:
        # f.write(b'\xAA\xAA\xAA\xAA')
        data = ser.read(256)
        count += len(data)
        # print(data)
        f.write(data)
        print(count / size * 100)
        # print(count)
