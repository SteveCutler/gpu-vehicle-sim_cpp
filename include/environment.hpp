#pragma once
#include <vector>

class environment
{
public: 

std::size_t m_width;
std::size_t m_height;

private:
std::vector<float> velFieldx, velFieldy;

public:
environment(std::size_t w, std::size_t h);

std::pair<float,float> getDisturbance(std::size_t x, std::size_t y, float time) const;

};

