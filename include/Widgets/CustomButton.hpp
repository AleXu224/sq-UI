#ifndef SQ_UI_CUSTOMBUTTON_HPP
#define SQ_UI_CUSTOMBUTTON_HPP

#include "../widget.hpp"
#include "align.hpp"
#include "box.hpp"

namespace squi {
	struct ButtonStyle {
		Color color = Color::fromHexRGB("60CDFF");
		Color hoverColor = Color::fromHexRGB("60CDFF").withAlpha(0.9);
		Color pressColor = Color::fromHexRGB("60CDFF").withAlpha(0.8);
	};

	struct CustomButtonArgs {
		WidgetData data{};
		ButtonStyle style{};
		std::function<void()> onClick{};
		Widget *child = nullptr;
	};

	class CustomButton : public Widget {
		std::shared_ptr<Key> boxKey = std::make_shared<Key>();
		ButtonStyle style;
	public:
		explicit CustomButton(CustomButtonArgs args);

		void update() override;
	};
}// namespace squi

#endif//SQ_UI_CUSTOMBUTTON_HPP
