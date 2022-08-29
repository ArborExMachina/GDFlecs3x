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
}

GDEntity::GDEntity() {
    valid = false;
}

GDEntity::~GDEntity()
{
	
}

void GDEntity::Set(Ref<GDComponent> gdComp, Dictionary values)
{
    if (!valid)
    {
        std::cout << "FLECS: tried to add comp to a GDEntity with no backer entity" << std::endl;
        return;
    }

    // just tag the entity, pair stuff is a deadend
    e.add(gdComp->gd_comp);
    
    // update the databag with the values
    auto se = e.get_mut<ScriptEntity>();
    se->data_bag[gdComp->gd_comp.id()] = values;

    //std::cout << "FLECS: adding scriptable tag " << gdComp->gd_comp.id() << " to " << e.id() << std::endl;

    // auto data = ecs->entity().set<ScriptableData>({values});
    // std::cout << "FLECS: created data bag entity, id " << data.id() << std::endl;

    // auto pair = ecs->pair(gdComp->gd_comp, data);
    // std::cout << "FLECS: created pair id" << pair << std::endl;

    // e.add(pair);
}

int GDEntity::GetID() const
{
    return e.id();
}

String GDEntity::GetTypeID() const
{
    return e.type_id().str().c_str();
}