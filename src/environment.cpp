#include "environment.hpp"

environment::environment(std::size_t w, std::size_t h): 
width(w), 
height(h),
velFieldx(w*h,0.0f), 
velFieldy(w*h,0.0f){

    //wind vel field  zero across the board for first implementation
    //in later implementation create curl noise field


}

std::pair<float,float> environment::getDisturbance(std::size_t x, std::size_t y) const{
    {

    std::size_t pos = y * width + x;
    return {velFieldx[pos], velFieldy[pos]};

}

}