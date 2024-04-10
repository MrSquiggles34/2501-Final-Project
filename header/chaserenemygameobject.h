#ifndef CHASER_ENEMY_GAME_OBJECT_H_
#define CHASER_ENEMY_GAME_OBJECT_H_

#include "enemygameobject.h"

namespace game {
	class ChaserEnemyGameObject : public EnemyGameObject {
		public:
			ChaserEnemyGameObject(const glm::vec3 &position, TextureManager *manager, int texture);
			
			virtual void Update(double delta_time) override;
	};
}

#endif
