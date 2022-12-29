#include <utility>

#include "../include/widget.hpp"
using namespace squi;

int Widget::instances = 0;

WidgetData &Widget::getData() {
	if (contentType == WidgetContentType::invisibleWithChild) {
		if (auto child = getChild()) return child->getData();
	}
	return m_data;
}

const WidgetData &Widget::getData() const {
	if (contentType == WidgetContentType::invisibleWithChild) {
		if (auto child = getChild()) return child->getData();
	}
	return m_data;
}

const vec2 &Widget::getSize() const {
	return getData().size;
}

const Margin &Widget::getMargin() const {
	return getData().margin;
}

const Margin &Widget::getPadding() const {
	return getData().padding;
}

void Widget::setSize(const vec2 &v) {
	getData().size = v;
}

void Widget::setMargin(const Margin &m) {
	getData().margin = m;
}

void Widget::setPadding(const Margin &m) {
	getData().padding = m;
}

const vec2 &Widget::getPos() const {
	return m_pos;
}

void Widget::setPos(const vec2 &p) {
	m_pos = p;
}

Widget *Widget::getParent() const {
	return m_parent;
}

void Widget::setParent(Widget *p) {
	if (p) m_parent = p;
}

vec2 Widget::getContentSize() const {
	return getSize() - getPadding().getHorizontalVectical();
}

vec2 Widget::getLayoutSize() const {
	return getSize() + getMargin().getHorizontalVectical();
}

Rect Widget::getRect() const {
	return Rect::fromPosSize(getPos() + getMargin().getTopLeft(), getSize());
}

Rect Widget::getContentRect() const {
	return Rect::fromPosSize(getPos() + getMargin().getTopLeft() + getPadding().getTopLeft(), getSize() - getPadding().getHorizontalVectical());
}

Rect Widget::getLayoutRect() const {
	return Rect::fromPosSize(getPos(), getSize() + getMargin().getHorizontalVectical() + getPadding().getHorizontalVectical());
}

const std::shared_ptr<Key> &Widget::getKey() const {
	return m_data.key;
}

const vec2 &Widget::getSizeHint() const {
	return sizeHint;
}

void Widget::setSizeHint(const vec2 &s) {
	sizeHint = s;
}

std::shared_ptr<Widget> &Widget::getChild() {
	if (contentType != WidgetContentType::singleChild && contentType != WidgetContentType::invisibleWithChild) throw std::runtime_error("Child is not of singleChild contentType");
	return m_child;
}

const std::shared_ptr<Widget> &Widget::getChild() const {
	if (contentType != WidgetContentType::singleChild && contentType != WidgetContentType::invisibleWithChild) throw std::runtime_error("Child is not of singleChild contentType");
	return m_child;
}

std::vector<std::shared_ptr<Widget>> Widget::getChildren() const {
	if (contentType != WidgetContentType::multipleChildren) throw std::runtime_error("Child is not of multipleChildren contentType");

	return m_children;
}

const WidgetContentType &Widget::getChildCountType() const {
	return contentType;
}

void Widget::setChild(std::shared_ptr<Widget> c) {
	if (contentType != WidgetContentType::singleChild && contentType != WidgetContentType::invisibleWithChild)
		throw std::runtime_error("Child is not of singleChild contentType");

	m_child = std::move(c);
	if (contentType == WidgetContentType::invisibleWithChild && m_child) {
		m_child->overrideData(m_data);
	}
}

void Widget::setChild(const Child &child) {
	if (contentType != WidgetContentType::singleChild && contentType != WidgetContentType::invisibleWithChild)
		throw std::runtime_error("Child is not of singleChild contentType");

	m_child = child;
	if (contentType == WidgetContentType::invisibleWithChild && m_child) {
		m_child->overrideData(m_data);
	}
}

void Widget::setChildren(std::vector<std::shared_ptr<Widget>> c) {
	if (contentType != WidgetContentType::multipleChildren) throw std::runtime_error("Child is not of multipleChildren contentType");

	m_children = std::move(c);
}

