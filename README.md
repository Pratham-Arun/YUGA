<div align="center">

<img src="engine-core/examples/yuga-ai-gamecraft-main/public/logo.png" alt="YUGA Logo" width="150"/>

# 🎮 YUGA - AI-Powered Godot Companion
**Yielding Unified Game Automation**

**The Ultimate AI Co-Pilot for Godot Engine**

[![Version](https://img.shields.io/badge/godot-4.0%2B-blue.svg)](https://godotengine.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Backend](https://img.shields.io/badge/backend-Node.js-green.svg)](https://nodejs.org/)

</div>

> **Turn imagination into playable content instantly** - Supercharge your Godot workflow with AI-powered coding and asset generation.

---

## 🚀 What is YUGA?

YUGA is not just a plugin; it's a **conversational development partner** for Godot. By combining a powerful **Godot Editor Plugin** with an intelligent **Node.js Backend**, YUGA integrates State-of-the-Art AI directly into your game development environment.

We combine real-time AI-assisted coding with AI-generated assets, enabling indie teams, studios, and solo developers to rapidly prototype and build games significantly faster.

---

## 🏛️ Architecture

YUGA operates as a hybrid system to bypass engine limitations and leverage cloud AI power:

1.  **Godot Plugin (`yuga_ai_plugin`)**: Sitting inside the editor, it handles the UI (AI Console), reads your scene state, and executes changes (creating nodes, saving resources).
2.  **AI Backend (`yuga_ai_backend`)**: A local server that processes your requests, manages context (RAG), and communicates with AI providers (OpenAI, Gemini, or local models).

---

## ✨ Key Features

### 1. 🤖 AI Console & Agent Mode
*Located in the Bottom Panel*
- **Chat**: Ask general questions about Godot or your specific project.
- **Agent Mode**: Give complex commands like "Create a UI with a health bar and score counter." The Agent plans the steps and executes them one by one, creating scenes and scripts automatically.

### 2. 🎨 Asset Forge
- **Texture Generation**: "Create a seamless stone wall texture with moss." -> Generates and imports the image to `res://generated/`.
- **3D Prototyping**: Generate mock 3D models to block out levels instantly.

### 3. 🧠 Context-Aware Coding (RAG)
- **Index Your Project**: YUGA scans your project files (`.gd`, `.tscn`) to understand your custom classes and logic.
- **Project-Specific Answers**: Ask "How do I spawn my `EnemyV3` class?" and it knows exactly what that class does.

### 4. 🚑 Smart Debugger
- **Auto-Fix**: Paste an error from the Output debugger, and YUGA analyzes the stack trace and the relevant script to propose a fix.

### 5. 🏗️ Scene Builder
- **Prompt-to-Scene**: Describe a scene structure (e.g., "A RigidBody2D player with a Sprite and CollisionShape"). YUGA builds the node hierarchy and saves it as a `.tscn` file ready to instance.

---

## 🚀 Installation & Setup

### Prerequisites
- **Godot Engine 4.x**
- **Node.js** (v16+) & npm

### Step 1: Set up the Backend
The brain of the operation must be running locally.

```bash
cd yuga_ai_backend
npm install
```

1.  Copy `.env.example` to `.env`.
2.  Set your API keys (OpenAI or Gemini) if using real AI mode.
3.  Start the server:
    ```bash
    npm start
    ```
    *Server runs on `http://localhost:3000` by default.*

### Step 2: Install the Plugin
1.  Copy the `yuga_ai_plugin/addons/yuga_ai` folder into your Godot project's `addons/` directory.
    *(Review path: `res://addons/yuga_ai/`)*
2.  Open your project in Godot.
3.  Go to **Project > Project Settings > Plugins**.
4.  Enable **YUGA AI**.

---

## 🎯 How YUGA Solves Development Pain Points

### 1. 🧩 The Blank Page Syndrome
**❌ Problem:** Staring at an empty scene, not knowing where to start coding or designing.
**✅ YUGA Solution:**
```text
User: "Create a basic platformer level with a player and 3 platforms"
YUGA: Generates the Scene Tree, attaches scripts for movement, and sets up collisions.
```

### 2. 🎨 "I Can Code, But I Can't Draw"
**❌ Problem:** Developers often stall because they lack assets.
**✅ YUGA Solution:**
```text
User: "Generate a pixel art spaceship sprite, blue and white"
YUGA: Creates the sprite and imports it for immediate use.
```

### 3. 🐛 "Why is this crashing?"
**❌ Problem:** Cryptic error messages in the debugger.
**✅ YUGA Solution:** Debug Mode analyzes the specific runtime error in context of your script and suggests the exact line change needed to fix it.

---

## 🤝 Contributing

We welcome contributions to both the Plugin (GDScript) and the Backend (JavaScript/Node.js).

1.  Fork the repository.
2.  Create a feature branch.
3.  Submit a Pull Request.

---

## 📄 License
MIT License - See [LICENSE](LICENSE) file.
