import matplotlib.pyplot as plt
from scipy.fft import rfft, rfftfreq
import numpy as np
from scipy.io.wavfile import write
from scipy.signal import blackman, hann, hamming, kaiser

data = np.fromfile('data.raw', dtype='<f4')
# print(np.min(data), np.max(data))
# write("log.wav", 44100, data.astype(np.int16))


# Number of sample points
N = 1024
# sample spacing
T = 1.0 / 44100
# x = np.linspace(0.0, N*T, N, endpoint=False)
y = data[:N]
w = hann(N, False)
yf = np.abs(rfft(y * w))
xf = rfftfreq(N, d=T)
print(len(xf))
plt.plot(xf, yf, '-o')
plt.xscale('log')
print(xf[np.argmax(yf)])
plt.grid()
plt.show()
