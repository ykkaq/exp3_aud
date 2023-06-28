import serial

# シリアルポートを開く（ポート名とボーレートは適切に設定してください）
ser = serial.Serial("/dev/ttyACM0", 9600)

# テキストファイルを開く
with open("output.txt", "w") as f:
    while True:
        # シリアルポートからデータを読み取る
        line = ser.readline().decode("utf-8").strip()

        # データをテキストファイルに書き込む
        f.write(line + "\n")

# シリアルポートを閉じる
ser.close()
