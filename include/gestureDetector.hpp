#ifndef SQ_UI_GESTUREDETECTOR_HPP
#define SQ_UI_GESTUREDETECTOR_HPP

#include "functional"
#include "key.hpp"
#include "memory"
#include "rect.hpp"
#include "unordered_map"
#include "utility"
#include "vec2.hpp"

namespace squi {
	struct KeyState {
		int action;
		int mods;
	};

	class GestureDetector {
		static vec2 lastCursorPos;
		vec2 scrollDelta{0};
		vec2 dragStart{0};
	public:
		// The key to the m_parent widget
		std::shared_ptr<Key> key;

		static vec2 g_cursorPos;
		static std::unordered_map<int, KeyState> g_keys;
		static unsigned char g_textInput;
		static vec2 g_scrollDelta;
		static std::vector<Rect> g_hitCheckRects;
		static vec2 g_dpi;
		static bool g_cursorInside;

		// Wether the cursor is directly above the widget, without a stacked widget being on top
		bool hovered = false;
		// Wether the left mouse button is currently being held on top of the widget
		bool focused = false;
		// Wether the left mouse button started being held outside of the widget
		bool focusedOutside = false;
		// Indicates if the widget has been activated by a click and no other widget has been focused since
		bool active = false;
		unsigned int charInput = 0;

		std::function<void(GestureDetector *)> onEnter{};
		std::function<void(GestureDetector *)> onLeave{};
		std::function<void(GestureDetector *)> onClick{};

		explicit GestureDetector(std::shared_ptr<Key> key) : key(std::move(key)) {}

		[[nodiscard]] static bool isKey(int key, int action, int mods = 0);

		[[nodiscard]] static bool isKeyPressedOrRepeat(int key, int mods = 0);

		void update();

		[[nodiscard]] const vec2& getMousePos() const;
		// Get how much the cursor has moved since the last frame
		[[nodiscard]] vec2 getMouseDelta() const;
		// Get how much the scroll has moved in the last frame
		[[nodiscard]] const vec2& getScroll() const;
		// Get how much the cursor has moved since it began dragging
		[[nodiscard]] vec2 getDragOffset() const;
		// Get the location of where the drag began
		[[nodiscard]] const vec2& getDragStartPos() const;
	};
}// namespace squi

#endif//SQ_UI_GESTUREDETECTOR_HPP
