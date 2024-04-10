#ifndef SPAWNER_GAME_OBJECT_H_
#define SPAWNER_GAME_OBJECT_H_

#include "gameobject.h"
#include <vector>
#include <unordered_map>

namespace game {
    class SpawnerGameObject : public GameObject {
    private:
        std::unordered_map<int, double> lastSpawnTimes_; // Track the time of the last spawn for each object type
        std::unordered_map<int, double> spawnIntervals_; // Interval between spawns for each object type
        std::unordered_map<int, glm::vec3> spawnLocations_; // Locations where objects can spawn

    public:
        // Constructor
        SpawnerGameObject(glm::vec3 position, TextureManager* textureManager);

        // Destructor
        ~SpawnerGameObject();

        // Method to add spawn parameters for an object type
        void AddSpawnParameters(int objectType, double spawnInterval, glm::vec3 spawnLocation);

        // Override the Update method to handle spawning logic
        void Update(double delta_time) override;

    private:
        // Method to spawn objects of a given type
        void SpawnObject(int objectType);
    };
}

#endif // SPAWNER_GAME_OBJECT_H_
