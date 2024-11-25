import numpy as np
import pynbody

class Simulation:
    def __init__(self, dt=0.0001, t_max=0.01, N=1000):
        self.dt = dt
        self.t_max = t_max
        self.N = N
        self.x = np.random.rand(3 * self.N).astype(np.float32)
        self.v = np.zeros(3 * self.N, dtype=np.float32)
        self.m = np.ones(self.N, dtype=np.float32)
        self.positions = self.x.reshape(-1, 3)

    def reset(self, dt=None, t_max=None, N=None):
        """Reset the simulation parameters and state"""
        if dt is not None:
            self.dt = dt
        if t_max is not None:
            self.t_max = t_max
        if N is not None:
            self.N = N
        self.x = np.random.rand(3 * self.N).astype(np.float32)
        self.v = np.zeros(3 * self.N, dtype=np.float32)
        self.m = np.ones(self.N, dtype=np.float32)
        self.positions = self.x.reshape(-1, 3)

    def step(self):
        """Perform a single step of the simulation"""
        pynbody.stepf(self.x, self.v, self.m, self.dt)
        self.positions = self.x.reshape(-1, 3)
