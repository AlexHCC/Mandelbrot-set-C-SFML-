#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//Variables
const int WIDTH =  800, HEIGHT = 800;
sf::Image fractal;
sf::Texture draw;
sf::Sprite print;

void mapValues(float posX, float posY, int &linkX, int &linkY, float canvasSize);

int main(int argc, char** argv) {
    
    //Initialization
    if (!draw.create(WIDTH, HEIGHT)) {return -1;}
    fractal.create(WIDTH, HEIGHT, sf::Color(30, 30, 30));
    
    cout << "Mandelbrot set" << endl;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        
        //for(int i = 0; i < 800; i++) {fractal.setPixel(i, i, sf::Color(255, 255, 0));}
        
        int x, y = 0;
        
        mapValues(0.5555555f, 1.99999999999f, x, y, 2.0f);
        fractal.setPixel(x, y, sf::Color(255, 255, 0));
        
        draw.update(fractal);     
        window.clear();
        print.setTexture(draw, false);
        window.draw(print);
        window.display();
    }

    return 0;
}

void mapValues(float posX, float posY, int &linkX, int &linkY, float canvasSize) {
    if (posX > canvasSize || posX < -canvasSize || posY > canvasSize || posY < -canvasSize) {
        cout << "Out of bounds map values" << endl;
        return;
    }
    linkX = ((int)(WIDTH / 2 + (posX * WIDTH / 2) / canvasSize));
    linkY = ((int)(HEIGHT / 2 - (posY * HEIGHT / 2) / canvasSize));
}
