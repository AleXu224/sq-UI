#ifndef SQ_UI_TEXTINPUT_HPP
#define SQ_UI_TEXTINPUT_HPP

#include "../widget.hpp"
#include "../gestureDetector.hpp"
#include "text.hpp"

namespace squi {
	struct TextInputArgs {
		WidgetData data;
		Color cursorColor{1, 1, 1};
		TextArgs textArgs;
		std::function<void(std::string)> onChange{};
	};

	class TextInput : public Widget {
		GestureDetector gd{getKey()};
		int cursorPos = 0;
		int selectStart = -1;
		float horizontalScroll = 0;
		Color cursorColor;
		std::string value{};

		std::function<void(std::string)> onChange{};

		std::shared_ptr<Text> selectText;
	public:

		explicit TextInput(const TextInputArgs &args);

		void update() override;
		void draw() override;
	};
}

#endif//SQ_UI_TEXTINPUT_HPP
