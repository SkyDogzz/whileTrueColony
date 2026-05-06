#pragma once

#include <iosfwd>

class Vec2 {
private:
    float x = 0.0f;
    float y = 0.0f;

public:
    Vec2();
    Vec2(float x, float y);
    ~Vec2();

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);
    void set(float x, float y);

    bool isZero() const;
    bool isNearlyZero(float epsilon = 0.0001f) const;

    float length() const;
    float lengthSquared() const;
    float angle() const;

    Vec2 normalized() const;
    Vec2 perpendicular() const;
    Vec2 rotated(float radians) const;

    void normalize();
    void rotate(float radians);

    float dot(const Vec2& other) const;
    float cross(const Vec2& other) const;
    float distanceTo(const Vec2& other) const;
    float distanceSquaredTo(const Vec2& other) const;
    float angleTo(const Vec2& other) const;

    Vec2 directionTo(const Vec2& target) const;
    Vec2 movedTowards(const Vec2& target, float maxDistance) const;
    Vec2 lerped(const Vec2& target, float amount) const;
    Vec2 clampedLength(float maxLength) const;

    bool equals(const Vec2& other) const;
    bool nearlyEquals(const Vec2& other, float epsilon = 0.0001f) const;

    Vec2 operator+() const;
    Vec2 operator-() const;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(float scalar);
    Vec2& operator/=(float scalar);

    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;

    static Vec2 zero();
    static Vec2 one();
    static Vec2 up();
    static Vec2 down();
    static Vec2 left();
    static Vec2 right();
    static Vec2 fromAngle(float radians);
    static float dot(const Vec2& a, const Vec2& b);
    static float cross(const Vec2& a, const Vec2& b);
    static float distance(const Vec2& a, const Vec2& b);
    static float distanceSquared(const Vec2& a, const Vec2& b);
    static Vec2 lerp(const Vec2& a, const Vec2& b, float amount);
    static Vec2 moveTowards(const Vec2& current, const Vec2& target, float maxDistance);
};

Vec2 operator*(float scalar, const Vec2& vector);
std::ostream& operator<<(std::ostream& output, const Vec2& vector);
