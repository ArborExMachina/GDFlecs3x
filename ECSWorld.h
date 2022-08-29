#ifndef ECSWORLD_H
#define ECSWORLD_H

#include "core/reference.h"
#include "scene/main/node.h"

#include "flecs/flecs.h"

class GDEntity;
class GDComponent;

class ECSWorld : public Node {
	GDCLASS(ECSWorld, Node);

private:
	flecs::world world;
	float _delta;

protected:
	static void _bind_methods();

public:
	ECSWorld();
	~ECSWorld();
	
	Ref<GDEntity> Entity();
	Ref<GDComponent> ECSWorld::CreateComponent(const String& name);
	Array Query(const String& query);

	void Tick();
};

#endif
