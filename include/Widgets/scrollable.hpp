#ifndef SQ_UI_SCROLLABLE_HPP
#define SQ_UI_SCROLLABLE_HPP

#include "../gestureDetector.hpp"
#include "../widget.hpp"

namespace squi {
	struct ScrollableArgs {
		WidgetData data{};
		float spaceBetween = 0;
		Children children{};
	};

	class Scrollable : public Widget {
		std::shared_ptr<Key> columnKey = std::make_shared<Key>();
		GestureDetector gd{getKey()};
		float scroll = 0;
		float lastScroll = 0;
		bool transitionCleared = false;

	public:
		explicit Scrollable(const ScrollableArgs &args);

		void setScroll(const float &newScroll, bool instant = false);
		[[nodiscard]] const float &getScroll() const;

		void updateBeforeChild() override;
		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_SCROLLABLE_HPP
