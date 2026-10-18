#include "ProbabilityMap.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include "DriftDynamics.hpp"

ProbabilityMap::ProbabilityMap(DriftDynamics& DD, ::size_t width, std::size_t height, std::size_t num_p, float est_x, float est_y, float p_rad):
width_(width),
height_(height),
num_p_(num_p),
map_(width*height, 0.f),
DD_(DD)
{
    //reserve space for probability particles
    particles_.reserve(num_p_);

    

    //RNG setup 
    std::mt19937 rng(25);

    constexpr float margin = 5.f;

    float max_x = std::clamp((est_x + p_rad), 0.f, static_cast<float>(width_));
    float min_x = std::clamp((est_x - p_rad), 0.f, static_cast<float>(width_));
    float max_y = std::clamp((est_y + p_rad), 0.f, static_cast<float>(height_));
    float min_y = std::clamp((est_y - p_rad), 0.f, static_cast<float>(height_));

    std::uniform_real_distribution<float> randomX(min_x + margin, max_x - margin);
    std::uniform_real_distribution<float> randomY(min_y + margin, max_y - margin);

    float x;
    float y;

    for(size_t i = 0; i < num_p_; i++){
        particles_.emplace_back( 
            PredictionParticle(randomX(rng), randomY(rng)) 
        );
    };


};

void ProbabilityMap::update(const environment& env, float dt){

    //update probability particle drift
    for(auto& p : particles_){
        DD_.DriftUpdate(p.pos, env.getDisturbance(p.pos.x, p.pos.y, 0.f), dt);
    }

};