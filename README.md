# Serial Implementation for later CUDA Porting

TO DO:

-color code goals and vehicles together
-shrink vehicle size
-implement some measurment of error mechanism to compare GPU version against
-create a CPU benchmark

# PHASE 2

Add DriftItem class and DriftDynamics to move it around in the current
Add PredictionParticle class and PredictionUpdate which spawns particles and predicts potential drift based on current knowledge
Use PredictionParticles to generate ProbabilityMap field
Add Sensor class and use Sensor observations from searching vehicles to update particle weights for ProbabilityMap, update Probability Map and guidance functions
Use HedacPlanner control method which solves ProbabilityMap like the heat PDE, uses to generate guidance

Later potentially implement MPPI environmental learning

Create imperfect current knowledge field for vehicles to derive predictions from, update as searching and gain more knowledge
For earlier implementations maybe does current field from evolving to provide static currents, better for probabalistic search
