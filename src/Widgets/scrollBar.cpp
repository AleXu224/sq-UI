#include "../../include/Widgets/scrollBar.hpp"
#include "../../include/Widgets/box.hpp"
#include "../../include/Widgets/scrollable.hpp"
#include "algorithm"

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
				.duration = 200ms,
				.curve = TransitionCurves::easeInOut,
				.animatedValues = [](std::shared_ptr<Key> key) {
					return TransitionValues{
						&key->getAs<Box>()->getData().size.x,
						&key->getAs<Box>()->color,
						&key->getAs<Box>()->getData().padding.left,
						&key->getAs<Box>()->getData().padding.right,
					};
				},
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
					.duration = 200ms,
					.curve = TransitionCurves::easeInOut,
					.animatedValues = [](std::shared_ptr<Key> key) {
						return TransitionValues{
							&key->getAs<Box>()->getData().size.x,
						};
					},
				},
			},
			.color{thumbColor},
			.borderRadius = 3,
			.shouldUpdateGestureDetector = true,
		}),
	}));
}

void ScrollBar::updateFromScrollable() {
	auto scrollable = scrollableKey->getAs<Scrollable>();
	auto bg = bgKey->getAs<Box>();
	auto thumb = thumbKey->getAs<Box>();

	auto scroll = scrollable->getScroll();
	auto contentSize = scrollable->getChild()->getLayoutSize().y;
	auto scrollableSize = scrollable->getContentSize().y;

	auto availableThumbSpace = bg->getContentSize().y;

	// Size
	auto thumbSize = (scrollableSize / contentSize) * availableThumbSpace;
	thumbSize = std::clamp(thumbSize, 10.0f, (std::max)(10.0f, availableThumbSpace));
	if (thumbSize == availableThumbSpace)
		shouldHide = true;
	else
		shouldHide = false;
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

		scrollable->setScroll(dragScrollStart - thumbGD.getDragOffset().y * (contentSize / availableThumbSpace), true);
	} else {
		dragging = false;
	}
}

void ScrollBar::draw() {
	if (!shouldHide) Widget::draw();
}
