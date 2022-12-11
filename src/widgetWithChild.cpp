#include "../include/widgetWithChild.hpp"

using namespace squi;

void WidgetWithChild::update() {
	if (!child) return;
	child->setParent(this);
	child->update();
}

void WidgetWithChild::draw() {
	const auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();
	if (child) {
		child->setPos(pos);
		child->draw();
	}
}
