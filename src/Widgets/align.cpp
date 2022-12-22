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
