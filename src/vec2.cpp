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
