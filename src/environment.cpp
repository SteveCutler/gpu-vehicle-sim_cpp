#include "environment.hpp"
#include <cmath>

environment::environment(std::size_t w, std::size_t h): 
m_width(w), 
m_height(h),
velFieldx(w*h,0.0f), 
velFieldy(w*h,0.0f){

    //wind vel field  zero across the board for first implementation
    //in later implementation create curl noise field


}

std::pair<float,float> environment::getDisturbance(float x, float y, float time) const{
    {
        // bounds check
    if(x < 0.f || x >= static_cast<float>(m_width) || y < 0.f || y >= static_cast<float>(m_height)){
        return {0.0f, 0.0f};
    }

    //cyclical wind field parameters
    constexpr float amplitude = 5.5f;
    constexpr float wavelength = 1000.f;
    constexpr float timeMult = 10.f;
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