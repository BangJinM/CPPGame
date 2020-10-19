#pragma once

#define ClassID(x) CLASS_##x
#define DefineClassID(x, classID) ClassID(x) = classID

// Runtime classIDs are kept intentionally small.
enum ClassIDType
{
	DefineClassID(Undefined, -1),
	DefineClassID(RendererCommand, 1),
	DefineClassID(MeshRendererCommand, 2),
	DefineClassID(MeshDatas, 3),
	DefineClassID(Transform, 5),
	DefineClassID(Camera, 6),
	DefineClassID(Light, 7),
	DefineClassID(CanvasRenderer, 8),
	DefineClassID(Widget, 9),
};

//make sure people dont accidentally define classids in other files:
#undef DefineClassID
