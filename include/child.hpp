#ifndef SQUI_CHILD_HPP
#define SQUI_CHILD_HPP

#include "memory"
#include "vector"

namespace squi {
	class Widget;

	class Child {
		std::shared_ptr<Widget> m_child{};

	public:
		Child() = default;
		Child(Child &child) : m_child(child.m_child) {}
		Child(const Child &child) : m_child(child.m_child) {}
		Child(std::shared_ptr<Widget> child) : m_child(child) {}
	
		template<typename T>
		Child(T &&child) : m_child(std::make_shared<T>(std::move(child))) {
			static_assert(std::is_base_of<Widget, T>::value, "Child must be a Widget");
		}
		template<typename T>
		Child operator=(T &&child) {
			static_assert(std::is_base_of<A, T>::value, "Child must be a Widget");
			m_child = std::make_shared<T>(std::move(child));
			return *this;
		}


		Child operator=(const Child &child) {
			m_child = child.m_child;
			return *this;
		}

		operator std::shared_ptr<Widget>() const {
			return m_child;
		}
	};

	class Children {
		std::vector<std::shared_ptr<Widget>> m_children{};

	public:
		Children() = default;
		Children(std::vector<std::shared_ptr<Widget>> children) : m_children(children) {}
		Children(Children &children) : m_children(children.m_children) {}
		Children(const Children &children) : m_children(children.m_children) {}

		template<typename... T>
		Children(T &&...children) : m_children{std::make_shared<T>(std::move(children))...} {
			static_assert((std::is_base_of<Widget, T>::value && ...), "Children must be Widgets");
		}

		void add(Child child) {
			m_children.push_back(child);
		}

		operator std::vector<std::shared_ptr<Widget>>() const {
			return m_children;
		}
	};
}// namespace squi

#endif