#ifndef SQUI_TOPNAV_HPP
#define SQUI_TOPNAV_HPP

#include "../widget.hpp"

namespace squi {
	// Button
	struct TopNavButtonArgs {
		WidgetData data{};
		std::string text{};
		std::function<void()> onClick{};
	};

	class TopNavButton : public Widget {
		std::shared_ptr<Key> underlineKey = std::make_shared<Key>();

	public:
		bool isActive = false;
		explicit TopNavButton(const TopNavButtonArgs &args);

		void updateBeforeChild() override;
	};

	// TabNav
	struct TopNavTab {
		std::string name{};
		Child child{};
	};

	struct TopNavArgs {
		WidgetData data{};
		const std::vector<TopNavTab> tabs{};
	};

	class TopNav : public Widget {
		const std::vector<TopNavTab> tabs;
		std::shared_ptr<Key> contentKey = std::make_shared<Key>();
		std::shared_ptr<Key> buttonsKey = std::make_shared<Key>();
		int activeTab = 0;

	public:
		explicit TopNav(const TopNavArgs &args);

		void updateBeforeChild() override;
	};
}// namespace squi

#endif