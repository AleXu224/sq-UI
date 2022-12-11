#include "../include/margin.hpp"

using namespace squi;
vec2 Margin::getTopLeft() const {
	return vec2{left, top};
}

vec2 Margin::getHorizontalVectical() const {
	return vec2{left + right, top + bottom};
}