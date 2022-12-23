#ifndef SQ_UI_SCREEN_HPP
#define SQ_UI_SCREEN_HPP

#include "GLFW/glfw3.h"
#include "d2d1.h"
#include "dwrite.h"
#include "widget.hpp"
#include "Widgets/performanceOverlay.hpp"
#include "overlay.hpp"

namespace squi {
	class Screen : public Widget {
		bool isWin11 = false;
		bool supportsNewMica = false;

		static Screen *currentScreen;

		std::vector<std::shared_ptr<Overlay>> overlays{};

		void init_glfw();
		void init_direct2d();

		void customUpdate() override;
		void draw() override;

		bool isAnimationRunning = false;
	public:
		GLFWwindow *window = nullptr;
		ID2D1HwndRenderTarget *canvas = nullptr;
		ID2D1Factory *factory = nullptr;
//		IDWriteFactory5 *textFactory = nullptr;
		IDWriteFactory *textFactory = nullptr;
		// Time in seconds between frames
		double deltaTime = 1;
		double pollTime = 1;
		double updateTime = 1;
		double drawTime = 1;
		Screen();

		void run();

		void addOverlay(Overlay *o);

		void animationRunning();

		static Screen *getCurrentScreen();
	};
}// namespace squi

#endif//SQ_UI_SCREEN_HPP
