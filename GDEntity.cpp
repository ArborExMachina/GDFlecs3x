/* summator.cpp */
#include <iostream>
#include "GDEntity.h"
#include "GDComponent.h"
#include "ECSWorld.h"
#include "Components/ScriptableData.h"
#include "components/ScriptEntity.h"

void GDEntity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("Set", "gd_comp_def"), &GDEntity::Set);
    ClassDB::bind_method(D_METHOD("GetID"), &GDEntity::GetID);
    ClassDB::bind_method(D_METHOD("GetTypeID"), &GDEntity::GetTypeID);
    ClassDB::bind_method(D_METHOD("Remove", "component"), &GDEntity::Remove);
    ClassDB::bind_method(D_METHOD("Get", "component"), &GDEntity::Get);
}

GDEntity::GDEntity() {
    valid = false;
}

GDEntity::~GDEntity()
{
    entity.destruct();
}

void GDEntity::Set(Ref<GDComponent> gdComp, Dictionary values)
{
    if (!valid)
    {
        std::cout << "FLECS: tried to add comp to a GDEntity with no backer entity" << std::endl;
        return;
    }

    auto tag = gdComp->gd_comp;
    if (entity.has(tag))
    {
        return;
    }

    // just tag the entity, pair stuff is a deadend
    entity.add(tag);
    
    // update the databag with the values
    auto se = entity.get_mut<ScriptEntity>();
    se->data_bag[tag.id()] = values;
}

void GDEntity::Remove(Ref<GDComponent> gdComp)
{
    auto tag = gdComp->gd_comp;
    if(entity.has(tag))
    {
        entity.remove(tag);
        auto data_bag = entity.get_mut<ScriptEntity>();
        data_bag->data_bag.erase(tag.id());
    }
}

Dictionary GDEntity::Get(Ref<GDComponent> gdComp)
{
    auto tag = gdComp->gd_comp;
    if(entity.has(tag))
    {
        entity.remove(tag);
        auto data_bag = entity.get<ScriptEntity>();
        return data_bag->data_bag.get(tag.id(), Dictionary());
    }
}

int GDEntity::GetID() const
{
    return entity.id();
}

String GDEntity::GetTypeID() const
{
    return entity.type_id().str().c_str();
}
