#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "playergameobject.h"
#include "texturemanager.h"
#include "sprite.h"
#include "shader.h"
#include <vector>

namespace game {
	class Game {
		public:
			Game();
			~Game();
			
			void Init(void);
			void Setup(void);
			void Run(void);
		protected:
			// Run at start
			void LoadAllTextures();
			void SetTexture(GLuint w, const char* fname);
			
			// Run each frame
			void HandleUserInput();
			void Update(double delta_time);
			void Render();
			
			double currentTime_;
			
			Geometry* sprite_;
			Shader spriteShader_;
			
			GLFWwindow* window_;
			
			static void ResizeCallback(GLFWwindow *window, int width, int height);
			
			TextureManager textureManager_;
			GLuint* tex_;
			
			std::vector<GameObject*> gameObjects_;
			GameObject* player_;
	};
}

#endif // GAME_H_
