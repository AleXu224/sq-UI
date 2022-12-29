#ifndef SQ_UI_KEY_HPP
#define SQ_UI_KEY_HPP

#include "stdexcept"
#include "type_traits"
#include "vector"

namespace squi {
	class Widget;
}

namespace squi {
	class Key {
		std::vector<Widget *> instances{};

	public:
		template<typename T>
		[[nodiscard]] T *getAs() const {
			static_assert(std::is_base_of<Widget, T>::value, "T must be a widget");
			if (instances.empty())
				throw std::runtime_error("Key has not been initialized yet or has expired");
			if (instances.size() == 1)
				return dynamic_cast<T *>(instances.at(0));
			else
				throw std::runtime_error("Widget has more than 1 instance, can't return content");
		};

		[[nodiscard]] Widget *get() const {
			if (instances.empty())
				throw std::runtime_error("Key has not been initialized yet or has expired");
			if (instances.size() == 1)
				return instances.at(0);
			else
				throw std::runtime_error("Widget has more than 1 instance, can't return content");
		};

		void reset(Widget *newWidget) {
			if (std::find(instances.begin(), instances.end(), newWidget) != instances.end())
				throw std::runtime_error("Key has already been set to this widget");

			instances.clear();
			instances.push_back(newWidget);
		}

		void set(Widget *newWidget) {
			if (std::find(instances.begin(), instances.end(), newWidget) != instances.end())
				throw std::runtime_error("Key has already been set to this widget");

			instances.push_back(newWidget);
		}

		void remove(Widget *widget) {
			if (std::find(instances.begin(), instances.end(), widget) == instances.end())
				return;

			instances.erase(std::remove(instances.begin(), instances.end(), widget), instances.end());
		}
	};
}// namespace squi


#endif//SQ_UI_KEY_HPP
