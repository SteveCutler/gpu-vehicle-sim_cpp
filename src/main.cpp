#include <cstddef>
#include "environment.hpp"
#include "vehicleBatch.hpp"
#include "controller.hpp"
#include "dynamics.hpp"
#include <chrono>
#include <iostream>

#ifdef ENABLE_RENDERER
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#endif

int main(){


    std::cout << "starting up..." << std::endl;
    //master variables
    constexpr std::size_t width = 256;
    constexpr std::size_t height = 256;
    constexpr std::size_t N = 1;

    constexpr float dt = 0.02f;
    constexpr std::size_t steps = 100;
    std::size_t curr_step = 0;

    //initialize environment with 0 wind at first
    environment env(width, height);

    //initialize vehicleState data
    vehicleBatch vehicles(N, env);

    //create controller object
    Controller controller;

    //create dynamics updater
    Dynamics dynamics;

    //allocating variables outside hot loop
    VehicleState vs;
    Action action;
    VehicleState newState;

    // create a clock to track the elapsed time
    // TO DO create performance clock

    //if rendering enabled create rendering logic
    #ifdef ENABLE_RENDERER
         std::cout << "test renderer" << std::endl;
        //create renderer
        Renderer renderer(width, height);
    #endif

    
    //main update loop
    while(true){

        //run sim for steps amount of steps
        while(curr_step < steps){

            //loop over every vehicle every step
            for(int x = 0; x < N; x++){
                //load vehicle state
                vs = vehicles.load(x);
    
                //pass to controller 
                /*
                // must write controller logic still
                action = controller.steer_controller(vs);

                //calculate new state
                newState = dynamics.step_update(vs, action, env, dt);

                //update old state
                vehicles.set(x, newState);

                */




               
    
            }
                    //optionally display data
        #ifdef ENABLE_RENDERER

            renderer.draw(vehicles);
            
            //check if window has been closed and end sim that way
            // if(!window.isOpen()) break;
        #endif
        }

    }

    std::cout << "Sim complete : )" << std::endl;

    return 0;
}