#include <iostream>
#include <cmath>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

//Variables
const int WIDTH = 400, HEIGHT = 400; //Change resolution of the fractal picture.
sf::Image fractal;
sf::Texture draw;
sf::Sprite print;
sf::RenderWindow window;

int numOfIterations = 30; //The higher it looks better, but less optimized.
bool isUpdate = true; 
float optimisationFactor = 1.8; //The higher the better, but it impacts the performance a lot!
float upscaleValue = 1.0f; //The lower the better. 1 is recommended.
long double lod = 1.0f;
long double holder = 1.0f;

long double scale = 2.0f;
long double translation = 0.1f;
long double xOffset = -0.5f;
long double yOffset = 0.0f;

void mapValues(int posX, int posY, long double &linkX, long double &linkY, long double canvasSize);
void moveCanvas(int pointx, int pointy, int widthx, int widthy);
sf::Color hsv(int hue, long double sat, long double val);

int main(int argc, char** argv) {
    
    //Initialization
    if (!draw.create(WIDTH, HEIGHT)) {return -1;}
    fractal.create(WIDTH, HEIGHT, sf::Color(30, 30, 30));
    
    cout << "Mandelbrot set" << endl;
    window.create(sf::VideoMode(WIDTH*upscaleValue, HEIGHT*upscaleValue), "Mandelbrot set", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {xOffset = xOffset - translation*scale; isUpdate = true;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {xOffset = xOffset + translation*scale; isUpdate = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {yOffset = yOffset - translation*scale; isUpdate = true;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {yOffset = yOffset + translation*scale; isUpdate = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {scale = scale * 0.9; lod = lod * optimisationFactor; isUpdate = true;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {scale = scale / 0.9; lod = lod / optimisationFactor; isUpdate = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}
        }
        
        if (lod > holder + 1.0f) {numOfIterations = numOfIterations + 1; holder = holder + 1.0f; isUpdate = true;}
        else if (lod < holder - 1.0f) {numOfIterations = numOfIterations - 1; holder = holder - 1.0f; isUpdate = true;}
        if (isUpdate) {
            
            thread tf(moveCanvas, 0, 0, WIDTH/2, HEIGHT/2);
            tf.join();
            thread ts(moveCanvas, WIDTH/2, 0, WIDTH, HEIGHT/2);
            ts.join();
            thread tt(moveCanvas, 0, HEIGHT/2, WIDTH/2, HEIGHT);
            tt.join();
            thread tq(moveCanvas, WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
            tq.join();
            
            window.display();
            isUpdate = false;
        }
    }

    return 0;
}

void mapValues(int posX, int posY, long double &linkX, long double &linkY, long double canvasSize) {
    if (posX > WIDTH || posX < -WIDTH || posY > HEIGHT || posY < -HEIGHT) {
        cout << "Out of bounds map values" << endl;
        return;
    }
    //posX = WIDTH / 2 + (linkX * WIDTH / 2) / canvasSize;
    //posY = HEIGHT / 2 - (linkY * HEIGHT / 2) / canvasSize;
    
    linkX = (posX - WIDTH / 2) * canvasSize / WIDTH * 2;
    linkY = (posY - HEIGHT / 2) * canvasSize / HEIGHT * 2;  
}

void moveCanvas(int pointx, int pointy, int widthx, int widthy) {
    for (int x = pointx; x < widthx; x++) { for (int y = pointy; y < widthy; y++) {
        long double a, b;
        mapValues(x, y, a, b, scale);
        long double tx = 0.0f;
        long double ty = 0.0f;
        a = a + xOffset;
        b = b + yOffset;
        
        float var = 0.25f;
        a = a - var;
        long double p = sqrt((a-1/4)*(a-1/4)+b*b);
        long double q = (a-1/4)*(a-1/4)+b*b;
        
        if (a < p-2*p*p+1/4) {fractal.setPixel(x, y, sf::Color(0, 0, 0));}
        else {
            a= a + var;
            for (int i = 0; i < numOfIterations; i++) {
                long double xtemp =  tx*tx - ty*ty + a;
                ty = 2*tx*ty + b;
                tx = xtemp;
                //Different coloring options
                //if (tx*tx + ty*ty >= 2*2) {fractal.setPixel(x, y, hsv((i*5-(i-1)*5) * numOfIterations - i*5, 255, 255)); i = numOfIterations;}
                //if (tx*tx + ty*ty >= 2*2) {fractal.setPixel(x, y, hsv((i*5-(i-1)*5) * numOfIterations + i*5, 255, 255)); i = numOfIterations;}
                //if (tx*tx + ty*ty >= 2*2) {fractal.setPixel(x, y, hsv((i*5-(i-1)*5) / numOfIterations - i*5, 255, 255)); i = numOfIterations;}
                if (tx*tx + ty*ty >= 2*2) {fractal.setPixel(x, y, hsv((i*5-(i-1)*5) * i + i*5, 255, 255)); i = numOfIterations;}
                else {fractal.setPixel(x, y, sf::Color(0, 0, 0));}
            } 
        }
           
    }}
        
        draw.update(fractal);
        window.clear();
        print.setTexture(draw, false);
        print.setScale(upscaleValue,upscaleValue);
        window.draw(print);
             
}

sf::Color hsv(int hue, long double sat, long double val) {
    hue %= 360;
    while(hue<0) {hue += 360;}

    if(sat<0.f) {sat = 0.0f;}
    if(sat>1.f) {sat = 1.0f;}

    if(val<0.f) {val = 0.f;}
    if(val>1.f) {val = 1.f;}

    int h = hue/60;
    long double f = double(hue) / 60-h;
    long double p = val*(1.0f - sat);
    long double q = val*(1.0f - sat*f);
    long double t = val*(1.0f - sat*(1-f));

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
