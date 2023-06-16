import serial

# Arduinoとのシリアル通信を開始
arduino = serial.Serial("/dev/ttyACM0", 9600)

count = 0

# ファイルを開く（書き込みモード）
with open("output.txt", "w") as f:
    while True:
        # Arduinoからのデータを読み込む
        # data = arduino.readline().decode("utf-8").strip()
        data = arduino.readline()
        data = data.decode("ascii", errors="ignore").strip()

        # ファイルに書き込む
        f.write(data + "\n")
        count += 1
        if count >= 1030:
            break

# シリアル通信を終了
arduino.close()
