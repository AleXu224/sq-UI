#include "../include/rect.hpp"
using namespace squi;

Rect Rect::fromPosSize(const vec2 &pos, const vec2 &size) {
	return Rect{
		pos.x,
		pos.y,
		pos.x + size.x,
		pos.y + size.y,
	};
}

bool Rect::contains(const vec2 &pos) const {
	if (pos.x >= left && pos.x < right && pos.y >= top && pos.y < bottom) return true;
	return false;
}

void Rect::overlap(const Rect &r) {
	if (r.left > left && r.left <= right)
		left = r.left;
	else
		left = right;

	if (r.top > top && r.top <= r.bottom)
		top = r.top;
	else
		top = bottom;

	if (r.right < right && r.right >= left)
		right = r.right;
	else
		right = left;

	if (r.bottom < bottom && r.bottom >= top)
		bottom = r.bottom;
	else
		bottom = top;
}

Rect::operator D2D_RECT_F() const {
	return D2D1::RectF(left, top, right, bottom);
}

Rect& Rect::inset(const float &dist) {
	left += dist;
	top += dist;
	right -= dist;
	bottom -= dist;
	return *this;
}
