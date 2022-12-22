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
				},
			}),
		}),
	}));
}

void PerformanceOverlay::update() {
	if (GestureDetector::isKey(GLFW_KEY_F11, GLFW_PRESS)) {
		shouldDraw = !shouldDraw;
	}
	if (!shouldDraw) return;
	Screen *pScreen = Screen::getCurrentScreen();
	//	fpsValues.push_back(pScreen->deltaTime);
	//	if (fpsValues.size() > (unsigned long long) (1 / pScreen->deltaTime)) fpsValues.erase(fpsValues.begin());
	//	pollValues.push_back(pScreen->pollTime * 1000);
	//	if (pollValues.size() > fpsValues.size()) pollValues.erase(pollValues.begin());
	//	updateValues.push_back(pScreen->updateTime * 1000);
	//	if (updateValues.size() > fpsValues.size()) updateValues.erase(updateValues.begin());
	//	drawValues.push_back(pScreen->drawTime * 1000);
	//	if (drawValues.size() > fpsValues.size()) drawValues.erase(drawValues.begin());

	if (glfwGetTime() - lastFpsUpdate > 0.1) {
		fpsKey->getAs<Text>()->setText(std::format("Fps: {:.0f}", 1 / pScreen->deltaTime));
		pollKey->getAs<Text>()->setText(std::format("Poll: {:.2f}ms", pScreen->pollTime * 1000));
		updateKey->getAs<Text>()->setText(std::format("Update: {:.2f}ms", pScreen->updateTime * 1000));
		drawKey->getAs<Text>()->setText(std::format("Draw: {:.2f}ms", pScreen->drawTime * 1000));
		lastFpsUpdate = glfwGetTime();
	}
	Overlay::update();
}

void PerformanceOverlay::draw() {
	if (shouldDraw) Overlay::draw();
}
