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
#include "include/Widgets/textBox.hpp"
#include "include/Widgets/textButton.hpp"
#include "include/Widgets/textInput.hpp"
#include "include/Widgets/topnav.hpp"
#include "include/screen.hpp"
#include "layoutMenu.hpp"
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

	// screen.setChild(new ScrollableWithScrollbar(ScrollableArgs{
	// 	.data{
	// 		.expand = Axis::both,
	// 	},
	// 	.children {
	// 		new Box(BoxArgs{
	// 			.data {
	// 				.size{300},
	// 				.margin{0, 0, 0, 5},
	// 			},
	// 			.color {0, 0.5, 1},
	// 		}),
	// 		new Box(BoxArgs{
	// 			.data {
	// 				.size{300},
	// 				.margin{0, 0, 0, 5},
	// 			},
	// 			.color {0, 0.6, 1},
	// 		}),
	// 		new Box(BoxArgs{
	// 			.data {
	// 				.size{300},
	// 				.margin{0, 0, 0, 5},
	// 			},
	// 			.color {0, 0.7, 1},
	// 		}),
	// 		new Box(BoxArgs{
	// 			.data {
	// 				.size{300},
	// 				.margin{0, 0, 0, 5},
	// 			},
	// 			.color {0, 0.8, 1},
	// 		}),
	// 		new Box(BoxArgs{
	// 			.data {
	// 				.size{300},
	// 				.margin{0, 0, 0, 5},
	// 			},
	// 			.color {0, 0.9, 1},
	// 		}),
	// 	},
	// }));

	// std::shared_ptr<Key> kk = std::make_shared<Key>();

	// Test the new transitions

	// screen.setChild(new Column(ColumnArgs{
	// 	.data{
	// 		.shrinkWrap = Axis::both,
	// 	},
	// 	.children{
	// 		new Box(BoxArgs{
	// 			.data{
	// 				.key{kk},
	// 				.size{100},
	// 				.transition{
	// 					.enabled = true,
	// 					.duration = 200,
	// 					.curve = TransitionCurves::easeInOut,
	// 				},
	// 			},
	// 			.color{0, 0, 1},
	// 		}),
	// 		new CustomButton(CustomButtonArgs{
	// 			.data{
	// 				.shrinkWrap = Axis::both,
	// 				.transition{
	// 					.enabled = true,
	// 					.duration = 200,
	// 					.curve = TransitionCurves::easeInOut,
	// 				},
	// 			},
	// 			.onClick = [&]() {
	// 				static bool s = false;
	// 				auto elem = kk->getAs<Box>();
	// 				// elem->setSize(vec2{200, 200});
	// 				if (s) {
	// 					elem->setMargin(Margin{0});
	// 					elem->border.size = 0;
	// 					elem->borderRadius = 0;
	// 					elem->setSize(vec2{100, 100});
	// 				} else {
	// 					elem->setMargin(Margin{15});
	// 					elem->border.size = 4;
	// 					elem->borderRadius = 20;
	// 					elem->setSize(vec2{200, 200});
	// 				}
	// 				s = !s;
	// 			},
	// 			.child = new Text(TextArgs{
	// 				.data{
	// 					.margin{12, 6},
	// 				},
	// 				.text{"Modify Box"},
	// 				.color{0, 0, 0, 0.8},
	// 			}),
	// 		}),
	// 	},
	// }));

	// std::shared_ptr<Key> k = std::make_shared<Key>();

	// screen.setChild(new CustomButton(CustomButtonArgs{
	// 	.data{
	// 		.key{k},
	// 		.size{100},
	// 	},
	// 	.onClick = [&](){
	// 		static bool s = false;
	// 		auto elem = k->getAs<CustomButton>();
	// 		if (s) {
	// 			elem->setMargin(Margin{0});
	// 			elem->setSize(vec2{100, 100});
	// 		} else {
	// 			elem->setMargin(Margin{15});
	// 			elem->setSize(vec2{200, 200});
	// 		}
	// 		s = !s;
	// 	},
	// }));

	// screen.setChild(new TextBox(TextBoxArgs{
	// 	.data {
	// 		.margin{4},
	// 		.expand = squi::Axis::horizontal,
	// 	},
	// }));

	// screen.setChild(new TextButton(TextButtonArgs{
	// 	.data{
	// 		.shrinkWrap = Axis::vertical,
	// 		.expand = Axis::horizontal,
	// 	},
	// 	.text{
	// 		.text{"Some button withh some even longer text plz work"},
	// 		// .maxWidth = 200,
	// 		.lineWrap = true,
	// 	},
	// }));

	screen.setChild(new TopNav(TopNavArgs{
		.tabs{
			TopNavTab{
				.name{"Tab 1"},
				.child = new Text(TextArgs{
					.text{"Tab 1"},
				}),
			},
			TopNavTab{
				.name{"Tab 2"},
				.child = new Text(TextArgs{
					.text{"Tab 2"},
				}),
			},
			TopNavTab{
				.name{"Tab 3 With some extra text"},
				.child = new Align(AlignArgs{
					.child = new Box(BoxArgs{
						.data{
							.size{200},
						},
						.color{0, 1, 1},
					}),
				}),
			},
		},
	}));
	// screen.addOverlay(new Overlay(OverlayArgs{
	// 	.data{
	// 		.expand = Axis::both,
	// 	},
	// 	.children{
	// 		new Align(AlignArgs{
	// 			.alignment{1, 1},
	// 			.child = new Box(BoxArgs{
	// 				.data{
	// 					.size{400},
	// 					.margin{20},
	// 				},
	// 				.color{0.1, 0.1, 0.1, 1},
	// 				.child = new ScrollableWithScrollbar(ScrollableArgs{
	// 					.data{
	// 						.expand = Axis::both,
	// 					},
	// 					.children{
	// 						new LayoutMenuButton(LayoutMenuButtonArgs{
	// 							.widget = screen.getChild(),
	// 						}),
	// 					},
	// 				}),
	// 			}),
	// 		}),
	// 	},
	// }));

	screen.run();
	return 0;
}
