const fs = require('fs');
const path = require('path');

const DATA_FILE = path.join(__dirname, '../../rag_data.json');

class RagService {
    constructor() {
        this.documents = []; // Array of { path, content }
        this.loadIndex();
    }

    loadIndex() {
        try {
            if (fs.existsSync(DATA_FILE)) {
                const data = fs.readFileSync(DATA_FILE, 'utf-8');
                this.documents = JSON.parse(data);
                console.log(`[RagService] Loaded ${this.documents.length} documents from disk.`);
            }
        } catch (err) {
            console.error("[RagService] Error loading index:", err);
        }
    }

    saveIndex() {
        try {
            fs.writeFileSync(DATA_FILE, JSON.stringify(this.documents, null, 2));
            console.log(`[RagService] Saved index to disk.`);
        } catch (err) {
            console.error("[RagService] Error saving index:", err);
        }
    }

    addDocuments(docs) {
        // docs: [{ path: string, content: string }]
        console.log(`[RagService] Indexing ${docs.length} documents...`);
        // Simple overwrite/append logic for MVP
        // In real app, we'd check for duplicates or use a real vector DB
        docs.forEach(doc => {
            const existingIndex = this.documents.findIndex(d => d.path === doc.path);
            if (existingIndex >= 0) {
                this.documents[existingIndex] = doc;
            } else {
                this.documents.push(doc);
            }
        });
        console.log(`[RagService] Total documents indexed: ${this.documents.length}`);
        this.saveIndex();
    }

    search(query, limit = 3) {
        console.log(`[RagService] Searching for: "${query}"`);
        // Extremely simple keyword match for MVP
        // Ranking by number of keyword occurrences
        const keywords = query.toLowerCase().split(/\s+/).filter(w => w.length > 3);

        const results = this.documents.map(doc => {
            let score = 0;
            const contentLower = doc.content.toLowerCase();
            keywords.forEach(kw => {
                const regex = new RegExp(kw.replace(/[.*+?^${}()|[\]\\]/g, '\\$&'), 'g');
                const count = (contentLower.match(regex) || []).length;
                score += count;
            });
            return { doc, score };
        });

        // Sort by score and take top N
        return results
            .filter(r => r.score > 0)
            .sort((a, b) => b.score - a.score)
            .slice(0, limit)
            .map(r => r.doc);
    }
}

module.exports = new RagService();
