#include <utility>

#include "../include/widget.hpp"
using namespace squi;

int Widget::instances = 0;

const vec2 &Widget::getSize() const {
	return m_data.size;
}

const Margin &Widget::getMargin() const {
	return m_data.margin;
}

const Margin &Widget::getPadding() const {
	return m_data.padding;
}

void Widget::setSize(const vec2 &v) {
	m_data.size = v;
}

void Widget::setMargin(const Margin &m) {
	m_data.margin = m;
}

void Widget::setPadding(const Margin &m) {
	m_data.padding = m;
}

const vec2 &Widget::getPos() const {
	return m_pos;
}

void Widget::setPos(const vec2 &p) {
	m_pos = p;
}

Widget *Widget::getParent() const {
	return m_parent;
}

void Widget::setParent(Widget *p) {
	if (p) m_parent = p;
}

vec2 Widget::getContentSize() const {
	return getSize() - getPadding().getHorizontalVectical();
}

vec2 Widget::getLayoutSize() const {
	return getSize() + getMargin().getHorizontalVectical();
}

Rect Widget::getRect() const {
	return Rect::fromPosSize(getPos() + getMargin().getTopLeft(), getSize());
}

Rect Widget::getContentRect() const {
	return Rect::fromPosSize(getPos() + getMargin().getTopLeft() + getPadding().getTopLeft(), getSize() - getPadding().getHorizontalVectical());
}

Rect Widget::getLayoutRect() const {
	return Rect::fromPosSize(getPos(), getSize() + getMargin().getHorizontalVectical() + getPadding().getHorizontalVectical());
}

const std::shared_ptr<Key> &Widget::getKey() const {
	return m_data.key;
}

const vec2 &Widget::getSizeHint() const {
	return sizeHint;
}

void Widget::setSizeHint(const vec2 &s) {
	sizeHint = s;
}

const std::shared_ptr<Widget> &Widget::getChild() const {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");
	return m_child;
}

std::vector<std::shared_ptr<Widget>> Widget::getChildren() const {
	if (count != WidgetChildCount::multiple) throw std::runtime_error("Child is not of multiple count");

	return m_children;
}

const WidgetChildCount &Widget::getChildCountType() const {
	return count;
}

void Widget::setChild(Widget *c) {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");

	m_child.reset(c);
}

void Widget::setChild(std::shared_ptr<Widget> c) {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");

	m_child = std::move(c);
}

std::vector<std::shared_ptr<Widget>> Widget::childrenFromPointers(const std::vector<Widget *> &children) {
	std::vector<std::shared_ptr<Widget>> ret{};
	ret.reserve(children.size());

	for (auto *child : children) {
		ret.push_back(std::shared_ptr<Widget>(child));
	}

	return ret;
}

void Widget::setChildren(const std::vector<Widget *>& c) {
	if (count != WidgetChildCount::multiple) throw std::runtime_error("Child is not of multiple count");

	m_children = childrenFromPointers(c);
}

void Widget::setChildren(std::vector<std::shared_ptr<Widget>> c) {
	if (count != WidgetChildCount::multiple) throw std::runtime_error("Child is not of multiple count");

	m_children = std::move(c);
}

void Widget::shrinkWrapWidget() {
	auto padding = getPadding().getHorizontalVectical();
	if (m_data.shrinkWrap == Axis::horizontal || m_data.shrinkWrap == Axis::both)
		m_data.size.x = m_child->getLayoutSize().x + padding.x;

	if (m_data.shrinkWrap == Axis::vertical || m_data.shrinkWrap == Axis::both)
		m_data.size.y = m_child->getLayoutSize().y + padding.y;
}

void Widget::expandWidget() {
	auto margin = getMargin().getHorizontalVectical();
	if (m_data.expand == Axis::horizontal || m_data.expand == Axis::both)
		m_data.size.x = m_parent->getContentSize().x - margin.x;

	if (m_data.expand == Axis::vertical || m_data.expand == Axis::both)
		m_data.size.y = m_parent->getContentSize().y - margin.y;
}

void Widget::getHintedSize() {
	if (sizeHint.x != -1) m_data.size.x = sizeHint.x;
	if (sizeHint.y != -1) m_data.size.y = sizeHint.y;
}

void Widget::update() { // NOLINT(misc-no-recursion)
	switch (count) {
		case WidgetChildCount::none: {
			expandWidget();
			getHintedSize();
			return;
		}
		case WidgetChildCount::single: {
			if (m_child) {
				m_child->setParent(this);
				shrinkWrapWidget();
			}
			if (m_parent != nullptr) expandWidget();
			getHintedSize();

			if (m_child) m_child->update();
			return;
		}
		case WidgetChildCount::multiple: {
			if (m_parent != nullptr) expandWidget();
			getHintedSize();

			for (auto &childPtr : m_children) {
				if (!childPtr) continue;
				childPtr->setParent(this);
				childPtr->update();
			}
			return;
		}
	}
}

void Widget::draw() { // NOLINT(misc-no-recursion)
	switch (count) {
		case WidgetChildCount::none: {
			return;
		}
		case WidgetChildCount::single: {
			auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

			auto child = getChild();

			if (child) {
				child->setPos(pos);
				child->draw();
			}
			return;
		}
		case WidgetChildCount::multiple: {
			auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

			auto children = getChildren();

			for (auto &child : children) {
				child->setPos(pos);
				child->draw();
			}
			return;
		}
	}
}

std::vector<Rect> Widget::getHitcheckRects() const {
	switch (count) {
		case WidgetChildCount::none: {
			return {};
		}
		default: {
			if (m_data.passThrough) return {};
			return {getRect()};
		}
	}
}

const Axis &Widget::getShrinkWrap() const {
	return m_data.shrinkWrap;
}

const Axis &Widget::getExpand() const {
	return m_data.expand;
}

const bool &Widget::getPassThough() const {
	return m_data.passThrough;
}

void Widget::setPassThrough(const bool &p) {
	m_data.passThrough = p;
}

WidgetData WidgetData::withKey(std::shared_ptr<Key> newKey) const {
	auto ret = *this;
	ret.key = newKey;
	return ret;
}

WidgetData WidgetData::withSize(const vec2 &newSize) const {
	auto ret = *this;
	ret.size = newSize;
	return ret;
}

WidgetData WidgetData::withMargin(const Margin &newMargin) const {
	auto ret = *this;
	ret.margin = newMargin;
	return ret;
}

WidgetData WidgetData::withPadding(const Margin &newPadding) const {
	auto ret = *this;
	ret.padding = newPadding;
	return ret;
}

WidgetData WidgetData::withShrinkWrap(const Axis &newShrinkWrap) const {
	auto ret = *this;
	ret.shrinkWrap = newShrinkWrap;
	return ret;
}

WidgetData WidgetData::withExpand(const Axis &newExpand) const {
	auto ret = *this;
	ret.expand = newExpand;
	return ret;
}

WidgetData WidgetData::withPassThrough(const bool &newPassThrough) const {
	auto ret = *this;
	ret.passThrough = newPassThrough;
	return ret;
}
