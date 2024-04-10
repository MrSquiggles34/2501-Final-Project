#include "shooterenemygameobject.h"

namespace game {
	ShooterEnemyGameObject::ShooterEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture, GameObject* target)
	 : EnemyGameObject(position, manager, texture),
	   ShootingGameObject(0.5, ShootingGameObject::ENEMY_BULLET) {
		targetObj_ = target;
		SetCollisionMaskInBit(GameObject::ENEMY_BODY_SHOOTER, true);
	}
	
	void ShooterEnemyGameObject::Update(double delta_time) {
		glm::vec3 deltaToTarget = position_;
		glm::vec3 motion(deltaToTarget.x, 0.0f, 0.0f);
		if (glm::length(deltaToTarget) > 40.0f) {
			// Evasive maneuvers
			motion.y = -deltaToTarget.y;
		}
		if (deltaToTarget.x < 8.0f) {
			// If you're close on the horizontal, shoot.
			SetIsShooting(true);
		}
		motion = glm::normalize(motion);
		AddMotion(motion);
		GameObject::Update(delta_time);
	}
}
