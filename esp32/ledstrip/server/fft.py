import numpy as np
from scipy.fft import rfft, fft

x = np.arange(2**10)
print(len(x))
# print(fft(x))
print('======')
yf = rfft(x)
print(np.sum(yf))

print('SUM MAG**2:')
print(np.sum(np.abs(yf)**2))

print('SUM MAG:')
print(np.sum(np.abs(yf)))
