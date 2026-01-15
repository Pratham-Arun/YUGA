@tool
extends Control

# UI Components
var output_log: RichTextLabel
var prompt_input: LineEdit
var send_button: Button

# Debug Components
var debug_toggle: CheckButton
var asset_toggle: CheckButton
var scene_toggle: CheckButton
var agent_toggle: CheckButton

var debug_panel: VBoxContainer
var error_log_input: TextEdit
var file_path_input: LineEdit
var fix_button: Button

var code_preview_window: Window
var code_preview_instance

var backend_url = "http://localhost:3000"

func _load_settings():
	var config = ConfigFile.new()
	var err = config.load("res://addons/yuga_ai/settings.cfg")
	if err == OK:
		backend_url = config.get_value("general", "backend_url", "http://localhost:3000")
	else:
		_log_ai("Could not load settings.cfg, using default URL.")

func _get_backend_url() -> String:
	return backend_url.trim_suffix("/")

func _init():
	# Setup UI layout
	var vlog = VBoxContainer.new()
	vlog.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(vlog)
	
	_load_settings()

	# --- Log Area ---
	output_log = RichTextLabel.new()
	output_log.size_flags_vertical = Control.SIZE_EXPAND_FILL
	output_log.scroll_following = true
	vlog.add_child(output_log)

	# --- Control Bar ---
	var hbox = HBoxContainer.new()
	vlog.add_child(hbox)
	
	# CheckButton for Debug
	debug_toggle = CheckButton.new()
	debug_toggle.text = "Debug Mode"
	debug_toggle.toggled.connect(_on_debug_toggled)
	hbox.add_child(debug_toggle)
	
	# CheckButton for Asset
	asset_toggle = CheckButton.new()
	asset_toggle.text = "Asset Mode"
	asset_toggle.toggled.connect(func(t): 
		if t: 
			debug_toggle.button_pressed = false
			if scene_toggle: scene_toggle.button_pressed = false
			if agent_toggle: agent_toggle.button_pressed = false
			_on_mode_changed("asset")
		elif not debug_toggle.button_pressed:
			_on_mode_changed("code")
	)
	hbox.add_child(asset_toggle)
	
	# CheckButton for Scene
	scene_toggle = CheckButton.new()
	scene_toggle.text = "Scene Mode"
	
	scene_toggle.toggled.connect(func(t):
		if t:
			debug_toggle.button_pressed = false
			asset_toggle.button_pressed = false
			_on_mode_changed("scene")
		elif not debug_toggle.button_pressed and not asset_toggle.button_pressed:
			_on_mode_changed("code")
	)
	hbox.add_child(scene_toggle)
	
	# CheckButton for Agent
	agent_toggle = CheckButton.new()
	agent_toggle.text = "Agent Mode"
	agent_toggle.toggled.connect(func(t):
		if t:
			debug_toggle.button_pressed = false
			asset_toggle.button_pressed = false
			scene_toggle.button_pressed = false
			_on_mode_changed("agent")
		elif not debug_toggle.button_pressed and not asset_toggle.button_pressed and not scene_toggle.button_pressed:
			_on_mode_changed("code")
	)
	hbox.add_child(agent_toggle)

	# --- Standard Prompt Input ---
	prompt_input = LineEdit.new()
	prompt_input.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	prompt_input.placeholder_text = "Ask Yuga AI... (or Asset description)"
	prompt_input.text_submitted.connect(_on_send_pressed)
	hbox.add_child(prompt_input)

	send_button = Button.new()
	send_button.text = "Send"
	send_button.pressed.connect(func(): _on_send_pressed(prompt_input.text))
	hbox.add_child(send_button)
	
	var index_button = Button.new()
	index_button.text = "Index Codebase"
	index_button.pressed.connect(_on_index_pressed)
	hbox.add_child(index_button)
	
	var mic_button = Button.new()
	mic_button.text = "Hold to Speak"
	mic_button.button_down.connect(_on_mic_down)
	mic_button.button_up.connect(_on_mic_up)
	hbox.add_child(mic_button)
	
	_setup_audio_bus()
	
	# --- Debug Panel (Hidden by default) ---
	debug_panel = VBoxContainer.new()
	debug_panel.visible = false
	vlog.add_child(debug_panel)
	
	var file_hbox = HBoxContainer.new()
	debug_panel.add_child(file_hbox)
	var file_label = Label.new()
	file_label.text = "File to Fix:"
	file_hbox.add_child(file_label)
	file_path_input = LineEdit.new()
	file_path_input.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	file_path_input.placeholder_text = "res://path/to/script.gd"
	file_hbox.add_child(file_path_input)

	var error_label = Label.new()
	error_label.text = "Error Log:"
	debug_panel.add_child(error_label)
	
	error_log_input = TextEdit.new()
	error_log_input.custom_minimum_size = Vector2(0, 100)
	error_log_input.placeholder_text = "Paste error log here..."
	debug_panel.add_child(error_log_input)
	
	fix_button = Button.new()
	fix_button.text = "Fix Error"
	fix_button.pressed.connect(_on_fix_pressed)
	debug_panel.add_child(fix_button)

