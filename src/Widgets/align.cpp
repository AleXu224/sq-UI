#include "../../include/Widgets/align.hpp"

using namespace squi;

void Align::draw() {
	auto child = getChild();

	auto pos = InvisibleWidget::getPos();
	auto maxOffset = InvisibleWidget::getParent()->getContentSize() - getChild()->getLayoutSize();

	auto offset = maxOffset * alignment;

	child->setPos(pos + offset);
	child->draw();
}
