import pynbody
import numpy as np

dt = 0.0001
t_max = 0.01

N = 1000 
x = np.random.rand(3 * N).astype(np.float32)
v = np.zeros(3 * N, dtype=np.float32)
m = np.ones(N, dtype=np.float32)

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

positions = x.reshape(-1, 3)

fcolor = 'white'
plt.style.use('classic')
plt.rcParams.update({'text.color': fcolor, 
                     'axes.labelcolor': fcolor,
                     'axes.edgecolor': fcolor,
                     'xtick.color': fcolor,
                     'ytick.color': fcolor,
                     'font.family': 'serif'})

fig, ax = plt.subplots()
fig.patch.set_facecolor('black')
ax.set_facecolor('black')
ax.set_aspect('equal', 'box')

bsize = 1
ax.set_xlim(0, bsize)
ax.set_ylim(0, bsize)

scatter = ax.scatter(positions[:, 0], positions[:, 1], color='white', s=m)

def update(frame):
    pynbody.stepf(x, v, m, dt)
    positions = x.reshape(-1, 3)
    scatter.set_offsets(positions[:, :2])
    return scatter,

ani = FuncAnimation(fig, update, frames=np.arange(0, t_max, dt),
                    blit=True, interval=10)

plt.show()

