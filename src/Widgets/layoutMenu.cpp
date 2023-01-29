#include "layoutMenu.hpp"
#include "align.hpp"
#include "box.hpp"
#include "column.hpp"
#include "random"
#include "row.hpp"
#include "screen.hpp"
#include "scrollableWithScrollbar.hpp"
#include "text.hpp"
#include "textButton.hpp"

using namespace squi;

class LayoutMenuButtonData : public Widget {
	std::shared_ptr<squi::Widget> child;
	std::shared_ptr<Key> posKey = std::make_shared<Key>();
	std::shared_ptr<Key> sizeKey = std::make_shared<Key>();
	std::shared_ptr<Key> marginKey = std::make_shared<Key>();
	std::shared_ptr<Key> paddingKey = std::make_shared<Key>();

public:
	LayoutMenuButtonData(std::shared_ptr<squi::Widget> child)
		: Widget(WidgetData{}, WidgetContentType::invisibleWithChild), child(child) {
		auto &data = child->getData();
		auto &pos = child->getPos();
		setChild(new Column(ColumnArgs{
			.data{
				.shrinkWrap = Axis::both,
			},
			.children{
				new Text(TextArgs{
					.data{.key = posKey},
					.text = std::format("Pos: x:{} y:{}", pos.x, pos.y),
				}),
				new Text(TextArgs{
					.data{.key = sizeKey},
					.text = std::format("Size: width:{} height:{}", data.size.x, data.size.y),
				}),
				new Text(TextArgs{
					.data{.key = marginKey},
					.text = std::format("Margin: l:{} r:{} t:{} b:{}", data.margin.left, data.margin.right, data.margin.top, data.margin.bottom),
				}),
				new Text(TextArgs{
					.data{.key = paddingKey},
					.text = std::format("Padding: l:{} r:{} t:{} b:{}", data.padding.left, data.padding.right, data.padding.top, data.padding.bottom),
				}),
			},
		}));
	}

	void updateBeforeChild() override {
		const auto &data = child->getData();
		const auto &pos = child->getPos();
		posKey->getAs<Text>()->setText(std::format("Pos: x:{} y:{}", pos.x, pos.y));
		sizeKey->getAs<Text>()->setText(std::format("Size: width:{} height:{}", data.size.x, data.size.y));
		marginKey->getAs<Text>()->setText(std::format("Margin: l:{} r:{} t:{} b:{}", data.margin.left, data.margin.right, data.margin.top, data.margin.bottom));
		paddingKey->getAs<Text>()->setText(std::format("Padding: l:{} r:{} t:{} b:{}", data.padding.left, data.padding.right, data.padding.top, data.padding.bottom));
	}
};

