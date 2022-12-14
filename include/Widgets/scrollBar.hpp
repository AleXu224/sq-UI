#ifndef SQ_UI_SCROLLBAR_HPP
#define SQ_UI_SCROLLBAR_HPP

#include "../color.hpp"
#include "../widget.hpp"

namespace squi {
	struct ScrollbarArgs {
		WidgetData data{};
		std::shared_ptr<Key> scrollableKey;
	};

	class ScrollBar : public Widget {
		std::shared_ptr<Key> scrollableKey = std::make_shared<Key>();
		std::shared_ptr<Key> bgKey = std::make_shared<Key>();
		std::shared_ptr<Key> thumbKey = std::make_shared<Key>();

		bool dragging = false;
		float dragScrollStart = 0;
		bool shouldHide = false;

		const Color bgColor = Color::fromHexRGBA("#FFFFFF0B");
		const Color bgColorInactive = Color{0};
		const Color thumbColor = Color::fromHexRGBA("#FFFFFF8B");

	public:
		explicit ScrollBar(const ScrollbarArgs &args);

		void updateFromScrollable();

		void updateBeforeChild() override;

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_SCROLLBAR_HPP
