#include <iostream>

#include "core/engine.h"

#include "ECSWorld.h"
#include "GDEntity.h"
#include "GDComponent.h"
#include "Systems/GDSystem.h"
#include "Components/ScriptEntity.h"


const auto ENTITY = "entity";

void ECSWorld::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("tick", "delta"), &ECSWorld::Tick);
	ClassDB::bind_method(D_METHOD("entity"), &ECSWorld::Entity);
	ClassDB::bind_method(D_METHOD("create_component_type", "name"), &ECSWorld::CreateComponent);
	ClassDB::bind_method(D_METHOD("filter", "filter_statement"), &ECSWorld::Filter);
	ClassDB::bind_method(D_METHOD("get_entity_count"), &ECSWorld::GetEntityCount);
}

ECSWorld::ECSWorld()
{
	world.component<ScriptEntity>();
}

ECSWorld::~ECSWorld()
{

}

void ECSWorld::_notification(int p_notification)
{
	Node::_notification(p_notification);

	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	switch (p_notification) {
		case NOTIFICATION_PROCESS: {
				Tick(get_process_delta_time());
		} break;
		case NOTIFICATION_READY: {
			int child_count = get_child_count();
			for (int i = 0; i < child_count; i++)
			{
				GDSystem *gd_system = static_cast<GDSystem*>(get_child(i));
				gd_system->InitSystem(this);
			}
			set_process(true);
		} break;
		case NOTIFICATION_PREDELETE: {
			world.defer_begin();
			world.filter<ScriptEntity>()
				.each([](flecs::entity e, ScriptEntity& se){
					//std::cout << "finalizing entity " << e.id() << std::endl;
					se.ent->call("free");
				});
			world.defer_end();
		} break;
	}
}

void ECSWorld::Tick(float delta)
{
	//world.progress();
	int child_count = get_child_count();
	for (int i = 0; i < child_count; i++)
	{
		GDSystem *gd_system = static_cast<GDSystem*>(get_child(i));
		gd_system->Tick(delta);
	}
}

GDEntity* ECSWorld::Entity()
{

	GDEntity* ref = memnew(GDEntity);
	ref->ecs = &world;
	
	// bool defered = world.is_deferred();
	// if (!defered)
	// 	world.defer_begin();
	auto e = world.entity().set<ScriptEntity>({});
	e.get_mut<ScriptEntity>()->ent = ref;
	ref->entity = e;
	ref->valid = true;

	//std::cout << "created entity " << e.id() << std::endl;
	//std::cout << "created entity " << e.get<ScriptEntity>()->ent->entity.id() << std::endl;
	// if (!defered)
	// 	world.defer_end();

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

Array ECSWorld::Filter(const String& dsl)
{
	std::wstring ws = dsl.c_str();
	std::string s(ws.begin(), ws.end());
	
	flecs::filter<ScriptEntity> f = world.filter_builder<ScriptEntity>()
		.expr(s.c_str())
		.build();
	//std::cout << "FLECS: ForEach query result: " << f.iter().to_json().c_str() << std::endl << std::endl;

	Array ret = Array();

	f.each([&ret](flecs::iter& it, size_t index, ScriptEntity& script_ent) {
		Dictionary ent_data = Dictionary();
		Dictionary comps = Dictionary(); // TODO: Make a dedicated return object. 'entity' and 'comps' are fields that will always exist and type completion is nice
		ent_data[ENTITY] = script_ent.ent;
		ent_data["comps"] = comps;

		int ent_id = it.id(1);
		int field_count = it.field_count() + 1;
		//std::cout << it.entity(1) << ":" << std::endl;
		for (int i = 2; i < field_count; i++)
		{
			//std::cout << "\t" << it.id(i) << " " << it.src(i) << std::endl;
			auto comp = it.id(i);
			comps[comp.name().c_str()] = script_ent.ent->dataBag[comp.id()];
		}		

		ret.append(ent_data);
	});

	return ret;
}

flecs::query<ScriptEntity> ECSWorld::BuildSystemQuery(const String& query) const
{
	std::wstring ws = query.c_str();
	std::string s(ws.begin(), ws.end());
	
	auto q = world.query_builder<ScriptEntity>()
		.expr(s.c_str())
		.build();
	return q;
}

int ECSWorld::GetEntityCount() const
{
	return world.count<ScriptEntity>();
}
