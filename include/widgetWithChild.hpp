#ifndef SQ_UI_WIDGETWITHCHILD_HPP
#define SQ_UI_WIDGETWITHCHILD_HPP

#include "widget.hpp"

namespace squi {
	class WidgetWithChild : public Widget {
	public:
		std::shared_ptr<Widget> child;

		explicit WidgetWithChild(const WidgetData &data)
			: Widget(data) {
		}

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_WIDGETWITHCHILD_HPP
