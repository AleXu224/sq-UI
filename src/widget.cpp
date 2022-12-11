#include <utility>

#include "../include/widget.hpp"
using namespace squi;

int Widget::instances = 0;

const vec2 &Widget::getSize() const {
	return data.size;
}

const Margin &Widget::getMargin() const {
	return data.margin;
}

const Margin &Widget::getPadding() const {
	return data.margin;
}

void Widget::setSize(const vec2 &v) {
	data.size = v;
}

void Widget::setMargin(const Margin &m) {
	data.margin = m;
}

void Widget::setPadding(const Margin &m) {
	data.padding = m;
}

const vec2 &Widget::getPos() const {
	return pos;
}

void Widget::setPos(const vec2 &p) {
	pos = p;
}

Widget *Widget::getParent() const {
	return parent;
}

void Widget::setParent(Widget *p) {
	if (p) parent = p;
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
	return data.key;
}

const vec2 &Widget::getSizeHint() const {
	return sizeHint;
}

void Widget::setSizeHint(const vec2 &s) {
	sizeHint = s;
}

const std::shared_ptr<Widget> &Widget::getChild() const {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");
	return child;
}

std::vector<std::shared_ptr<Widget>> Widget::getChildren() const {
	if (count != WidgetChildCount::multiple) throw std::runtime_error("Child is not of multiple count");

	return children;
}

const WidgetChildCount &Widget::getChildCountType() const {
	return count;
}

void Widget::setChild(Widget *c) {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");

	child.reset(c);
}

void Widget::setChild(std::shared_ptr<Widget> c) {
	if (count != WidgetChildCount::single) throw std::runtime_error("Child is not of single count");

	child = std::move(c);
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

	children = childrenFromPointers(c);
}

void Widget::setChildren(std::vector<std::shared_ptr<Widget>> c) {
	if (count != WidgetChildCount::multiple) throw std::runtime_error("Child is not of multiple count");

	children = std::move(c);
}

void Widget::shrinkWrapWidget() {
	if (data.shrinkWrap == Axis::horizontal || data.shrinkWrap == Axis::both)
		data.size.x = child->getLayoutSize().x + getPadding().getHorizontalVectical().x;

	if (data.shrinkWrap == Axis::vertical || data.shrinkWrap == Axis::both)
		data.size.y = child->getLayoutSize().y + getPadding().getHorizontalVectical().y;
}

void Widget::expandWidget() {
	if (data.expand == Axis::horizontal || data.expand == Axis::both)
		data.size.x = parent->getContentSize().x;

	if (data.expand == Axis::vertical || data.expand == Axis::both)
		data.size.y = parent->getContentSize().y;
}

void Widget::getHintedSize() {
	if (sizeHint.x != -1) data.size.x = sizeHint.x;
	if (sizeHint.y != -1) data.size.y = sizeHint.y;
}

void Widget::update() { // NOLINT(misc-no-recursion)
	switch (count) {
		case WidgetChildCount::none: {
			expandWidget();
			getHintedSize();
			return;
		}
		case WidgetChildCount::single: {
			if (child) {
				child->setParent(this);
				shrinkWrapWidget();
			}
			if (parent != nullptr) expandWidget();
			getHintedSize();

			if (child) child->update();
			return;
		}
		case WidgetChildCount::multiple: {
			if (parent != nullptr) expandWidget();
			getHintedSize();

			for (auto &childPtr : children) {
				if (!childPtr) continue;
				childPtr->setParent(this);
				childPtr->update();
			}
			return;
		}
	}
}
