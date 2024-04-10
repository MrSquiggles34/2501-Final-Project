#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib> 
#include <ctime>   

#include "gameobject.h"
#include "playergameobject.h"
#include "texturemanager.h"
#include "coingameobject.h"
#include "heartgameobject.h"
#include "powerupgameobject.h"
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
			Geometry* particles_;

			Shader spriteShader_;
			Shader particleShader_;
			Shader textShader_;
			
			GLFWwindow* window_;
			
			static void ResizeCallback(GLFWwindow *window, int width, int height);
			
			TextureManager textureManager_;
			GLuint* tex_;
			
			std::vector<GameObject*> gameObjects_;
			PlayerGameObject* player_;

			// Spawning items (I'm sorry)
			double lastCoinSpawnTime_ = 0.0; 
			double coinSpawnInterval_ = 11.0; 

			double lastHeartSpawnTime_ = 0.0; 
			double heartSpawnInterval_ = 60.0; 

			double lastPowerSpawnTime_ = 0.0;
			double powerSpawnInterval_ = 29.0;
			
			bool cycleWeaponButtonPressed_ = false;

			private:
				void SpawnCoin() {
					// Spawn a new coin object and add it to the gameObjects_ vector
					float posX = static_cast<float>((std::rand() % 600 - 300)) / 100.0f;

					CoinGameObject* coin = new CoinGameObject(glm::vec3(posX, 8.0f, 0.0f), &textureManager_, 4);
					gameObjects_.push_back(coin);
				}

				void SpawnHeart() {
					// Spawn a new coin object and add it to the gameObjects_ vector
					float posX = static_cast<float>((std::rand() % 600 - 300)) / 100.0f;

					HeartGameObject* heart = new HeartGameObject(glm::vec3(posX, 8.0f, 0.0f), &textureManager_, 5);
					gameObjects_.push_back(heart);
				}

				void SpawnPower() {
					// Spawn a new coin object and add it to the gameObjects_ vector
					float posX = static_cast<float>((std::rand() % 600 - 300)) / 100.0f;

					PowerUpGameObject* power = new PowerUpGameObject(glm::vec3(posX, 8.0f, 0.0f), &textureManager_, 6);
					gameObjects_.push_back(power);
				}
	};
}

#endif // GAME_H_
