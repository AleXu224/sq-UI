#ifndef SQ_UI_MARGIN_HPP
#define SQ_UI_MARGIN_HPP

#include "vec2.hpp"

namespace squi {
	class Margin {
	public:
		float left;
		float right;
		float top;
		float bottom;

		Margin() : left(0), right(0), top(0), bottom(0) {}
		Margin(const float &lrtb) : left(lrtb), right(lrtb), top(lrtb), bottom(lrtb) {}
		Margin(const float &lr, const float &tb) : left(lr), right(lr), top(tb), bottom(tb) {}
		Margin(const float &l, const float &r, const float &t, const float &b) : left(l), right(r), top(t), bottom(b) {}

		[[nodiscard]] vec2 getTopLeft() const;
		[[nodiscard]] vec2 getHorizontalVectical() const;
	};
}// namespace squi

#endif//SQ_UI_MARGIN_HPP
