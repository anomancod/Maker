#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(800, 600), "The Maker");

    sf::RectangleShape box(sf::Vector2f(50.f, 50.f));
    box.setFillColor(sf::Color::White);
    box.setPosition(100.f, 100.f);

    sf::RectangleShape table(sf::Vector2f(800.f, 50.f));
    table.setFillColor(sf::Color::Yellow);
    table.setPosition(0.f, 550.f);

    sf::Vector2i mousePos, mousePosPast;
    float mouseMoveX, mouseMoveY;

    bool link = false;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                mousePos = sf::Mouse::getPosition(window);

                if (box.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    link = true;
                }
            }

            if (event.type == sf::Event::MouseMoved) 
            {
                mouseMoveX = sf::Mouse::getPosition(window).x - mousePosPast.x;
                mouseMoveY = sf::Mouse::getPosition(window).y - mousePosPast.y;

                mousePosPast = sf::Mouse::getPosition(window);

                if(link == true){ box.move(mouseMoveX, mouseMoveY); }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                link = false;
            }
        }

        // гравитация
        if (!table.getGlobalBounds().intersects(box.getGlobalBounds()) && link == false) 
        {
            box.move(0.f, 0.5f * time);
        }

        window.clear(sf::Color::Black);
        
        window.draw(table);
        window.draw(box);

        window.display();
    }
}
