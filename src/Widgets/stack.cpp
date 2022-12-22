#include "../../include/Widgets/stack.hpp"
#include "../../include/gestureDetector.hpp"

#include "cassert"
#include "ranges"

using namespace squi;

Stack::Stack(const StackArgs &args) : Widget(args.data, WidgetContentType::multipleChildren) {
	setChildren(args.children);
}

void Stack::update() {
	auto parent = getParent();
	assert(parent != nullptr);

	// Goes through the children in reverse order so that the topmost widget will get updated first
	// This is needed because the widgets that are behind need the information that a widget is above them
	auto savedHitchecks = GestureDetector::g_hitCheckRects;

	vec2 newSize{0};

	auto children = getChildren();
	for (auto &child : std::views::reverse(children)) {
		child->setParent(parent);
		child->update();

		// This check is required in order for expanded children to take a
		// proper size when inside a shrinkwrap parent
		auto childExpand = child->getExpand();
		auto childSize = child->getLayoutSize();
		if (childExpand == Axis::none || childExpand == Axis::vertical)
			newSize.x = (std::max)(childSize.x, newSize.x);
		if (childExpand == Axis::none || childExpand == Axis::horizontal)
			newSize.y = (std::max)(childSize.y, newSize.y);

		auto &hitCheckRects = GestureDetector::g_hitCheckRects;
		auto newHitChecks = child->getHitcheckRects();
		hitCheckRects.insert(hitCheckRects.end(), newHitChecks.begin(), newHitChecks.end());
	}

	Widget::setSize(newSize);
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

std::vector<Rect> Stack::getHitcheckRects() const {
	std::vector<Rect> ret{};
	auto children = getChildren();
	ret.reserve(children.size());

	for (auto &child : children) {
		ret.push_back(child->getRect());
	}
	return ret;
}
