import matplotlib.pyplot as plt

args = [2, 4, 7, 8, 16, 20, 40]
S20000 = [1.95, 3.76, 6.45, 7.32, 13.78, 16.86, 27.50]
S40000 = [1.96, 3.80, 6.57, 7.50, 14.75, 18.24, 31.51]

fig, ax = plt.subplots()
ax.set_xlabel("p", fontsize=16, loc="right")
ax.set_ylabel("Sp", fontsize=16, loc="top", rotation=0)
plt.title('График ускорения зависимости от количества потоков', weight='bold', size=22)
plt.plot(args, S20000, label='M = 20000')
plt.plot(args, S40000, label='M = 40000')
plt.plot([1, 40], [1, 40], linestyle='--', color='red', label='Linear')
plt.legend(loc='best')
plt.show()