LayoutMenuButton::LayoutMenuButton(const LayoutMenuButtonArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild), argsChild(args.widget) {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(50, 255);
	Children children{};
	std::shared_ptr<Widget> child = args.widget;
	if (!child) return;
	const auto data = child->getData();
	if (child->getChildCountType() != WidgetContentType::invisibleWithChild)
		children.add(new LayoutMenuButtonData(child));
	switch (child->getChildCountType()) {
		case WidgetContentType::singleChild: {
			children.add(new LayoutMenuButton(LayoutMenuButtonArgs{
				.widget = child->getChild(),
			}));
			break;
		}
		case WidgetContentType::multipleChildren: {
			for (auto &c: child->getChildren()) {
				children.add(new LayoutMenuButton(LayoutMenuButtonArgs{
					.widget = c,
				}));
			}
			break;
		}
		case WidgetContentType::invisibleWithChild: {
			isExpanded = true;
			children.add(new LayoutMenuButton(LayoutMenuButtonArgs{
				.widget = child->getChild(),
			}));
			break;
		}
		case WidgetContentType::none: {
			break;
		}
	}

	Color color = Color::fromRGB255(dist(rng), dist(rng), dist(rng));

	setChild(new Column(ColumnArgs{
		.data{
			.shrinkWrap = Axis::vertical,
			.expand = Axis::horizontal,
		},
		.children{
			new Box(BoxArgs{
				.data{
					.size{16},
					.padding{16, 4},
					.shrinkWrap = Axis::vertical,
					.expand = Axis::horizontal,
				},
				.color{1, 1, 1, 0.25},
				.onClick = [&](GestureDetector *gd) {
					this->isExpanded = !this->isExpanded;
				},
				.child = new Text(TextArgs{
					.text{typeid(*child.get()).name()},
				}),
			}),
			new Box(BoxArgs{
				.data{
					.size{2},
					.expand = Axis::horizontal,
				},
				.color{color},
			}),
			new Box(BoxArgs{
				.data{
					.key{contentKey},
					.shrinkWrap = Axis::vertical,
					.expand = Axis::horizontal,
					.transition{
						.duration = 200ms,
						.curve = TransitionCurves::easeOut,
						.animatedValues = [](std::shared_ptr<squi::Key> key) {
							return TransitionValues{&key->get()->getData().size.y};
						},
					},
				},
				.color{0, 0, 0, 0},
				.shouldClipContents = true,
				.child = new Row(RowArgs{
					.data{
						.shrinkWrap = Axis::vertical,
						.expand = Axis::horizontal,
					},
					.spaceBetween = 4,
					.children{
						new Box(BoxArgs{
							.data{
								.size{2},
								.expand = Axis::vertical,
							},
							.color{color},
						}),
						new Column(ColumnArgs{
							.data{
								.key{childrenKey},
								.shrinkWrap = Axis::vertical,
								.expand = Axis::horizontal,
							},
							.spaceBetween = 1,
							.children{children},
						}),
					},
				}),
			}),
		},
	}));
}

void LayoutMenuButton::updateBeforeChild() {
	if (!contentKey->isValid()) return;
	auto content = contentKey->get();
	if (isExpanded) {
		content->getData().shrinkWrap = Axis::vertical;
	} else {
		content->getData().shrinkWrap = Axis::none;
		content->setSizeHint(content->getSizeHint().withY(0));
	}
}

LayoutMenuOverlay::LayoutMenuOverlay() : Overlay(OverlayArgs{}) {
	setChild(new Align(AlignArgs{
		.alignment{1, 1},
		.child = new Box(BoxArgs{
			.data{
				.size{400},
				.margin{20},
			},
			.color{0.1, 0.1, 0.1, 1},
			.child = new ScrollableWithScrollbar(ScrollableArgs{
				.data{
					.expand = Axis::both,
				},
				.children{
					new TextButton(TextButtonArgs{
						.data{
							.margin{8, 8},
							.expand = Axis::horizontal,
						},
						.onClick = [&]() {
							contentKey->get()->setChildren(Children{new LayoutMenuButton(LayoutMenuButtonArgs{
								.widget = Screen::getCurrentScreen()->getChild(),
							})});
						},
						.text{
							.text{"Refresh widget tree"},
						},
					}),
					new Column(ColumnArgs{
						.data{
							.key{contentKey},
							.shrinkWrap = Axis::vertical,
							.expand = Axis::horizontal,
						},
						.children{
							new LayoutMenuButton(LayoutMenuButtonArgs{
								.widget = Screen::getCurrentScreen()->getChild(),
							}),
						},
					}),
				},
			}),
		}),
	}));
}

void LayoutMenuOverlay::updateBeforeChild() {
	if (GestureDetector::isKey(GLFW_KEY_F11, GLFW_PRESS, GLFW_MOD_SHIFT)) {
		shouldDisplay = !shouldDisplay;
		if (!shouldDisplay) {
			contentKey->get()->setChildren(Children{});
		}
	}
}

void LayoutMenuOverlay::draw() {
	if (!shouldDisplay) return;
	Overlay::draw();
}
