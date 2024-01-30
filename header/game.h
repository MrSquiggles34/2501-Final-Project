#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace game {
	class Game {
		public:
			Game();
			~Game();
			
			void Init(void);
			void Setup(void);
			void Run(void);
		protected:
			void HandleUserInput();
			
			GLFWwindow *window_;
			
			static void ResizeCallback(GLFWwindow *window, int width, int height);
	};
}

#endif // GAME_H_
