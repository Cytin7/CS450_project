import matplotlib.pyplot as plt
import struct

# define your expect function here


def f(x, N, L, p):
    return 0.0

# read binary file


def read_data(filename="data"):
    data = []
    with open(filename, 'rb') as file:
        while True:
            data_bytes = file.read(8)  # size(double) = 8 bit
            if not data_bytes:
                break
            value, = struct.unpack('d', data_bytes)
            data.append(value)
    return data


if __name__ == "__main__":
    with open("config", "r") as config:
        N, L, p = config.read().split(',')
    N, L, p = int(N), int(L), float(p)

    data = read_data()
    M = len(data)

    calc = [f(i, N, L, p) for i in range(M)]
    rel_err = [abs(data[i]-calc[i])/data[i] for i in range(M)]

    plt.figure(figsize=(15, 5))
    plt.subplot(1, 2, 1)
    plt.plot(range(M), calc, 'r')
    plt.plot(range(M), data, 'b:')
    plt.subplot(1, 2, 2)
    plt.plot(range(M), rel_err, 'r')
    plt.show()
