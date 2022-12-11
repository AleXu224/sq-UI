#ifndef SQ_UI_BORDER_HPP
#define SQ_UI_BORDER_HPP

#include "color.hpp"

namespace squi {
	enum class BorderPosition {
		inside,
		outside,
	};

	struct Border {
		float size{0};
		Color color{0, 0, 0, 1};
		BorderPosition position = BorderPosition::outside;
	};
}

#endif//SQ_UI_BORDER_HPP
