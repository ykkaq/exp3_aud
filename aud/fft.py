import numpy as np
import matplotlib.pyplot as plt

# サンプルデータの生成
Fs = 1000  # サンプリング周波数
T = 1 / Fs  # サンプリング間隔


Ls = []  # サンプル数
L = 64

t = np.linspace(0.0, L * T, L)  # 時間ベクトル

# 信号を生成（50Hzと120Hzの合成信号）
S = 0.7 * np.sin(2 * np.pi * 50 * t) + np.sin(2 * np.pi * 120 * t)

# FFTを実行
Y = np.fft.fft(S)

# 2つのサブプロットを作成
fig, ax = plt.subplots(2, 1)

# 時間領域の信号をプロット
ax[0].plot(t, S)
ax[0].set_xlabel("Time")
ax[0].set_ylabel("Amplitude")

# 周波数領域の信号をプロット
ax[1].plot(2.0 / L * np.abs(Y[: L // 2]))
ax[1].set_xlabel("Frequency (Hz)")
ax[1].set_ylabel("|Y(f)|")

# グラフを表示
plt.show()
