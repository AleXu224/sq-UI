#include <memory>

#include "algorithm"
#include "include/Widgets/align.hpp"
#include "include/Widgets/box.hpp"
#include "include/Widgets/column.hpp"
#include "include/Widgets/row.hpp"
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

	screen.setChild(new Box(BoxArgs{
		.data{
			.size{300},
			.margin{2},
			.padding{2},
			.expand = squi::Axis::both,
		},
		.color{0},
		.child = new Box(BoxArgs{
			.data{
				.shrinkWrap = squi::Axis::both,
			},
			.color{1, 0, 0},
			.child = new TextInput(TextInputArgs{
				.data{
					.size{300},
					.shrinkWrap = squi::Axis::vertical,
				},
				.textArgs{
					.text{"Hello there"},
				},
			}),
		}),
	}));

	screen.run();
	return 0;
}
