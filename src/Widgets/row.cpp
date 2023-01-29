#include "../../include/Widgets/row.hpp"

using namespace squi;

void Row::customUpdate() {
	auto children = getChildren();

	float totalChildrenWidth = 0;
	float maxHeight = 0;

	Widget::expandWidget();

	std::vector<std::shared_ptr<Widget>> expandedChildren{};
	for (auto &child: children) {
		if (!child) continue;

		child->setParent(this);

		auto childExpand = child->getExpand();
		auto childSize = child->getLayoutSize();

		if (childExpand == Axis::horizontal || childExpand == Axis::both) {
			expandedChildren.push_back(child);
		} else {
			child->update();
			childSize = child->getLayoutSize();
			totalChildrenWidth += childSize.x;
		}
		if (childExpand != Axis::vertical && childExpand != Axis::both)
			maxHeight = (std::max)(maxHeight, childSize.y);
	}

	auto shrinkWrap = getShrinkWrap();
	float spaceBetweenOffset = spaceBetween * static_cast<float>((std::max)(children.size(), 1llu) - 1);
	spaceBetweenOffset = (std::max)(spaceBetweenOffset, 0.f);
	if (shrinkWrap == Axis::horizontal || shrinkWrap == Axis::both) {
		if (!expandedChildren.empty()) throw std::runtime_error("Can't shrinkWrap when there are expanded children");
		setSize(getSize().withX(totalChildrenWidth + spaceBetweenOffset + getPadding().getHorizontalVectical().x));
	}
	if (shrinkWrap == Axis::vertical || shrinkWrap == Axis::both) {
		setSize(getSize().withY(maxHeight + getPadding().getHorizontalVectical().y));
	}

	getHintedSize();

	if (!expandedChildren.empty()) {
		auto widthHint = (getContentSize().x - spaceBetweenOffset - totalChildrenWidth) / static_cast<float>(expandedChildren.size());
		for (auto &child: expandedChildren) {
			child->setSizeHint({widthHint, child->getSizeHint().y});
			child->update();
		}
	}
}

void Row::draw() {
	auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

	auto children = getChildren();
	vec2 cursor{0};
	auto rowHeight = getContentSize().y;
	for (auto &child: children) {
		if (!child) continue;
		switch (alignment) {
			case RowAlignment::top: {
				child->setPos(pos + cursor);
				break;
			}
			case RowAlignment::center: {
				child->setPos((pos + cursor).withYOffset((rowHeight - child->getLayoutSize().y) / 2));
				break;
			}
			case RowAlignment::bottom: {
				child->setPos((pos + cursor).withYOffset(rowHeight - child->getLayoutSize().y));
				break;
			}
		}
		child->draw();
		cursor.x += child->getLayoutSize().x + spaceBetween;
	}
}