void Widget::shrinkWrapWidget() {
	auto padding = getPadding().getHorizontalVectical();
	auto &data = getData();
	if (sizeHint.x == -1)
		if (data.expand != Axis::horizontal && data.expand != Axis::both)
			if (data.shrinkWrap == Axis::horizontal || data.shrinkWrap == Axis::both)
				data.size.x = m_child->getLayoutSize().x + padding.x;

	if (sizeHint.y == -1)
		if (data.expand != Axis::vertical && data.expand != Axis::both)
			if (data.shrinkWrap == Axis::vertical || data.shrinkWrap == Axis::both)
				data.size.y = m_child->getLayoutSize().y + padding.y;
}

void Widget::expandWidget() {
	auto margin = getMargin().getHorizontalVectical();
	if (sizeHint.x == -1)
		if (getData().expand == Axis::horizontal || getData().expand == Axis::both)
			getData().size.x = m_parent->getContentSize().x - margin.x;

	if (sizeHint.y == -1)
		if (getData().expand == Axis::vertical || getData().expand == Axis::both)
			getData().size.y = m_parent->getContentSize().y - margin.y;
}

void Widget::getHintedSize() {
	if (sizeHint.x != -1) getData().size.x = sizeHint.x;
	if (sizeHint.y != -1) getData().size.y = sizeHint.y;
	// Reset the size hint
	sizeHint = vec2{-1, -1};
}

void Widget::customUpdate() {
	hasCustomUpdate = false;
}

void Widget::update() {// NOLINT(misc-no-recursion)
	hasCustomUpdate = true;
	customUpdate();
	if (hasCustomUpdate) return;

	switch (contentType) {
		case WidgetContentType::none: {
			expandWidget();
			getHintedSize();
			updateBeforeChild();
			transition.update(getKey());
			return;
		}
		case WidgetContentType::singleChild: {
			if (m_parent != nullptr) expandWidget();
			getHintedSize();

			updateBeforeChild();
			if (m_child) {
				m_child->setParent(this);
				m_child->update();
				shrinkWrapWidget();
			}
			updateAfterChild();
			transition.update(getKey());
			
			return;
		}
		case WidgetContentType::invisibleWithChild: {
			updateBeforeChild();
			if (m_child) {
				m_child->setParent(getParent());
				m_child->update();
			}
			updateAfterChild();
			transition.update(getKey());
			return;
		}
		case WidgetContentType::multipleChildren: {
			if (m_parent != nullptr) expandWidget();
			getHintedSize();
			updateBeforeChild();

			for (auto &childPtr: m_children) {
				if (!childPtr) continue;
				childPtr->setParent(this);
				childPtr->update();
			}
			updateAfterChild();
			transition.update(getKey());
			return;
		}
	}
}

void Widget::draw() {// NOLINT(misc-no-recursion)
	switch (contentType) {
		case WidgetContentType::none: {
			return;
		}
		case WidgetContentType::singleChild: {
			auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

			if (auto child = getChild()) {
				child->setPos(pos);
				child->draw();
			}
			return;
		}
		case WidgetContentType::invisibleWithChild: {
			if (auto child = getChild()) {
				child->setPos(getPos());
				child->draw();
			}
			return;
		}
		case WidgetContentType::multipleChildren: {
			auto pos = getPos() + getMargin().getTopLeft() + getPadding().getTopLeft();

			auto children = getChildren();

			for (auto &child: children) {
				child->setPos(pos);
				child->draw();
			}
			return;
		}
	}
}

// TODO: should instead get the hitcheck rects of the child
// Only things like Boxes should actually return a hitcheck rect in practice
std::vector<Rect> Widget::getHitcheckRects() const {
	switch (contentType) {
		case WidgetContentType::none: {
			return {};
		}
		default: {
			if (getData().passThrough) return {};
			return {getRect()};
		}
	}
}