func _on_debug_toggled(toggled: bool):
	debug_panel.visible = toggled
	prompt_input.visible = !toggled
	send_button.visible = !toggled

var current_mode = "code" # code, debug, asset

func _on_mode_changed(new_mode: String):
	current_mode = new_mode
	if new_mode == "asset":
		_log_ai("Switched to Asset Mode. Type a description (e.g. 'Wood Texture')")
	elif new_mode == "code":
		_log_ai("Switched to Code Mode.")

func _on_send_pressed(text: String):
	if text.strip_edges() == "":
		return
	
	_log_user(text)
	prompt_input.text = ""
	
	if current_mode == "asset":
		_send_asset_request(text, "texture") # Default to texture for MVP
	elif current_mode == "scene":
		_send_scene_request(text)
	elif current_mode == "agent":
		_send_agent_task(text)
	else:
		_send_generate_request(text)

func _send_agent_task(prompt: String):
	_log_ai("Agent planning task...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/agent-task"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"prompt": prompt})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _execute_agent_plan(steps: Array):
	_log_ai("Agent Plan: " + str(steps.size()) + " steps.")
	# Simple recursive execution or loop with delay
	for step in steps:
		var type = step.get("type")
		var prompt = step.get("prompt")
		_log_ai("Executing Step: " + type.to_upper() + " - " + prompt)
		
		# Synchronous-ish execution is hard in Godot without await or signals.
		# For MVP, we will fire requests. A real implementation needs a queue.
		await get_tree().create_timer(1.0).timeout 
		
		if type == "asset":
			_send_asset_request(prompt, "texture")
		elif type == "code":
			_send_generate_request(prompt)
		elif type == "scene":
			_send_scene_request(prompt)
		
		await get_tree().create_timer(1.0).timeout

