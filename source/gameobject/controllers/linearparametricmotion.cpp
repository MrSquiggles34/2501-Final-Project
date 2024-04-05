#include "linearparametricmotion.h"

namespace game {
	LinearParametricMotion::LinearParametricMotion(glm::vec3 &delta) {
		motionDelta_ = delta;
	}
	
	glm::vec3 LinearParametricMotion::PositionAt(double t) {
		return motionDelta_ * ((float) t);
	}
}
