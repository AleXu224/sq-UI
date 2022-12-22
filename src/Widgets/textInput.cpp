#include "../../include/Widgets/textInput.hpp"
#include "../../include/screen.hpp"

using namespace squi;

TextInput::TextInput(const TextInputArgs &args)
	: Widget(args.data, WidgetContentType::singleChild),
	  cursorColor(args.cursorColor),
	  onChange(args.onChange),
	  selectText(std::make_shared<Text>(TextArgs{
		  .fontSize = args.textArgs.fontSize,
		  .fontFamily{args.textArgs.fontFamily},
		  .weight = args.textArgs.weight,
		  .color{args.textArgs.color},
	  })) {

	setChild(new Text(TextArgs{
		.fontSize = args.textArgs.fontSize,
		.fontFamily{args.textArgs.fontFamily},
		.weight = args.textArgs.weight,
		.color{args.textArgs.color},
	}));
}

void TextInput::update() {
	Widget::update();
	gd.update();

	if (!gd.active) return;

	auto valueCopy = value;

	const auto removeSelectedRegion = [&]() {
		int selectStartPos = (std::min)(cursorPos, selectStart);
		int selectEndPos = (std::max)(cursorPos, selectStart);
		value.replace(selectStartPos, selectEndPos - selectStartPos, "");
		selectStart = -1;
		cursorPos = selectStartPos > static_cast<int>(value.size()) ? static_cast<int>(value.size()) : selectStartPos;
	};
	if (gd.charInput) {
		if (selectStart != -1) removeSelectedRegion();
		value.insert(cursorPos, std::string{static_cast<char>(gd.charInput)});
		++cursorPos;
	}
	// TODO: add more keybinds
	// https://www.howtogeek.com/115664/42-text-editing-keyboard-shortcuts-that-work-almost-everywhere/
	// At least usable for now
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_BACKSPACE) && !value.empty()) {
		if (selectStart != -1) {
			removeSelectedRegion();
		} else if (cursorPos != 0) {
			value.replace(cursorPos - 1, 1, "");
			--cursorPos;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_BACKSPACE, GLFW_MOD_CONTROL) && !value.empty()) {
		if (selectStart != -1) {
			removeSelectedRegion();
		} else {
			int step = cursorPos;
			int i = cursorPos - 1;
			for (; i >= 0; i--) {
				if (!isspace(value.at(i))) break;
				step = i;
			}
			for (; i >= 0; i--) {
				if (isspace(value.at(i))) break;
				step = i;
			}
			if (step == cursorPos && step > 0) --step;
			value.replace(step, cursorPos - step, "");
			cursorPos = step;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_DELETE) && !value.empty()) {
		if (selectStart != -1) {
			removeSelectedRegion();
		} else if (cursorPos != static_cast<int>(value.size())) {
			value.replace(cursorPos, 1, "");
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_DELETE, GLFW_MOD_CONTROL) && !value.empty()) {
		if (selectStart != -1) {
			removeSelectedRegion();
		} else {
			int step = cursorPos;
			int i = cursorPos + 1;
			for (; i <= static_cast<int>(value.size()); i++) {
				if (!isspace(value.at(i - 1))) break;
				step = i;
			}
			for (; i <= static_cast<int>(value.size()); i++) {
				if (isspace(value.at(i - 1))) break;
				step = i;
			}
			if (step == cursorPos && step < static_cast<int>(value.size())) ++step;
			value.replace(cursorPos, step - cursorPos, "");
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_LEFT)) {
		if (selectStart != -1) cursorPos = (std::min)(cursorPos, selectStart);
		else
			cursorPos = --cursorPos < 0 ? 0 : cursorPos;
		selectStart = -1;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_LEFT, GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		cursorPos = --cursorPos < 0 ? 0 : cursorPos;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_LEFT, GLFW_MOD_CONTROL)) {
		selectStart = -1;
		if (cursorPos != 0) {
			int step = cursorPos;
			int i = cursorPos - 1;
			// Step through all the whitespace characters until it hits a non whitespace
			// then it should go through all the non whitespace characters
			// This is the behaviour most people expect out of this
			for (; i >= 0; i--) {
				if (!isspace(value.at(i))) break;
				step = i;
			}
			for (; i >= 0; i--) {
				if (isspace(value.at(i))) break;
				step = i;
			}
			if (step == cursorPos && step > 0) --cursorPos;
			else
				cursorPos = step;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_LEFT, GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		if (cursorPos != 0) {
			int step = cursorPos;
			int i = cursorPos - 1;
			for (; i >= 0; i--) {
				if (!isspace(value.at(i))) break;
				step = i;
			}
			for (; i >= 0; i--) {
				if (isspace(value.at(i))) break;
				step = i;
			}
			if (step == cursorPos && step > 0) --cursorPos;
			else
				cursorPos = step;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_RIGHT)) {
		if (selectStart != -1)
			cursorPos = (std::max)(cursorPos, selectStart);
		else
			cursorPos = ++cursorPos > static_cast<int>(value.size()) ? static_cast<int>(value.size()) : cursorPos;
		selectStart = -1;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_RIGHT, GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		cursorPos = ++cursorPos > static_cast<int>(value.size()) ? static_cast<int>(value.size()) : cursorPos;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_RIGHT, GLFW_MOD_CONTROL)) {
		selectStart = -1;
		if (cursorPos != static_cast<int>(value.size())) {
			int step = cursorPos;
			int i = cursorPos + 1;
			for (; i <= static_cast<int>(value.size()); i++) {
				if (!isspace(value.at(i - 1))) break;
				step = i;
			}
			for (; i <= static_cast<int>(value.size()); i++) {
				if (isspace(value.at(i - 1))) break;
				step = i;
			}
			if (step == cursorPos && step < static_cast<int>(value.size())) ++cursorPos;
			else
				cursorPos = step;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_RIGHT, GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		if (cursorPos != static_cast<int>(value.size())) {
			int step = cursorPos;
			int i = cursorPos + 1;
			for (; i <= static_cast<int>(value.size()); i++) {
				if (!isspace(value.at(i - 1))) break;
				step = i;
			}
			for (; i <= static_cast<int>(value.size()); i++) {
				if (isspace(value.at(i - 1))) break;
				step = i;
			}
			if (step == cursorPos && step < static_cast<int>(value.size())) ++cursorPos;
			else
				cursorPos = step;
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_END)) {
		selectStart = -1;
		cursorPos = static_cast<int>(value.size());
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_END, GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		cursorPos = static_cast<int>(value.size());
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_HOME)) {
		selectStart = -1;
		cursorPos = 0;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_HOME, GLFW_MOD_SHIFT)) {
		if (selectStart == -1) selectStart = cursorPos;
		cursorPos = 0;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_ESCAPE)) {
		selectStart = -1;
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_V, GLFW_MOD_CONTROL)) {
		const char *clipboardContents = glfwGetClipboardString(Screen::getCurrentScreen()->window);
		if (clipboardContents) {
			const std::string output{clipboardContents};
			if (selectStart != -1) removeSelectedRegion();
			value.insert(cursorPos, output);
			cursorPos += static_cast<int>(output.size());
		}
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_C, GLFW_MOD_CONTROL) && selectStart != -1) {
		int selectStartPos = (std::min)(cursorPos, selectStart);
		int selectEndPos = (std::max)(cursorPos, selectStart);
		glfwSetClipboardString(Screen::getCurrentScreen()->window,
							   value.substr(selectStartPos, selectEndPos - selectStartPos).c_str());
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_X, GLFW_MOD_CONTROL) && selectStart != -1) {
		int selectStartPos = (std::min)(cursorPos, selectStart);
		int selectEndPos = (std::max)(cursorPos, selectStart);
		glfwSetClipboardString(Screen::getCurrentScreen()->window,
							   value.substr(selectStartPos, selectEndPos - selectStartPos).c_str());
		removeSelectedRegion();
	}
	if (GestureDetector::isKeyPressedOrRepeat(GLFW_KEY_A, GLFW_MOD_CONTROL)) {
		selectStart = 0;
		cursorPos = static_cast<int>(value.size());
	}
	auto child = getChild()->getKey()->getAs<Text>();
	float cursorXPos = child->calculateSizeFor(value.substr(0, cursorPos)).x;
	// Check if the cursor is going out of bounds on the right
	if (cursorXPos - horizontalScroll > getSize().x) {
		horizontalScroll = cursorXPos - getSize().x;
	}
	// Check if the cursor is going out of bounds on the left
	if (cursorXPos - horizontalScroll < 0) {
		horizontalScroll = cursorXPos;
	}
	// Check if there is empty non whitespace space on the right of the text
	auto valueSize = child->calculateSizeFor(value);
	if (horizontalScroll + getSize().x > valueSize.x) {
		horizontalScroll = valueSize.x - getSize().x;
		horizontalScroll = horizontalScroll < 0 ? 0 : horizontalScroll;
	}


	if (valueCopy != value) {
		child->setText(value);
		if (onChange) onChange(value);
	}
}

