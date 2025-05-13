
unsigned int make_color(unsigned int red, unsigned int green, unsigned int blue) {
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

