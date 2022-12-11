#include "../../include/Widgets/box.hpp"

#include "../../include/screen.hpp"
#include "d2d1.h"

using namespace squi;

Box::Box(const BoxArgs &args) : WidgetWithChild(args.data) {
	borderRadius = args.borderRadius;
	color = args.color;
	border = args.border;
	child.reset(args.child);
	shouldUpdateGd = args.shouldUpdateGestureDetector;
	gd.onClick = args.onClick;
	gd.onEnter = args.onEnter;
	gd.onLeave = args.onLeave;
	if (gd.onClick || gd.onEnter || gd.onLeave) shouldUpdateGd = true;
}

void Box::update() {
	WidgetWithChild::update();

	if (shouldUpdateGd) gd.update();
}

void Box::draw() {
	auto pos = getPos() + getMargin().getTopLeft();
	auto pos2 = pos + getSize();

	auto &canvas = Screen::getCurrentScreen()->canvas;

	ID2D1SolidColorBrush *brush = nullptr;
	canvas->CreateSolidColorBrush(color, &brush);

	if (border.position == BorderPosition::outside) {
		auto rr = D2D1::RoundedRect(getRect().inset(border.size), borderRadius - border.size, borderRadius - border.size);
		canvas->FillRoundedRectangle(rr, brush);
	} else {
		auto rr = D2D1::RoundedRect(getRect(), borderRadius, borderRadius);
		canvas->FillRoundedRectangle(rr, brush);
	}

	if (border.size > 0) {
		auto p = pos + (border.size / 2);
		auto p2 = pos2 - (border.size / 2);
		auto rr2 = D2D1::RoundedRect(D2D1::RectF(p.x, p.y, p2.x, p2.y), borderRadius - border.size / 2, borderRadius - border.size / 2);
		ID2D1SolidColorBrush *borderBrush = nullptr;
		canvas->CreateSolidColorBrush(border.color, &borderBrush);
		canvas->DrawRoundedRectangle(rr2, borderBrush, border.size);
		borderBrush->Release();
	}
	brush->Release();

	if (!child) return;
	child->setPos(pos + getPadding().getTopLeft());
	child->draw();
}
