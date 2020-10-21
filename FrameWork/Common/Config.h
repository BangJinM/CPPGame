#pragma once

#include <memory>

#define GameEngineBegin namespace GameEngine {
#define GameEngineEnd } // namespace GameEngine

#define UseGameEngine using namespace GameEngine;

GameEngineBegin

class Object;
class GameObject;
class Material;
class Mesh;
class Texture;
class Widget;
class Renderer;

#define SharePtr SharePtr
#define SharedObject SharePtr<Object>
#define SharedGameObject SharePtr<GameObject>
#define SharedMaterial SharePtr<Material>
#define SharedMesh SharePtr<Mesh>
#define SharedTexture SharePtr<Texture>

GameEngineEnd