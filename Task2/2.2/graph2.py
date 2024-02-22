import matplotlib.pyplot as plt

args = [2, 4, 7, 8, 16, 20, 40]
sForNsteps40000000 = [1.9, 3.49, 5.72, 6.42, 10.82, 12.55, 18.01]
sForNsteps80000000 = [1.92, 3.65, 6.10, 6.87, 13.20, 15.24, 19.94]

fig, ax = plt.subplots()
ax.set_xlabel("p", fontsize=16, loc="right")
ax.set_ylabel("Sp", fontsize=16, loc="top", rotation=0)
plt.title('График ускорения зависимости от количества потоков', weight='bold', size=22)
plt.plot(args, sForNsteps40000000, label='nsteps = 40000000')
plt.plot(args, sForNsteps80000000, label='nsteps = 80000000')
plt.plot([1, 40], [1, 40], linestyle='--', color='red', label='Linear')
plt.legend(loc='best')
plt.show()
