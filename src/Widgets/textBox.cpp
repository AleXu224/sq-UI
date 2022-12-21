#include "../../include/Widgets/textBox.hpp"
#include "../../include/Widgets/CustomButton.hpp"
#include "../../include/Widgets/stack.hpp"

using namespace squi;

TextBox::TextBox(const TextBoxArgs &args) : InvisibleWidget(args.data) {
	setChild(new Box{BoxArgs{
		// Force shrinkwrap to be verical at the very least in order to properly fit the text
		.data{
			args.data
				.withSize(args.data.size.withY(32))
				.withKey(boxKey),
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
		.child = new Stack(StackArgs{
			.children = {
				new Align(AlignArgs{
					.child = new TextInput(TextInputArgs{
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
				new Align(AlignArgs{
					.alignment{0, 1},
					.child = new Box(BoxArgs{
						.data{
							.key{underlineKey},
							.size{1},
							.expand = Axis::horizontal,
						},
						.color{Color::fromHexRGBA("#FFFFFF8B")},
					}),
				}),
			}}),
	}});
}

void TextBox::update() {
	InvisibleWidget::update();

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
		underline->color = Color::fromHexRGB("#60CDFF");
	}
}
