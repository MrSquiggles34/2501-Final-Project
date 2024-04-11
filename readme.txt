Game Controls

WASD for movement
Space to shoot
Tab to swap weapons


How to play

Move around, dodge the enemies and their attacks, and get as high a score as possible.


Design Requirements

 - Meaningful gameplay and a meaningful ending condition: The game ends when the player loses all of their lives, and the player seeks to acquire the highest score they can before this happens.
 - At least 3 different enemy types: A "shooter" enemy, that attacks from a distance; a "chaser" enemy that tries to get close to you, then explodes; and a "hazard" enemy that makes its way across the screen, acting as an environmental challenge.
 - Two different weapons: A long range torpedo and a short-range "blast" weapon.
 - Collectibles: A 5s invincibility powerup, a score boosting coin, and an extra life heart.


Technical Requirements

 - All movement handled through transformations: GameObject::Render() and all its overrides operate through transformations.
 - Use of both physically-based and parametrically-based motion: Most things in the game move using physics-based motion, but there is a "hazard" enemy that moves across the screen using parametric motion.
 - Collision detection between game objects: Yup. This is handled by GameObject::IsCollidingWith(), GameObject::OnCollisionWith(), and their related functions. The gameobjects use two bitmasks to determine both what the object *is* (from a collisions perspective), and what the object collides with.
 - At least two instances of particle systems: The "chase" enemy and secondary weapon both use particle systems to display.
 - Advanced methods: Steering behaviours: Not sure if this counts, but the ShooterEnemyGameObject has a fairly complex AI for what it does. It will attempt to pursue the player, but remain at least a certain distance away from you, fleeing if you get closer.
