#ifndef SQ_UI_TRANSITION_HPP
#define SQ_UI_TRANSITION_HPP

#include "functional"
#include "unordered_map"
#include "chrono"
#include "variant"
#include "vec2.hpp"
#include "margin.hpp"
#include "color.hpp"
#include "border.hpp"

namespace squi {
	typedef std::vector<std::variant<float*, vec2*, Margin*, Color*, Border*>> TransitionValues;
	typedef std::function<float(float t)> Curve;

	struct TransitionCurves {
		static const Curve linear;
		static const Curve easeInOut;
	};

	class TransitionData {
		// The actual value that will be affected by the transition
		float *value;
		// The duration in miliseconds that the transition will take
		std::chrono::duration<float> &duration;
		// The curve that will be used to calculate the transition
		Curve &curve;
		// The value that the transition started from
		float startValue{*value};
		// The value that the transition is going to
		float targetValue{*value};
		// The value that the transition set the value to last time
		// Will be used to detect if there was an outside change to the value
		float setValue{*value};
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<float>> transitionStartTime = std::chrono::high_resolution_clock::now();
		// The progress of the transition
		float progress{1};

	public:
		TransitionData(float *value, std::chrono::duration<float> &duration, Curve &curve);

		void to(const float &newValue);

		void update();

		bool isFinised();
	};

	using namespace std::chrono_literals;
	struct TransitionArgs {
		bool enabled{false};
		std::chrono::duration<float> duration = 0ms;
		Curve curve{TransitionCurves::linear};
	};

	class Transition {
	private:
		std::vector<TransitionData> watchList{};

	public:
		bool enabled;
		std::chrono::duration<float> duration;
		Curve curve;

		Transition() : enabled(false), duration(0), curve(TransitionCurves::linear) {}
		explicit Transition(const TransitionArgs &args)
			: enabled(args.enabled), duration(args.duration), curve(args.curve) {}

		void update();

		void addWatch(float *value);
		void addWatch(vec2 *value);
		void addWatch(Margin *value);
		void addWatch(Color *value);
		void addWatch(Border *value);
		void addWatch(const TransitionValues &values);

		void only(const TransitionValues &values);

		void clear();
	};
}// namespace squi

#endif//SQ_UI_TRANSITION_HPP
