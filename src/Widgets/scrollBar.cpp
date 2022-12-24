#include "../../include/Widgets/scrollBar.hpp"
#include "../../include/Widgets/box.hpp"
#include "../../include/Widgets/scrollable.hpp"

using namespace squi;

ScrollBar::ScrollBar(const ScrollbarArgs &args)
	: Widget(args.data,
			 WidgetContentType::invisibleWithChild),
	  scrollableKey(args.scrollableKey) {
	setChild(new Box(BoxArgs{
		.data{
			.key{bgKey},
			.size{12},
			.padding{3, 2},
			.expand = Axis::vertical,
			.transition{
				.enabled = true,
				.duration = 200,
				.curve = TransitionCurves::easeInOut,
			},
		},
		.color{bgColorInactive},
		.borderRadius = 6,
		.shouldUpdateGestureDetector = true,
		.child = new Box(BoxArgs{
			.data{
				.key{thumbKey},
				.size{6},
				.transition{
					.enabled = true,
					.duration = 200,
					.curve = TransitionCurves::easeInOut,
				},
			},
			.color{thumbColor},
			.borderRadius = 3,
			.shouldUpdateGestureDetector = true,
		}),
	}));

	auto bgWidget = bgKey->getAs<Box>();
	auto &bgTransition = bgWidget->getTransition();
	bgTransition.clear();
	bgTransition.addWatch(bgWidget->getData().size.x);
	bgTransition.addWatch(bgWidget->color.r);
	bgTransition.addWatch(bgWidget->color.g);
	bgTransition.addWatch(bgWidget->color.b);
	bgTransition.addWatch(bgWidget->color.a);
	bgTransition.addWatch(bgWidget->getData().padding.left);
	bgTransition.addWatch(bgWidget->getData().padding.right);

	auto thumbWidget = thumbKey->getAs<Box>();
	auto &thumbTransition = thumbWidget->getTransition();
	thumbTransition.clear();
	thumbTransition.addWatch(thumbWidget->getData().size.x);
}

void ScrollBar::updateFromScrollable() {
	auto scrollable = scrollableKey->getAs<Scrollable>();
	auto bg = bgKey->getAs<Box>();
	auto thumb = thumbKey->getAs<Box>();

	auto scroll = scrollable->getScroll();
	auto contentSize = scrollable->getChild()->getLayoutSize().y;
	auto scrollableSize = scrollable->getSize().y;

	auto availableThumbSpace = bg->getContentSize().y;

	// Size
	auto thumbSize = (scrollableSize / contentSize) * availableThumbSpace;
	thumb->setSize(thumb->getSize().withY(thumbSize));

	// Position
	auto thumbOffset = (scroll / contentSize) * availableThumbSpace;
	thumb->setMargin(Margin{0, 0, thumbOffset, 0});
}

void ScrollBar::updateBeforeChild() {
	auto scrollable = scrollableKey->getAs<Scrollable>();
	auto bg = bgKey->getAs<Box>();
	auto thumb = thumbKey->getAs<Box>();

	auto scroll = scrollable->getScroll();
	auto contentSize = scrollable->getChild()->getLayoutSize().y;

	auto availableThumbSpace = bg->getContentSize().y;

	// Hover
	auto bgGD = bg->getGD();
	auto thumbGD = thumb->getGD();
	if (bgGD.hovered || thumbGD.focused) {
		bg->color = bgColor;
		bg->setPadding(Margin{3, 5});
		thumb->setSize(thumb->getSize().withX(6));
	} else {
		bg->color = bgColorInactive;
		bg->setPadding(Margin{5, 5});
		thumb->setSize(thumb->getSize().withX(2));
	}

	// Drag
	if (thumbGD.focused) {
		if (!dragging) {
			dragging = true;
			dragScrollStart = scroll;
		}

		scrollable->setScroll(dragScrollStart - thumbGD.getDragOffset().y * (contentSize / availableThumbSpace));
	} else {
		dragging = false;
	}
}
