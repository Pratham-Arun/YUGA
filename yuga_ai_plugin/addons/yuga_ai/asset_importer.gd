@tool
extends Node

func save_base64_image(base64_string: String, filename_slug: String) -> String:
	var image = Image.new()
	var buffer = Marshalls.base64_to_raw(base64_string)
	
	# Try loading as PNG first
	var err = image.load_png_from_buffer(buffer)
	if err != OK:
		# If it's not PNG, maybe it's JPG (not handled in mock, but good practice)
		err = image.load_jpg_from_buffer(buffer)
	
	if err != OK:
		push_error("YUGA AI: Failed to load image from base64 buffer")
		return ""
	
	var dir = DirAccess.open("res://")
	if not dir.dir_exists("assets"):
		dir.make_dir("assets")
	
	var path = "res://assets/" + filename_slug + ".png"
	image.save_png(path)
	
	# Trigger Godot import
	EditorInterface.get_resource_filesystem().scan()
	return path

func import_texture(path: String, texture_data: PackedByteArray):
	# ... legacy logic if needed ...
	pass
