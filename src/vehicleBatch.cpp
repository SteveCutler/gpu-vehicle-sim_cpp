#include "vehicleBatch.hpp"


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

    for(int x = 0; x < N; x++){
        //intializing a single vehicle with basic parameters for verification
        m_x[x] = env.width*0.5f;
        m_y[x] = env.height*0.9f;

        m_vx[x] = 0.f;
        m_vy[x] = 0.f;

        m_heading[x] = 0.f;
        m_turnRate[x] = 0.f;

        m_goalx[x] = env.width*.5;
        m_goaly[x] = env.height*.1;
        
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