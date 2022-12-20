#ifndef SQ_UI_SCROLLABLEWITHSCROLLBAR_HPP
#define SQ_UI_SCROLLABLEWITHSCROLLBAR_HPP

#include "../invisibleWidget.hpp"
#include "scrollBar.hpp"
#include "scrollable.hpp"
#include "stack.hpp"

namespace squi {
	class ScrollableWithScrollbar : public InvisibleWidget {
		std::shared_ptr<Key> scrollableKey = std::make_shared<Key>();
		std::shared_ptr<Key> scrollbarKey = std::make_shared<Key>();
	public:
		explicit ScrollableWithScrollbar(const ScrollableArgs &args);

		void update() override;
	};
}

#endif//SQ_UI_SCROLLABLEWITHSCROLLBAR_HPP
