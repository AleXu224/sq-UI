#ifndef SQ_UI_TEXT_HPP
#define SQ_UI_TEXT_HPP

#include "../color.hpp"
#include "../widget.hpp"

namespace squi {
	struct TextArgs {
		WidgetData data{};
		std::string text{};
		float fontSize = 14;
		std::wstring fontFamily{L"Segoe"};
		Color color{1, 1, 1};
		// Wether the text can be wrapped or not
		// Setting this to true with the default maxWidth will match the parent's size
		bool lineWrap = false;
		// The max width the text can be before being wrapped to a new line
		// Will override lineWrap to true when set
		float maxWidth = -1;
	};

	class Text : public Widget {
		std::string text;
		float fontSize;
		std::wstring fontFamily;
		Color color;
		bool lineWrap;
		float maxWidth;
		IDWriteTextFormat* format = nullptr;
		IDWriteTextLayout *layout = nullptr;

	public:
		explicit Text(const TextArgs &args);

		void setText(std::string newText);

		void update() override;

		void draw() override;

		~Text() override;
	};
}// namespace squi

#endif//SQ_UI_TEXT_HPP
