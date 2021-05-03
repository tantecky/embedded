import numpy as np
from scipy.fft import rfft, fft

x = np.arange(8)
print(x)
print(fft(x))
print('======')
print(rfft(x))
