#include "hazardenemygameobject.h"

namespace game {
	HazardEnemyGameObject::HazardEnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture, ParametricMotion *controller)
	 : EnemyGameObject(position, manager, texture) {
		motionController_ = controller;
		currentTime_ = 0;
		origin_ = position;
		
		SetCollisionMaskInBit(GameObject::ENEMY_BODY_HAZARD, true);
	}
	
	HazardEnemyGameObject::~HazardEnemyGameObject() {
		delete motionController_;
	}
	
	void HazardEnemyGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);
		currentTime_ += delta_time;
		SetPosition(origin_ + motionController_->PositionAt(currentTime_));
	}
}
