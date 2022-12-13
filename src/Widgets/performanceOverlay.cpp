#include "../../include/Widgets/performanceOverlay.hpp"
#include "../../include/Widgets/column.hpp"
#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"
#include "GLFW/glfw3.h"

#include "format"

using namespace squi;

PerformanceOverlay::PerformanceOverlay()
	: Overlay(OverlayArgs{
		  .data{
			  .expand = Axis::both,
		  },
	  }) {
	Overlay::setChild(new Align(AlignArgs{
		.alignment{1},
		.child = new Box(BoxArgs{
			.data{
				.size{100},
				.margin{16},
				.padding{8},
				.shrinkWrap = Axis::both,
			},
			.color{0, 0, 0, 0.25},
			.borderRadius = 8,
			.child = new Column(ColumnArgs{
				.data{
					.shrinkWrap = Axis::both,
				},
				.children{
					new Text(TextArgs{
						.data{
							.key{fpsKey},
						},
						.text{"FPS"},
					}),
				},
			}),
		}),
	}));
}

void PerformanceOverlay::update() {
	if (GestureDetector::isKey(GLFW_KEY_F11, GLFW_PRESS)) {
		shouldDraw = !shouldDraw;
	}
	if (glfwGetTime() - lastFpsUpdate > 0.1) {
		fpsKey->getAs<Text>()->setText(std::format("FPS: {:.0f}", 1 / Screen::getCurrentScreen()->deltaTime));
		lastFpsUpdate = glfwGetTime();
	}
	Overlay::update();
}

void PerformanceOverlay::draw() {
	if (shouldDraw) Overlay::draw();
}
