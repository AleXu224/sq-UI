#ifndef SQ_UI_ROW_HPP
#define SQ_UI_ROW_HPP

#include "../widget.hpp"

namespace squi {
	enum class RowAlignment {
		top,
		center,
		bottom,
	};

	struct RowArgs {
		WidgetData data{};
		RowAlignment alignment = RowAlignment::top;
		float spaceBetween = 0;
		std::vector<Widget *> children{};
	};

	class Row : public Widget {
		RowAlignment alignment;
		float spaceBetween;
	public:
		explicit Row(const RowArgs &args) : Widget(args.data, WidgetContentType::multipleChildren), alignment(args.alignment), spaceBetween(args.spaceBetween) {
			setChildren(args.children);
		}

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_ROW_HPP
