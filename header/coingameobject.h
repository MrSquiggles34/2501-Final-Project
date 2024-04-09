#ifndef COIN_GAME_OBJECT_H_
#define COIN_GAME_OBJECT_H_

#include "collectablegameobject.h"

namespace game {
	class CoinGameObject : public CollectableGameObject {
	public:
		CoinGameObject(const glm::vec3& position, TextureManager* manager, int texture);

		void Update(double delta_time) override;

		// Getters


		// Setters


	private:

	};
}




#endif