const Axis &Widget::getShrinkWrap() const {
	return getData().shrinkWrap;
}

const Axis &Widget::getExpand() const {
	return getData().expand;
}

const TransitionArgs &Widget::getTransitionArgs() const {
	return getData().transition;
}

Transition &Widget::getTransition() {
	return transition;
}

const bool &Widget::getPassThough() const {
	return getData().passThrough;
}

void Widget::setPassThrough(const bool &p) {
	getData().passThrough = p;
}

void Widget::overrideData(const WidgetData &newData) {
	m_data.overrideFrom(newData);
	transition = Transition{m_data.transition};

	if (contentType == WidgetContentType::invisibleWithChild) {
		if (auto child = getChild()) {
			child->overrideData(newData);
		}
	}
}

WidgetData WidgetData::withKey(std::shared_ptr<Key> newKey) const {
	auto ret = *this;
	ret.key = newKey;
	return ret;
}

WidgetData WidgetData::withSize(const vec2 &newSize) const {
	auto ret = *this;
	ret.size = newSize;
	return ret;
}

WidgetData WidgetData::withMargin(const Margin &newMargin) const {
	auto ret = *this;
	ret.margin = newMargin;
	return ret;
}

WidgetData WidgetData::withPadding(const Margin &newPadding) const {
	auto ret = *this;
	ret.padding = newPadding;
	return ret;
}

WidgetData WidgetData::withShrinkWrap(const Axis &newShrinkWrap) const {
	auto ret = *this;
	ret.shrinkWrap = newShrinkWrap;
	return ret;
}

WidgetData WidgetData::withExpand(const Axis &newExpand) const {
	auto ret = *this;
	ret.expand = newExpand;
	return ret;
}

WidgetData WidgetData::withPassThrough(const bool &newPassThrough) const {
	auto ret = *this;
	ret.passThrough = newPassThrough;
	return ret;
}

WidgetData WidgetData::withTransition(const TransitionArgs &newTransition) const {
	auto ret = *this;
	ret.transition = newTransition;
	return ret;
}

void WidgetData::initializeTransition(Transition &transition) {
	transition.addWatch(TransitionValues{&size, &margin, &padding});
	// transition.addWatch(&size);
	// transition.addWatch(&margin);
	// transition.addWatch(&padding);
}

void WidgetData::overrideFrom(const WidgetData &rhs) {
	WidgetData defaultData{};
	if (rhs.size.x != defaultData.size.x) size.x = rhs.size.x;
	if (rhs.size.y != defaultData.size.y) size.y = rhs.size.y;

	if (rhs.margin.top != defaultData.margin.top) margin.top = rhs.margin.top;
	if (rhs.margin.right != defaultData.margin.right) margin.right = rhs.margin.right;
	if (rhs.margin.bottom != defaultData.margin.bottom) margin.bottom = rhs.margin.bottom;
	if (rhs.margin.left != defaultData.margin.left) margin.left = rhs.margin.left;

	if (rhs.padding.top != defaultData.padding.top) padding.top = rhs.padding.top;
	if (rhs.padding.right != defaultData.padding.right) padding.right = rhs.padding.right;
	if (rhs.padding.bottom != defaultData.padding.bottom) padding.bottom = rhs.padding.bottom;
	if (rhs.padding.left != defaultData.padding.left) padding.left = rhs.padding.left;

	if (rhs.shrinkWrap != defaultData.shrinkWrap) shrinkWrap = rhs.shrinkWrap;
	if (rhs.expand != defaultData.expand) expand = rhs.expand;
	if (rhs.passThrough != defaultData.passThrough) passThrough = rhs.passThrough;

	if (rhs.transition.duration != defaultData.transition.duration) transition.duration = rhs.transition.duration;
	if (rhs.transition.curve.target_type() != defaultData.transition.curve.target_type()) transition.curve = rhs.transition.curve;
}
