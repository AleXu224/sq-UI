#ifndef SQ_UI_TEXTBOX_HPP
#define SQ_UI_TEXTBOX_HPP

#include "../invisibleWidget.hpp"
#include "textInput.hpp"

namespace squi {
	struct TextBoxArgs {
		WidgetData data{};
		std::function<void(std::string)> onChange{};
	};

	class TextBox : public InvisibleWidget {

	};
}

#endif//SQ_UI_TEXTBOX_HPP
