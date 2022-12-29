#include "../../include/Widgets/topnav.hpp"

#include "../../include/Widgets/box.hpp"
#include "../../include/Widgets/column.hpp"
#include "../../include/Widgets/row.hpp"
#include "../../include/Widgets/stack.hpp"
#include "../../include/Widgets/align.hpp"
#include "../../include/Widgets/text.hpp"
#include "../../include/screen.hpp"

#include "cassert"

using namespace squi;

TopNavButton::TopNavButton(const TopNavButtonArgs &args) : Widget(args.data, WidgetContentType::invisibleWithChild) {
    setChild(new Box(BoxArgs{
        .data{
            .size{40},
            .shrinkWrap = Axis::horizontal,
        },
        .color = Color{0},
        .onClick = [onClick = args.onClick](GestureDetector *gd) {
            if (onClick) {
                onClick();
            }
        },
        .child = new Stack(StackArgs{
            .data {
                .expand = Axis::both,
            },
            .children{
                new Text(TextArgs{
                    .data{
                        .margin{12, 10},
                    },
                    .text{args.text},
                }),
                new Align(AlignArgs{
                    .alignment{0.5, 1},
                    .child = new Box(BoxArgs{
                        .data{
                            .key{underlineKey},
                            .size{0, 3},
                            .transition {
                                .duration = 200ms,
                                .curve = TransitionCurves::easeOut,
                                .animatedValues = [](std::shared_ptr<Key> key) {
                                    return TransitionValues{
                                        &key->getAs<Box>()->getData().size.x,
                                    };
                                },
                            },
                        },
                        .color{Screen::getSystemAccentColor()},
                        .borderRadius = 1.5,
                    }),
                }),
            },
        }),
    }));
}

void TopNavButton::updateBeforeChild() {
    auto underline = underlineKey->getAs<Box>();

    underline->color = Screen::getSystemAccentColor();
    if (isActive) {
        underline->setSize({16, 3});
    } else {
		underline->setSize({0, 3});
	}
}

TopNav::TopNav(const TopNavArgs &args)
	: Widget(args.data, WidgetContentType::invisibleWithChild),
	  tabs(args.tabs) {

    assert(tabs.size() > 0);
    Children tabWidgets;
    int index = 0;
    for (auto &tab : tabs) {
        tabWidgets.add(new TopNavButton(TopNavButtonArgs{
            .text = tab.name,
            .onClick = [key = getKey(), index = index++]() {
                auto widget = key->getAs<TopNav>();
                auto buttons = widget->buttonsKey->get()->getChildren();
                buttons.at(widget->activeTab)->getKey()->getAs<TopNavButton>()->isActive = false;
                widget->activeTab = index;
                buttons.at(widget->activeTab)->getKey()->getAs<TopNavButton>()->isActive = true;
                widget->contentKey->get()->setChild(widget->tabs.at(index).child);
            },
        }));
    }

	setChild(new Column(ColumnArgs{
		.data{
			.expand = Axis::both,
		},
		.children{
			new Row(RowArgs{
				.data{
                    .key{buttonsKey},
					.padding{4},
					.shrinkWrap = Axis::vertical,
					.expand = Axis::horizontal,
				},
				.children{tabWidgets},
			}),
			new Box(BoxArgs{
				.data{
					.size{1},
					.expand = Axis::horizontal,
				},
				.color = Color::fromHexRGBA("#0000001A"),
			}),
			new Box(BoxArgs{
				.data{
					.key{contentKey},
					.expand = Axis::both,
				},
				.color = Color::fromHexRGBA("#3A3A3A4D"),
			}),
		},
	}));

	if (tabs.size() > 0) {
		contentKey->get()->setChild(tabs.at(0).child);
        buttonsKey->get()->getChildren().at(0)->getKey()->getAs<TopNavButton>()->isActive = true;
    }
}

void TopNav::updateBeforeChild() {}
