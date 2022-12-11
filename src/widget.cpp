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

const Widget *Widget::getParent() const {
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
