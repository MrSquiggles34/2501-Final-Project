#include "shooterenemygameobject.h"
#include "enemybulletgameobject.h"

namespace game {
	ShooterEnemyGameObject::ShooterEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture, GameObject* target)
	 : EnemyGameObject(position, manager, texture),
	   ShootingGameObject(0.5, ShootingGameObject::ENEMY_BULLET) {
		targetObj_ = target;
		SetCollisionMaskInBit(GameObject::ENEMY_BODY_SHOOTER, true);
	}
	
	void ShooterEnemyGameObject::Update(double delta_time) {
		glm::vec3 deltaToTarget = targetObj_->GetPosition() - position_;
		glm::vec3 motion(0.0f);
		if (glm::abs(deltaToTarget.x) > 0.4f) {
			motion.x = deltaToTarget.x;
		}
		if (glm::length(deltaToTarget) < 3.0f) {
			// Evasive maneuvers
			motion.y = -deltaToTarget.y;
		}
		if (deltaToTarget.x < 1.0f) {
			// If you're close on the horizontal, shoot.
			SetIsShooting(true);
		}
		//std::cout << "Motion: " << motion.x << ", " << motion.y << std::endl;
		//std::cout << "Position: " << position_.x << ", " << position_.y << std::endl;
		if (motion.x != 0.0f || motion.y != 0.0f) {
			motion = glm::normalize(motion);
			AddMotion(motion);
		}
		GameObject::Update(delta_time);
	}
	
	ProjectileGameObject* ShooterEnemyGameObject::CreateProjectile() {
		float bulletOffset = -0.5f;
		glm::vec3 bulletPosition = position_ + glm::vec3(0.0f, bulletOffset, 0.0f);
		ProjectileGameObject* bullet;
		bullet = new EnemyBulletGameObject(bulletPosition, textureManager_, 1);
		return bullet;
	}
}
