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
	const auto pos = getPos() + getMargin().getTopLeft();
	const auto &size = getSize();

	auto &canvas = Screen::getCurrentScreen()->canvas;

	if (size != oldSize || color != oldColor || textChanged) {
		oldSize = size;
		oldColor = color;
		textChanged = false;
		ID2D1BitmapRenderTarget *cachePtr = nullptr;
		canvas->CreateCompatibleRenderTarget(D2D1::SizeF(std::ceil(size.x), std::ceil(size.y)), &cachePtr);
		cache.reset(cachePtr, [](ID2D1BitmapRenderTarget *p) { p->Release(); });
		cache->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		cache->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

		cache->BeginDraw();
		cache->Clear();

		ID2D1SolidColorBrush *brush = nullptr;
		cache->CreateSolidColorBrush(color, &brush);

		cache->DrawTextLayout(vec2{0, 0}, layout.get(), brush);
		brush->Release();

		cache->EndDraw();
	}


	ID2D1Bitmap *bitmap = nullptr;
	cache->GetBitmap(&bitmap);

	const auto roundedPos = vec2{std::round(pos.x), std::round(pos.y)};
	canvas->DrawBitmap(bitmap, Rect::fromPosSize(roundedPos, vec2{std::ceil(size.x), std::ceil(size.y)}), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

	bitmap->Release();
}
void Text::setText(std::string newText) {
	if (text == newText) return;
	text = std::move(newText);
	IDWriteTextLayout *layoutPtr = nullptr;
	Screen::getCurrentScreen()->textFactory->CreateTextLayout(std::wstring(text.begin(), text.end()).c_str(), text.size(), format.get(), INFINITY, 0, &layoutPtr);
	layout.reset(layoutPtr, [](IDWriteTextLayout *p) { p->Release(); });
	textChanged = true;
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
