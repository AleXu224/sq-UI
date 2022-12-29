#ifndef SQ_UI_ALIGN_HPP
#define SQ_UI_ALIGN_HPP

#include "../widget.hpp"

namespace squi {
	struct AlignArgs {
		WidgetData data{};
		vec2 alignment{0.5};
		Child child{};
	};

	class Align : public Widget {
	public:
		vec2 alignment;
		explicit Align(const AlignArgs &args)
			: Widget(args.data, WidgetContentType::invisibleWithChild), alignment(args.alignment) {
			setChild(args.child);
		}

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_ALIGN_HPP
