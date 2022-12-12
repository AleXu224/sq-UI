#ifndef SQ_UI_ALIGN_HPP
#define SQ_UI_ALIGN_HPP

#include "../invisibleWidget.hpp"

namespace squi {
	struct AlignArgs {
		WidgetData data{};
		vec2 alignment{0.5};
		Widget *child = nullptr;
	};

	class Align : public InvisibleWidget {
	public:
		vec2 alignment;
		explicit Align(const AlignArgs &args)
			: InvisibleWidget(args.data), alignment(args.alignment) {
			setChild(args.child);
		}

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_ALIGN_HPP
