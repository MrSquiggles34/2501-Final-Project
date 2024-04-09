target_sources(${PROJ_NAME}
	PRIVATE
		gameobject.cpp
		playergameobject.cpp
		playerbulletgameobject.cpp
		projectilegameobject.cpp
		enemygameobject.cpp
		hazardenemygameobject.cpp
		collectablegameobject.cpp
		coingameobject.cpp
		powerupgameobject.cpp
		heartgameobject.cpp
		textgameobject.cpp
)

add_subdirectory(controllers)
