import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from simulation import Simulation

simulation = Simulation()

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
scatter = ax.scatter(simulation.positions[:, 0], simulation.positions[:, 1], color='white', s=simulation.m)

def update(frame):
    simulation.step()
    scatter.set_offsets(simulation.positions[:, :2])
    return scatter,

root = tk.Tk()
root.title("N-Body Problem")


canvas = FigureCanvasTkAgg(fig, master=root)
canvas_widget = canvas.get_tk_widget()
canvas_widget.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

ani = FuncAnimation(fig, update, frames=None, blit=True, interval=10)

control_frame = ttk.Frame(root)
control_frame.pack(side=tk.BOTTOM, fill=tk.X, padx=5, pady=5)

def update_parameters():
    global ani
    # Get values from the user
    dt = float(dt_slider.get())
    t_max = float(tmax_entry.get())
    N = int(n_particles_entry.get())
    
    # Reset simulation params
    simulation.reset(dt=dt, t_max=t_max, N=N)
    
    # Restart animation
    ani.event_source.stop()
    ani = FuncAnimation(fig, update, frames=None, blit=True, interval=10)
    ani.event_source.start()

ttk.Label(control_frame, text="dt (Time Step)").pack(side=tk.LEFT, padx=5)
dt_slider = ttk.Scale(control_frame, from_=0.00001, to=0.001, value=simulation.dt, orient=tk.HORIZONTAL)
dt_slider.pack(side=tk.LEFT, padx=5)

ttk.Label(control_frame, text="t_max (Max Time)").pack(side=tk.LEFT, padx=5)
tmax_entry = ttk.Entry(control_frame)
tmax_entry.insert(0, str(simulation.t_max))
tmax_entry.pack(side=tk.LEFT, padx=5)

ttk.Label(control_frame, text="N (Particles)").pack(side=tk.LEFT, padx=5)
n_particles_entry = ttk.Entry(control_frame)
n_particles_entry.insert(0, str(simulation.N))
n_particles_entry.pack(side=tk.LEFT, padx=5)

# Update 
update_button = ttk.Button(control_frame, text="Update Parameters", command=update_parameters)
update_button.pack(side=tk.LEFT, padx=5)


def start_animation():
    ani.event_source.start()

def stop_animation():
    ani.event_source.stop()

start_button = ttk.Button(control_frame, text="Start", command=start_animation)
start_button.pack(side=tk.LEFT, padx=5)

stop_button = ttk.Button(control_frame, text="Stop", command=stop_animation)
stop_button.pack(side=tk.LEFT, padx=5)

# Run tikiintwer
root.mainloop()
