const express = require('express');
const cors = require('cors');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 3000;

const aiRoutes = require('./routes/ai_routes');

app.use(cors());
app.use(express.json());

// Use AI Routes prefixed with /api/ai or root
app.use('/', aiRoutes); // Keeping it at root to match previous contract for now, or move to /api/ai

app.get('/', (req, res) => {
    res.send('YUGA AI Backend is running.');
});

app.listen(PORT, () => {
    console.log(`YUGA AI Backend running on http://localhost:${PORT}`);
});
