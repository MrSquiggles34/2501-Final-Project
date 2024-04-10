#include "lifespangameobject.h"

namespace game {
	LifespanGameObject::LifespanGameObject(const glm::vec3 &position, TextureManager *manager, int texture, double lifespan)
	 : GameObject(position, manager, texture), lifespanTimer_() {
		lifespanTimer_.Start(lifespan);
	}
	
	void LifespanGameObject::Update(double delta_time) {
		lifespanTimer_.Update(delta_time);
		if (lifespanTimer_.Finished()) {
			SetMarkedForDeletion(true);
		}
	}
}
