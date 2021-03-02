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

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(MyGame PRIVATE 
    glfw 
    glad::glad 
    Framework
    imgui::imgui
) 
