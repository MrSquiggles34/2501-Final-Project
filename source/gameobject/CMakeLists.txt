target_sources(${PROJ_NAME}
	PRIVATE
		gameobject.cpp
		lifespangameobject.cpp
		projectilegameobject.cpp
		shootinggameobject.cpp
		textgameobject.cpp
)

add_subdirectory(collectable)
add_subdirectory(controllers)
add_subdirectory(enemy)
add_subdirectory(player)
