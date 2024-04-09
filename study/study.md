# SDL2
### A Journey of Learning

## Types:
1. Color: 
```c++
typedef struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;
```
2. Pixel:
```c++
typedef struct Pixel{
    float x;
    float y;
} Pixel;
```
3. Segment:
```c++
typedef struct Segment{
    Pixel xy1;
    Pixel xy2;
    Color color;
} Line;
```
4. Coords: 
```c++
typedef struct Coords{
    float *x;
    float *y;
} Coords;
```
5. Polygon:
```c++
typedef struct Polygon{
    Coords coords;
    Pixel center;
    Color color;
    uint16_t count;
    float length;
    float real_length;
    float orientation;
} Polygon;
```
