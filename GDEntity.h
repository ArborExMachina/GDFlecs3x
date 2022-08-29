
#ifndef GDENTITY_H
#define GDENTITY_H

#include <core/reference.h>
#include "flecs/flecs.h"

class GDComponent;

class GDEntity : public Reference {
	GDCLASS(GDEntity, Reference);

private:
// add a dictionary/map that maps a scriptable comp id to its corrasponding pair on this entity, then write a Get() method that takes a GDComp and returns the ScriptableData dictionary for it
protected:
	static void _bind_methods();

public:
	flecs::world* ecs;
	bool valid;
	flecs::entity e;
	GDEntity();
	~GDEntity();

	void Set(Ref<GDComponent> gdComp, Dictionary values);
	int GetID() const;
	String GetTypeID() const;
};

#endif // SUMMATOR_H
