import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq
import numpy as np
from scipy.io.wavfile import write

data = np.fromfile('data.raw', dtype='<i2')
print(np.min(data), np.max(data))
write("log.wav", 44100, data.astype(np.int16))


# Number of sample points
N = 1024
# sample spacing
T = 1.0 / 44100
x = np.linspace(0.0, N*T, N, endpoint=False)
y = data[:N]
yf = fft(y)
xf = fftfreq(N, T)[:N//2]
print(xf)
plt.plot(xf, 2.0/N * np.abs(yf[0:N//2]))
plt.grid()
plt.show()
