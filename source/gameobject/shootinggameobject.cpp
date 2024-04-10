#include "shootinggameobject.h"

namespace game {
	ShootingGameObject::ShootingGameObject(double delay, BulletType bulletType) {
		shotDelay_ = delay;
		type_ = bulletType;
	}
}
