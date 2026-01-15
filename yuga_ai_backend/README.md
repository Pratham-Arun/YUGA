# YUGA AI Backend

The **YUGA AI Backend** serves as the intelligence layer for the YUGA Engine. It acts as a middleman between the Godot Plugin and AI Providers (Mock or OpenAI).

## Features

- **Code Generation**: Generates GDScript code based on text prompts.
- **RAG (Project Awareness)**: Indexes your project's scripts to provide context-aware answers.
- **Debugging**: Fixes GDScript errors by analyzing the script and error log.
- **Asset Generation**: Creates textures (using DALL-E 3) and mock 3D models.
- **Scene Builder**: Generates Godot Scene Trees (JSON) from descriptions.
- **Agent Mode**: Breaks down complex tasks ("Make a game") into executable steps.

## Setup

1.  **Install Dependencies**:
    ```bash
    npm install
    ```

2.  **Configuration**:
    Copy `.env.example` to `.env` and configure:
    ```env
    PORT=3000
    USE_REAL_LLM=true # Set to false to use Mock provider (free/offline)
    OPENAI_API_KEY=sk-... # Required if USE_REAL_LLM is true
    ```

3.  **Run Server**:
    ```bash
    npm start
    ```

## API Endpoints

| Method | Endpoint | Description |
| :--- | :--- | :--- |
| `POST` | `/generate-code` | Generates GDScript code. Body: `{ prompt, model }` |
| `POST` | `/debug` | Fixes a script. Body: `{ script, error, model }` |
| `POST` | `/generate-asset` | Generates texture/model. Body: `{ prompt, type: "texture"\|"model" }` |
| `POST` | `/generate-scene` | Generates scene tree JSON. Body: `{ prompt }` |
| `POST` | `/agent-task` | Plans a complex task. Body: `{ prompt }` |
| `POST` | `/index-project` | Indexes files for RAG. Body: `{ files: [{path, content}] }` |

## Architecture

- **`src/server.js`**: Entry point.
- **`src/routes/`**: API Route definitions.
- **`src/controllers/`**: Request handling logic.
- **`src/providers/`**:
    - `mock_llm.js`: Simulates AI responses for testing/offline use.
    - `openai_llm.js`: Real implementation using OpenAI API.
- **`src/services/`**:
    - `rag_service.js`: In-memory vector/keyword store for context retrieval.
