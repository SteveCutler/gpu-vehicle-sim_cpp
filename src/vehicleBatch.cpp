#include "vehicleBatch.hpp"
#include <random>


vehicleBatch::vehicleBatch(std::size_t N, environment env):
    m_x(N),
    m_y(N),
    m_vx(N),
    m_vy(N),
    m_heading(N),
    m_turnRate(N),
    m_goalx(N),
    m_goaly(N),
    m_size(N)
{

    //RNG setup 
    std::mt19937 rng(25);

    constexpr float margin = 10.f;
    constexpr float pi = 3.14159265359f;

    std::uniform_real_distribution<float> randomX(
        margin, static_cast<float>(env.m_width) - margin);

    std::uniform_real_distribution<float> randomY(
        margin, static_cast<float>(env.m_height) - margin);

    std::uniform_real_distribution<float> randomHeading(-pi, pi);


    for(int x = 0; x < N; x++){
        //intializing a single vehicle with basic parameters for verification
        m_x[x] = randomX(rng);
        m_y[x] = randomY(rng);

        m_vx[x] = 0.f;
        m_vy[x] = 0.f;

        m_heading[x] = randomHeading(rng);
        m_turnRate[x] = 0.f;

        m_goalx[x] = randomX(rng);
        m_goaly[x] = randomY(rng);
        
    }

};

VehicleState vehicleBatch::load(std::size_t i) const{

    return {
        m_x[i], 
        m_y[i], 
        m_vx[i], 
        m_vy[i], 
        m_heading[i], 
        m_turnRate[i],
        m_goalx[i],
        m_goaly[i]
    };

};

void vehicleBatch::set(std::size_t i, const VehicleState& newState){
    m_x[i] = newState.x;
    m_y[i] = newState.y;
    m_vx[i] = newState.vx;
    m_vy[i] = newState.vy;
    m_heading[i] = newState.heading;
    m_turnRate[i] = newState.turnRate;
};

std::size_t vehicleBatch::getSize() const{
    return m_size;
};

/*
TO DO

write function to assign random x y vx vy heading turnrate values on initialization

every vehicle same goal for now

write update function that takes in action and vehicle state structs
*/