const { GoogleGenerativeAI } = require("@google/generative-ai");
require('dotenv').config();

async function listModels() {
    const apiKey = process.env.GOOGLE_API_KEY;
    if (!apiKey) {
        console.error("No API KEY");
        return;
    }
    const genAI = new GoogleGenerativeAI(apiKey);
    console.log("Fetching available models...");
    try {
        // According to documentation, we might need to hit a REST endpoint manually if the SDK helper is hidden?
        // Actually the SDK has no direct 'listModels' helper exposed on the main class in some versions.
        // But let's try a simple generation on "gemini-1.5-flash" again with verbose catch.

        const model = genAI.getGenerativeModel({ model: "gemini-1.5-flash" });
        const result = await model.generateContent("Hello");
        console.log("Success with gemini-1.5-flash");
        console.log(result.response.text());

    } catch (e) {
        console.error("Failed with flash:", e.message);
        try {
            const model2 = genAI.getGenerativeModel({ model: "gemini-pro" });
            const result2 = await model2.generateContent("Hello");
            console.log("Success with gemini-pro");
        } catch (e2) {
            console.error("Failed with pro:", e2.message);
        }
    }
}

listModels();
