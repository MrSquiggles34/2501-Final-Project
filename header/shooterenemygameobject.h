#ifndef SHOOTER_ENEMY_GAME_OBJECT_H_
#define SHOOTER_ENEMY_GAME_OBJECT_H_

#include "enemygameobject.h"
#include "shootinggameobject.h"

namespace game {
	class ShooterEnemyGameObject : public EnemyGameObject, public ShootingGameObject {
		public:
			ShooterEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture, GameObject* target);
			
			virtual void Update(double delta_time) override;
			
			virtual ProjectileGameObject* CreateProjectile() override;
		protected:
			GameObject* targetObj_;
	};
}

#endif
