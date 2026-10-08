#pragma once
#include <vector>
#include <cstddef>
#include "environment.hpp"
#include "vehicleTypes.hpp"


class vehicleBatch
{

public:
    std::vector<float> m_x, m_y;
    std::vector<float> m_vx, m_vy;
    std::vector<float> m_heading, m_turnRate;
    std::vector<float> m_goalx, m_goaly;
    std::size_t m_size;


public:
    vehicleBatch(std::size_t N, std::size_t width, std::size_t height);

    VehicleState load(std::size_t i) const;

    void set(std::size_t i, const VehicleState& state);
    
    std::size_t getSize() const;
    

};


// TO DO write update function

