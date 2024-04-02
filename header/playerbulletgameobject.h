#ifndef PLAYER_BULLET_GAME_OBJECT_H_
#define PLAYER_BULLET_GAME_OBJECT_H_

#include "projectile_game_object.h"

namespace game {
    // Inherits from GameObject
    class PlayerBulletGameObject : public GameObject {
    
        public:
            PlayerBulletGameObject(const glm::vec3& position, TextureManager* textureManager, int texture);

            virtual void Update(double delta_time) override;
    }
}

#endif