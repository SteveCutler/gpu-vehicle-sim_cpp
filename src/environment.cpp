#include "environment.hpp"

environment::environment(std::size_t w, std::size_t h): 
width(w), 
height(h),
velFieldx(w*h), 
velFieldy(w*h){

    //wind vel field  zero across the board for first implementation
    //in later implementation create curl noise field


}