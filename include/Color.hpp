#pragma once

class Color {
private:
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float alpha = 1.0f;

public:
    Color();
    Color(float red, float green, float blue);
    Color(float red, float green, float blue, float alpha);
    ~Color();

    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getAlpha() const;

    void setRed(float red);
    void setGreen(float green);
    void setBlue(float blue);
    void setAlpha(float alpha);
    void set(float red, float green, float blue);
    void set(float red, float green, float blue, float alpha);
};
