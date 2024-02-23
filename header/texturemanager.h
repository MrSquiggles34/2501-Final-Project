#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <iostream>
#include <vector>
#include "gametexture.h"

namespace game {
	class TextureManager {
		public:
			TextureManager();
			~TextureManager();
			inline void AddTexture(GameTexture* texture) {textures_.push_back(texture);}
			inline void AddTexture(Geometry* geom, Shader* shader, GLuint texture) {textures_.push_back(new GameTexture(geom, shader, texture));}
			inline GameTexture* GetTexture(int n) {
				std::cout << "Getting texture [" << n << "] of " << textures_.size() << " textures." << std::endl;
				return (n >= 0 && n < textures_.size()) ? textures_[n] : nullptr;
			}
		protected:
			std::vector<GameTexture*> textures_;
	};
}

#endif
