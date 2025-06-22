
#ifndef GLOBALS_H
#define GLOBALS_H

#define COLOR_RGBA
//#define ULTRA_HD

#define PERIPHERAL_BASE 0xFE000000

#ifdef ULTRA_HD
    #define SCREENWIDTH 1920
    #define SCREENHEIGHT 1080
#else 
    #define SCREENWIDTH 640
    #define SCREENHEIGHT 480
#endif


#define VIRTUAL_SCREENWIDTH SCREENWIDTH
#define VIRTUAL_SCREENHEIGHT SCREENHEIGHT*2

#ifdef COLOR_RGBA
    #define DEPTH 32
#else 
    #define DEPTH 24
#endif

#endif

