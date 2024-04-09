#include "coingameobject.h"

namespace game {
	CoinGameObject::CoinGameObject(const glm::vec3& position, TextureManager* manager, int texture)
		: CollectableGameObject(position, manager, texture) {
		
		width_ = 0.2f;
		height_ = 0.2f;

		SetCollisionMaskInBit(GameObject::COIN, true);
		SetCollisionMaskOutBit(GameObject::PLAYER_BODY, true);
	}

	void CoinGameObject::Update(double delta_time) {
		CollectableGameObject::Update(delta_time);
	}
}
