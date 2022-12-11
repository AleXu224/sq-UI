#include "../include/color.hpp"

Color::operator _D3DCOLORVALUE() const {
	return D2D1::ColorF(r, g, b, a);
}

Color Color::fromRGB255(int r, int g, int b) {
	return Color{
		static_cast<float>(r) / 255.f,
		static_cast<float>(g) / 255.f,
		static_cast<float>(b) / 255.f,
		1.0f,
	};
}

Color Color::fromRGBA255(int r, int g, int b, int a) {
	return Color{
		static_cast<float>(r) / 255.f,
		static_cast<float>(g) / 255.f,
		static_cast<float>(b) / 255.f,
		static_cast<float>(a) / 255.f,
	};
}

Color Color::fromRGBA255(int r, int g, int b, float a) {
	return Color{
		static_cast<float>(r) / 255.f,
		static_cast<float>(g) / 255.f,
		static_cast<float>(b) / 255.f,
		a,
	};
}
