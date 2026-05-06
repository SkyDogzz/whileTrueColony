#include "Vec2.hpp"
#include <cmath>
#include <ostream>

Vec2::Vec2() { }

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{
}

Vec2::~Vec2() { }

float Vec2::getX() const { return x; }

float Vec2::getY() const { return y; }

void Vec2::setX(float x) { this->x = x; }

void Vec2::setY(float y) { this->y = y; }

void Vec2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool Vec2::isZero() const { return x == 0 && y == 0; }

bool Vec2::isNearlyZero(float epsilon) const { return length() <= epsilon; }

float Vec2::length() const { return std::sqrt(lengthSquared()); }

float Vec2::lengthSquared() const { return x * x + y * y; }

float Vec2::angle() const { return std::atan2(y, x); }

Vec2 Vec2::normalized() const
{
    const float currentLength = length();

    if (currentLength == 0.0f)
        return Vec2::zero();
    return Vec2(x / currentLength, y / currentLength);
}

Vec2 Vec2::perpendicular() const { return Vec2(-y, x); }

Vec2 Vec2::rotated(float radians) const
{
    const float cosAngle = std::cos(radians);
    const float sinAngle = std::sin(radians);

    return Vec2(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle);
}

void Vec2::normalize()
{
    const Vec2 result = normalized();

    set(result.x, result.y);
}

void Vec2::rotate(float radians)
{
    const Vec2 result = rotated(radians);

    set(result.x, result.y);
}

float Vec2::dot(const Vec2& other) const { return x * other.x + y * other.y; }

float Vec2::cross(const Vec2& other) const { return x * other.y - y * other.x; }

float Vec2::distanceTo(const Vec2& other) const { return Vec2::distance(*this, other); }

float Vec2::distanceSquaredTo(const Vec2& other) const { return Vec2::distanceSquared(*this, other); }

float Vec2::angleTo(const Vec2& other) const
{
    const float lengthProduct = length() * other.length();

    if (lengthProduct == 0.0f)
        return 0.0f;

    float cosine = dot(other) / lengthProduct;
    if (cosine < -1.0f)
        cosine = -1.0f;
    if (cosine > 1.0f)
        cosine = 1.0f;
    return std::acos(cosine);
}

Vec2 Vec2::directionTo(const Vec2& target) const { return (target - *this).normalized(); }

Vec2 Vec2::movedTowards(const Vec2& target, float maxDistance) const
{
    return Vec2::moveTowards(*this, target, maxDistance);
}

Vec2 Vec2::lerped(const Vec2& target, float amount) const { return Vec2::lerp(*this, target, amount); }

Vec2 Vec2::clampedLength(float maxLength) const
{
    if (maxLength <= 0.0f)
        return Vec2::zero();
    if (lengthSquared() <= maxLength * maxLength)
        return *this;
    return normalized() * maxLength;
}

bool Vec2::equals(const Vec2& other) const { return *this == other; }

bool Vec2::nearlyEquals(const Vec2& other, float epsilon) const
{
    return std::fabs(x - other.x) <= epsilon && std::fabs(y - other.y) <= epsilon;
}

Vec2 Vec2::operator+() const { return *this; }

Vec2 Vec2::operator-() const { return Vec2(-x, -y); }

Vec2 Vec2::operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }

Vec2 Vec2::operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }

Vec2 Vec2::operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }

Vec2 Vec2::operator/(float scalar) const { return Vec2(x / scalar, y / scalar); }

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vec2::operator==(const Vec2& other) const { return x == other.x && y == other.y; }

bool Vec2::operator!=(const Vec2& other) const { return !(*this == other); }

Vec2 Vec2::zero() { return Vec2(0.0f, 0.0f); }

Vec2 Vec2::one() { return Vec2(1.0f, 1.0f); }

Vec2 Vec2::up() { return Vec2(0.0f, 1.0f); }

Vec2 Vec2::down() { return Vec2(0.0f, -1.0f); }

Vec2 Vec2::left() { return Vec2(-1.0f, 0.0f); }

Vec2 Vec2::right() { return Vec2(1.0f, 0.0f); }

Vec2 Vec2::fromAngle(float radians) { return Vec2(std::cos(radians), std::sin(radians)); }

float Vec2::dot(const Vec2& a, const Vec2& b) { return a.dot(b); }

float Vec2::cross(const Vec2& a, const Vec2& b) { return a.cross(b); }

float Vec2::distance(const Vec2& a, const Vec2& b) { return (b - a).length(); }

float Vec2::distanceSquared(const Vec2& a, const Vec2& b) { return (b - a).lengthSquared(); }

Vec2 Vec2::lerp(const Vec2& a, const Vec2& b, float amount) { return a + (b - a) * amount; }

Vec2 Vec2::moveTowards(const Vec2& current, const Vec2& target, float maxDistance)
{
    const Vec2 toTarget = target - current;
    const float distance = toTarget.length();

    if (distance == 0.0f || distance <= maxDistance)
        return target;
    if (maxDistance <= 0.0f)
        return current;
    return current + toTarget / distance * maxDistance;
}

Vec2 operator*(float scalar, const Vec2& vector) { return vector * scalar; }

std::ostream& operator<<(std::ostream& output, const Vec2& vector)
{
    output << "Vec2(" << vector.getX() << ", " << vector.getY() << ")";
    return output;
}
