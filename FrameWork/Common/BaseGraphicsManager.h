#pragma once

#include <list>
#include <memory>

#include "Config.h"
#include "Renderer.h"
#include "IRuntimeModule.h"
#include "Render/IDrawPass.h"
#include "Material.h"
#include "Mesh.h"
GameEngineBegin

	class Scene;

struct RendererCammand
{
	Material material;
	SharedMesh mesh;
	int index;
};

class BaseGraphicsManager : public IRuntimeModule
{
public:
	virtual ~BaseGraphicsManager() {}

	virtual int Initialize();
	virtual void Finalize();

	virtual void Tick();
	virtual void Clear();
	virtual void Draw();

	void addRendererCommand(RendererCammand command);
	std::list<RendererCammand> getRendererCommand();

	virtual void PrepareMesh(SharedMesh mesh, int index) = 0;
	virtual void BindTexture(SharedTexture texture) = 0;
	virtual void PrepareMaterial(Material &material) = 0;

protected:
	std::list<RendererCammand> m_RendererCommands;
	std::list<std::shared_ptr<IDrawPass>> m_IDrawPass;
};

extern BaseGraphicsManager *g_pGraphicsManager;
GameEngineEnd
