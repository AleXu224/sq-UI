#include "../../include/Widgets/scrollable.hpp"
#include "../../include/Widgets/column.hpp"
#include "../../include/screen.hpp"

using namespace squi;

Scrollable::Scrollable(const ScrollableArgs &args)
	: Widget(args.data.withTransition(TransitionArgs{
				 .duration = 100ms,
				 .curve = TransitionCurves::easeOut,
				 .animatedValues = [](std::shared_ptr<Key> key){
					return TransitionValues{
						&key->getAs<Scrollable>()->scroll,
					};
				 },
			 }),
			 WidgetContentType::singleChild) {
	// A scrollable that is shrink wrapped makes no sense and defeats the purpose of the whole widget
	if (args.data.shrinkWrap != Axis::none) {
		throw std::runtime_error("Cannot have a scrollable that is shrink wrapped!");
	}
	setChild(new Column(ColumnArgs{
		.data{WidgetData{
			.key{columnKey},
			.shrinkWrap = Axis::vertical,
			.expand = Axis::horizontal,
		}},
		.children = args.children,
	}));
}

void Scrollable::updateBeforeChild() {
	gd.update();

	setScroll(lastScroll + gd.getScroll().y * -40);
}

void Scrollable::setScroll(const float &newScroll, bool instant) {
	auto &transition = getTransition();
	if (instant) {
		getTransition().clear();
		transitionCleared = true;
	} else if (newScroll != lastScroll && transitionCleared) {
		transition.only(TransitionValues{&scroll});
		transition.update(getKey());
		transitionCleared = false;
	}

	scroll = newScroll;

	const auto &child = getChild();
	const auto childSize = child->getLayoutSize();
	const auto scrollableSize = getSize();
	const auto maxScroll = childSize.y - scrollableSize.y;

	if (childSize.y < scrollableSize.y) scroll = 0;
	else if (scroll > maxScroll)
		scroll = maxScroll;
	scroll = (std::max)(scroll, 0.f);
	lastScroll = scroll;
}

const float &Scrollable::getScroll() const {
	return scroll;
}

void Scrollable::draw() {
	const auto pos = getPos() + getMargin().getTopLeft();
	const auto &canvas = Screen::getCurrentScreen()->canvas;

	canvas->PushAxisAlignedClip(Rect::fromPosSize(pos, getSize()), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	auto &child = getChild();
	child->setPos((pos + getPadding().getTopLeft()).withYOffset(-scroll));
	child->draw();

	canvas->PopAxisAlignedClip();
}
