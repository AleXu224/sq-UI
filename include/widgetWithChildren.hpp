#ifndef SQ_UI_WIDGETWITHCHILDREN_HPP
#define SQ_UI_WIDGETWITHCHILDREN_HPP

#include "vector"
#include "widget.hpp"

namespace squi {
	class WidgetWithChildren : public Widget {
	public:
		std::vector<std::shared_ptr<Widget>> children{};

		explicit WidgetWithChildren(const WidgetData &data) : Widget(data) {}

		void update() override;
		void draw() override;

		[[nodiscard]] static std::vector<std::shared_ptr<Widget>> childrenFromPointers(const std::vector<Widget *> &children);
	};
}// namespace squi

#endif//SQ_UI_WIDGETWITHCHILDREN_HPP
