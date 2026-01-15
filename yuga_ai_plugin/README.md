# YUGA AI Plugin

The **YUGA AI Plugin** integrates AI capabilities directly into the Godot Engine Editor.

## Installation

1.  Copy the `addons/yuga_ai` folder into your Godot project's `addons/` directory.
2.  Enable the plugin in **Project Settings > Plugins**.

## Features

### 1. AI Console (Bottom Panel)
The central hub for interacting with the AI.
- **Chat**: Ask general questions or request code.
- **Agent Mode**: Toggle this to let the AI plan and execute complex tasks automatically (e.g., creating assets, scripts, and scenes in one go).
- **Index Codebase**: Scans your project files so the AI understands your custom classes and logic.

### 2. Asset Generator
- Switch to "Asset Mode" (or use Agent Mode).
- Type a description (e.g., "Stone Wall Texture").
- The asset is generated and saved to `res://generated/`.

### 3. Scene Builder
- Switch to "Scene Mode".
- Describe a scene (e.g., "A player node with a sprite and collision").
- The plugin builds the scene structure and saves it as a `.tscn`.

### 4. Smart Debugger
- Toggle "Debug Mode".
- Paste an error log and the file path.
- The AI will analyze the error and propose a code fix.

## Configuration

The plugin communicates with the **YUGA AI Backend**.
Ensure the backend is running (default: `http://localhost:3000`).
