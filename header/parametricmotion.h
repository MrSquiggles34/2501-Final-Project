#ifndef PARAMETRIC_MOTION_H_
#define PARAMETRIC_MOTION_H_

#include <glm/glm.hpp>

namespace game {
	class ParametricMotion {
		public:
			virtual glm::vec3 PositionAt(double t) = 0;
	};
}

#endif
