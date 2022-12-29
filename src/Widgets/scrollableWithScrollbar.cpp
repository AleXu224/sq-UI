#include "../../include/Widgets/scrollableWithScrollbar.hpp"
#include "../../include/Widgets/align.hpp"

using namespace squi;
ScrollableWithScrollbar::ScrollableWithScrollbar(const ScrollableArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild) {
	setChild(Stack(StackArgs{
		.children{
			Scrollable{ScrollableArgs{
				.data{
					args.data
						.withKey(scrollableKey),
				},
				.children{args.children},
			}},
			Align(AlignArgs{
				.alignment{1, 0},
				.child = ScrollBar(ScrollbarArgs{
					.data{
						.key{scrollbarKey},
					},
					.scrollableKey{scrollableKey},
				}),
			}),
		},
	}));
}

void ScrollableWithScrollbar::updateAfterChild() {
	scrollbarKey->getAs<ScrollBar>()->updateFromScrollable();
}
