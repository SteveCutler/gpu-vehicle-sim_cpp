#include "controller.hpp"
#include <cmath>
#include <algorithm>

Controller::Controller(){

};

Action Controller::steer_controller(const VehicleState& vs){

    constexpr float pi = 3.14159265359f;

    //use arctangent to calculate desired heading angle
    const float desiredHeading = std::atan2(vs.goaly - vs.y, vs.goalx - vs.x);

    //calculate shortest angle corrective between current heading and desired heading
    const float headingError = std::remainder(desiredHeading - vs.heading, 2.0f * pi);

    //PD controls
    constexpr float kp = 4.f;
    constexpr float kd = 2.f;
    constexpr float maxTorque = 4.f;

    Action action{};
    action.torque = std::clamp(
        kp * headingError - kd * vs.turnRate,
        -maxTorque, maxTorque
    );

    //create dynamic thrust
    action.thrust = 10.f;

    return action;
}