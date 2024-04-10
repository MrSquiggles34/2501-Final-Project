#ifndef POWERUP_GAME_OBJECT_H_
#define POWERUP_GAME_OBJECT_H_

#include "collectablegameobject.h"

namespace game {
	class PowerUpGameObject : public CollectableGameObject {
		public:
			PowerUpGameObject(const glm::vec3& position, TextureManager* manager, int texture);
	};
}

#endif
