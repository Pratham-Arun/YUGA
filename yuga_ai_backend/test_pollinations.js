const https = require('https');
const fs = require('fs');

const prompt = "pixel art sword";
const url = `https://image.pollinations.ai/prompt/${encodeURIComponent(prompt)}`;

console.log("Requesting:", url);

https.get(url, (res) => {
    console.log("Status:", res.statusCode);
    console.log("Content-Type:", res.headers['content-type']);

    if (res.statusCode === 200) {
        console.log("Success! API is active (free, no key).");
    } else {
        console.log("Failed.");
    }
}).on('error', (e) => {
    console.error("Error:", e.message);
});
