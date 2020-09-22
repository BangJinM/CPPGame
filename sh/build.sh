sh build_crossguid.sh
sh build_glfw.sh
sh build_OpenGEX.sh
sh build_glm.sh
sh build_freetype.sh

mkdir -p ../build
pushd ../build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
popd
