#ifndef SQ_UI_VEC2_HPP
#define SQ_UI_VEC2_HPP

#include "d2d1.h"

namespace squi {

	class vec2 {
	public:
		float x;
		float y;

		vec2() : x(0), y(0) {}
		vec2(const float &xy) : x(xy), y(xy) {}
		vec2(const float &x, const float &y) : x(x), y(y) {}

		void operator+=(const vec2 &v);
		[[nodiscard]] vec2 operator+(const vec2 &v) const;
		[[nodiscard]] vec2 operator+(const float &v) const;

		void operator-=(const vec2 &v);
		[[nodiscard]] vec2 operator-(const vec2 &v) const;
		[[nodiscard]] vec2 operator-(const float &v) const;

		void operator*=(const vec2 &v);
		[[nodiscard]] vec2 operator*(const vec2 &v) const;
		[[nodiscard]] vec2 operator*(const float &v) const;

		void operator/=(const vec2 &v);
		[[nodiscard]] vec2 operator/(const vec2 &v) const;
		[[nodiscard]] vec2 operator/(const float &v) const;

		vec2 &withY(const float& newY);
		vec2 &withX(const float& newX);

		[[nodiscard]] vec2 withY(const float&newY) const;
		[[nodiscard]] vec2 withX(const float& newX) const;

		[[nodiscard]] vec2 withYOffset(const float& yOffset) const;
		[[nodiscard]] vec2 withXOffset(const float& xOffset) const;

		operator D2D_POINT_2F() const;
	};
}// namespace squi

#endif//SQ_UI_VEC2_HPP
