#include <iostream>

#include "ECSWorld.h"
#include "GDEntity.h"
#include "GDComponent.h"
#include "Components/ScriptableData.h"
#include "Components/ScriptEntity.h"


const auto ENTITY = "entity";

void ECSWorld::_bind_methods() {
	ClassDB::bind_method(D_METHOD("Tick"), &ECSWorld::Tick);
	ClassDB::bind_method(D_METHOD("Entity"), &ECSWorld::Entity);
	ClassDB::bind_method(D_METHOD("CreateComponent", "name"), &ECSWorld::CreateComponent);
	ClassDB::bind_method(D_METHOD("Query", "query"), &ECSWorld::Query);
}

ECSWorld::ECSWorld()
{
	_delta = 0;
	world.component<ScriptEntity>();
	world.component<ScriptableData>();
}

ECSWorld::~ECSWorld()
{
	// I think the world explodes if the world disposes before GDEntity's do.
}

void ECSWorld::Tick()
{
	world.progress();
}

Ref<GDEntity> ECSWorld::Entity()
{
	Ref<GDEntity> ref;
	ref.instance();
	ref->ecs = &world;
	
	auto e = world.entity().set<ScriptEntity>({ref});	
	ref->entity = e;

	ref->valid = true;
	return ref;
}

Ref<GDComponent> ECSWorld::CreateComponent(const String& name)
{
	std::wstring ws = name.c_str();
	std::string tag_name(ws.begin(), ws.end());
	
	auto gd_comp = world.component(tag_name.c_str());

	Ref<GDComponent> ref;
	ref.instance();
	ref->gd_comp = gd_comp;
	return ref;
}

Array ECSWorld::Query(const String& query)
{
	std::wstring ws = query.c_str();
	std::string s(ws.begin(), ws.end());
	
	flecs::query<ScriptEntity> f = world.query_builder<ScriptEntity>()
		.expr(s.c_str())
		.build();
	std::cout << "FLECS: ForEach query result: " << f.iter().to_json().c_str() << std::endl << std::endl;

	Array ret = Array();

	f.each([&ret](flecs::iter& it, size_t index, ScriptEntity& script_ent) {
		Dictionary ent_data = Dictionary();
		Dictionary comps = Dictionary(); // TODO: Make a dedicated return object. 'entity' and 'comps' are fields that will always exist and type completion is nice
		ent_data[ENTITY] = script_ent.ent;
		ent_data["comps"] = comps;

		int ent_id = it.id(1);
		int field_count = it.field_count() + 1; // why +1? I don't know. Found it experimentally. Lord help me.
		//std::cout << it.entity(1) << ":" << std::endl;
		for (int i = 2; i < field_count; i++)
		{
			//std::cout << "\t" << it.id(i) << " " << it.src(i) << std::endl;
			auto comp = it.id(i);
			comps[comp.name().c_str()] = script_ent.data_bag[comp.id()];
		}		

		ret.append(ent_data);
	});

	return ret;
}
