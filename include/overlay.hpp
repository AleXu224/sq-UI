#ifndef SQ_UI_OVERLAY_HPP
#define SQ_UI_OVERLAY_HPP

#include "Widgets/stack.hpp"

namespace squi {
	struct OverlayArgs {
		WidgetData data{};
		std::vector<Widget *> children{};
	};

	class Overlay : public Widget {
	public:
		bool shouldClose = false;
		bool canClose = false;

		explicit Overlay(const OverlayArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild) {
			setChild(new Stack(StackArgs{
				.children{args.children},
			}));
		}
	};
}// namespace squi

#endif//SQ_UI_OVERLAY_HPP
