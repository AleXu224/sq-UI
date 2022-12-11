#ifndef SQ_UI_WIDGET_HPP
#define SQ_UI_WIDGET_HPP

#include <utility>

#include "key.hpp"
#include "margin.hpp"
#include "memory"
#include "rect.hpp"
#include "vec2.hpp"

namespace squi {
	struct WidgetData {
		std::shared_ptr<Key> key = std::make_shared<Key>();
		vec2 size{0, 0};
		Margin margin{};
		Margin padding{};
	};

	class Widget {
		WidgetData data;
		vec2 pos{0};
		Widget *parent = nullptr;
		static int instances;

	public:
		Widget() : data(WidgetData{}) {
			++instances;
		}
		explicit Widget(WidgetData data) : data(std::move(data)) {
			this->data.key->set(this);
			++instances;
		}

		Widget(const Widget&) = delete;
		Widget(Widget &&) = delete;

		[[nodiscard]] virtual const vec2 &getPos() const;
		[[nodiscard]] virtual const vec2 &getSize() const;
		[[nodiscard]] virtual const Margin &getMargin() const;
		[[nodiscard]] virtual const Margin &getPadding() const;
		[[nodiscard]] virtual const Widget *getParent() const;

		[[nodiscard]] virtual const std::shared_ptr<Key> &getKey() const;

		[[nodiscard]] vec2 getContentSize() const;
		[[nodiscard]] vec2 getLayoutSize() const;

		[[nodiscard]] Rect getRect() const;
		[[nodiscard]] Rect getContentRect() const;
		[[nodiscard]] Rect getLayoutRect() const;

		virtual void setPos(const vec2 &p);
		virtual void setSize(const vec2 &v);
		virtual void setMargin(const Margin &m);
		virtual void setPadding(const Margin &m);
		virtual void setParent(Widget *p);

		virtual void update() = 0;
		virtual void draw() = 0;

		virtual ~Widget() {
			this->data.key->markExpired();
			--instances;
		}
	};
}// namespace squi

#endif//SQ_UI_WIDGET_HPP
