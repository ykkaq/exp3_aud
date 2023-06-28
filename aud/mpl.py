import pandas as pd
import matplotlib.pyplot as plt

a = pd.read_csv("a.csv", header=None)
b = pd.read_csv("b.csv", header=None)

plt.plot(a[1])
plt.plot(b[1])
plt.grid(True)
plt.show()
