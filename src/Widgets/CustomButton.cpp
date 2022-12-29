#include "../../include/Widgets/CustomButton.hpp"

#include "../../include/screen.hpp"

using namespace squi;

CustomButton::CustomButton(CustomButtonArgs args) : Widget(args.data, WidgetContentType::invisibleWithChild), style(args.style) {
	setChild(Box(BoxArgs{
		.data{
			.key{boxKey},
			.transition{
				.duration = 200ms,
				.curve = TransitionCurves::easeInOut,
			},
		},
		.color{Color::fromHexRGB("60CDFF")},
		.borderRadius = 4,
		.shouldUpdateGestureDetector = true,
		.onClick = [oc = args.onClick](GestureDetector *gd) {
			if (oc) oc();
		},
		.child = Align(AlignArgs{
			.child = args.child,
		}),
	}));

	auto boxWidget = boxKey->getAs<Box>();
	boxWidget->getTransition().only(TransitionValues{
		&boxWidget->color
	});
}

void CustomButton::updateBeforeChild() {
	auto boxWidget = boxKey->getAs<Box>();
	auto boxGD = boxWidget->getGD();

	if (boxGD.focused) {
		boxWidget->color = Screen::getSystemAccentColor().withAlpha(0.8);
	} else if (boxGD.hovered) {
		boxWidget->color = Screen::getSystemAccentColor().withAlpha(0.9);
	} else {
		boxWidget->color = Screen::getSystemAccentColor();
	}
}
