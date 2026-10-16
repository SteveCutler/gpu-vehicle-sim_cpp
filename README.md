2D Vehicle Simulator — C++ Reference
A C++17 simulation of independent, goal seeking vehicles moving through a time varying disturbance field. This repo provides the serial CPU reference for a companion CUDA implementation, with final state CSV export for numerical comparisons and an optional SFML visualization.
Built to explore the numerical and systems foundations of parallel simulation: feedback control, time integration, data layout, and reproducible CPU/GPU comparisons.
CUDA implementation · Experiment notebook


What it does
- Simulates position, velocity, heading, and angular velocity for each vehicle.
- Uses a fixed controller with PD heading control and alignment-aware speed control to generate bounded thrust and torque.
- Applies linear and rotational drag, including drag relative to a spatially and temporally varying flow.
- Advances state with semi-implicit Euler integration.
- Stores vehicle components in separate contiguous arrays.
- Initializes positions, headings, and goals with a fixed random seed.
- Reports elapsed time and vehicle updates per second, and optionally exports final states to CSV.

Vehicles are independent: they do not collide or influence one another. This makes the model useful for studying parallel rollouts, while keeping the CPU implementation easy to inspect.
Build and run
Headless build
Requires CMake 3.16 or newer and a compiler with C++17 support. SFML is not needed for this build.
git clone https://github.com/SteveCutler/gpu-vehicle-sim_cpp.git
cd gpu-vehicle-sim_cpp

cmake -S . -B out/headless -DCMAKE_BUILD_TYPE=Release -DENABLE_RENDERER=OFF
cmake --build out/headless --parallel

# 10,000 vehicles, 1,000 timesteps, optional final-state export
./out/headless/vehicle_sim 10000 1000 states_cpu.csv
The examples use a single-configuration build on a Unix-like shell. Multi-configuration generators may place the executable in a configuration subdirectory.
Command-line arguments
vehicle_sim [vehicle_count] [step_count] [output_csv]
Argument	Default	Meaning
vehicle_count	5	Number of independent vehicles
step_count	1000	Number of fixed simulation timesteps
output_csv	Omitted	Export the final state of every vehicle


Use positive vehicle counts and non-negative step counts. Argument validation is currently minimal.
Optional visualization
The repository includes an SFML 3 renderer for vehicles, goals, and flow arrows. Rendering is enabled by default in CMake; the headless command above disables it explicitly.
cmake -S . -B out/render -DCMAKE_BUILD_TYPE=Release -DENABLE_RENDERER=ON
cmake --build out/render --parallel
./out/render/vehicle_sim 25 1000
If CMake cannot find SFML 3, supply its installation prefix through CMAKE_PREFIX_PATH. The window remains open at the final state until closed.
Current renderer issue: the flow-arrow vertex buffer uses floor division for its allocation, while the sampling loops round up. At the default 500 × 500 size this underallocates the buffer. Before using the visualization, correct the allocation to ((width + 15) / 16) * ((height + 15) / 16) * 6, or disable arrow_viz in src/main.cpp.
Use the headless build for performance measurements: rendering and its frame limit are inside the timed CPU loop.
Simulation model
Each vehicle stores eight single-precision values:
x, y, vx, vy, heading, turnRate, goalx, goaly
At each timestep:
1. Compute the desired heading to the goal and wrap the heading error.
2. Calculate steering torque and thrust from heading, distance, and forward speed.
3. Sample the procedural flow at the vehicle's position and current simulation time.
4. Calculate linear and angular acceleration.
5. Update velocity before position, and angular velocity before heading.
The default world is 500 × 500 units, with a timestep of 0.02 seconds and initialization seed 25. These values are set in the source rather than exposed as command-line options. The environment returns zero flow outside its domain; vehicles are not constrained by walls.
The total simulation work is O(N × S) for N vehicles and S timesteps.
Code map
File	Responsibility
src/main.cpp	Configuration, serial update loop, timing, and export
src/vehicleBatch.cpp	Seeded initialization and structure-of-arrays state storage
src/controller.cpp	Heading and speed feedback control
src/dynamics.cpp	Forces, drag, and semi-implicit integration
src/environment.cpp	Procedural disturbance field
src/renderer.cpp	Optional SFML visualization
include/stateExport.hpp	Final-state CSV export


CPU/GPU validation
The CPU implementation is the numerical reference for the CUDA project. Both versions use the same initialization seed and model parameters.
CSV exports have this header:
id,x,y,vx,vy,heading,turnRate,goalx,goaly
The accompanying experiment notebook compares vehicle counts, IDs, goals, finite state values, and numerical differences. Reported checks include:
- Zero timesteps to compare initialization.
- One vehicle for one timestep.
- 255, 256, and 257 vehicles for 100 timesteps, covering CUDA block boundaries.
- 10,000 vehicles for one and 1,000 timesteps.
At 10,000 vehicles and 1,000 timesteps, the project report records maximum CPU/GPU differences of 0.002655 world units per position component, 0.00173 world units/s per velocity component, and 0.000123561 radians in heading. All three CUDA variants produced the same reported error summaries.
These are observed differences for the tested cases, not universal tolerances or validation against a physical vehicle. For comparisons across toolchains, verify zero-step initialization first: a fixed engine seed alone does not guarantee identical floating-point distribution output across standard-library implementations.
Performance context
In the project's Google Colab experiments, the single-threaded CPU reference took 20.55 seconds for 1,000,000 vehicles × 100 timesteps on an Intel Xeon CPU reported at 2.20 GHz. The companion batched CUDA version took 0.269 seconds on an NVIDIA Tesla T4, approximately 76.4× faster for that workload.
Results are medians of five measured runs after a discarded warmup. CPU timing covers the update loop; CUDA host timing includes device allocation, transfers, execution, synchronization, and cleanup. Both exclude initial vehicle generation and CSV export. Small workloads favored the CPU.
See the CUDA README and experiment notebook for the comparison and measurement context.
Scope and next steps
This is a simplified simulation and performance study with a fixed controller. It does not currently implement reinforcement learning, lidar, obstacle avoidance, vehicle collisions, or a calibrated real-vehicle model.
Planned extensions include sensing, rewards, episode resets, and policy integration for Search and Rescue missions. The CPU reference provides a readable baseline for checking those additions.
