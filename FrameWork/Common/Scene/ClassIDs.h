#ifndef Gameengine_Common_Scene_CLASSIDS_H_
#define Gameengine_Common_Scene_CLASSIDS_H_

#define ClassID(x) CLASS_##x
#define DefineClassID(x, classID) ClassID(x) = classID

// Runtime classIDs are kept intentionally small.
enum ClassIDType
{
	DefineClassID(Undefined, -1),
	DefineClassID(RendererCommand, 1),
	DefineClassID(MeshRendererCommand, 2),
	DefineClassID(MeshDatas, 3),
	DefineClassID(Material, 4),
	DefineClassID(Transform, 5),
	DefineClassID(Camera, 6),
	DefineClassID(PointLight, 7),
	DefineClassID(AreaLight, 8),
	DefineClassID(SpotLight, 9),
	DefineClassID(DirectionalLight, 10),
};

//make sure people dont accidentally define classids in other files:
#undef DefineClassID

#endif
