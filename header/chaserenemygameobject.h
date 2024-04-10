#ifndef CHASER_ENEMY_GAME_OBJECT_H_
#define CHASER_ENEMY_GAME_OBJECT_H_

#include "enemygameobject.h"

namespace game {
	class ChaserEnemyGameObject : public EnemyGameObject {
		public:
			ChaserEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture, GameObject* target);
			
			virtual void Update(double delta_time) override;
			virtual void OnCollisionWith(GameObject* other) override;
			
			inline int GetExplosionState() const { return explosionState_; }
			void Explode();
		protected:
			GameObject* targetObj_;
			int explosionState_ = 0;
			double explosionCountdown_ = 3.0;
	};
}

#endif
