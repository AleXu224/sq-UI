#include <utility>

#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"

#include "d2d1.h"
#include "dwrite.h"

using namespace squi;

Text::Text(const TextArgs &args)
	: Widget(args.data, WidgetChildCount::none),
	  text(args.text),
	  fontSize(args.fontSize),
	  fontFamily(args.fontFamily),
	  color(args.color),
	  lineWrap(args.lineWrap),
	  maxWidth(args.maxWidth) {
	IDWriteFontSet* pFontSet;
	Screen::getCurrentScreen()->textFactory->CreateTextFormat(fontFamily.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", &format);
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(text.begin(), text.end()).c_str(), text.size(), format, INFINITY, 0, &layout);
}

void Text::update() {
	if (maxWidth == -1 && !lineWrap) {
		if (layout->GetMaxWidth() != INFINITY) layout->SetMaxWidth(INFINITY);
	} else if (maxWidth == -1) {
		const auto width = getParent()->getContentSize().x;
		if (layout->GetMaxWidth() != width) layout->SetMaxWidth(width);
	} else {
		if (layout->GetMaxWidth() != maxWidth) layout->SetMaxWidth(maxWidth);
	}

	DWRITE_TEXT_METRICS metrics{};
	layout->GetMetrics(&metrics);
	setSize({metrics.width, metrics.height});

	Widget::update();
}

void Text::draw() {
	auto pos = getPos() + getMargin().getTopLeft();

	auto &canvas = Screen::getCurrentScreen()->canvas;

	ID2D1SolidColorBrush *brush = nullptr;
	canvas->CreateSolidColorBrush(color, &brush);

	canvas->DrawTextLayout(pos, layout, brush);
	brush->Release();
}

Text::~Text() {
	layout->Release();
	format->Release();
}
void Text::setText(std::string newText) {
	if (text == newText) return;
	text = std::move(newText);
	layout->Release();
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(text.begin(), text.end()).c_str(), text.size(), format, INFINITY, 0, &layout);
}
