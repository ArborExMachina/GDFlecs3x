#ifndef GDSYSTEM_H
#define GDSYSTEM_H

#include "scene/main/node.h"
#include "../flecs/flecs.h"

class ECSWorld;
struct ScriptEntity;

class GDSystem : public Node {
    GDCLASS(GDSystem, Node);

    private:
        String filterDsl;

    protected:
        static void _bind_methods();
        flecs::query<ScriptEntity> q;
        
    public:
        flecs::world* ecs;
        GDSystem();
        ~GDSystem();
        void InitSystem(ECSWorld* world);
        void Tick(float delta);
        void SetFilter(const String& dsl);
        String GetFilter() const;
};

#endif
