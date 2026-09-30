#pragma once
#include <vector>
#include <cstddef>
#include "environment.hpp"


class vehicleBatch
{

private:
    std::vector<float> m_x, m_y;
    std::vector<float> m_vx, m_vy;
    std::vector<float> m_heading, m_turnRate;
    std::vector<float> m_goalx, m_goaly;


public:
    vehicleBatch(std::size_t N, environment env);
};


