@tool
extends Control

signal applied(code: String)
signal cancelled()

var code_edit: CodeEdit
var apply_button: Button
var cancel_button: Button

func _init():
	var vbox = VBoxContainer.new()
	vbox.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(vbox)
	
	code_edit = CodeEdit.new()
	code_edit.size_flags_vertical = Control.SIZE_EXPAND_FILL
	code_edit.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	vbox.add_child(code_edit)
	
	var hbox = HBoxContainer.new()
	vbox.add_child(hbox)
	
	apply_button = Button.new()
	apply_button.text = "Apply to Project"
	apply_button.pressed.connect(func(): applied.emit(code_edit.text))
	hbox.add_child(apply_button)
	
	cancel_button = Button.new()
	cancel_button.text = "Cancel"
	cancel_button.pressed.connect(func(): cancelled.emit())
	hbox.add_child(cancel_button)

func set_preview(code: String):
	code_edit.text = code
