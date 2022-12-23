#ifndef SQ_UI_PERFORMANCEOVERLAY_HPP
#define SQ_UI_PERFORMANCEOVERLAY_HPP

#include "../overlay.hpp"
#include "align.hpp"
#include "box.hpp"

namespace squi {
	class PerformanceOverlay : public Overlay {
		bool shouldDraw = false;
		std::shared_ptr<Key> fpsKey = std::make_shared<Key>();
		std::shared_ptr<Key> pollKey = std::make_shared<Key>();
		std::shared_ptr<Key> updateKey = std::make_shared<Key>();
		std::shared_ptr<Key> drawKey = std::make_shared<Key>();
		std::shared_ptr<Key> instancesKey = std::make_shared<Key>();
		double lastFpsUpdate = 0;
	public:
		PerformanceOverlay();

		void updateBeforeChild() override;

		void draw() override;
	};
}// namespace squi

#endif//SQ_UI_PERFORMANCEOVERLAY_HPP
