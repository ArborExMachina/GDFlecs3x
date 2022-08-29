#ifndef GDSYSTEM_H
#define GDSYSTEM_H

#include "scene/main/node.h"
#include "../flecs/flecs.h"
#include "../ECSWorld.h"

class GDSystem : public Node {
    //GDCLASS(GDSystem, Node);
    
   /* protected:
        static void _bind_methods();*/
        
    public:
        GDSystem();
        ~GDSystem();
		virtual void Register(ECSWorld& world) = 0;
};

#endif
