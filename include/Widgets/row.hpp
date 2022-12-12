#ifndef SQ_UI_ROW_HPP
#define SQ_UI_ROW_HPP

#include "../widget.hpp"

namespace squi {
	struct RowArgs {
		WidgetData data{};
		std::vector<Widget *> children{};
	};

	class Row : public Widget {
	public:
		explicit Row(const RowArgs &args) : Widget(args.data, WidgetChildCount::multiple) {
			setChildren(args.children);
		}

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_ROW_HPP
