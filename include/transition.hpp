#ifndef SQ_UI_TRANSITION_HPP
#define SQ_UI_TRANSITION_HPP

#include "functional"
#include "unordered_map"
#include "chrono"

namespace squi {
	typedef std::function<float(float t)> Curve;

	struct TransitionCurves {
		static const Curve linear;
		static const Curve easeInOut;
	};

	class TransitionData {
		// The actual value that will be affected by the transition
		float &value;
		// The duration in miliseconds that the transition will take
		float &duration;
		// The curve that will be used to calculate the transition
		Curve &curve;
		// The value that the transition started from
		float startValue{value};
		// The value that the transition is going to
		float targetValue{value};
		// The value that the transition set the value to last time
		// Will be used to detect if there was an outside change to the value
		float setValue{value};
		std::chrono::steady_clock::time_point transitionStartTime = std::chrono::high_resolution_clock::now();
		// The progress of the transition
		float progress{1};

	public:
		TransitionData(float &value, float &duration, Curve &curve);

		void to(const float &newValue);

		void update();

		bool isFinised();
	};

	struct TransitionArgs {
		bool enabled{false};
		float duration{0};
		Curve curve{TransitionCurves::linear};
	};

	class Transition {
	private:
		std::vector<TransitionData> watchList{};

	public:
		bool enabled;
		float duration;
		Curve curve;

		Transition() : enabled(false), duration(0), curve(TransitionCurves::linear) {}
		explicit Transition(const TransitionArgs &args)
			: enabled(args.enabled), duration(args.duration), curve(args.curve) {}

		void update();

		void addWatch(float &value);

		void clear();
	};
}// namespace squi

#endif//SQ_UI_TRANSITION_HPP
