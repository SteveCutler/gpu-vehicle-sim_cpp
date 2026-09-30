#include "renderer.hpp"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Renderer::Renderer(std::size_t width, std::size_t height):
m_width(width),
m_height(height),
m_texture(sf::Vector2u(width, height)),
m_scale(sf::Vector2f(1.0f, 1.0f)),
m_sprite(m_texture),
m_window(sf::VideoMode({m_width, m_height}), "Vehicle Sim")
{
    //Render logic initialization
    m_sprite.setScale(m_scale);
    m_window.setFramerateLimit(60);
             //create window logic

    //TO DO 
    //display performance time here
};

bool Renderer::draw(const vehicleBatch& vehicles){

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

    sf::ConvexShape vehicleShape(3);
    vehicleShape.setPoint(0, {10.f, 0.f});   
    vehicleShape.setPoint(1, {-7.f, -6.f});
    vehicleShape.setPoint(2, {-7.f,  6.f});
    vehicleShape.setFillColor(sf::Color::Cyan);

    sf::CircleShape goalShape(4.f);
    goalShape.setOrigin({4.f, 4.f});
    goalShape.setFillColor(sf::Color::Green);

    //clear previous frame    
    m_window.clear(sf::Color::Black);

    // Load pixel RGBA data into texture
    for(int i = 0; i<count; i++){
        VehicleState s = vehicles.load(i);

        vehicleShape.setPosition({s.x, m_height - s.y});
        vehicleShape.setRotation(sf::radians(-s.heading));
        m_window.draw(vehicleShape);

        goalShape.setPosition({s.goalx, m_height - s.goaly});
        m_window.draw(goalShape);
    }
    m_window.display();



    return true;


};