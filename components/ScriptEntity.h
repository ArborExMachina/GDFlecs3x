#ifndef SCRIPTENTITY_H
#define SCRIPTENTITY_H

#include <core/dictionary.h>
#include "core/reference.h"
#include "../flecs/flecs.h"
#include "../GDEntity.h"

struct ScriptEntity
{
    public:
    Ref<GDEntity> ent;
    Dictionary data_bag;
};

#endif 
