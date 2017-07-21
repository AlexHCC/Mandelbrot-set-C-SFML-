# Mandelbrot set

Simple program made in c++ and SFML that simulates the "Mandelbrot set", witch is a recursive function: f(z) = z^2 + c (c = x + y*i). The values that belong to the set are those that their recursive limit isn't infinity. Those points are drawn black, and the others get a color based on the rate that they escape to infinity.

<p align="center">
  <img style="float: right;" src="http://i.imgur.com/jCl7InV.png"/>
</p>

## Feautures:

- Move around WASD
- Esc to exit
- Zoom in/Out with + and -
- High precision 

## TODO:

- Optimize (A lot!)
- Smooth colors (Linear interpolation)
- Add Julia set rendering

## Screenshots

<p align="left">
  <img style="float: right;" src="http://i.imgur.com/0mRVnr5.png"/>
</p>
<p align="left">
  <img style="float: right;" src="http://i.imgur.com/UO9e36r.png"/>
</p>

## Useful links:
https://en.wikipedia.org/wiki/Mandelbrot_set

## Build:
Use make. Latest version of -lSFML and GCC recommended.
