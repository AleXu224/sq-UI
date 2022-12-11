#ifndef SQ_UI_INVISIBLEWIDGET_HPP
#define SQ_UI_INVISIBLEWIDGET_HPP

#include "widgetWithChild.hpp"

namespace squi {
	// A widget that is invisible to the layout
	// Acts as a way to create a Widget out of other Widgets
	// Will report the data of the child to the parent and vice versa
	class InvisibleWidget : public WidgetWithChild {
	public:
		explicit InvisibleWidget(const WidgetData& data) : WidgetWithChild(data) {}

		[[nodiscard]] const vec2 &getPos() const override;
		[[nodiscard]] const vec2 &getSize() const override;
		[[nodiscard]] const Margin &getMargin() const override;
		[[nodiscard]] const Margin &getPadding() const override;
		[[nodiscard]] Widget *getParent() const override;
		[[nodiscard]] const vec2 &getSizeHint() const override;

		[[nodiscard]] const std::shared_ptr<Key> &getKey() const override;

		[[nodiscard]] vec2 getContentSize() const override;
		[[nodiscard]] vec2 getLayoutSize() const override;

		[[nodiscard]] Rect getRect() const override;
		[[nodiscard]] Rect getContentRect() const override;
		[[nodiscard]] Rect getLayoutRect() const override;

		void setPos(const vec2 &p) override;
		void setSize(const vec2 &v) override;
		void setMargin(const Margin &m) override;
		void setPadding(const Margin &m) override;
		void setParent(Widget *p) override;
		void setSizeHint(const vec2 &s) override;

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_INVISIBLEWIDGET_HPP
