#ifndef SQ_UI_COLUMN_HPP
#define SQ_UI_COLUMN_HPP

#include "../widget.hpp"

namespace squi {
	struct ColumnArgs {
		WidgetData data{};
		std::vector<Widget *> children{};
	};

	class Column : public Widget {
	public:
		explicit Column(const ColumnArgs &args) : Widget(args.data, WidgetChildCount::multiple) {
			setChildren(args.children);
		}

		void update() override;

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_COLUMN_HPP
