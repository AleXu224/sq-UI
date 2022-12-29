#include "../../include/Widgets/textBox.hpp"
#include "../../include/Widgets/CustomButton.hpp"
#include "../../include/Widgets/stack.hpp"

#include "../../include/screen.hpp"

using namespace squi;

TextBox::TextBox(const TextBoxArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild) {
	setChild(Box{BoxArgs{
		// Force shrinkwrap to be verical at the very least in order to properly fit the text
		.data{
			.key{boxKey},
			.size{32},
		},
		.color{Color::fromHexRGBA("#FFFFFF0F")},
		.borderRadius = 4,
		.border{
			.size = 1,
			.color = Color::fromHexRGBA("#FFFFFF12"),
			.position = BorderPosition::outside,
		},
		.shouldUpdateGestureDetector = true,
		.shouldClipContents = true,
		.child = Stack(StackArgs{
			.children = {
				Align(AlignArgs{
					.child = TextInput(TextInputArgs{
						.data{
							.key{textInputKey},
							.margin{12, 12, 0, 0},
							.shrinkWrap = Axis::vertical,
							.expand = Axis::horizontal,
						},
						.textArgs{
							.fontSize = 14,
							.fontFamily = "Segoe UI",
							.color{1, 1, 1, 0.8},
						},
					}),
				}),
				Align(AlignArgs{
					.alignment{0, 1},
					.child = Box(BoxArgs{
						.data{
							.key{underlineKey},
							.size{1},
							.expand = Axis::horizontal,
							.transition{
								.duration = 200ms,
								.curve = TransitionCurves::easeInOut,
							}
						},
						.color{Color::fromHexRGBA("#FFFFFF8B")},
					}),
				}),
			}}),
	}});

	boxKey->get()->getTransition().only(TransitionValues{
		&boxKey->getAs<Box>()->color,
	});

	auto underline = underlineKey->getAs<Box>();
	underline->getTransition().only(TransitionValues{
		&underline->getData().size.y,
		&underline->color,
	});
}

void TextBox::updateBeforeChild() {
	auto box = boxKey->getAs<Box>();
	auto textInput = textInputKey->getAs<TextInput>();
	auto underline = underlineKey->getAs<Box>();

	auto boxGD = box->getGD();
	if (boxGD.hovered && !boxGD.active) {
		box->color = Color::fromHexRGBA("#FFFFFF15");
		underline->setSize(underline->getSize().withY(1));
		underline->color = Color::fromHexRGBA("#FFFFFF8B");
	} else if (!boxGD.hovered && !boxGD.active) {
		box->color = Color::fromHexRGBA("#FFFFFF0F");
		underline->setSize(underline->getSize().withY(1));
		underline->color = Color::fromHexRGBA("#FFFFFF8B");
	} else if (box->getGD().active) {
		textInput->setActive();

		box->color = Color::fromHexRGBA("#1E1E1EB2");
		underline->setSize(underline->getSize().withY(2));
		underline->color = Screen::getSystemAccentColor();
	}
}
