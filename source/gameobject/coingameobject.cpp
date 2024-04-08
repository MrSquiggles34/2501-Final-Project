
#include "coingameobject.h"

namespace game {
	CoinGameObject::CoinGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: CollectableGameObject(position, manager, texture) {
		
		SetCollisionMaskInBit(GameObject::COIN, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
	}
}
