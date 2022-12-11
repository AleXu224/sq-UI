#ifndef SQ_UI_WIDGET_HPP
#define SQ_UI_WIDGET_HPP

#include <utility>

#include "key.hpp"
#include "margin.hpp"
#include "memory"
#include "rect.hpp"
#include "vec2.hpp"
#include "vector"

namespace squi {
	enum class Axis {
		both,
		vertical,
		horizontal,
		none,
	};

	enum class WidgetChildCount {
		none,
		single,
		multiple,
	};

	struct WidgetData {
		// A key to the widget which you can use anywhere in your code to access its data
		std::shared_ptr<Key> key = std::make_shared<Key>();

		// The size of the widget in pixels, this does not include the margin
		// The layout size of the wiget will be margin + size
		vec2 size{0, 0};

		// The distance your widget should be offset in relation to the parent
		Margin margin{};

		// The distance the content of the widget should be offset from the widget's position
		Margin padding{};

		// The axes in which this widget should match the outer size of the child
		// The resulting size will be the size of the margin + the size of the child
		// If expand is set to expand in one or both of the same axes as shrinkWrap
		// then expand will take priority
		Axis shrinkWrap = Axis::none;

		// The axes in which this widget should match the inner size of the parent
		// The resulting size will be the size of the parent - the size of the parent's padding
		// If expand is set to expand in one or both of the same axes as shrinkWrap
		// then this will take priority
		Axis expand = Axis::none;
	};

	class Widget {
		WidgetData data;
		vec2 pos{0};
		Widget *parent = nullptr;
		static int instances;

		// The ammount of children this widget will have
		const WidgetChildCount count;

		// A hint as to what the size of the widget should be
		// This should be given by another widget that would like to change the
		// size of the widget when shrinkWrap or expand is set
		vec2 sizeHint{-1};

		std::shared_ptr<Widget> child{};
		std::vector<std::shared_ptr<Widget>> children{};

	public:
		Widget() : data(WidgetData{}), count(WidgetChildCount::none) {
			++instances;
		}
		explicit Widget(WidgetData data, WidgetChildCount count = WidgetChildCount::none)
			: data(std::move(data)), count(WidgetChildCount::none) {
			this->data.key->set(this);
			++instances;
		}

		Widget(const Widget &) = delete;
		Widget(Widget &&) = delete;

		[[nodiscard]] virtual const vec2 &getPos() const;
		[[nodiscard]] virtual const vec2 &getSize() const;
		[[nodiscard]] virtual const Margin &getMargin() const;
		[[nodiscard]] virtual const Margin &getPadding() const;
		[[nodiscard]] virtual Widget *getParent() const;
		[[nodiscard]] virtual const vec2 &getSizeHint() const;
		[[nodiscard]] const std::shared_ptr<Widget> &getChild() const;
		[[nodiscard]] std::vector<std::shared_ptr<Widget>> getChildren() const;
		[[nodiscard]] const WidgetChildCount& getChildCountType() const;

		[[nodiscard]] virtual const std::shared_ptr<Key> &getKey() const;

		[[nodiscard]] virtual vec2 getContentSize() const;
		[[nodiscard]] virtual vec2 getLayoutSize() const;

		[[nodiscard]] virtual Rect getRect() const;
		[[nodiscard]] virtual Rect getContentRect() const;
		[[nodiscard]] virtual Rect getLayoutRect() const;

		virtual void setPos(const vec2 &p);
		virtual void setSize(const vec2 &v);
		virtual void setMargin(const Margin &m);
		virtual void setPadding(const Margin &m);
		virtual void setParent(Widget *p);
		virtual void setSizeHint(const vec2 &s);
		void setChild(Widget *c);
		void setChild(std::shared_ptr<Widget> c);
		void setChildren(const std::vector<Widget *>& c);
		void setChildren(std::vector<std::shared_ptr<Widget>> c);

		[[nodiscard]] static std::vector<std::shared_ptr<Widget>> childrenFromPointers(const std::vector<Widget *> &children);

		virtual void update();
		virtual void draw() = 0;

		virtual ~Widget() {
			this->data.key->markExpired();
			--instances;
		}

	private:
		// Helper functions
		void shrinkWrapWidget();
		void expandWidget();
		void getHintedSize();
	};
}// namespace squi

#endif//SQ_UI_WIDGET_HPP
