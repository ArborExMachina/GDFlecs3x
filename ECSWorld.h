#ifndef ECSWORLD_H
#define ECSWORLD_H

#include "core/reference.h"
#include "scene/main/node.h"

#include "flecs/flecs.h"

class GDEntity;
class GDComponent;
struct ScriptEntity;

class ECSWorld : public Node {
	GDCLASS(ECSWorld, Node);

private:
	
protected:
	static void _bind_methods();
	void _notification(int p_notification);

public:
	ECSWorld();
	~ECSWorld();
	
	flecs::world world;
	GDEntity* Entity();
	Ref<GDComponent> ECSWorld::CreateComponent(const String& name);
	Array Filter(const String& query);
	void Tick(float delta);

	flecs::query<ScriptEntity> BuildSystemQuery(const String& query) const;
	int GetEntityCount() const;
};

#endif
