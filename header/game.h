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
#include "hazardenemygameobject.h"
#include "shooterenemygameobject.h"
#include "chaserenemygameobject.h"
#include "linearparametricmotion.h"
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
			
			double lastEnemySpawnTime_ = 0.0;
			double enemySpawnInterval_ = 8.0;
			
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
				
				void SpawnEnemy() {
					float posX = static_cast<float>((std::rand() % 600 - 300)) / 100.0f;
					
					int enemyType = (std::rand() % 3);
					
					EnemyGameObject* enemy;
					glm::vec3 enemyPos(posX, 8.0f, 0.0f);
					glm::vec3 motionVec;
					
					switch (enemyType) {
						case 0: // Parametric Motion Enemy
							motionVec = glm::normalize(glm::vec3(-2* posX, -16.0f, 0.0f));
							enemy = new HazardEnemyGameObject(enemyPos, &textureManager_, 2, new LinearParametricMotion(motionVec));
							break;
						case 1: // Shooter Enemy
							enemy = new ShooterEnemyGameObject(enemyPos, &textureManager_, 2, player_);
							break;
						case 2: // Chaser Enemy
							enemy = new ChaserEnemyGameObject(enemyPos, &textureManager_, 2, player_);
							break;
					}
					gameObjects_.push_back(enemy);
				}
	};
}

#endif // GAME_H_
