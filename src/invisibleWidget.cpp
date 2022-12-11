#include "../include/invisibleWidget.hpp"

#include "cassert"

using namespace squi;

const vec2 &InvisibleWidget::getPos() const {
	assert(child != nullptr);
	return child->getPos();
}

const vec2 &InvisibleWidget::getSize() const {
	assert(child != nullptr);
	return child->getSize();
}

const Margin &InvisibleWidget::getMargin() const {
	assert(child != nullptr);
	return child->getMargin();
}

const Margin &InvisibleWidget::getPadding() const {
	assert(child != nullptr);
	return child->getPadding();
}

Widget *InvisibleWidget::getParent() const {
	assert(child != nullptr);
	return child->getParent();
}

const std::shared_ptr<Key> &InvisibleWidget::getKey() const {
	assert(child != nullptr);
	return child->getKey();
}

vec2 InvisibleWidget::getContentSize() const {
	assert(child != nullptr);
	return child->getContentSize();
}

vec2 InvisibleWidget::getLayoutSize() const {
	assert(child != nullptr);
	return child->getLayoutSize();
}

Rect InvisibleWidget::getRect() const {
	assert(child != nullptr);
	return child->getRect();
}

Rect InvisibleWidget::getContentRect() const {
	assert(child != nullptr);
	return child->getContentRect();
}

Rect InvisibleWidget::getLayoutRect() const {
	assert(child != nullptr);
	return child->getLayoutRect();
}

void InvisibleWidget::setPos(const vec2 &p) {
	assert(child != nullptr);
	child->setPos(p);
}

void InvisibleWidget::setSize(const vec2 &v) {
	assert(child != nullptr);
	child->setSize(v);
}

void InvisibleWidget::setMargin(const Margin &m) {
	assert(child != nullptr);
	child->setMargin(m);
}

void InvisibleWidget::setPadding(const Margin &m) {
	assert(child != nullptr);
	child->setPadding(m);
}

void InvisibleWidget::setParent(Widget *p) {
	assert(child != nullptr);
	child->setParent(p);
}

void InvisibleWidget::update() {
	WidgetWithChild::update();
}

void InvisibleWidget::draw() {
	WidgetWithChild::draw();
}

const vec2 &InvisibleWidget::getSizeHint() const {
	assert(child != nullptr);
	return child->getSizeHint();
}

void InvisibleWidget::setSizeHint(const vec2 &s) {
	assert(child != nullptr);
	child->setSizeHint(s);
}
