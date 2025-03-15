# example plotting shader

import matplotlib.pyplot as plt

fig, ax = plt.subplots()

ax.plot(x, y)

ax.set_title(title)
ax.set_xlabel(xlabel)
ax.set_ylabel(ylabel)

plt.savefig('../graph.png')
plt.show()
