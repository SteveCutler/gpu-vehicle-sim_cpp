#include "vehicleBatch.hpp"


vehicleBatch::vehicleBatch(std::size_t N, environment env):
    m_x(N),
    m_y(N),
    m_vx(N),
    m_vy(N),
    m_heading(N),
    m_turnRate(N),
    m_goalx(N),
    m_goaly(N)
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

}

/*
TO DO

write function to assign random x y vx vy heading turnrate values on initialization

every vehicle same goal for now
*/