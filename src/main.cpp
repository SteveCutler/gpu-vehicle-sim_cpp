#include <cstddef>
#include "environment.hpp"
#include "vehicleBatch.hpp"
#include "controller.hpp"

int main(){

    constexpr std::size_t width = 256;
    constexpr std::size_t height = 256;
    constexpr std::size_t N = 256;

    //initialize environment with 0 wind at first
    environment env(width, height);

    //initialize vehicleState data
    vehicleBatch vehicles(N, env);

    //new action variable
    Action action;
    VehicleState vs;

    while(true){

        for(int x = 0; x < N; x++){
        //create vehicle state
        //pass to controller
        //action = controller::steer_controller()

        }
    }






    /*
    UPDATE FLOW
    load vehicle state i
    call steer_controller and compute action based on state and goal
    call step_vehicle, compute next state with current state, action, dynamics, dt
    save new state, update display if rendering enabled

    
    */

    return 0;
}