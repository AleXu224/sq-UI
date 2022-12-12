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

	// Goes through the children in reverse order so that the topmost widget will get updated first
	// This is needed because the widgets that are behind need the information that a widget is above them
	auto savedHitchecks = GestureDetector::g_hitCheckRects;
	auto children = getChildren();
	for (auto &child : std::views::reverse(children)) {
		child->setParent(parent);
		child->update();
		auto &hitCheckRects = GestureDetector::g_hitCheckRects;
		auto newHitChecks = child->getHitcheckRects();
		hitCheckRects.insert(hitCheckRects.end(), newHitChecks.begin(), newHitChecks.end());
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

const vec2 &Stack::getSize() const {
	auto parent = getParent();
	assert(parent != nullptr);
	return parent->getSize();
}

const Margin &Stack::getMargin() const {
	auto parent = getParent();
	assert(parent != nullptr);
	return parent->getMargin();
}

const Margin &Stack::getPadding() const {
	auto parent = getParent();
	assert(parent != nullptr);
	return parent->getPadding();
}

void Stack::setSize(const vec2 &v) {
	auto parent = getParent();
	assert(parent != nullptr);
	parent->setSize(v);
}

void Stack::setMargin(const Margin &m) {
	auto parent = getParent();
	assert(parent != nullptr);
	parent->setMargin(m);
}

void Stack::setPadding(const Margin &m) {
	auto parent = getParent();
	assert(parent != nullptr);
	parent->setPadding(m);
}

std::vector<Rect> Stack::getHitcheckRects() const {
	std::vector<Rect> ret{};
	auto children = getChildren();
	ret.reserve(children.size());

	for (auto &child : children) {
		ret.push_back(child->getRect());
	}
	return ret;
}
