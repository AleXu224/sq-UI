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

	enum class WidgetContentType {
		none,
		singleChild,
		invisibleWithChild,
		multipleChildren,
	};

	struct WidgetData {
		// A key to the widget which you can use anywhere in your code to access its m_data
		std::shared_ptr<Key> key = std::make_shared<Key>();

		// The size of the widget in pixels, this does not include the margin
		// The layout size of the wiget will be margin + size
		vec2 size{0, 0};

		// The distance your widget should be offset in relation to the m_parent
		Margin margin{};

		// The distance the content of the widget should be offset from the widget's position
		Margin padding{};

		// The axes in which this widget should match the outer size of the m_child
		// The resulting size will be the size of the margin + the size of the m_child
		// If expand is set to expand in one or both of the same axes as shrinkWrap
		// then expand will take priority
		Axis shrinkWrap = Axis::none;

		// The axes in which this widget should match the inner size of the m_parent
		// The resulting size will be the size of the m_parent - the size of the m_parent's padding
		// If expand is set to expand in one or both of the same axes as shrinkWrap
		// then this will take priority
		Axis expand = Axis::none;

		// When true this widget will not be detected by hitchecks
		// Useful when making a widget that should ignore inputs like an overlay
		bool passThrough = false;

		[[nodiscard]] WidgetData withKey(std::shared_ptr<Key> newKey) const;
		[[nodiscard]] WidgetData withSize(const vec2& newSize) const;
		[[nodiscard]] WidgetData withMargin(const Margin& newMargin) const;
		[[nodiscard]] WidgetData withPadding(const Margin& newPadding) const;
		[[nodiscard]] WidgetData withShrinkWrap(const Axis& newShrinkWrap) const;
		[[nodiscard]] WidgetData withExpand(const Axis& newExpand) const;
		[[nodiscard]] WidgetData withPassThrough(const bool& newPassThrough) const;
	};

	class Widget {
		WidgetData m_data;
		vec2 m_pos{0};
		Widget *m_parent = nullptr;
		static int instances;

		// The type content this widget will have
		const WidgetContentType contentType;

		// A hint as to what the size of the widget should be
		// This should be given by another widget that would like to change the
		// size of the widget when shrinkWrap or expand is set
		vec2 sizeHint{-1};

		std::shared_ptr<Widget> m_child{};
		std::vector<std::shared_ptr<Widget>> m_children{};

		[[nodiscard]] WidgetData& getData();
		[[nodiscard]] const WidgetData& getData() const;
	protected:
		void overrideData(const WidgetData &newData);
	public:
		Widget() : m_data(WidgetData{}), contentType(WidgetContentType::none) {
			this->m_data.key->set(this);
			++instances;
		}
		explicit Widget(WidgetData data, WidgetContentType contentType = WidgetContentType::none)
			: m_data(std::move(data)), contentType(contentType) {
			this->m_data.key->set(this);
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
		[[nodiscard]] std::shared_ptr<Widget> &getChild();
		[[nodiscard]] const std::shared_ptr<Widget> &getChild() const;
		[[nodiscard]] std::vector<std::shared_ptr<Widget>> getChildren() const;
		[[nodiscard]] const Axis &getShrinkWrap() const;
		[[nodiscard]] const Axis &getExpand() const;
		[[nodiscard]] const bool &getPassThough() const;
		[[nodiscard]] const WidgetContentType &getChildCountType() const;

		[[nodiscard]] virtual const std::shared_ptr<Key> &getKey() const;

		[[nodiscard]] virtual vec2 getContentSize() const;
		[[nodiscard]] virtual vec2 getLayoutSize() const;

		[[nodiscard]] virtual Rect getRect() const;
		[[nodiscard]] virtual Rect getContentRect() const;
		[[nodiscard]] virtual Rect getLayoutRect() const;

		[[nodiscard]] virtual std::vector<Rect> getHitcheckRects() const;

		virtual void setPos(const vec2 &p);
		virtual void setSize(const vec2 &v);
		virtual void setMargin(const Margin &m);
		virtual void setPadding(const Margin &m);
		virtual void setParent(Widget *p);
		virtual void setSizeHint(const vec2 &s);
		void setChild(Widget *c);
		void setChild(std::shared_ptr<Widget> c);
		void setChildren(const std::vector<Widget *> &c);
		void setChildren(std::vector<std::shared_ptr<Widget>> c);
		void setPassThrough(const bool& p);

		[[nodiscard]] static std::vector<std::shared_ptr<Widget>> childrenFromPointers(const std::vector<Widget *> &children);

		virtual void update();
		virtual void draw();

		virtual ~Widget() {
			this->m_data.key->markExpired();
			--instances;
		}

		void getHintedSize();
	private:
		// Helper functions
		void shrinkWrapWidget();
		void expandWidget();
	};
}// namespace squi

#endif//SQ_UI_WIDGET_HPP
