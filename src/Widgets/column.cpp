#include "../../include/Widgets/column.hpp"

using namespace squi;

void Column::customUpdate() {
	auto children = getChildren();

	float totalChildrenHeight = 0;
	float maxWidth = 0;

	std::vector<std::shared_ptr<Widget>> expandedChildren{};
	for (auto &child: children) {
		if (!child) continue;

		child->setParent(this);
		child->update();

		auto childExpand = child->getExpand();
		auto childSize = child->getLayoutSize();

		if (childExpand == Axis::vertical || childExpand == Axis::both) {
			expandedChildren.push_back(child);
		} else {
			totalChildrenHeight += childSize.y;
		}
		maxWidth = (std::max)(maxWidth, childSize.x);
	}

	auto shrinkWrap = getShrinkWrap();
	if (shrinkWrap == Axis::horizontal || shrinkWrap == Axis::both) {
		setSize(getSize().withX(maxWidth + getPadding().getHorizontalVectical().x));
	}
	float spaceBetweenOffset = spaceBetween * static_cast<float>(children.size() - 1);
	spaceBetweenOffset = (std::max)(spaceBetweenOffset, 0.f);
	if (shrinkWrap == Axis::vertical || shrinkWrap == Axis::both) {
		if (!expandedChildren.empty()) throw std::runtime_error("Can't shrinkWrap when there are expanded children");
		setSize(getSize().withY(totalChildrenHeight + spaceBetweenOffset + getPadding().getHorizontalVectical().y));
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
		auto heightHint = (getContentSize().y - spaceBetweenOffset - totalChildrenHeight) / static_cast<float>(expandedChildren.size());
		for (auto &child: expandedChildren) {
			child->setSizeHint({child->getSizeHint().x, heightHint});
			child->getHintedSize();
		}
	}
}

void Column::draw() {
	auto pos = getPos() + getMargin().getTopLeft();

	auto children = getChildren();
	vec2 cursor{0};
	auto columnWidth = getContentSize().x;
	for (auto &child : children) {
		if (!child) continue;
		switch (alignment) {
			case ColumnAlignment::left: {
				child->setPos(pos + cursor);
				break;
			}
			case ColumnAlignment::center: {
				child->setPos((pos + cursor).withXOffset((columnWidth - child->getLayoutSize().x) / 2.f));
				break;
			}
			case ColumnAlignment::right: {
				child->setPos((pos + cursor).withXOffset(columnWidth - child->getLayoutSize().x));
				break;
			}
		}
		child->draw();
		cursor.y += child->getLayoutSize().y + spaceBetween;
	}
}
