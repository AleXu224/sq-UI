#include <memory>

#include "algorithm"
#include "include/Widgets/CustomButton.hpp"
#include "include/Widgets/align.hpp"
#include "include/Widgets/box.hpp"
#include "include/Widgets/column.hpp"
#include "include/Widgets/row.hpp"
#include "include/Widgets/scrollable.hpp"
#include "include/Widgets/scrollableWithScrollbar.hpp"
#include "include/Widgets/stack.hpp"
#include "include/Widgets/text.hpp"
#include "include/Widgets/textInput.hpp"
#include "include/screen.hpp"
#include "ranges"

int main() {
	using namespace squi;
	Screen screen;
	auto key = std::make_shared<Key>();
	//	screen.m_child.reset(new Box())

	//	screen.m_child = std::make_shared<Box>(BoxArgs{
	//		.m_data{
	//			.key{key},
	//			.size{200},
	//			.margin{20},
	//		},
	//		.color{Color::fromRGB255(128, 128, 128)},
	//		.borderRadius = 20,
	//		.border{
	//			.size = 10,
	//			.color{1, 1, 1, 1},
	//			.position = squi::BorderPosition::outside
	//		},
	//		.onClick = [](GestureDetector *gd) {
	//			printf("YOOO I GOT CLICKED");
	//		},
	//		.m_child = new Box(BoxArgs{
	//			.m_data{
	//				.size{20},
	//				.margin{10},
	//			},
	//			.color{0, 0, 0, 1},
	//		})
	//	});

//	screen.setChild(new Box(BoxArgs{
//		.data{
//			.margin{2},
//			.padding{2},
//			.expand = squi::Axis::both,
//		},
//		.color{0},
//		.child = new CustomButton(CustomButtonArgs{
//			.data{
//				.padding{12, 7},
//				.shrinkWrap = squi::Axis::both,
//			},
//			.onClick = []() {
//				printf("This works?\n");
//			},
//			.child = new Text(TextArgs{
//				.text = "CText",
//				.color{0, 0, 0, 1},
//			}),
//		}),
//	}));

	screen.setChild(new ScrollableWithScrollbar(ScrollableArgs{
		.data{
			.expand = Axis::both,
		},
		.children {
			new Box(BoxArgs{
				.data {
					.size{300},
					.margin{0, 0, 0, 5},
				},
				.color {0, 0.5, 1},
			}),
			new Box(BoxArgs{
				.data {
					.size{300},
					.margin{0, 0, 0, 5},
				},
				.color {0, 0.6, 1},
			}),
			new Box(BoxArgs{
				.data {
					.size{300},
					.margin{0, 0, 0, 5},
				},
				.color {0, 0.7, 1},
			}),
			new Box(BoxArgs{
				.data {
					.size{300},
					.margin{0, 0, 0, 5},
				},
				.color {0, 0.8, 1},
			}),
			new Box(BoxArgs{
				.data {
					.size{300},
					.margin{0, 0, 0, 5},
				},
				.color {0, 0.9, 1},
			}),
		},
	}));

	screen.run();
	return 0;
}
