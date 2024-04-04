#ifndef HAZARD_ENEMY_GAME_OBJECT_H_
#define HAZARD_ENEMY_GAME_OBJECT_H_

#include "enemygameobject.h"

namespace game {
	class HazardEnemyGameObject : public EnemyGameObject {
		public:
			HazardEnemyGameObject(const glm::vec3 &position, TextureManager* manager, int texture);
			
			virtual void Update(double delta_time);
	};
}

#endif
