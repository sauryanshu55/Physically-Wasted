from flask import Flask, request, jsonify, render_template
import sys
import os

# Add the parent directory to sys.path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

# Import the function from nbody.py
from nbody import run_simulation


app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')


@app.route('/simulate', methods=['POST'])
def simulate():
    # Parse input from the user
    data = request.json
    N = int(data.get('N', 1000))  # Default to 1000 particles
    dt = float(data.get('dt', 0.0001))  # Default time step
    t_max = float(data.get('t_max', 0.01))  # Default max simulation time

    # Run the simulation
    frames = run_simulation(N, dt, t_max)

    # Return frames as JSON
    return jsonify(frames)

if __name__ == '__main__':
    app.run(port=5500)

