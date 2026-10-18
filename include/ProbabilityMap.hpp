#pragma once
#include <vector>

class ProbabilityMap
{
private:
    std::size_t width_;
    std::size_t height_;
    std::vector<float> map;

public:
    ProbabilityMap(std::size_t width, std::size_t height);
    ~ProbabilityMap() = default;
};

