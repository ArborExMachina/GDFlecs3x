
#ifndef GDCOMP_H
#define GDCOMP_H

#include <string.h>
#include <core/reference.h>
#include "flecs/flecs.h"

class GDComponent : public Reference {
	GDCLASS(GDComponent, Reference);

protected:
	static void _bind_methods();

public:
    flecs::entity gd_comp;

	GDComponent();
	~GDComponent();

    StringName GetTypeName();	
	int GetID();
};

#endif // SUMMATOR_H
