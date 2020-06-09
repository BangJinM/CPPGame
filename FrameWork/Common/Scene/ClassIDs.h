#ifndef Gameengine_Common_Scene_CLASSIDS_H_
#define Gameengine_Common_Scene_CLASSIDS_H_

#define ClassID(x)                CLASS_##x
#define	DefineClassID(x,classID)  ClassID(x) = classID,

// Runtime classIDs are kept intentionally small.
enum ClassIDType
{
	DefineClassID  (Undefined			,-1)
	DefineClassID  (Mesh        		, 1)
	DefineClassID  (Material			, 2)
};

//make sure people dont accidentally define classids in other files:
#undef DefineClassID

#endif
