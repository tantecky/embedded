import numpy as np
from scipy.fft import rfft, fft

x = np.arange(2**10)
print(len(x))
# print(fft(x))
print('======')
# print(rfft(x))
print(np.sum(rfft(x)))
