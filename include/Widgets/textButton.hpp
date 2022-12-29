#ifndef SQ_UI_TEXTBUTTON_HPP
#define SQ_UI_TEXTBUTTON_HPP

#include "../widget.hpp"
#include "CustomButton.hpp"
#include "text.hpp"

namespace squi {
	struct TextButtonArgs {
		WidgetData data{};
		std::function<void()> onClick{};
		TextArgs text{};
		float maxWidth = -1;
	};

	class TextButton : public Widget {
		std::shared_ptr<Key> textKey = std::make_shared<Key>();
	public:
		explicit TextButton(const TextButtonArgs &args);

		void updateBeforeChild() override;
	};
}// namespace squi

#endif//SQ_UI_TEXTBUTTON_HPP