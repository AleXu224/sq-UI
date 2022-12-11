#ifndef SQ_UI_STACK_HPP
#define SQ_UI_STACK_HPP

#include "../widgetWithChildren.hpp"

namespace squi {
	struct StackArgs {
		const WidgetData& data{};
		std::vector<Widget *> children{};
	};

	class Stack : public WidgetWithChildren {
	public:
		explicit Stack(const StackArgs& args);

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_STACK_HPP
