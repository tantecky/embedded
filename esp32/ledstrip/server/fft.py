import numpy as np
from scipy.fft import rfft, fft, rfftfreq

N = 2**10
T = 1.0 / 44100

x = np.arange(N)
print(len(x))
# print(fft(x))
print('======')
yf = rfft(x)
print(np.sum(yf))

print('SUM MAG**2:')
print(np.sum(np.abs(yf)**2))

print('SUM MAG:')
print(np.sum(np.abs(yf)))

# print(rfftfreq(N, d=T))
print(len(rfftfreq(N, d=T)))
