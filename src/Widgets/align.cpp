#include "../../include/Widgets/align.hpp"

using namespace squi;

void Align::draw() {
	auto &child = getChild();
	if (!child) return;

	auto pos = getPos();
	auto maxOffset = getParent()->getContentSize() - child->getLayoutSize();

	auto offset = maxOffset * alignment;

	child->setPos(pos + offset);
	child->draw();
}

std::vector<Rect> Align::getHitcheckRects() const {
	auto &child = getChild();
	if (!child) return {};

	return child->getHitcheckRects();
}
