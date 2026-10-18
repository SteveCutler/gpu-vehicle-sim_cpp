#include "renderer.hpp"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "environment.hpp"
#include "DriftItem.hpp"

Renderer::Renderer(std::size_t width, std::size_t height, bool arrow_viz):
m_width(width),
m_height(height),
m_texture(sf::Vector2u(width, height)),
m_scale(sf::Vector2f(1.0f, 1.0f)),
m_sprite(m_texture),
m_arrow_viz(arrow_viz),
m_arrows(sf::PrimitiveType::Lines, width/16 * height/16 * 6),
m_window(sf::VideoMode({m_width, m_height}), "Search&Rescue Sim")
{
    //Render logic initialization
    m_sprite.setScale(m_scale);
    m_window.setFramerateLimit(60);
             //create window logic

    //TO DO 
    //display performance time here
};

bool Renderer::draw(const vehicleBatch& vehicles, float dt, std::size_t curr_step, const environment& env, DriftItem& target){

    //check if window has been closed:
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
            std::cout << "window closed" << std::endl;
        }
    }

    if (!m_window.isOpen()) return false;

    
    //vehicle count
    const std::size_t count = vehicles.getSize();

    //create vehicle shape
    sf::ConvexShape vehicleShape(3);
    vehicleShape.setPoint(0, {10.f, 0.f});   
    vehicleShape.setPoint(1, {-7.f, -6.f});
    vehicleShape.setPoint(2, {-7.f,  6.f});
    vehicleShape.setFillColor(sf::Color::Cyan);

    //create goal shape
    sf::CircleShape goalShape(4.f);
    goalShape.setOrigin({4.f, 4.f});
    goalShape.setFillColor(sf::Color::Green);

    //create target shape
    sf::ConvexShape targetShape(10);
    targetShape.setPoint(0, {0.f, -5.f});
    targetShape.setPoint(1, {1.18f, -1.62f});
    targetShape.setPoint(2, {4.76f, -1.55f});
    targetShape.setPoint(3, {1.9f, 0.62f});
    targetShape.setPoint(4, {2.94f, 4.05f});
    targetShape.setPoint(5, {0.f, 2.f});
    targetShape.setPoint(6, {-2.94f, 4.05f});
    targetShape.setPoint(7, {-1.9f, 0.62f});
    targetShape.setPoint(8, {-4.76f, -1.55f});
    targetShape.setPoint(9, {-1.18f, -1.62f});
    targetShape.setFillColor(sf::Color::Red);

    //clear previous frame    
    m_window.clear(sf::Color::Black);

    // draw velocity arrow samples

    if(m_arrow_viz){
        std::size_t index=0;
        for (std::size_t y = 0; y<m_height; y+=16){
            std::size_t row = y*m_width;
            
            for(std::size_t x =0; x<m_width; x+=16){
                std::size_t i = row+x;
                
                //extract u and v velocity directions
                auto [u, v] = env.getDisturbance(x, y, dt*curr_step);

                //increase length for display
              //  u *= 10;
              //  v *= 10;
                
                //create arrow points
                m_arrows[index].position = sf::Vector2f(static_cast<float>(x),static_cast<float>(y));
                m_arrows[index+1].position = sf::Vector2f(static_cast<float>(x+u),static_cast<float>(y+v));
                
                m_arrows[index+2].position = sf::Vector2f(static_cast<float>(x+u),static_cast<float>(y+v));
                m_arrows[index+3].position = sf::Vector2f(static_cast<float>(x+u - u*.25 + v*.25),static_cast<float>(y+v - v*.25-u*.25));
                
                m_arrows[index+4].position = sf::Vector2f(static_cast<float>(x+u),static_cast<float>(y+v));
                m_arrows[index+5].position = sf::Vector2f(static_cast<float>(x+u - u*.25 - v*.25),static_cast<float>(y+v - v*.25+u*.25));
                
                
                index += 6;
            }

        }
    }

    // Load pixel RGBA data into texture
    for(int i = 0; i<count; i++){
        VehicleState s = vehicles.load(i);

        vehicleShape.setPosition({s.x, m_height - s.y});
        vehicleShape.setRotation(sf::radians(-s.heading));
        m_window.draw(vehicleShape);

        goalShape.setPosition({s.goalx, m_height - s.goaly});
        m_window.draw(goalShape);
    }
    //render arrows
    if(m_arrow_viz){
        m_window.draw(m_arrows);
    }
    
    //draw target
    targetShape.setPosition({target.x,target.y});
    m_window.draw(targetShape);

    m_window.display();



    return true;


};