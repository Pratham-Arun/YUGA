const mockLLM = require('../providers/mock_llm');
const OpenAILLM = require('../providers/openai_llm');
const GeminiLLM = require('../providers/gemini_llm');
const ScenarioProvider = require('../providers/scenario_provider');


const ragService = require('../services/rag_service');

class AIController {
    constructor() {
        if (process.env.USE_REAL_LLM === 'true') {
            if (process.env.LLM_PROVIDER === 'gemini') {
                console.log("[AIController] Using Gemini Provider.");
                const apiKey = process.env.GOOGLE_API_KEY;
                if (!apiKey) throw new Error("GOOGLE_API_KEY is missing.");
                this.llmProvider = new GeminiLLM(apiKey);
            } else {
                console.log("[AIController] Using OpenAI Provider.");
                const apiKey = process.env.OPENAI_API_KEY;
                if (!apiKey) throw new Error("OPENAI_API_KEY is missing.");
                this.llmProvider = new OpenAILLM(apiKey);
            }

            // Dedicated Asset Provider Setup
            if (process.env.ASSET_PROVIDER === 'scenario') {
                console.log("[AIController] Using Scenario.com for Assets.");
                this.assetProvider = new ScenarioProvider();
            } else {
                this.assetProvider = this.llmProvider; // Fallback
            }
        } else {
            console.log("[AIController] Using MockLLM Provider.");
            this.llmProvider = mockLLM;
            this.assetProvider = mockLLM;
        }

    }

    async indexProject(req, res) {
        try {
            const { files } = req.body; // Expects { files: [{ path, content }] }
            if (!files || !Array.isArray(files)) {
                return res.status(400).json({ error: "Files array is required" });
            }

            ragService.addDocuments(files);
            res.json({ message: `Indexed ${files.length} files.` });
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async generateCode(req, res) {
        try {
            const { prompt, model } = req.body;
            if (!prompt) {
                return res.status(400).json({ error: "Prompt is required" });
            }

            // RAG Step: Retrieve context
            const contextDocs = ragService.search(prompt);
            let augmentedPrompt = prompt;

            if (contextDocs.length > 0) {
                const contextStr = contextDocs.map(d => `File: ${d.path} \nContent: \n${d.content} \n`).join("\n---\n");
                augmentedPrompt = `Context from codebase: \n${contextStr} \n\nQuestion: ${prompt} `;
                console.log(`[AIController] Augmented prompt with ${contextDocs.length} context files.`);
            }

            const result = await this.llmProvider.generateCode(augmentedPrompt, model);

            // Should we attach the retrieval info to the explanation?
            if (contextDocs.length > 0) {
                result.explanation += `\n(Used ${contextDocs.length} codebase files for context)`;
            }

            res.json(result);
        } catch (error) {
            console.error(error);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async debug(req, res) {
        try {
            const { script, error, model } = req.body;
            if (!script || !error) {
                return res.status(400).json({ error: "Script and Error are required" });
            }

            const result = await this.llmProvider.debugCode(script, error, model);
            res.json(result);
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async generateAsset(req, res) {
        try {
            const { prompt, type } = req.body;
            if (!prompt || !type) {
                return res.status(400).json({ error: "Prompt and Type are required" });
            }

            let result;
            if (type === 'texture') {
                result = await this.assetProvider.generateTexture(prompt);
            } else if (type === 'model') {
                result = await this.assetProvider.generateModel(prompt);
            } else {
                return res.status(400).json({ error: "Invalid asset type" });
            }

            res.json(result);
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async generateScene(req, res) {
        try {
            const { prompt, model } = req.body;
            if (!prompt) {
                return res.status(400).json({ error: "Prompt is required" });
            }

            const result = await this.llmProvider.generateScene(prompt);
            res.json(result);
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async agentTask(req, res) {
        try {
            const { prompt, model } = req.body;
            if (!prompt) {
                return res.status(400).json({ error: "Prompt is required" });
            }

            const result = await this.llmProvider.planTask(prompt);
            res.json(result);
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }

    async transcribe(req, res) {
        try {
            const { audio } = req.body; // Expects base64 string
            if (!audio) {
                return res.status(400).json({ error: "Audio data (base64) is required" });
            }

            const buffer = Buffer.from(audio, 'base64');
            const result = await this.llmProvider.transcribe(buffer);
            res.json(result);
        } catch (err) {
            console.error(err);
            res.status(500).json({ error: "Internal Server Error" });
        }
    }
}

module.exports = new AIController();
