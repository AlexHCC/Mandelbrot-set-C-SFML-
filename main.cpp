#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

//Variables
const int WIDTH =  800, HEIGHT = 800;
sf::Image fractal;
sf::Texture draw;
sf::Sprite print;
int numOfIterations = 50;

void mapValues(int posX, int posY, float &linkX, float &linkY, float canvasSize);

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
        
        for (int x = 0; x < WIDTH; x++) { for (int y = 0; y < HEIGHT; y++) {
            float a, b;
            mapValues(x, y, a, b, 2.0f);
            float tx = 0.0f;
            float ty = 0.0f;
            
            for (int i = 0; i < numOfIterations; i++) {
                float xtemp =  tx*tx - ty*ty + a;
                ty = 2*tx*ty + b;
                tx = xtemp;
                if (tx*tx + ty*ty >= 2*2 || tx > 20) {i = numOfIterations;  fractal.setPixel(x, y, sf::Color(255, 255, 255));}
            }
           
        }}
        
        //int x, y = 0;
        //mapValues(0.5555f, 1.99999f, x, y, 2.0f);
        //fractal.setPixel(x, y, sf::Color(255, 255, 0));
        //for(int i = 0; i < 800; i++) {fractal.setPixel(i, i, sf::Color(255, 255, 0));}
        
        draw.update(fractal);     
        window.clear();
        print.setTexture(draw, false);
        window.draw(print);
        window.display();
    }

    return 0;
}

void mapValues(int posX, int posY, float &linkX, float &linkY, float canvasSize) {
    if (posX > WIDTH || posX < -WIDTH || posY > HEIGHT || posY < -HEIGHT) {
        cout << "Out of bounds map values" << endl;
        return;
    }
    //posX = WIDTH / 2 + (linkX * WIDTH / 2) / canvasSize;
    //posY = HEIGHT / 2 - (linkY * HEIGHT / 2) / canvasSize;
    
    linkX = (posX - WIDTH / 2) * canvasSize / WIDTH * 2;
    linkY = (posY - HEIGHT / 2) * canvasSize / HEIGHT * 2;
    
}
