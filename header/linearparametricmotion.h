#ifndef LINEAR_PARAMETRIC_MOTION_H_
#define LINEAR_PARAMETRIC_MOTION_H_

#include "parametricmotion.h"

namespace game {
	class LinearParametricMotion : public ParametricMotion {
		public:
			LinearParametricMotion(glm::vec3 &delta);
			
			virtual glm::vec3 PositionAt(double t);
		protected:
			glm::vec3 motionDelta_;
	};
}

#endif
