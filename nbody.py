import pynbody
import numpy as np

def run_simulation(N, dt, t_max):
    """
    Runs the n-body simulation and returns the positions of particles at each time step.

    Args:
        N (int): Number of particles.
        dt (float): Time step.
        t_max (float): Maximum simulation time.

    Returns:
        list: A list of frames where each frame contains (x, y) positions of particles.
    """
    # Initialize positions, velocities, and masses
    x = np.random.rand(3 * N).astype(np.float32)
    v = np.zeros(3 * N, dtype=np.float32)
    m = np.ones(N, dtype=np.float32)

    frames = []  # To store particle positions over time
    for t in np.arange(0, t_max, dt):
        pynbody.stepf(x, v, m, dt)  # Perform a single simulation step
        positions = x.reshape(-1, 3)
        frames.append(positions[:, :2].tolist())  # Store (x, y) positions only

    return frames
