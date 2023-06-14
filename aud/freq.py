import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Arduinoのシリアルポートを開く
arduino = serial.Serial("COM3", 9600)

# データを格納するリスト
data_amp1 = []
data_amp2 = []
data_phase = []


# プロットを更新する関数
def update(frame):
    line = arduino.readline().decode("utf-8").strip()
    amp1, amp2, phase = map(float, line.split())
    data_amp1.append(amp1)
    data_amp2.append(amp2)
    data_phase.append(phase)
    if len(data_amp1) > 50:
        data_amp1.pop(0)
        data_amp2.pop(0)
        data_phase.pop(0)
    plt.cla()
    plt.plot(data_amp1, label="Amplitude 1")
    plt.plot(data_amp2, label="Amplitude 2")
    plt.plot(data_phase, label="Phase difference")
    plt.legend()


# アニメーションを作成
ani = FuncAnimation(plt.gcf(), update, interval=100)

# プロットを表示
plt.show()
