#ifndef HEART_GAME_OBJECT_H_
#define HEART_GAME_OBJECT_H_

#include "collectablegameobject.h"

namespace game {
	class HeartGameObject : public CollectableGameObject {
		public:
			HeartGameObject(const glm::vec3& position, TextureManager* manager, int texture);
	};
}




#endif
