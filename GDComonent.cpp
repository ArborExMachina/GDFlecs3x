/* summator.cpp */

#include "GDComponent.h"

void GDComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GetTypeName"), &GDComponent::GetTypeName);
    ClassDB::bind_method(D_METHOD("GetID"), &GDComponent::GetID);
}

GDComponent::GDComponent() {
    
}

GDComponent::~GDComponent()
{
	
}

StringName GDComponent::GetTypeName()
{
    return gd_comp.name().c_str();
}

int GDComponent::GetID()
{
    return gd_comp.id();
}
