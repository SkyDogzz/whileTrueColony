#include "Color.hpp"

Color::Color() { }

Color::Color(float red, float green, float blue)
    : red(red)
    , green(green)
    , blue(blue)
{
}

Color::Color(float red, float green, float blue, float alpha)
    : red(red)
    , green(green)
    , blue(blue)
    , alpha(alpha)
{
}

Color::~Color() { }

float Color::getRed() const { return red; }

float Color::getGreen() const { return green; }

float Color::getBlue() const { return blue; }

float Color::getAlpha() const { return alpha; }

void Color::setRed(float red) { this->red = red; }

void Color::setGreen(float green) { this->green = green; }

void Color::setBlue(float blue) { this->blue = blue; }

void Color::setAlpha(float alpha) { this->alpha = alpha; }

void Color::set(float red, float green, float blue)
{
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

void Color::set(float red, float green, float blue, float alpha)
{
    setRed(red);
    setGreen(green);
    setBlue(blue);
    setAlpha(alpha);
}
