#pragma once
#include <vector>

class environment
{
public: 

std::size_t width;
std::size_t height;

private:
std::vector<float> velFieldx, velFieldy;

public:
environment(std::size_t w, std::size_t h);


};