func _send_asset_request(prompt: String, type: String):
	_log_ai("Generating asset (" + type + ")...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/generate-asset"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"prompt": prompt, "type": type})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _send_generate_request(prompt: String):
	# ... (same as before) ...
	_log_ai("Processing...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/generate-code"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"prompt": prompt, "model": "gpt-4.1-mini"})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _send_debug_request(script: String, error: String):
	_log_ai("Analyzing error...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/debug"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"script": script, "error": error, "model": "gpt-4.1-mini"})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _send_scene_request(prompt: String):
	_log_ai("Generating scene...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/generate-scene"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"prompt": prompt})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _on_index_pressed():
	_log_ai("Scanning codebase...")
	var indexer = preload("res://addons/yuga_ai/project_indexer.gd").new()
	var files = indexer.scan_project()
	_log_ai("Found " + str(files.size()) + " scripts. Sending to backend...")
	
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(_on_request_completed)
	
	var url = _get_backend_url() + "/index-project"
	var headers = ["Content-Type: application/json"]
	# Note: large projects might hit body size limits or timeout. For MVP it's okay.
	var body = JSON.stringify({"files": files})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _on_request_completed(result, response_code, headers, body):
	if response_code == 200:
		var json = JSON.new()
		json.parse(body.get_string_from_utf8())
		var response = json.get_data()
		
		# Handle Asset Response
		if response and "type" in response and response["type"] == "texture":
			_log_ai(response.get("explanation", "Asset generated."))
			# Import Logic
			var importer = preload("res://addons/yuga_ai/asset_importer.gd").new()
			var path = importer.save_base64_image(response["data"], "generated_asset_" + str(Time.get_unix_time_from_system()))
			_log_ai("Saved to: " + path)
			
		# Handle Index Response
		elif response and "message" in response and response["message"].begins_with("Indexed"):
			_log_ai(response["message"])

		# Handle Agent Response
		elif response and "steps" in response:
			_log_ai(response.get("explanation", "Plan ready."))
			_execute_agent_plan(response["steps"])

		# Handle Scene Response
		elif response and "tree" in response:
			_log_ai(response.get("explanation", "Scene generated."))
			# Build Scene
			var builder = preload("res://addons/yuga_ai/scene_builder.gd").new()
			var scene_root = builder.build_scene_from_json(response, "Scene_" + str(Time.get_unix_time_from_system()))
			
			if scene_root:
				var dir = DirAccess.open("res://")
				if not dir.dir_exists("generated/scenes"):
					dir.make_dir_recursive("generated/scenes")
				
				var path = "res://generated/scenes/" + scene_root.name + ".tscn"
				builder.save_scene_to_disk(scene_root, path)
				_log_ai("Scene saved to: " + path)
				
				# Free the node after saving, as we just wanted to generate the file
				scene_root.free()
				EditorInterface.get_resource_filesystem().scan()
			else:
				_log_ai("Failed to build scene.")

		# Handle Code Response
		elif response and "script" in response:
			_log_ai(response.get("explanation", "Solution ready."))
			_show_code_preview(response["script"])
		elif response and "answer" in response:
			_log_ai(str(response["answer"]))
		else:
			_log_ai("Raw: " + str(response))
	else:
		_log_ai("Backend Failed: " + str(response_code))

var record_effect: AudioEffectRecord
var recording_player: AudioStreamPlayer

func _setup_audio_bus():
	# Ensure Record bus exists or use a dedicated bus
	var bus_idx = AudioServer.get_bus_index("Record")
	if bus_idx == -1:
		bus_idx = AudioServer.bus_count
		AudioServer.add_bus()
		AudioServer.set_bus_name(bus_idx, "Record")
		AudioServer.set_bus_mute(bus_idx, true) # Mute to avoid feedback
	
	# Add Record Effect if missing
	var effect_idx = -1
	for i in range(AudioServer.get_bus_effect_count(bus_idx)):
		if AudioServer.get_bus_effect(bus_idx, i) is AudioEffectRecord:
			effect_idx = i
			break
			
	if effect_idx == -1:
		record_effect = AudioEffectRecord.new()
		AudioServer.add_bus_effect(bus_idx, record_effect)
	else:
		record_effect = AudioServer.get_bus_effect(bus_idx, effect_idx)

	# Setup a player to capture mic input
	recording_player = AudioStreamPlayer.new()
	recording_player.bus = "Record"
	recording_player.stream = AudioStreamMicrophone.new()
	add_child(recording_player)
	
func _on_mic_down():
	if not recording_player.playing:
		recording_player.play()
	record_effect.set_recording_active(true)
	_log_ai("Listening...")

