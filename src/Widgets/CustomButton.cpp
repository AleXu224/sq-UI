#include "../../include/Widgets/CustomButton.hpp"

using namespace squi;

CustomButton::CustomButton(CustomButtonArgs args) : Widget(args.data, WidgetContentType::invisibleWithChild), style(args.style) {
	setChild(new Box(BoxArgs{
		.data{args.data.withKey(boxKey)},
		.color{Color::fromHexRGB("60CDFF")},
		.borderRadius = 4,
		.shouldUpdateGestureDetector = true,
		.onClick = [oc = args.onClick](GestureDetector *gd) {
			if (oc) oc();
		},
		.child = new Align(AlignArgs{
			.child = args.child,
		}),
	}));
}

void CustomButton::updateBeforeChild() {
	auto boxWidget = boxKey->getAs<Box>();
	auto boxGD = boxWidget->getGD();

	if (boxGD.focused) {
		boxWidget->color = style.pressColor;
	} else if (boxGD.hovered) {
		boxWidget->color = style.hoverColor;
	} else {
		boxWidget->color = style.color;
	}
}
