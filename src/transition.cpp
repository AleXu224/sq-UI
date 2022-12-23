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

TransitionData::TransitionData(float &value, float &duration, Curve &curve)
	: value(value),
	  duration(duration),
	  curve(curve) {}

void TransitionData::to(const float &newValue) {
	if (newValue == targetValue && value == targetValue) return;

	if (newValue == startValue) {
		startValue = targetValue;
		targetValue = newValue;
		progress = 1 - progress;
		transitionStartTime = std::chrono::high_resolution_clock::now() - std::chrono::microseconds(static_cast<int>(duration * progress * 1000));
	} else {
		startValue = setValue;
		targetValue = newValue;
		progress = 0;
		transitionStartTime = std::chrono::high_resolution_clock::now();
	}
	value = setValue;
}

void TransitionData::update() {
	if (progress >= 1 && value == targetValue && setValue == targetValue) return;
	Screen::getCurrentScreen()->animationRunning();

	// If the value was changed outside of the transition then update the target value
	if (value != setValue) to(value);

	if (duration == 0)
		progress = 1;
	else
		progress = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - transitionStartTime).count() / duration;

	progress = std::clamp(progress, 0.0f, 1.0f);

	value = startValue + (targetValue - startValue) * curve(progress);
	setValue = value;
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

void Transition::addWatch(float &value) {
	watchList.emplace_back(value, duration, curve);
}

void Transition::clear() {
	watchList.clear();
}