func _on_mic_up():
	record_effect.set_recording_active(false)
	var recording = record_effect.get_recording()
	recording_player.stop()
	
	if recording:
		var data = recording.get_data() # returns PackedByteArray of WAV if saved? No, returns AudioStreamWAV usually.
		# Note: get_recording() returns AudioStreamWAV (Godot 4).
		# We need to save it to a buffer.
		if recording is AudioStreamWAV:
			# For simplicity, let's just save to disk and read back, or construct WAV header manually.
			# Godot's save_to_wav is not directly exposed as bytes easily without file.
			# Let's save to a temp file.
			var path = "user://temp_voice.wav"
			recording.save_to_wav(path)
			
			var file = FileAccess.open(path, FileAccess.READ)
			if file:
				var wav_bytes = file.get_buffer(file.get_length())
				file.close()
				var base64 = Marshalls.raw_to_base64(wav_bytes)
				_send_voice_request(base64)
			else:
				_log_ai("Error reading temp voice file.")
	else:
		_log_ai("No audio captured.")

func _send_voice_request(base64_audio: String):
	_log_ai("Transcribing...")
	var http = HTTPRequest.new()
	add_child(http)
	http.request_completed.connect(func(result, code, headers, body):
		if code == 200:
			var json = JSON.new()
			json.parse(body.get_string_from_utf8())
			var response = json.get_data()
			if response and "text" in response:
				_log_ai("Heard: " + response["text"])
				prompt_input.text = response["text"]
				_on_send_pressed(response["text"])
		else:
			_log_ai("Transcription failed.")
	)
	
	var url = _get_backend_url() + "/transcribe"
	var headers = ["Content-Type: application/json"]
	var body = JSON.stringify({"audio": base64_audio})
	http.request(url, headers, HTTPClient.METHOD_POST, body)

func _show_code_preview(code: String):
	if not code_preview_window:
		code_preview_window = Window.new()
		code_preview_window.title = "YUGA AI - Code Preview"
		code_preview_window.initial_position = Window.WINDOW_INITIAL_POSITION_CENTER_MAIN_WINDOW_SCREEN
		code_preview_window.size = Vector2i(600, 400)
		code_preview_window.close_requested.connect(func(): code_preview_window.hide())
		
		code_preview_instance = preload("res://addons/yuga_ai/code_preview.gd").new()
		code_preview_window.add_child(code_preview_instance)
		code_preview_instance.applied.connect(_on_code_applied)
		code_preview_instance.cancelled.connect(func(): code_preview_window.hide())
	
	code_preview_instance.set_preview(code)
	if not code_preview_window.visible:
		add_child(code_preview_window)
		code_preview_window.popup()
	else:
		code_preview_window.show()

func _on_code_applied(code: String):
	code_preview_window.hide()
	
	# Determine target file
	# If in debug mode, overwrite the target file.
	# If in generate mode, write to generated/
	
	var target_path = ""
	if debug_toggle.button_pressed:
		target_path = file_path_input.text
	else:
		var dir = DirAccess.open("res://")
		if not dir.dir_exists("generated"):
			dir.make_dir("generated")
		target_path = "res://generated/ai_script_" + str(Time.get_unix_time_from_system()) + ".gd"
	
	var file = FileAccess.open(target_path, FileAccess.WRITE)
	if file:
		file.store_string(code)
		file.close()
		_log_ai("Code saved to " + target_path)
		EditorInterface.get_resource_filesystem().scan()
	else:
		_log_ai("Error saving file to " + target_path)

		_log_ai("Error saving file to " + target_path)

func _log_ai(message: String):
	print("[YUGA AI] " + message)
	if output_log:
		output_log.append_text("[color=yellow][AI]:[/color] " + message + "\n")

func _log_user(message: String):
	if output_log:
		output_log.append_text("[color=cyan][You]:[/color] " + message + "\n")

func _on_fix_pressed():
	if error_log_input.text.strip_edges() == "":
		_log_ai("Please paste an error log first.")
		return
	
	# If file path is provided, read its content
	var script_content = ""
	var path = file_path_input.text.strip_edges()
	if path != "":
		var file = FileAccess.open(path, FileAccess.READ)
		if file:
			script_content = file.get_as_text()
			file.close()
		else:
			_log_ai("Could not read file at: " + path)
			return
	
	_send_debug_request(script_content, error_log_input.text)
