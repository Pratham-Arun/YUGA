@tool
extends Node

func scan_project() -> Array:
	var files = []
	_scan_dir_recursive("res://", files)
	return files

func _scan_dir_recursive(path: String, files: Array):
	var dir = DirAccess.open(path)
	if dir:
		dir.list_dir_begin()
		var file_name = dir.get_next()
		while file_name != "":
			if dir.current_is_dir():
				if file_name != "." and file_name != ".." and file_name != ".godot":
					_scan_dir_recursive(path + file_name + "/", files)
			else:
				if file_name.ends_with(".gd") or file_name.ends_with(".shader"):
					var full_path = path + file_name
					var content = _read_file(full_path)
					if content != "":
						files.append({ "path": full_path, "content": content })
			file_name = dir.get_next()
	else:
		push_error("An error occurred when trying to access the path: " + path)

func _read_file(path: String) -> String:
	var file = FileAccess.open(path, FileAccess.READ)
	if file:
		var content = file.get_as_text()
		file.close()
		return content
	else:
		return ""
