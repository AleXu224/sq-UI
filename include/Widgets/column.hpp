#ifndef SQ_UI_COLUMN_HPP
#define SQ_UI_COLUMN_HPP

#include "../widget.hpp"

namespace squi {
	enum class ColumnAlignment {
		left,
		center,
		right,
	};

	struct ColumnArgs {
		WidgetData data{};
		ColumnAlignment alignment = ColumnAlignment::left;
		float spaceBetween = 0;
		std::vector<Widget *> children{};
	};

	class Column : public Widget {
		ColumnAlignment alignment;
		float spaceBetween;
	public:
		explicit Column(const ColumnArgs &args) : Widget(args.data, WidgetContentType::multipleChildren), alignment(args.alignment), spaceBetween(args.spaceBetween) {
			setChildren(args.children);
		}

		void update() override;

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_COLUMN_HPP
