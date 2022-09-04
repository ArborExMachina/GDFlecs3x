extends GDSystem

onready var world := get_parent()

var time = 0

func _pre_tick(delta):
	time += delta
	if time > 0.1:
		world.make_entity()
		time = 0

func _proccess_entity(delta, ent:GDEntity, comps:Array):
	comps[0].x -= delta
	if (comps[0].x <= 0):
		print("clearing entity %s" % ent.get_id())
		ent.free()
