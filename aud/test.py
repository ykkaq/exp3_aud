import numpy as np
import matplotlib.pyplot as plt


def emphasis(ph, am):
    emphasized_ph = []
    for p, a in zip(ph, am):
        if abs(a) < 10:
            emphasized_ph.append(0.0)
        else:
            emphasized_ph.append(p)
    return np.array(emphasized_ph)


# 波形データの生成 (ここでは2つのサイン波を生成)
N = 1000  # サンプル数
f1 = 5  # 周波数1
f2 = 5  # 周波数2
phi = np.pi / 3  # 位相差
t = np.arange(N)  # 時間軸
y1 = np.sin(2 * np.pi * f1 * t / N)  # 波形1
y2 = np.sin(2 * np.pi * f2 * t / N + phi)  # 波形2 (位相差phiをもつ)


# フーリエ変換
Y1 = np.fft.fft(y1)
Y2 = np.fft.fft(y2)

# 位相スペクトルの計算
phase1 = np.angle(Y1)
phase2 = np.angle(Y2)

phase1 = emphasis(phase1, Y1)
phase2 = emphasis(phase2, Y2)

# phase1 = np.degrees(phase1)
# phase2 = np.degrees(phase2)

# 位相差の計算
phase_diff = phase1 - phase2

print(abs(max(phase1)))
print(abs(max(phase2)))
print(abs(max(phase_diff)))


plt.subplot(3, 1, 1)
plt.grid(True)
plt.plot(y1)
plt.plot(y2)

plt.subplot(3, 1, 2)
plt.grid(True)
plt.plot(np.abs(Y1))
plt.plot(np.abs(Y2))


plt.subplot(3, 1, 3)
plt.plot(phase_diff, alpha=0.4)
# plt.subplot(3, 1, 1)
plt.plot(phase1, alpha=0.4)
# plt.subplot(3, 1, 2)
plt.plot(phase2, alpha=0.4)
plt.grid(True)

plt.show()