void TextInput::draw() {
	auto pos = getPos() + getMargin().getTopLeft();
	auto &canvas = Screen::getCurrentScreen()->canvas;

	canvas->PushAxisAlignedClip(getContentRect(), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	auto child = getChild()->getKey()->getAs<Text>();
	child->setPos(pos.withXOffset(-horizontalScroll));
	child->draw();

	if (!gd.active) {
		canvas->PopAxisAlignedClip();
		return;
	}

	if (selectStart != -1) {
		int selectStartPos = (std::min)(cursorPos, selectStart);
		int selectEndPos = (std::max)(cursorPos, selectStart);

		auto leftMargin = selectText->calculateSizeFor(value.substr(0, selectStartPos)).x;
		selectText->setText(value.substr(selectStartPos, selectEndPos - selectStartPos));
		selectText->setParent(this);
		selectText->update();

		auto selectPos = pos.withXOffset(leftMargin - horizontalScroll);

		ID2D1SolidColorBrush *brush = nullptr;
		canvas->CreateSolidColorBrush(Color::fromRGB255(0, 120, 215), &brush);
		canvas->FillRectangle(Rect::fromPosSize(selectPos, selectText->getSize()), brush);

		selectText->setPos(selectPos);
		selectText->draw();

		brush->Release();
	}

	ID2D1SolidColorBrush *cursorBrush = nullptr;
	canvas->CreateSolidColorBrush(cursorColor, &cursorBrush);

	canvas->PopAxisAlignedClip();

	float cursorXPos = child->calculateSizeFor(value.substr(0, cursorPos)).x - horizontalScroll;
	Rect r{
		pos.x + cursorXPos - 1,
		pos.y,
		pos.x + cursorXPos + 1,
		pos.y + child->getSize().y,
	};
	canvas->FillRectangle(r, cursorBrush);
	cursorBrush->Release();
}

void TextInput::setActive() {
	gd.active = true;
}
