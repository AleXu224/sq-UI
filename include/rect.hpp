#ifndef SQ_UI_RECT_HPP
#define SQ_UI_RECT_HPP

#include "d2d1.h"
#include "vec2.hpp"

namespace squi {
	class Rect {
	public:
		float left;
		float top;
		float right;
		float bottom;

		Rect(const vec2 &pos1, const vec2 &pos2)
			: left(pos1.x),
			  top(pos1.y),
			  right(pos2.x),
			  bottom(pos2.y) {}

		Rect(float left, float top, float right, float bottom)
			: left(left),
			  top(top),
			  right(right),
			  bottom(bottom) {}

		static Rect fromPosSize(const vec2 &pos, const vec2 &size);

		[[nodiscard]] bool contains(const vec2 &pos) const;

		void overlap(const Rect &r);

		[[nodiscard]] operator D2D_RECT_F() const;

		Rect& inset(const float& dist);
	};
}// namespace squi

#endif//SQ_UI_RECT_HPP
