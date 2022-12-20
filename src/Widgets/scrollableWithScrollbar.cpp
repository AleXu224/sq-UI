#include "../../include/Widgets/scrollableWithScrollbar.hpp"
#include "../../include/Widgets/align.hpp"

using namespace squi;
ScrollableWithScrollbar::ScrollableWithScrollbar(const ScrollableArgs &args) : InvisibleWidget(args.data) {
	setChild(new Stack(StackArgs{
		.children {
			new Scrollable{ScrollableArgs{
				.data{args.data.withKey(scrollableKey)},
				.children{args.children},
			}},
			new Align(AlignArgs{
				.alignment{1, 0},
				.child = new ScrollBar(ScrollbarArgs{
					.data{
						.key{scrollbarKey},
					},
					.scrollableKey{scrollableKey},
				}),
			}),
		},
	}));
}

void ScrollableWithScrollbar::update() {
	InvisibleWidget::update();

	scrollbarKey->get()->update();
}
