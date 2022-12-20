#ifndef SQ_UI_SCROLLABLE_HPP
#define SQ_UI_SCROLLABLE_HPP

#include "../gestureDetector.hpp"
#include "../widget.hpp"

namespace squi {
	struct ScrollableArgs{
		WidgetData data{};
		std::vector<Widget*> children{};
	};

	class Scrollable : public Widget {
		std::shared_ptr<Key> columnKey = std::make_shared<Key>();
		GestureDetector gd{getKey()};
		float scroll = 0;
	public:

		explicit Scrollable(const ScrollableArgs& args);

		void setScroll(const float &newScroll);
		[[nodiscard]] const float& getScroll() const;

		void update() override;
		void draw() override;
	};
}

#endif//SQ_UI_SCROLLABLE_HPP
