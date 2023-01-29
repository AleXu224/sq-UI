#ifndef SQUI_LAYOUTMENU_HPP
#define SQUI_LAYOUTMENU_HPP

#include "../overlay.hpp"
#include "../widget.hpp"

namespace squi {
	struct LayoutMenuButtonArgs {
		WidgetData data{};
		Child widget{};
	};

	class LayoutMenuButton : public Widget {
		bool isExpanded = false;
		std::shared_ptr<Key> contentKey = std::make_shared<Key>();
		std::shared_ptr<Key> childrenKey = std::make_shared<Key>();
		Child argsChild;

	public:
		explicit LayoutMenuButton(const LayoutMenuButtonArgs &args);

		void updateBeforeChild() override;
	};

	class LayoutMenuOverlay : public Overlay {
		std::shared_ptr<Key> contentKey = std::make_shared<Key>();
		bool shouldDisplay = false;
	public:
		explicit LayoutMenuOverlay();

		void updateBeforeChild() override;

		void draw() override;
	};
}// namespace squi

#endif