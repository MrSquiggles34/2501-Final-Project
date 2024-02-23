#include "texturemanager.h"

namespace game {
	TextureManager::TextureManager() {}
	
	TextureManager::~TextureManager() {
		for (int i = 0; i < textures_.size(); i++) {
			delete textures_[i];
		}
	}
}
