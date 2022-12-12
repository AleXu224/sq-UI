#include "../../include/Widgets/row.hpp"

using namespace squi;

void Row::update() {
	auto children = getChildren();

	float totalChildrenWidth = 0;
	float maxHeight = 0;

	std::vector<std::shared_ptr<Widget>> expandedChildren{};
	for (auto &child: children) {
		if (!child) continue;

		child->setParent(this);
		child->update();

		auto childExpand = child->getExpand();
		auto childSize = child->getLayoutSize();

		if (childExpand == Axis::horizontal || childExpand == Axis::both) {
			expandedChildren.push_back(child);
		} else {
			totalChildrenWidth += childSize.x;
		}
		maxHeight = (std::max)(maxHeight, childSize.y);
	}

	auto shrinkWrap = getShrinkWrap();
	if (shrinkWrap == Axis::horizontal || shrinkWrap == Axis::both) {
		if (!expandedChildren.empty()) throw std::runtime_error("Can't shrinkWrap when there are expanded children");
		setSize(getSize().withX(totalChildrenWidth));
	}
	if (shrinkWrap == Axis::vertical || shrinkWrap == Axis::both) {
		setSize(getSize().withY(maxHeight));
	}

	auto expand = getExpand();
	if (expand == Axis::horizontal || expand == Axis::both) {
		setSize(getSize().withX(getParent()->getContentSize().x - getMargin().getHorizontalVectical().x));
	}
	if (expand == Axis::vertical || expand == Axis::both) {
		setSize(getSize().withY(getParent()->getContentSize().y - getMargin().getHorizontalVectical().y));
	}

	getHintedSize();

	if (!expandedChildren.empty()) {
		auto widthHint = (getContentSize().x - totalChildrenWidth) / static_cast<float>(expandedChildren.size());
		for (auto &child: expandedChildren) {
			child->setSizeHint({widthHint, child->getSizeHint().y});
			child->getHintedSize();
		}
	}
}

void Row::draw() {
	auto pos = getPos() + getMargin().getTopLeft();

	auto children = getChildren();
	vec2 cursor{0};
	for (auto &child : children) {
		if (!child) continue;
		child->setPos(pos + cursor);
		child->draw();
		cursor.x += child->getLayoutSize().x;
	}
}
