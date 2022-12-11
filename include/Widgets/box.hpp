#ifndef SQ_UI_BOX_HPP
#define SQ_UI_BOX_HPP

#include "../border.hpp"
#include "../color.hpp"
#include "../gestureDetector.hpp"
#include "../widget.hpp"

namespace squi {
	struct BoxArgs {
		WidgetData data{};
		Color color{};
		float borderRadius = 0;
		Border border;
		// Wether the container should update the gesture detector of not
		// Will be overriden to true if onEnter, onLeave or onClick is set
		bool shouldUpdateGestureDetector = false;
		std::function<void(GestureDetector *)> onEnter{};
		std::function<void(GestureDetector *)> onLeave{};
		std::function<void(GestureDetector *)> onClick{};
		Widget *child = nullptr;
	};

	class Box : public Widget {
		bool shouldUpdateGd;
	public:
		Color color;
		float borderRadius;
		Border border;
		GestureDetector gd{getKey()};

		explicit Box(const BoxArgs& args);

		void update() override;
		void draw() override;
	};
}// namespace squi


#endif//SQ_UI_BOX_HPP
