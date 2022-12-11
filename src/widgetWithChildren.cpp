#include "../include/widgetWithChildren.hpp"

using namespace squi;
std::vector<std::shared_ptr<Widget>> WidgetWithChildren::childrenFromPointers(const std::vector<Widget *> &children) {
	std::vector<std::shared_ptr<Widget>> ret{};
	ret.reserve(children.size());

	for (auto *child : children) {
		ret.push_back(std::shared_ptr<Widget>(child));
	}

	return ret;
}

void WidgetWithChildren::update() {
	for (auto &child : children) {
		if (child) {
			child->setParent(this);
			child->update();
		}
	}
}

// A default draw implementation that will draw all the children in the same place
// You should probably override this
void WidgetWithChildren::draw() {
	const auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

	for (auto &child : children) {
		if (child) {
			child->setPos(pos);
			child->draw();
		}
	}
}
