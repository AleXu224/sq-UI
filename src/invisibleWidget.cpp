#include "../include/invisibleWidget.hpp"

#include "cassert"

using namespace squi;

const vec2 &InvisibleWidget::getPos() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getPos();
}

const vec2 &InvisibleWidget::getSize() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getSize();
}

const Margin &InvisibleWidget::getMargin() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getMargin();
}

const Margin &InvisibleWidget::getPadding() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getPadding();
}

Widget *InvisibleWidget::getParent() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getParent();
}

const std::shared_ptr<Key> &InvisibleWidget::getKey() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getKey();
}

vec2 InvisibleWidget::getContentSize() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getContentSize();
}

vec2 InvisibleWidget::getLayoutSize() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getLayoutSize();
}

Rect InvisibleWidget::getRect() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getRect();
}

Rect InvisibleWidget::getContentRect() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getContentRect();
}

Rect InvisibleWidget::getLayoutRect() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getLayoutRect();
}

void InvisibleWidget::setPos(const vec2 &p) {
	auto child = getChild();
	assert(child != nullptr);
	child->setPos(p);
}

void InvisibleWidget::setSize(const vec2 &v) {
	auto child = getChild();
	assert(child != nullptr);
	child->setSize(v);
}

void InvisibleWidget::setMargin(const Margin &m) {
	auto child = getChild();
	assert(child != nullptr);
	child->setMargin(m);
}

void InvisibleWidget::setPadding(const Margin &m) {
	auto child = getChild();
	assert(child != nullptr);
	child->setPadding(m);
}

void InvisibleWidget::setParent(Widget *p) {
	auto child = getChild();
	assert(child != nullptr);
	child->setParent(p);
}

void InvisibleWidget::update() {
	Widget::update();
}

void InvisibleWidget::draw() {
	Widget::draw();
}

const vec2 &InvisibleWidget::getSizeHint() const {
	auto child = getChild();
	assert(child != nullptr);
	return child->getSizeHint();
}

void InvisibleWidget::setSizeHint(const vec2 &s) {
	auto child = getChild();
	assert(child != nullptr);
	child->setSizeHint(s);
}
