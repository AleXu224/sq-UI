#include "../include/vec2.hpp"
using namespace squi;
void vec2::operator+=(const vec2 &v) {
	this->x += v.x;
	this->y += v.y;
}

vec2 vec2::operator+(const vec2 &v) const {
	return vec2{this->x + v.x, this->y + v.y};
}

void vec2::operator-=(const vec2 &v) {
	this->x -= v.x;
	this->y -= v.y;
}

vec2 vec2::operator-(const vec2 &v) const {
	return vec2{this->x - v.x, this->y - v.y};
}

void vec2::operator*=(const vec2 &v) {
	this->x -= v.x;
	this->y -= v.y;
}

vec2 vec2::operator*(const vec2 &v) const {
	return vec2{this->x * v.x, this->y * v.y};
}

void vec2::operator/=(const vec2 &v) {
	this->x -= v.x;
	this->y -= v.y;
}

vec2 vec2::operator/(const vec2 &v) const {
	return vec2{this->x / v.x, this->y / v.y};
}

vec2 vec2::operator+(const float &v) const {
	return vec2{this->x + v, this->y + v};
}

vec2 vec2::operator-(const float &v) const {
	return vec2{this->x - v, this->y - v};
}

vec2 vec2::operator*(const float &v) const {
	return vec2{this->x * v, this->y * v};
}

vec2 vec2::operator/(const float &v) const {
	return vec2{this->x / v, this->y / v};
}

vec2 &vec2::withY(const float &newY) {
	y = newY;
	return *this;
}

vec2 &vec2::withX(const float &newX) {
	x = newX;
	return *this;
}

vec2 vec2::withY(const float &newY) const {
	return vec2{x, newY};
}

vec2 vec2::withX(const float &newX) const {
	return vec2{newX, y};
}
