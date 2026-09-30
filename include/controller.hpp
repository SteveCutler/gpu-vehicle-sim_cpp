#pragma once
#include "vehicleBatch.hpp"
#include "vehicleTypes.hpp"

class Controller
{
    public:
        Controller();

        Action steer_controller(const VehicleState& vs);
};

