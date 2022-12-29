#ifndef SQ_UI_TEXTBOX_HPP
#define SQ_UI_TEXTBOX_HPP

#include "../widget.hpp"
#include "box.hpp"
#include "textInput.hpp"

namespace squi {
	struct TextBoxArgs {
		WidgetData data{};
	};

	class TextBox : public Widget {
		std::shared_ptr<Key> boxKey = std::make_shared<Key>();
		std::shared_ptr<Key> textInputKey = std::make_shared<Key>();
		std::shared_ptr<Key> underlineKey = std::make_shared<Key>();
	public:
		explicit TextBox(const TextBoxArgs &args);

		void transitionInit() override;
		void updateBeforeChild() override;
	};
}// namespace squi

#endif//SQ_UI_TEXTBOX_HPP
