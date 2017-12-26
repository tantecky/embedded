#!/usr/bin/env python3
import numpy as np
from scipy.io.wavfile import read
from itertools import groupby

GAP_LENGTH = 10e3

def main():
    rate, data = read('./faac01.wav')
    print('sampling rate: {} Hz'.format(rate))
    print('uniq values: {}'.format(np.unique(data)))
    step = 1.0e6 / rate
    print('step: {} us'.format(step))

    zero = data.min()
    record = []

    print()
    for k, g in groupby(data[:] > zero):
        record.append((k, int(round(len(list(g)) * step, 0))))

    record = np.asarray(record)[1:-1, :]
    delays = record[:, 1]
    print('min delay: {} us'.format(delays.min()))
    print('max delay: {} us'.format(delays.max()))
    np.set_printoptions(threshold=len(delays) + 1)

    #  search for gaps > 10 ms
    gaps = np.where(delays > GAP_LENGTH)[0]
    chunks = np.array_split(delays, gaps)
    chunks_fixed = []

    for chunk in chunks:
        if chunk[0] > GAP_LENGTH:
            chunk = chunk[1:]

        chunks_fixed.append(chunk)

    print('chunks spans: {} us'.format(delays[gaps]))
    print('chunks count: {}'.format(len(chunks_fixed)))

    with open('faac/faac.h', 'w') as f:
        print('const int DELAYS[] = ', file=f)
        print(np.array2string(chunks_fixed[1], separator=',')
                .replace('[', '{')
                .replace(']', '};'),
                file=f)

if __name__ == "__main__":
    main()

