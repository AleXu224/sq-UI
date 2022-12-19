#include "../include/color.hpp"
#include "algorithm"
#include "format"
#include "ranges"
#include "stdexcept"

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

Color Color::fromHexRGB(std::string hex) {
	if (hex.contains('#')) {
		hex.replace(hex.find('#'), 1, "");
	}
	if (hex.size() < 6) return {};
	unsigned int n = 5;
	unsigned int val = 0;
	std::ranges::for_each(hex, [&](auto &elem) {
		auto upperElem = toupper(elem);
		auto elemCode = static_cast<unsigned int>(static_cast<unsigned char>(upperElem));
		unsigned int elemVal;
		if (elemCode >= 65 && elemCode <= 70) {
			// A - F
			elemVal = elemCode - 55;
		} else if (elemCode >= 48 && elemCode <= 57) {
			// 0 - 9
			elemVal = elemCode - 48;
		} else {
			// Other
			return;
		}

		val += elemVal << (4 * n--);
	});

	return Color{
		static_cast<float>((val >> 16) % 256) / 255.f,
		static_cast<float>((val >> 8) % 256) / 255.f,
		static_cast<float>(val % 256) / 255.f,
	};
}

Color Color::fromHexRGBA(std::string hex) {
	if (hex.contains('#')) {
		hex.replace(hex.find('#'), 1, "");
	}
	if (hex.size() < 8) return {};
	unsigned int n = 7;
	unsigned int val = 0;
	std::ranges::for_each(hex, [&](auto &elem) {
		auto upperElem = toupper(elem);
		auto elemCode = static_cast<unsigned int>(static_cast<unsigned char>(upperElem));
		// A - F
		unsigned int elemVal;
		if (elemCode >= 65 && elemCode <= 70) {
			elemVal = elemCode - 55;
		} else if (elemCode >= 48 && elemCode <= 57) {
			elemVal = elemCode - 48;
		} else {
			return;
		}

		val += elemVal << (4 * n--);
	});

	return Color{
		static_cast<float>((val >> 24) % 256) / 255.f,
		static_cast<float>((val >> 16) % 256) / 255.f,
		static_cast<float>((val >> 8) % 256) / 255.f,
		static_cast<float>(val % 256) / 255.f,
	};
}

Color &Color::withAlpha(const float &newAlpha) {
	a = newAlpha;
	return *this;
}
