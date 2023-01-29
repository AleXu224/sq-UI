#ifndef SQ_UI_SCREEN_HPP
#define SQ_UI_SCREEN_HPP

#include "GLFW/glfw3.h"
#include "Widgets/performanceOverlay.hpp"
#include "d2d1_1.h"
#include "dwrite.h"
#include "overlay.hpp"
#include "widget.hpp"

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

		static Color systemAccentColor;

	public:
		std::shared_ptr<GLFWwindow> window;
		std::shared_ptr<ID2D1HwndRenderTarget> canvas;
		std::shared_ptr<ID2D1Factory1> factory;
		std::shared_ptr<IDWriteFactory> textFactory;
		// Time in seconds between frames
		std::chrono::duration<float> deltaTime = 1ms;
		std::chrono::duration<float> pollTime = 1ms;
		std::chrono::duration<float> updateTime = 1ms;
		std::chrono::duration<float> drawTime = 1ms;
		Screen();

		void run();

		void addOverlay(Overlay *o);

		void animationRunning();

		static Screen *getCurrentScreen();

		static Color getSystemAccentColor();

		static std::tuple<std::shared_ptr<GLFWwindow>,
						  std::shared_ptr<ID2D1HwndRenderTarget>,
						  std::shared_ptr<ID2D1Factory1>,
						  std::shared_ptr<IDWriteFactory>>
		getTools();
	};
}// namespace squi

#endif//SQ_UI_SCREEN_HPP
