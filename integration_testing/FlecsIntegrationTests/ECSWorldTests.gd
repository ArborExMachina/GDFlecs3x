extends ECSWorld

onready var c := create_component_type("TestComp")

#func _ready() -> void:
#	$TestSystem.init_system(self, "TestComp")


func make_entity():
	var e := entity()
	var comp_data = TestComp.new()
	comp_data.x = randf() * 1
	e.set_comp(c, comp_data)

	print("created entity %s" % e.get_id())
	return e
#
#func _notification(what):
#	if what == MainLoop.NOTIFICATION_WM_QUIT_REQUEST:
#		print(get_entity_count())
#		var ents = filter("")
#		for e in ents:
#			e.entity.free()
#		print(get_entity_count())
