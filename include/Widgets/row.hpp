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
		std::vector<Widget *> children{};
	};

	class Row : public Widget {
		RowAlignment alignment;
	public:
		explicit Row(const RowArgs &args) : Widget(args.data, WidgetChildCount::multiple), alignment(args.alignment) {
			setChildren(args.children);
		}

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_ROW_HPP
