import matplotlib.pyplot as plt
import numpy as np

# ファイルを開く（読み込みモード）
with open("output.txt", "r") as f:
    # データを行ごとに読み取る
    lines = f.readlines()

    # データを数値に変換してリストに格納する
    data_x = []
    data_y = []
    time = 0

    for line in lines:
        values = line.strip().split(",")
        print(values)
        data_x.append(float(values[0]))
        data_y.append(float(values[1]))
        time += float(values[2])

data_x = data_x[:1024]
data_y = data_y[:1024]
time /= 10**6

print(time)


r = 2  # Row
c = 1  # Column

# グラフの描画
plt.subplot(r, c, 1)
plt.plot(data_x, label="X")
# plt.plot(data_y, label="Y")
plt.xlabel("Sample")
plt.ylabel("Value")
plt.title("Data from output.txt")
plt.legend()

# --------
rate = 1024 / time
fft_x = np.abs(np.fft.fft(data_x))
freq_x = np.fft.fftfreq(len(fft_x), time)

print(fft_x)
print(freq_x)

plt.subplot(r, c, 2)
plt.plot(freq_x, fft_x)

# ---
plt.show()
