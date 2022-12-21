#ifndef SQ_UI_TEXTBOX_HPP
#define SQ_UI_TEXTBOX_HPP

#include "../invisibleWidget.hpp"
#include "box.hpp"
#include "textInput.hpp"

namespace squi {
	struct TextBoxArgs {
		WidgetData data{};
	};

	class TextBox : public InvisibleWidget {
		std::shared_ptr<Key> boxKey = std::make_shared<Key>();
		std::shared_ptr<Key> textInputKey = std::make_shared<Key>();
		std::shared_ptr<Key> underlineKey = std::make_shared<Key>();
	public:
		explicit TextBox(const TextBoxArgs &args);

		void update() override;
	};
}// namespace squi

#endif//SQ_UI_TEXTBOX_HPP
