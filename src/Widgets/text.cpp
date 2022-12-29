#include "string"
#include <utility>

#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"

#include "d2d1.h"
#include "dwrite.h"

using namespace squi;

Text::Text(const TextArgs &args)
	: Widget(args.data, WidgetContentType::none),
	  text(args.text),
	  fontSize(args.fontSize),
	  fontFamily(args.fontFamily),
	  lineWrap(args.lineWrap),
	  maxWidth(args.maxWidth),
	  color(args.color) {
	IDWriteTextFormat *formatPtr = nullptr;
	IDWriteTextLayout *layoutPtr = nullptr;
	Screen::getCurrentScreen()->textFactory->CreateTextFormat(std::wstring(fontFamily.begin(), fontFamily.end()).c_str(), nullptr, (DWRITE_FONT_WEIGHT) args.weight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", &formatPtr);
	format.reset(formatPtr, [](IDWriteTextFormat *p) { p->Release(); });
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(text.begin(), text.end()).c_str(), text.size(), format.get(), INFINITY, 0, &layoutPtr);
	layout.reset(layoutPtr, [](IDWriteTextLayout *p) { p->Release(); });
	//	Screen::getCurrentScreen()->textFactory->CreateTextLayout(L"\uE115", 1, format, INFINITY, 0, &layout);

	getTransition().addWatch(&color);
}

void Text::updateBeforeChild() {
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
	setSize({metrics.widthIncludingTrailingWhitespace, metrics.height});
}

void Text::draw() {
	auto pos = getPos() + getMargin().getTopLeft();

	auto &canvas = Screen::getCurrentScreen()->canvas;

	ID2D1SolidColorBrush *brush = nullptr;
	canvas->CreateSolidColorBrush(color, &brush);

	canvas->DrawTextLayout(pos, layout.get(), brush);
	brush->Release();
}
void Text::setText(std::string newText) {
	if (text == newText) return;
	text = std::move(newText);
	IDWriteTextLayout *layoutPtr = nullptr;
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(text.begin(), text.end()).c_str(), text.size(), format.get(), INFINITY, 0, &layoutPtr);
	layout.reset(layoutPtr, [](IDWriteTextLayout *p) { p->Release(); });
}

// Quite costly, should not be called often!
vec2 Text::calculateSizeFor(const std::string &val) const {
	IDWriteTextLayout *layoutTemp = nullptr;
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(val.begin(), val.end()).c_str(), val.size(), format.get(), INFINITY, 0, &layoutTemp);
	DWRITE_TEXT_METRICS metrics{};
	layoutTemp->GetMetrics(&metrics);
	auto ret = vec2{metrics.widthIncludingTrailingWhitespace, metrics.height};
	layoutTemp->Release();

	return ret;
}
