#include <memory>

#include "include/Widgets/box.hpp"
#include "include/screen.hpp"

int main() {
	using namespace squi;
	Screen screen;
	auto key = std::make_shared<Key>();
	//	screen.child.reset(new Box())

	screen.child = std::make_shared<Box>(BoxArgs{
		.data{
			.key{key},
			.size{200},
			.margin{20},
		},
		.color{Color::fromRGB255(128, 128, 128)},
		.borderRadius = 20,
		.border{
			.size = 10,
			.color{1, 1, 1, 1},
			.position = squi::BorderPosition::outside
		},
		.onClick = [](GestureDetector *gd) {
			printf("YOOO I GOT CLICKED");
		},
		.child = new Box(BoxArgs{
			.data{
				.size{20},
				.margin{10},
			},
			.color{0, 0, 0, 1},
		})
	});

	screen.run();
	return 0;
}
