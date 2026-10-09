#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "vehicleTypes.hpp"
#include "vehicleBatch.hpp"

class Renderer
{
private:
    unsigned int m_width;
    unsigned int m_height;
    sf::Texture m_texture;
    sf::Vector2f m_scale;
    sf::Sprite m_sprite;
    bool m_arrow_viz;
    sf::VertexArray m_arrows;
    sf::RenderWindow m_window;

public:
    Renderer(std::size_t width, std::size_t height, bool arrow_viz);

    bool draw(const vehicleBatch& vehicles, float dt, std::size_t curr_step, const environment& env);
    ~Renderer() = default;
};


