#ifndef SQ_UI_PERFORMANCEOVERLAY_HPP
#define SQ_UI_PERFORMANCEOVERLAY_HPP

#include "../overlay.hpp"
#include "align.hpp"
#include "box.hpp"

namespace squi {
	class PerformanceOverlay : public Overlay {
		bool shouldDraw = false;
	public:
		PerformanceOverlay();

		void update() override;

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_PERFORMANCEOVERLAY_HPP
