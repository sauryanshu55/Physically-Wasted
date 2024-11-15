import ctypes
import numpy as np
import os

lib_path = os.path.join(os.path.dirname(__file__), '..', 'lib', 'libnbody.so')
nbody_lib = ctypes.CDLL(lib_path)

nbody_stepf = nbody_lib.nbody_stepf
nbody_stepf.argtypes = [
    ctypes.POINTER(ctypes.c_float),  # x array
    ctypes.POINTER(ctypes.c_float),  # v array
    ctypes.POINTER(ctypes.c_float),  # m array
    ctypes.c_size_t,                 # N
    ctypes.c_float                   # dt
]
nbody_stepf.restype = None

def stepf(x, v, m, dt):
    """
    Python wrapper for the nbody_stepf function.
    
    Parameters:
        x (numpy.ndarray): Positions of the bodies.
        v (numpy.ndarray): Velocities of the bodies.
        m (numpy.ndarray): Masses of the bodies.
        dt (float): Time step for the simulation.
    
    Returns:
        None: The function modifies the x and v arrays in place.
    """
    x = np.asarray(x, dtype=np.float32)
    v = np.asarray(v, dtype=np.float32)
    m = np.asarray(m, dtype=np.float32)
    N = m.size
        
    if x.size != v.size or x.size != 3 * N:
        raise ValueError("Array sizes are incompatible: "
                         "Expected x and v to have size 3 * N, "
                         "and m to have size N.")


    nbody_stepf(
        x.ctypes.data_as(ctypes.POINTER(ctypes.c_float)),
        v.ctypes.data_as(ctypes.POINTER(ctypes.c_float)),
        m.ctypes.data_as(ctypes.POINTER(ctypes.c_float)),
        ctypes.c_size_t(N),
        ctypes.c_float(dt)
    )
