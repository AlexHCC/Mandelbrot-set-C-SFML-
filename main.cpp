#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

//Variables
const int WIDTH =  400, HEIGHT = 400;
sf::Image fractal;
sf::Texture draw;
sf::Sprite print;
int numOfIterations = 100;
float scale = 2.0f;
float translation = 0.1f;
float xOffset = 0.0f;
float yOffset = 0.0f;

void mapValues(int posX, int posY, float &linkX, float &linkY, float canvasSize);
void moveCanvas();
sf::Color hsv(int hue, float sat, float val);

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {xOffset = xOffset - translation*scale;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {xOffset = xOffset + translation*scale;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {yOffset = yOffset - translation*scale;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {yOffset = yOffset + translation*scale;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {scale = scale * 0.9;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {scale = scale / 0.9;}
        }
        
        for (int x = 0; x < WIDTH; x++) { for (int y = 0; y < HEIGHT; y++) {
            float a, b;
            mapValues(x, y, a, b, scale);
            float tx = 0.0f;
            float ty = 0.0f;
            a = a + xOffset;
            b = b + yOffset;
            
            for (int i = 0; i < numOfIterations; i++) {
                float xtemp =  tx*tx - ty*ty + a;
                ty = 2*tx*ty + b;
                tx = xtemp;
                if (tx*tx + ty*ty >= 2*2) {fractal.setPixel(x, y, hsv(i, 255, 255)); i = numOfIterations;}
                else {fractal.setPixel(x, y, sf::Color(255, 255, 255));}
            }
           
        }}
        
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
    //linkX = linkX - 0.5;
    //linkY = linkY - 0.5f;
    
}

void moveCanvas() {
    
}

sf::Color hsv(int hue, float sat, float val) {
    hue %= 360;
    while(hue<0) hue += 360;

    if(sat<0.f) sat = 0.f;
    if(sat>1.f) sat = 1.f;

    if(val<0.f) val = 0.f;
    if(val>1.f) val = 1.f;

    int h = hue/60;
    float f = float(hue)/60-h;
    float p = val*(1.f-sat);
    float q = val*(1.f-sat*f);
    float t = val*(1.f-sat*(1-f));

    switch(h) {
    default:
        case 0:
        case 6: return sf::Color(val*255, t*255, p*255);
        case 1: return sf::Color(q*255, val*255, p*255);
        case 2: return sf::Color(p*255, val*255, t*255);
        case 3: return sf::Color(p*255, q*255, val*255);
        case 4: return sf::Color(t*255, p*255, val*255);
        case 5: return sf::Color(val*255, p*255, q*255);
    }
}
