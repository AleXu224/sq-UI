// Disable the console for Release builds
#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "../include/screen.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "../include/color.hpp"
#include "../include/gestureDetector.hpp"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "VersionHelpers.h"
#include "assert.h"
#include "d2d1.h"
#include "dwmapi.h"
#include "dwrite_3.h"
#include "format"
#include "iostream"
#include "ranges"

using namespace squi;

Screen *Screen::currentScreen = nullptr;
Color Screen::systemAccentColor = Color::fromHexRGB("#60CDFF");

Screen::Screen() : Widget(WidgetData{}, WidgetContentType::singleChild) {
	const auto system = L"kernel32.dll";
	DWORD dummy;
	const auto cbInfo =
		::GetFileVersionInfoSizeExW(FILE_VER_GET_NEUTRAL, system, &dummy);
	std::vector<char> buffer(cbInfo);
	::GetFileVersionInfoExW(FILE_VER_GET_NEUTRAL, system, dummy,
							buffer.size(), &buffer[0]);
	void *p = nullptr;
	UINT size = 0;
	::VerQueryValueW(buffer.data(), L"\\", &p, &size);
	assert(size >= sizeof(VS_FIXEDFILEINFO));
	assert(p != nullptr);
	auto pFixed = static_cast<const VS_FIXEDFILEINFO *>(p);

	if (HIWORD(pFixed->dwFileVersionMS) == 10 && HIWORD(pFixed->dwFileVersionLS) >= 22000) {
		isWin11 = true;
		if (HIWORD(pFixed->dwFileVersionLS) >= 22523) supportsNewMica = true;
	}

	currentScreen = this;
	init_glfw();
	init_direct2d();
	overlays.push_back(std::shared_ptr<Overlay>(new PerformanceOverlay));
}

void Screen::run() {
	auto lastTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window)) {
		auto now = std::chrono::high_resolution_clock::now();
		deltaTime = now - lastTime;
		lastTime = now;

		if (isAnimationRunning) {
			isAnimationRunning = false;
			glfwPollEvents();
		} else {
			isAnimationRunning = false;
			// glfwWaitEventsTimeout(1);
			glfwWaitEvents();
		}
		auto pollPoint = std::chrono::high_resolution_clock::now();

		// Get the system accent accent color;
		COLORREF dwAccentRGB;
		BOOL bIsColorOpaque;
		DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);
		auto alpha = (dwAccentRGB >> 24) & 0xFF;
		auto red = ((dwAccentRGB >> 16) & 0xFF) * ((float) alpha / 255.f) + (255 - alpha);
		auto green = ((dwAccentRGB >> 8) & 0xFF) * ((float) alpha / 255.f) + (255 - alpha);
		auto blue = (dwAccentRGB & 0xFF) * ((float) alpha / 255.f) + (255 - alpha);
		systemAccentColor = Color::fromRGB255(red, green, blue);

		update();
		auto updatePoint = std::chrono::high_resolution_clock::now();
		draw();
		auto drawPoint = std::chrono::high_resolution_clock::now();

		pollTime = pollPoint - now;
		updateTime = updatePoint - pollPoint;
		drawTime = drawPoint - updatePoint;

		GestureDetector::g_keys.clear();
		GestureDetector::g_textInput = 0;
		GestureDetector::g_scrollDelta = vec2{0};
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

	glfwSetCursorPosCallback(window, [](GLFWwindow *m_window, double xpos, double ypos) {
		auto dpiScale = GestureDetector::g_dpi / vec2{96};
		GestureDetector::g_cursorPos = vec2{xpos, ypos} / dpiScale;
	});
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
		Screen::getCurrentScreen()->animationRunning();
		if (!GestureDetector::g_keys.contains(key))
			GestureDetector::g_keys.insert({key, {action, mods}});
		else
			GestureDetector::g_keys.at(key) = {action, mods};
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow *m_window, int button, int action, int mods) {
		Screen::getCurrentScreen()->animationRunning();
		if (!GestureDetector::g_keys.contains(button))
			GestureDetector::g_keys.insert({button, {action, mods}});
		else
			GestureDetector::g_keys.at(button) = {action, mods};
	});
	glfwSetCursorEnterCallback(window, [](GLFWwindow *m_window, int entered) {
		GestureDetector::g_cursorInside = static_cast<bool>(entered);
	});

	glfwMakeContextCurrent(window);

	HWND hwnd = glfwGetWin32Window(window);
	int darkMode = 1;
	int mica = 2;
	int micaOld = 1;
	if (isWin11) {
		DwmSetWindowAttribute(hwnd, 20, &darkMode, sizeof(darkMode));
		if (supportsNewMica)
			DwmSetWindowAttribute(hwnd, 38, &mica, sizeof(mica));
		else
			DwmSetWindowAttribute(hwnd, 1029, &micaOld, sizeof(micaOld));
	}
}

