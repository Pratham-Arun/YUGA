@tool
extends EditorPlugin

var ai_console_instance

func _enter_tree():
	# Load the AI Console UI
	ai_console_instance = preload("res://addons/yuga_ai/ai_console.gd").new()
	# Add to the bottom panel
	add_control_to_bottom_panel(ai_console_instance, "YUGA AI")

func _exit_tree():
	if ai_console_instance:
		remove_control_from_bottom_panel(ai_console_instance)
		ai_console_instance.free()
