
unsigned int make_color(unsigned int red, unsigned int green, unsigned int blue) {
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

unsigned int get_fb_of(unsigned int x, unsigned int y, unsigned int pitch) {
    return (y * pitch / 4) + x;
}

