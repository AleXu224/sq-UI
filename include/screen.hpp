#ifndef SQ_UI_SCREEN_HPP
#define SQ_UI_SCREEN_HPP

#include "GLFW/glfw3.h"
#include "d2d1.h"
#include "widget.hpp"
#include "Widgets/performanceOverlay.hpp"
#include "overlay.hpp"

namespace squi {
	class Screen : public Widget {
		static Screen *currentScreen;
		ID2D1Factory *factory = nullptr;

		std::vector<std::shared_ptr<Overlay>> overlays{
			std::shared_ptr<Overlay>(new PerformanceOverlay),
		};

		// Time in seconds between frames
		double deltaTime = 1;

		void init_glfw();
		void init_direct2d();

		void draw() override;
		void update() override {}

	public:
		GLFWwindow *window = nullptr;
		ID2D1HwndRenderTarget *canvas = nullptr;
		Screen();

		void run();

		void addOverlay(Overlay *o);

		static Screen *getCurrentScreen();
	};
}// namespace squi

#endif//SQ_UI_SCREEN_HPP
