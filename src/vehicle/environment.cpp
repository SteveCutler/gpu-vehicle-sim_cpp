#include "vehicle/environment.hpp"
#include <cmath>

environment::environment(std::size_t w, std::size_t h, std::vector<Emitter*>& emitters, std::size_t seed): 
m_width(w), 
m_height(h),
velFieldx(w*h,0.0f), 
velFieldy(w*h,0.0f),
emitters(emitters),
seed(seed),
fluid_grid(FluidGrid(m_width, m_height, emitters, seed, false)){

    //wind vel field  zero across the board for first implementation
    //in later implementation create curl noise field
    

    //initialize fluid grid
    fluid_grid = FluidGrid(m_width, m_height, emitters, seed, false);


}

void environment::update_fluid(float dt){
    fluid_grid.update(dt);
    return;
}

const std::vector<std::uint8_t> & environment::get_pixels() const{
    
    return fluid_grid.m_pixels;
};

std::pair<float,float> environment::getDisturbance(float x, float y, float time) const{
    {
        // bounds check
    if(x < 0.f || x >= static_cast<float>(m_width) || y < 0.f || y >= static_cast<float>(m_height)){
        return {0.0f, 0.0f};
    }

    //cyclical wind field parameters
    constexpr float amplitude = 5.5f;
    constexpr float wavelength = 500.f;
    constexpr float timeMult = 0.f;
    constexpr float twopi = 6.283185f;

    //time mult factor
    float x_evolve = x - timeMult * time;
    float y_evolve = y - timeMult*3.231 * time;

    //creating gust strength based on cycle point
    float x_angle = (x_evolve / wavelength) * twopi;
    float x_gust = std::sin(x_angle);

    float y_angle = (y_evolve / wavelength) * twopi;
    float y_gust = std::cos(y_angle);

    float windX = amplitude * x_gust;
    float windY = amplitude * y_gust;

    return {windX, windY};

    }

}