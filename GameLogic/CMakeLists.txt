set(GAMELOGIC_HEADER
	MyGameLogic.h
)
set(GAMELOGIC_SRC
	MyGameLogic.cpp
	GameLogicConfig.cpp
)

add_executable(MyGame 
    ${GAMELOGIC_HEADER}
    ${GAMELOGIC_SRC}
)

target_link_libraries(MyGame PRIVATE 
    Framework
) 
