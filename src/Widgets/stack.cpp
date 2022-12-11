#include "../../include/Widgets/stack.hpp"
#include "../../include/gestureDetector.hpp"

#include "cassert"
#include "ranges"

using namespace squi;

Stack::Stack(const StackArgs &args) : Widget(args.data, WidgetChildCount::multiple) {
	setChildren(args.children);
}

void Stack::update() {
	auto parent = getParent();
	assert(parent != nullptr);

	// Goes through the m_children in reverse order so that the topmost widget will get updated first
	// This is needed because the widgets that are behind need the information that a widget is above them
	auto savedHitchecks = GestureDetector::g_hitCheckRects;
	auto children = getChildren();
	for (auto &child : std::views::reverse(children)) {
		child->setParent(parent);
		child->update();
		GestureDetector::g_hitCheckRects.push_back(child->getRect());
	}
	GestureDetector::g_hitCheckRects = savedHitchecks;
}

void Stack::draw() {
	auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

	auto children = getChildren();

	for (auto &child : children) {
		child->setPos(pos);
		child->draw();
	}
}
