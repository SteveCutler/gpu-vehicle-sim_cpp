#include <cstddef>
#include "environment.hpp"
#include "vehicleBatch.hpp"
#include "controller.hpp"
#include "dynamics.hpp"
#include <chrono>
#include <iostream>
#include "stateExport.hpp"

#ifdef ENABLE_RENDERER
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#endif

using Clock = std::chrono::steady_clock;

int main(int argNum, char* argVals[]){


    std::cout << "starting up..." << std::endl;
    //master variables
    constexpr std::size_t width = 500;
    constexpr std::size_t height = 500;
    constexpr float dt = 0.02f;

    //default values
    std::size_t N = 5;
    std::size_t steps = 1000;

    //take in input variables
    //set vehicle batch size
    if (argNum > 1) N = std::stoi(argVals[1]);
    //set step size
    if (argNum > 2) steps = std::stoi(argVals[2]);
    
    std::cout << "Vehicles: " << N << "\nSteps: " << steps << '\n';
    
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
        //create renderer
        Renderer renderer(width, height);
    #endif


        //start wallclock timer for performance measurement
        const auto start = Clock::now();

        //run sim for steps amount of steps
        while(curr_step < steps){

            //loop over every vehicle every step
            for(int x = 0; x < N; x++){
                //load vehicle state
                vs = vehicles.load(x);
    
                //pass to controller 
                
                // must write controller logic still
                action = controller.steer_controller(vs);

                //calculate new state
                newState = dynamics.step_update(vs, action, env, dt);

                //update old state
                vehicles.set(x, newState);

    
            }
        //optionally display data
        #ifdef ENABLE_RENDERER
            bool running = renderer.draw(vehicles);
            if(!running) {
                break;
            }
        #endif


        //increment step counter
        curr_step++;
        }

        //end clock
        const auto stop = Clock::now();

        //calculate elapsed time
        const double seconds = 
            std::chrono::duration<double>(stop - start).count();

        //multiply steps by vehicles to get total updates
        const double updates = static_cast<double>(N) * curr_step;

        std::cout << "Vehicles: " << N << '\n';
        std::cout << "Completed steps: " << curr_step << '\n';
        std::cout << "Execution time: " << seconds << " seconds\n";
        std::cout << "Vehicle updates/sec: " << updates / seconds << '\n';

            //output file name for correctness comparison
            if (argNum > 3) {
                exportStates(vehicles, argVals[3]);
            }
            

    // Keep showing the final state and handling window events.
    #ifdef ENABLE_RENDERER
    while (renderer.draw(vehicles)) {}
    #endif

 

    return 0;
}