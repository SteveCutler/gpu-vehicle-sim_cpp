#pragma once
#include <vector>
#include <random>
#include "vehicle/DriftItem.hpp"
#include "vehicle/environment.hpp"
#include "vehicle/DriftDynamics.hpp"

class ProbabilityMap
{
private:
    std::size_t width_;
    std::size_t height_;
    DriftDynamics DD_;
    std::mt19937 rng_;
    float p_rad_;
    float origin_x_;
    float origin_y_;
    
    public:
    std::vector<PredictionParticle> particles_;
    std::size_t cell_size_;
    std::vector<float> map_;
    std::size_t num_p_;
    std::vector<std::size_t>occupied_cells;
    
public:
    ProbabilityMap(DriftDynamics& DD, ::size_t width, std::size_t height, std::size_t num_p, float est_x, float est_y, float p_rad, std::size_t cell_size);

    void update(const environment& env, float dt);
    
    void add_Particles();

    void computeProb();

    ~ProbabilityMap() = default;
};

