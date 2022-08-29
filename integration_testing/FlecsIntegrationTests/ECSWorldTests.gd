extends ECSWorld


func _ready() -> void:
	var c := CreateComponent("test_comp")
	var c1 := CreateComponent("more_test")
	print("created new comp type called %s with id %s" % [c.GetTypeName(), c.GetID()])
	print("created new comp type called %s with id %s" % [c1.GetTypeName(), c1.GetID()])
	
	var e := _make_entity([[c, {"test":1}], [c1, {"test1":2}]])
	var e1 := _make_entity([[c, {"test":3}], [c1, {"test1":4}]])

	var results := Query("test_comp, more_test");
	print(results)
	for r in results:
		r.comps.test_comp.test += 1
		r.comps.more_test.test1 += 10
	print(results)

	print(Query("test_comp, more_test"))


func _make_entity(comps:Array) -> GDEntity:
	var e := Entity()
	#print("created new entity id %s, type %s" % [e.GetID(), e.GetTypeID()])

	for c in comps:
		var comp = c[0]
		var vals = c[1]
		#print("added %s to entity %s" % [c.GetID(), e.GetID()])
		e.Set(comp, vals)
	return e
