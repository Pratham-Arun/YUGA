@tool
extends Node

func build_scene_from_json(json_data: Dictionary, root_name_override: String = "") -> Node:
	if not "tree" in json_data:
		push_error("Invalid scene JSON: missing 'tree' key")
		return null
	
	var tree_data = json_data["tree"]
	var root = _create_node_recursive(tree_data)
	
	if root and root_name_override != "":
		root.name = root_name_override
		
	return root

func _create_node_recursive(data: Dictionary) -> Node:
	var type = data.get("type", "Node")
	var name = data.get("name", "Node")
	
	if not ClassDB.can_instantiate(type):
		push_warning("YUGA AI: Cannot instantiate type '" + type + "'. Fallback to Node.")
		type = "Node"
	
	var node = ClassDB.instantiate(type)
	if not node:
		return null
		
	node.name = name
	
	# Set properties if present (e.g. position, rotation)
	if "properties" in data:
		for prop in data["properties"]:
			node.set(prop, data["properties"][prop])
			
	# Recursively create children
	if "children" in data:
		for child_data in data["children"]:
			var child_node = _create_node_recursive(child_data)
			if child_node:
				node.add_child(child_node)
				child_node.owner = node # Set owner for packed scene saving if root
				
	return node

func save_scene_to_disk(root_node: Node, path: String):
	var packed_scene = PackedScene.new()
	
	# To save a branch as a scene, all nodes must be owned by the root
	_set_owner_recursive(root_node, root_node)
	
	var result = packed_scene.pack(root_node)
	if result == OK:
		ResourceSaver.save(packed_scene, path)
		print("Saved scene to: " + path)
	else:
		push_error("Failed to pack scene")

func _set_owner_recursive(node: Node, root: Node):
	if node != root:
		node.owner = root
	for child in node.get_children():
		_set_owner_recursive(child, root)
