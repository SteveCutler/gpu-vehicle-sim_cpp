#pragma once
#include <vector>
#include "DriftItem.hpp"
#include "environment.hpp"
#include "DriftDynamics.hpp"

class ProbabilityMap
{
private:
    std::size_t width_;
    std::size_t height_;
    DriftDynamics DD_;
    std::vector<float> map_;
    
    public:
    std::vector<PredictionParticle> particles_;
    std::size_t num_p_;

public:
    ProbabilityMap(DriftDynamics& DD, ::size_t width, std::size_t height, std::size_t num_p, float est_x, float est_y, float p_rad);

    void update(const environment& env, float dt);

    ~ProbabilityMap() = default;
};

