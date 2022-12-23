#include "../../include/Widgets/performanceOverlay.hpp"
#include "../../include/Widgets/column.hpp"
#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"
#include "GLFW/glfw3.h"

#include "format"
#include "numeric"
#include "ranges"

using namespace squi;

PerformanceOverlay::PerformanceOverlay()
	: Overlay(OverlayArgs{WidgetData{
		  .size{100},
		  .margin{8},
		  .padding{8},
		  .shrinkWrap = Axis::both,
		  .passThrough = true,
	  }}) {
	setChild(new Align(AlignArgs{
		.alignment{1},
		.child = new Box(BoxArgs{
			.color{0, 0, 0, 0},
			.child = new Column(ColumnArgs{
				.data{
					.shrinkWrap = Axis::both,
				},
				.alignment = ColumnAlignment::right,
				.spaceBetween = 10.f,
				.children{
					new Text(TextArgs{
						.data{
							.key{fpsKey},
						},
						.text{"FPS"},
						.fontSize = 17,
					}),
					new Text(TextArgs{
						.data{
							.key{pollKey},
						},
						.text{"POLL"},
						.fontSize = 17,
					}),
					new Text(TextArgs{
						.data{
							.key{updateKey},
						},
						.text{"UPDATE"},
						.fontSize = 17,
					}),
					new Text(TextArgs{
						.data{
							.key{drawKey},
						},
						.text{"DRAW"},
						.fontSize = 17,
					}),
					new Text(TextArgs{
						.data{
							.key{instancesKey},
						},
						.text{"INSTANCES"},
						.fontSize = 17,
					}),
				},
			}),
		}),
	}));
}

void PerformanceOverlay::updateBeforeChild() {
	if (GestureDetector::isKey(GLFW_KEY_F11, GLFW_PRESS)) {
		shouldDraw = !shouldDraw;
	}
	if (!shouldDraw) return;
	Screen *pScreen = Screen::getCurrentScreen();

	if (glfwGetTime() - lastFpsUpdate > 0.1) {
		fpsKey->getAs<Text>()->setText(std::format("Fps: {:.0f}", 1 / pScreen->deltaTime));
		pollKey->getAs<Text>()->setText(std::format("Poll: {:.2f}ms", pScreen->pollTime * 1000));
		updateKey->getAs<Text>()->setText(std::format("Update: {:.2f}ms", pScreen->updateTime * 1000));
		drawKey->getAs<Text>()->setText(std::format("Draw: {:.2f}ms", pScreen->drawTime * 1000));
		instancesKey->getAs<Text>()->setText(std::format("Widgets: {}", Widget::getInstances()));
		lastFpsUpdate = glfwGetTime();
	}
}

void PerformanceOverlay::draw() {
	if (shouldDraw) Overlay::draw();
}
