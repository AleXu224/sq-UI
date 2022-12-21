#ifndef SQ_UI_STACK_HPP
#define SQ_UI_STACK_HPP

#include "../widget.hpp"

namespace squi {
	struct StackArgs {
		const WidgetData& data{};
		std::vector<Widget *> children{};
	};

	class Stack : public Widget {
	public:
		explicit Stack(const StackArgs& args);

		[[nodiscard]] std::vector<Rect> getHitcheckRects() const override;

		void update() override;

		void draw() override;
	};
}

#endif//SQ_UI_STACK_HPP
