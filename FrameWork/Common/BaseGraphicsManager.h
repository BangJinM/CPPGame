#pragma once

#include <list>

#include "Config.h"
#include "Renderer.h"
#include "IRuntimeModule.h"

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

protected:
	std::list<RendererCammand> m_RendererCommands;
};

extern BaseGraphicsManager *g_pGraphicsManager;
GameEngineEnd
