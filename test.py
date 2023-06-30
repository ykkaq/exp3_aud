import math

# 端点の座標
x1, y1 = -10, 0
x2, y2 = 10, 0

# 角度（ラジアン）
theta1 = math.radians(45)  # 45度
theta2 = math.radians(135)  # 30度

# 延長線の方程式の傾きとy切片を計算
m1 = math.tan(theta1)
b1 = -m1 * x1
m2 = math.tan(theta2)
b2 = -m2 * x2

# 2つの直線の交点を求める
x = (b2 - b1) / (m1 - m2)
y = m1 * x + b1

print(x1, x2)
print(theta1, theta2)
print(m1, m2)
print(x, y)
