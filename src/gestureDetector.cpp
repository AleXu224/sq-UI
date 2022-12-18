#include "../include/gestureDetector.hpp"
#include "../include/screen.hpp"
#include <GLFW/glfw3.h>

using namespace squi;
std::unordered_map<int, KeyState> GestureDetector::g_keys{};
unsigned char GestureDetector::g_textInput{0};
vec2 GestureDetector::g_scrollDelta{0};
std::vector<Rect> GestureDetector::g_hitCheckRects{};

bool GestureDetector::isKey(int key, int action, int mods) {
	if (!g_keys.contains(key)) return false;

	auto &keyInput = g_keys.at(key);
	return (keyInput.action == action && keyInput.mods == mods);
}

bool GestureDetector::isKeyPressedOrRepeat(int key, int mods) {
	if (!g_keys.contains(key)) return false;

	auto &keyInput = g_keys.at(key);
	return ((keyInput.action == GLFW_PRESS || keyInput.action == GLFW_REPEAT) && keyInput.mods == mods);
}

void GestureDetector::update() {
	double cursorX, cursorY;
	GLFWwindow *window = Screen::getCurrentScreen()->window;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	auto lmb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	lastCursorPos = cursorPos;
	cursorPos = vec2{
		static_cast<float>(cursorX),
		static_cast<float>(cursorY),
	};

	bool cursorInsideAnotherWidget = false;
	for (auto &widgetRect : g_hitCheckRects) {
		if (widgetRect.contains(cursorPos)) {
			cursorInsideAnotherWidget = true;
			break;
		}
	}

	if (!cursorInsideAnotherWidget && key->get()->getRect().contains(cursorPos)) {
		scrollDelta = g_scrollDelta;

		if (!hovered && onEnter) onEnter(this);
		hovered = true;

		if (lmb == GLFW_PRESS && !focusedOutside) {
			if (!focused) dragStart = cursorPos;
			focused = true;
			active = true;
		} else if (lmb == GLFW_RELEASE) {
			if (focused && !focusedOutside && onClick) onClick(this);
			focused = false;
			focusedOutside = false;
		}
	} else {
		scrollDelta = vec2{0};

		if (hovered && onLeave) onLeave(this);
		hovered = false;

		if (lmb == GLFW_PRESS && !focused) {
			focusedOutside = true;
			active = false;
		} else if (lmb == GLFW_RELEASE) {
			focused = false;
			focusedOutside = false;
		}
	}

	if (active) charInput = g_textInput;
	else charInput = 0;
}

const vec2 &GestureDetector::getMousePos() const {
	return cursorPos;
}

vec2 GestureDetector::getMouseDelta() const {
	return cursorPos - lastCursorPos;
}

const vec2 &GestureDetector::getScroll() const {
	return scrollDelta;
}

vec2 GestureDetector::getDragOffset() const {
	if (!focused) return vec2{0};
	return dragStart - cursorPos;
}

const vec2 &GestureDetector::getDragStartPos() const {
	return dragStart;
}
