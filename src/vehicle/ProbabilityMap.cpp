#include "vehicle/ProbabilityMap.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include "vehicle/DriftDynamics.hpp"

ProbabilityMap::ProbabilityMap(DriftDynamics& DD, ::size_t width, std::size_t height, std::size_t num_p, float est_x, float est_y, float p_rad, std::size_t cell_size):
width_(width),
height_(height),
num_p_(num_p),
cell_size_(cell_size),
map_((width/cell_size_) * (height/cell_size_), 0.f),
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

void ProbabilityMap::computeProb(){
    //clear map from last frame
    std::fill(map_.begin(), map_.end(), 0.0f);
    //clear previous frames' occupied cell list
    occupied_cells.clear();

    //calculate width of cells
    std::size_t rows = height_ / cell_size_;
    std::size_t cols = width_ / cell_size_;


    for(size_t i = 0; i < num_p_; i++){
        //OOB check
        if(particles_[i].pos.x >= 0 && particles_[i].pos.x < width_ &&
        particles_[i].pos.y >= 0 && particles_[i].pos.y < height_){

            //calc pmap grid cell
            std::size_t cell_row = std::floor(particles_[i].pos.y / cell_size_);
            std::size_t cell_col = std::floor(particles_[i].pos.x / cell_size_);

            std::size_t index = cell_row * cols + cell_col;

            if(map_[index] == 0.f){
                occupied_cells.push_back(index);
            }

            map_[index] += 1.0f / static_cast<float>(num_p_); 
        }
    }
};