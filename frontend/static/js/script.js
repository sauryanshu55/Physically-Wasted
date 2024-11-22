async function runSimulation() {
  // Get input values
  const N = document.getElementById("N").value;
  const dt = document.getElementById("dt").value;
  const t_max = document.getElementById("t_max").value;

  try {
    // Fetch simulation frames from the backend
    const response = await fetch("/simulate", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        N: parseInt(N),
        dt: parseFloat(dt),
        t_max: parseFloat(t_max),
      }),
    });

    if (!response.ok) {
      throw new Error("Failed to fetch simulation data.");
    }

    // Parse the response to get the frames
    const frames = await response.json();

    // Prepare the initial trace for Plotly
    const trace = {
      x: frames[0].map((p) => p[0]), // X-coordinates of the first frame
      y: frames[0].map((p) => p[1]), // Y-coordinates of the first frame
      mode: "markers",
      marker: { color: "white", size: 3 },
    };

    const layout = {
      title: "N-Body Simulation",
      xaxis: { range: [0, 1], title: "X" },
      yaxis: { range: [0, 1], title: "Y" },
      plot_bgcolor: "black",
      paper_bgcolor: "black",
      font: { color: "white" },
    };

    // Create frames for Plotly animation
    const plotlyFrames = frames.map((frame) => ({
      data: [
        {
          x: frame.map((p) => p[0]),
          y: frame.map((p) => p[1]),
        },
      ],
    }));

    // Plot the initial state
    Plotly.newPlot("simulation", [trace], layout);

    // Animate the frames
    Plotly.animate(
      "simulation",
      {
        data: plotlyFrames.map((frame) => frame.data[0]),
        traces: [0],
        layout: layout,
      },
      {
        frame: { duration: 100, redraw: true }, // Control animation speed (100 ms per frame)
        transition: { duration: 0 },
      }
    );
  } catch (error) {
    console.error("Error:", error);
  }
}
