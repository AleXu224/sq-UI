#ifndef SQ_UI_TEXT_HPP
#define SQ_UI_TEXT_HPP

#include "../color.hpp"
#include "../widget.hpp"

namespace squi {
	enum class FontWeight {
		thin = 100,
		extraLight = 200,
		light = 300,
		semiLight = 350,
		normal = 400,
		medium = 500,
		semiBold = 600,
		bold = 700,
		extraBold = 800,
		black = 900,
		extraBlack = 950,
	};

	struct TextArgs {
		WidgetData data{};
		std::string text{};
		float fontSize = 14;
		std::wstring fontFamily{L"Sans"};
		FontWeight weight = FontWeight::normal;
		Color color{1, 1, 1};
		// Wether the textArgs can be wrapped or not
		// Setting this to true with the default maxWidth will match the parent's size
		bool lineWrap = false;
		// The max width the textArgs can be before being wrapped to a new line
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

		vec2 calculateSizeFor(const std::string& val) const;

		void update() override;

		void draw() override;

		~Text() override;
	};
}// namespace squi

#endif//SQ_UI_TEXT_HPP
