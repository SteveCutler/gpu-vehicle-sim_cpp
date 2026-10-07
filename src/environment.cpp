#include "environment.hpp"

environment::environment(std::size_t w, std::size_t h): 
m_width(w), 
m_height(h),
velFieldx(w*h,0.0f), 
velFieldy(w*h,0.0f){

    //wind vel field  zero across the board for first implementation
    //in later implementation create curl noise field


}

std::pair<float,float> environment::getDisturbance(std::size_t x, std::size_t y) const{
    {
        // bounds check
    if(x < 0 || x >= m_width || y < 0 || y >= m_height){
        return {0.0f, 0.0f};
    }

    std::size_t pos = y * m_width + x;
    return {velFieldx[pos], velFieldy[pos]};

}

}