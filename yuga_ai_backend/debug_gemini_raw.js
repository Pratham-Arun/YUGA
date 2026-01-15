const https = require('https');
require('dotenv').config();

const apiKey = process.env.GOOGLE_API_KEY;
const url = `https://generativelanguage.googleapis.com/v1beta/models?key=${apiKey}`;

console.log(`Checking API access for key ending in ...${apiKey.slice(-5)}`);

https.get(url, (res) => {
    let data = '';
    res.on('data', (chunk) => data += chunk);
    res.on('end', () => {
        console.log(`Status Code: ${res.statusCode}`);
        try {
            const json = JSON.parse(data); // Pretty print
            console.log(JSON.stringify(json, null, 2));
        } catch (e) {
            console.log("Raw Body:", data);
        }
    });
}).on('error', (err) => {
    console.error("Network Error:", err.message);
});
