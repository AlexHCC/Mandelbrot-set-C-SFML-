#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//Variables
const int WIDTH =  800, HEIGHT = 800;
sf::Image fractal;
sf::Texture draw;
sf::Sprite print;

int main(int argc, char** argv) {
    
    //Initialization
    if (!draw.create(WIDTH, HEIGHT)) {return -1;}
    fractal.create(WIDTH, HEIGHT, sf::Color(100, 30, 30));
    
    cout << "Mandelbrot set" << endl;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        for(int i = 0; i < 800; i++) {fractal.setPixel(i, i, sf::Color(0, 30, 100));}
        
        draw.update(fractal);
              
        window.clear(sf::Color(30, 30, 30));
        print.setTexture(draw, false);
        window.draw(print);
        window.display();
    }

    return 0;
}

