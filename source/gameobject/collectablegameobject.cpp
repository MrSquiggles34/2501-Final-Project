#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "collectablegameobject.h"

namespace game {
	CollectableGameObject::CollectableGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: GameObject(position, manager, texture) {
	}
}
