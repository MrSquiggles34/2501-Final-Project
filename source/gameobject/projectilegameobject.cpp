#include "projectilegameobject.h"

namespace game {

    ProjectileGameObject::ProjectileGameObject(const glm::vec3& position, TextureManager* manager, int texture)
        : GameObject(position, manager, texture), lifespanTimer_() {
    }

} // namespace game