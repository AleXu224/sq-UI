#include "../../include/Widgets/textButton.hpp"
#include "../../include/screen.hpp"

using namespace squi;

TextButton::TextButton(const TextButtonArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild) {
	auto textArgs = args.text;
	textArgs.color = Screen::getSystemAccentColor().isDark() ? Color{1, 1, 1, 1} : Color{0, 0, 0, 1};
	textArgs.data.key = textKey;
	textArgs.data.transition = TransitionArgs{
		.duration = 200ms,
		.curve = TransitionCurves::easeInOut,
	};
	
	setChild(new CustomButton(CustomButtonArgs{
		.data{
			.padding{12, 7},
			.shrinkWrap = Axis::both,
		},
		.onClick = args.onClick,
		.child = new Text(textArgs),
	}));

	auto textWidget = textKey->getAs<Text>();

	textWidget->getTransition().only(TransitionValues{&textWidget->color});
}

void TextButton::updateBeforeChild() {
	auto textWidget = textKey->getAs<Text>();
	auto boxWidget = getChild()->getChild()->getKey()->getAs<Box>();
	auto boxColor = boxWidget->color;

	if (boxColor.isDark()) {
		if (boxWidget->getGD().focused) {
			textWidget->color = Color{1, 1, 1, 0.6};
		} else {
			textWidget->color = Color{1, 1, 1, 1};
		}
	} else {
		if (boxWidget->getGD().focused) {
			textWidget->color = Color{0, 0, 0, 0.6};
		} else {
			textWidget->color = Color{0, 0, 0, 1};
		}
	}
}