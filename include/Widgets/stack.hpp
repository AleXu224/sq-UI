#ifndef SQ_UI_STACK_HPP
#define SQ_UI_STACK_HPP

#include "../widget.hpp"

namespace squi {
	struct StackArgs {
		const WidgetData& data{};
		Children children{};
	};

	class Stack : public Widget {
	public:
		explicit Stack(const StackArgs& args);

		[[nodiscard]] std::vector<Rect> getHitcheckRects() const override;

		void customUpdate() override;

		void draw() override;
	};
}

#endif//SQ_UI_STACK_HPP
