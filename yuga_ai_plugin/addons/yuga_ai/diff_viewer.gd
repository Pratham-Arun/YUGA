@tool
extends Control

var label: Label

func _init():
	label = Label.new()
	label.text = "Diff Viewer (Placeholder)"
	add_child(label)
