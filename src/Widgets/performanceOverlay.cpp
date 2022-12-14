#include "../../include/Widgets/performanceOverlay.hpp"
#include "../../include/Widgets/column.hpp"
#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"
#include "GLFW/glfw3.h"

#include "format"
#include "ranges"
#include "numeric"

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
						.fontSize = 16,
					}),
					new Text(TextArgs{
						.data{
							.key{pollKey},
						},
						.text{"POLL"},
						.fontSize = 16,
					}),
					new Text(TextArgs{
						.data{
							.key{updateKey},
						},
						.text{"UPDATE"},
						.fontSize = 16,
					}),
					new Text(TextArgs{
						.data{
							.key{drawKey},
						},
						.text{"DRAW"},
						.fontSize = 16,
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
	fpsValues.push_back(pScreen->deltaTime);
	if (fpsValues.size() > (unsigned long long)(1 / pScreen->deltaTime)) fpsValues.erase(fpsValues.begin());
	pollValues.push_back(pScreen->pollTime * 1000);
	if (pollValues.size() > fpsValues.size()) pollValues.erase(pollValues.begin());
	updateValues.push_back(pScreen->updateTime * 1000);
	if (updateValues.size() > fpsValues.size()) updateValues.erase(updateValues.begin());
	drawValues.push_back(pScreen->drawTime * 1000);
	if (drawValues.size() > fpsValues.size()) drawValues.erase(drawValues.begin());

	if (glfwGetTime() - lastFpsUpdate > 0.1) {
		fpsKey->getAs<Text>()->setText(std::format("Fps: {:.0f}", 1 / (std::reduce(fpsValues.begin(), fpsValues.end()) / (double)fpsValues.size())));
		pollKey->getAs<Text>()->setText(std::format("Poll: {:.3f}ms", std::reduce(pollValues.begin(), pollValues.end()) / (double)pollValues.size()));
		updateKey->getAs<Text>()->setText(std::format("Update: {:.3f}ms", std::reduce(updateValues.begin(), updateValues.end()) / (double)updateValues.size()));
		drawKey->getAs<Text>()->setText(std::format("Draw: {:.3f}ms", std::reduce(drawValues.begin(), drawValues.end()) / (double)drawValues.size()));
		lastFpsUpdate = glfwGetTime();
	}
	Overlay::update();
}

void PerformanceOverlay::draw() {
	if (shouldDraw) Overlay::draw();
}
