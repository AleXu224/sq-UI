#ifndef SQ_UI_COLOR_HPP
#define SQ_UI_COLOR_HPP

#include "d2d1.h"
#include "string"

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color(): r{1}, g{1}, b{1}, a{1} {}
	explicit Color(const float& color): r{color}, g{color}, b{color}, a{color} {}
	Color(const float& r, const float& g, const float& b): r{r}, g{g}, b{b}, a{1} {}
	Color(const float& r, const float& g, const float& b, const float& a): r{r}, g{g}, b{b}, a{a} {}

	[[nodiscard]] Color &withAlpha(const float& newAlpha);

	static Color fromRGB255(int r, int g, int b);
	static Color fromRGBA255(int r, int g, int b, int a);
	static Color fromRGBA255(int r, int g, int b, float a);
	static Color fromHexRGB(std::string hex);
	static Color fromHexRGBA(std::string hex);

	operator _D3DCOLORVALUE() const;
};

#endif//SQ_UI_COLOR_HPP