void Screen::init_direct2d() {
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textFactory), (IUnknown **) &textFactory);
	//	IDWriteFontFile* pFontFile;
	//	textFactory->CreateFontFileReference(L"./segoe.tff", /* lastWriteTime*/ nullptr, &pFontFile);
	//	if (AddFontResourceA("./segoe.ttf") != 0) {
	//		printf("Success?");
	//	} else {
	//		printf("Fail :(");
	//	}
	//	if (AddFontResourceA("./segoe-semibold.ttf") != 0) {
	//		printf("Success?");
	//	} else {
	//		printf("Fail :(");
	//	}

	RECT rc;
	GetClientRect(glfwGetWin32Window(window), &rc);

	factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		D2D1::HwndRenderTargetProperties(
			glfwGetWin32Window(window),
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top),
			D2D1_PRESENT_OPTIONS_NONE),
		&canvas);
	canvas->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	canvas->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//	IDWriteRenderingParams *textRenderingParams = nullptr;
	//	textFactory->CreateCustomRenderingParams(1, 1, 1, DWRITE_PIXEL_GEOMETRY_FLAT, DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL, &textRenderingParams);
	//	//
	//	canvas->SetTextRenderingParams(textRenderingParams);

	//	textRenderingParams->Release();
}

Screen *Screen::getCurrentScreen() {
	return currentScreen;
}

Color Screen::getSystemAccentColor() {
	return systemAccentColor;
}

std::tuple<GLFWwindow *, ID2D1HwndRenderTarget *, ID2D1Factory *, IDWriteFactory *> getTools() {
	auto screen = Screen::getCurrentScreen();

	return {screen->window, screen->canvas, screen->factory, screen->textFactory};
}

void printWidgetTree(Widget *widget, int depth = 0) {
	if (!widget) return;

	switch (widget->getChildCountType()) {
		case WidgetContentType::none: {
			for (int i = 0; i < depth; i++) printf("-");
			auto size = widget->getSize();
			printf("%s\n", std::format("{:.2f}x{:.2f} {}", size.x, size.y, typeid(*widget).name()).c_str());
			break;
		}
		case WidgetContentType::singleChild: {
			for (int i = 0; i < depth; i++) printf("-");
			auto size = widget->getSize();
			printf("%s\n", std::format("{:.2f}x{:.2f} {}", size.x, size.y, typeid(*widget).name()).c_str());
			printWidgetTree(widget->getChild().get(), depth + 1);
			break;
		}
		case WidgetContentType::multipleChildren: {
			for (int i = 0; i < depth; i++) printf("-");
			auto size = widget->getSize();
			printf("%s\n", std::format("{:.2f}x{:.2f} {}", size.x, size.y, typeid(*widget).name()).c_str());
			for (auto &child: widget->getChildren()) {
				printWidgetTree(child.get(), depth + 1);
			}
			break;
		}
		case WidgetContentType::invisibleWithChild: {
			for (int i = 0; i < depth; i++) printf("-");
			printf("%s\n", typeid(*widget).name());
			printWidgetTree(widget->getChild().get(), depth);
			break;
		}
	}
}

void Screen::customUpdate() {
	auto size = canvas->GetSize();
	setSize({
		size.width,
		size.height,
	});
	float dpiX;
	float dpiY;
	canvas->GetDpi(&dpiX, &dpiY);
	GestureDetector::g_dpi = vec2{dpiX, dpiY};

	currentScreen = this;

	auto child = getChild();
	if (!child) return;

	overlays.erase(std::remove_if(overlays.begin(), overlays.end(), [](const std::shared_ptr<Overlay> &overlay) {
					   return (overlay->shouldClose && overlay->canClose);
				   }),
				   overlays.end());

	auto &hitcheckRects = GestureDetector::g_hitCheckRects;

	for (auto &overlay: std::views::reverse(overlays)) {
		overlay->setParent(this);
		overlay->update();

		auto overlayHitcheckRects = overlay->getHitcheckRects();
		hitcheckRects.insert(hitcheckRects.end(), overlayHitcheckRects.begin(), overlayHitcheckRects.end());
	}

	child->setParent(this);
	child->update();
	// printWidgetTree(child.get());
	hitcheckRects.clear();
}

void Screen::draw() {
	auto child = getChild();
	if (!child) return;

	canvas->BeginDraw();
	Color clearColor{0};
	if (!isWin11) clearColor = Color::fromRGB255(32, 32, 32);
	canvas->Clear(clearColor);

	child->setPos(getMargin().getTopLeft() + getPadding().getTopLeft());
	child->draw();

	for (auto &overlay: overlays) {
		overlay->draw();
	}

	canvas->EndDraw();
}

void Screen::addOverlay(Overlay *o) {
	overlays.push_back(std::shared_ptr<Overlay>(o));
}

void Screen::animationRunning() {
	isAnimationRunning = true;
}
