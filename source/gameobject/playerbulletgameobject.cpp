#include "player_bullet_game_object.h"

namespace game {

    PlayerBulletGameObject::PlayerBulletGameObject(const glm::vec3& position, TextureManager* textureManager, int texture)
        : GameObject(position, textureManager, texture) {
        
    }

    void PlayerBulletGameObject::Update(double delta_time) {

    }

} // namespace bullet