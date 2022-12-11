#ifndef SQ_UI_KEY_HPP
#define SQ_UI_KEY_HPP

#include "stdexcept"
#include "type_traits"

namespace squi {
	class Widget;
}

namespace squi {
	class Key {
		bool isExpired = false;
		bool isInitialized = false;
		Widget *widget = nullptr;

	public:
		template<typename T>
		[[nodiscard]] T *getAs() const {
			static_assert(std::is_base_of<Widget, T>::value, "T must be a widget");
			if (isInitialized && !isExpired) {
				return dynamic_cast<T *>(widget);
			} else {
				if (!isInitialized) throw std::runtime_error("Key has not been intialized yet, can't get value");
				throw std::runtime_error("Key has expired, can't return content");
			}
		};

		[[nodiscard]] Widget *get() const {
			if (isInitialized && !isExpired) {
				return widget;
			} else {
				if (!isInitialized) throw std::runtime_error("Key has not been intialized yet, can't get value");
				throw std::runtime_error("Key has expired, can't return content");
			}
		};

		void set(Widget *newWidget) {
			if (!isInitialized && !isExpired) {
				widget = newWidget;
				isInitialized = true;
			} else {
				if (isExpired) throw std::runtime_error("Can't set the value of an expired key");
				printf("WARNING: trying to set the value of an already set Key");
			}
		}

		void markExpired() {
			isExpired = true;
		}
	};
}// namespace squi


#endif//SQ_UI_KEY_HPP
