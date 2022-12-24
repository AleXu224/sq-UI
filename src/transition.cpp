#include "../include/transition.hpp"
#include "../include/screen.hpp"
#include "algorithm"

using namespace squi;

const Curve TransitionCurves::linear = [](float t) {
	return t;
};

const Curve TransitionCurves::easeInOut = [](float t) {
	return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
};

TransitionData::TransitionData(float *value, std::chrono::duration<float> &duration, Curve &curve)
	: value(value),
	  duration(duration),
	  curve(curve) {}

void TransitionData::to(const float &newValue) {
	if (newValue == targetValue && *value == targetValue) return;

	if (newValue == startValue) {
		startValue = targetValue;
		targetValue = newValue;
		progress = 1 - progress;
		transitionStartTime = std::chrono::high_resolution_clock::now() - std::chrono::duration<float>(duration.count() * progress);
	} else {
		startValue = setValue;
		targetValue = newValue;
		progress = 0;
		transitionStartTime = std::chrono::high_resolution_clock::now();
	}
	*value = setValue;
}

void TransitionData::update() {
	if (progress >= 1 && *value == targetValue && setValue == targetValue) return;
	Screen::getCurrentScreen()->animationRunning();

	// If the value was changed outside of the transition then update the target value
	if (*value != setValue) to(*value);

	if (duration == 0ms)
		progress = 1;
	else
		progress = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - transitionStartTime).count() / duration.count();

	progress = std::clamp(progress, 0.0f, 1.0f);

	// If progress is 1 then the value should be set to the target value
	// Floating point errors can cause the value to be slightly off from the target value
	// And this can cause the transition to never finish
	if (progress >= 1) *value = targetValue;
	else *value = startValue + (targetValue - startValue) * curve(progress);
	setValue = *value;
}

bool TransitionData::isFinised() {
	return progress >= 1;
}

void Transition::update() {
	if (!enabled) return;

	for (auto &transition: watchList) {
		transition.update();
	}
}

void Transition::addWatch(float *value) {
	watchList.emplace_back(value, duration, curve);
}
void Transition::addWatch(vec2 *value) {
	watchList.emplace_back(&value->x, duration, curve);
	watchList.emplace_back(&value->y, duration, curve);
}
void Transition::addWatch(Margin *value) {
	watchList.emplace_back(&value->left, duration, curve);
	watchList.emplace_back(&value->top, duration, curve);
	watchList.emplace_back(&value->right, duration, curve);
	watchList.emplace_back(&value->bottom, duration, curve);
}
void Transition::addWatch(Color *value) {
	watchList.emplace_back(&value->r, duration, curve);
	watchList.emplace_back(&value->g, duration, curve);
	watchList.emplace_back(&value->b, duration, curve);
	watchList.emplace_back(&value->a, duration, curve);
}
void Transition::addWatch(Border *value) {
	watchList.emplace_back(&value->size, duration, curve);
	addWatch(&value->color);
}
void Transition::addWatch(const TransitionValues &values) {
	for (auto &v: values) {
		std::visit([&](auto &&arg) { addWatch(arg); }, v);
	}
}

void Transition::only(const TransitionValues &values) {
	clear();
	addWatch(values);
}

void Transition::clear() {
	watchList.clear();
}
