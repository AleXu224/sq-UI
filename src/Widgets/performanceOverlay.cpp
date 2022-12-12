#include "../../include/Widgets/performanceOverlay.hpp"
#include "GLFW/glfw3.h"

using namespace squi;

PerformanceOverlay::PerformanceOverlay()
	: Overlay(OverlayArgs{
	.data{
		.expand = Axis::both,
	},
	.children{
		new Align(AlignArgs{
			.alignment{1},
			.child = new Box(BoxArgs{
				.data{
					.size{100},
					.margin{16},
				},
				.color{0, 0, 0, 0.5},
			}),
		}),
	},
}) {}

void PerformanceOverlay::update() {
	if (GestureDetector::isKey(GLFW_KEY_F12, GLFW_PRESS)) shouldDraw = !shouldDraw;
	Overlay::update();
}

void PerformanceOverlay::draw() {
	if (shouldDraw) Overlay::draw();
}
