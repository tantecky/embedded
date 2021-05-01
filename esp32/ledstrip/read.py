import numpy as np
from scipy.io.wavfile import write

data = np.fromfile('log.raw', dtype='>i2')
print(data, np.min(data), np.max(data))
print(len(data) / 16000)
write("log.wav", 16000, data.astype(np.int16))
