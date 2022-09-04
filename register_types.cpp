/* register_types.cpp */

#include "core/class_db.h"

#include "register_types.h"
#include "ECSWorld.h"
#include "GDEntity.h"
#include "GDComponent.h"
#include "Systems/GDSystem.h"

#include "flecs/flecs.h"

void register_ecs_types() {
    ClassDB::register_class<GDEntity>();
    ClassDB::register_class<GDComponent>();
    ClassDB::register_class<ECSWorld>();
    ClassDB::register_class<GDSystem>();

    //ecs_log_set_level(3);
}

void unregister_ecs_types() {
   // Nothing to do here in this example.
}

//void initialize_ecs_module(ModuleInitializationLevel p_level)
//{
//	ClassDB::register_class<Summator>();
//}
//
//void uninitialize_ecs_module(ModuleInitializationLevel p_level)
//{
//}
