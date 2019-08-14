#ifndef CLASSIDS_H_
#define CLASSIDS_H_

#define ClassID(x)                CLASS_##x
#define	DefineClassID(x,classID)  ClassID(x) = classID,

// Runtime classIDs are kept intentionally small.
enum ClassIDType
{
	DefineClassID  (Undefined			,-1)
	DefineClassID  (SpriteRenderer		, 1)
	DefineClassID  (Transform			, 2)
	DefineClassID  (BaseRenderer		, 3)
	DefineClassID  (Camera				, 4)	
};

//make sure people dont accidentally define classids in other files:
#undef DefineClassID

#endif
