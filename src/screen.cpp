#include "../include/screen.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "../include/color.hpp"
#include "../include/gestureDetector.hpp"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "d2d1.h"
#include "dwrite_3.h"
#include "dwmapi.h"
#include "format"
#include "ranges"

using namespace squi;

Screen *Screen::currentScreen = nullptr;

Screen::Screen() : Widget(WidgetData{}, WidgetChildCount::single) {
	currentScreen = this;
	init_glfw();
	init_direct2d();
	overlays.push_back(std::shared_ptr<Overlay>(new PerformanceOverlay));
}

void Screen::run() {
	auto lastTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window)) {
		auto now = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<double>(now - lastTime).count();
		lastTime = now;

//		glfwWaitEvents();
		glfwPollEvents();
		auto pollPoint = std::chrono::high_resolution_clock::now();

		update();
		auto updatePoint = std::chrono::high_resolution_clock::now();
		draw();
		auto drawPoint = std::chrono::high_resolution_clock::now();

		pollTime = std::chrono::duration<double>(pollPoint - now).count();
		updateTime = std::chrono::duration<double>(updatePoint - pollPoint).count();
		drawTime = std::chrono::duration<double>(drawPoint - updatePoint).count();

		GestureDetector::g_keys.clear();
	}
}

void Screen::init_glfw() {
	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
		exit(1);
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	window = glfwCreateWindow(800, 600, "te", nullptr, nullptr);
	if (!window) {
		printf("Failed to create window\n");
		exit(1);
	}

	glfwSetWindowSizeCallback(window, [](GLFWwindow *m_window, int width, int height) {
		D2D_SIZE_U newSize{
			.width = static_cast<UINT32>(width),
			.height = static_cast<UINT32>(height),
		};
		Screen::getCurrentScreen()->canvas->Resize(newSize);
		Screen::getCurrentScreen()->update();
		Screen::getCurrentScreen()->draw();
	});
	glfwSetCharCallback(window, [](GLFWwindow *m_window, unsigned int codepoint) {
		GestureDetector::g_textInput = static_cast<unsigned char>(codepoint);
	});
	glfwSetScrollCallback(window, [](GLFWwindow *m_window, double xoffset, double yoffset) {
		GestureDetector::g_scrollDelta = vec2{static_cast<float>(xoffset), static_cast<float>(yoffset)};
	});
	glfwSetKeyCallback(window, [](GLFWwindow *m_window, int key, int scancode, int action, int mods) {
		if (!GestureDetector::g_keys.contains(key)) GestureDetector::g_keys.insert({key, {action, mods}});
		else GestureDetector::g_keys.at(key) = {action, mods};
	});

	glfwMakeContextCurrent(window);

	HWND hwnd = glfwGetWin32Window(window);
	int darkMode = 1;
	int mica = 2;
	DwmSetWindowAttribute(hwnd, 20, &darkMode, sizeof(darkMode));
	DwmSetWindowAttribute(hwnd, 38, &mica, sizeof(mica));
}

void Screen::init_direct2d() {
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textFactory), (IUnknown**)&textFactory);
	textFactory->CreateFontSetBuilder(&fontBuilder);

	IDWriteFontFile* pFontFile;
	textFactory->CreateFontFileReference(L"./segoe.tff", /* lastWriteTime*/ nullptr, &pFontFile);

	fontBuilder->AddFontFile(pFontFile);
	IDWriteFontSet* pFontSet;
	fontBuilder->CreateFontSet(&pFontSet);

	RECT rc;
	GetClientRect(glfwGetWin32Window(window), &rc);

	factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		D2D1::HwndRenderTargetProperties(
			glfwGetWin32Window(window),
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top),
			D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&canvas);
	canvas->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	canvas->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
//	IDWriteRenderingParams *textRenderingParams = nullptr;
//	textFactory->CreateCustomRenderingParams(1, 1, 2);
//
//	canvas->SetTextRenderingParams(textRenderingParams);

//	textRenderingParams->Release();
}

Screen *Screen::getCurrentScreen() {
	return currentScreen;
}

void Screen::update() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	setSize({
		static_cast<float>(width),
		static_cast<float>(height),
	});

	currentScreen = this;

	auto child = getChild();
	if (!child) return;

	canvas->BeginDraw();
	canvas->Clear(Color{0});

	overlays.erase(std::remove_if(overlays.begin(), overlays.end(), [](const std::shared_ptr<Overlay> &overlay) {
					   return (overlay->shouldClose && overlay->canClose);
				   }), overlays.end());

	auto &hitcheckRects = GestureDetector::g_hitCheckRects;

	for (auto &overlay: std::views::reverse(overlays)) {
		overlay->setParent(this);
		overlay->update();

		auto overlayHitcheckRects = overlay->getHitcheckRects();
		hitcheckRects.insert(hitcheckRects.end(), overlayHitcheckRects.begin(), overlayHitcheckRects.end());
	}

	child->setParent(this);
	child->update();
	hitcheckRects.clear();
}

void Screen::draw() {
	auto child = getChild();
	if (!child) return;
	for (auto &overlay : overlays) {
		overlay->draw();
	}

	child->setPos(getMargin().getTopLeft() + getPadding().getTopLeft());
	child->draw();

	canvas->EndDraw();
}

void Screen::addOverlay(Overlay *o) {
	overlays.push_back(std::shared_ptr<Overlay>(o));
}
