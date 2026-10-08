#pragma once
#include "vehicleBatch.hpp"
#include "vehicleTypes.hpp"
#include <cuda_runtime.h>

class Controller
{
    public:
        __device__ Controller() = default;

        __device__ Action steer_controller(const VehicleState& vs);
};

