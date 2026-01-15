const express = require('express');
const router = express.Router();
const aiController = require('../controllers/ai_controller');

router.post('/generate-code', (req, res) => aiController.generateCode(req, res));
router.post('/debug', (req, res) => aiController.debug(req, res));
router.post('/generate-asset', (req, res) => aiController.generateAsset(req, res));
router.post('/generate-scene', (req, res) => aiController.generateScene(req, res));
router.post('/agent-task', (req, res) => aiController.agentTask(req, res));
router.post('/transcribe', (req, res) => aiController.transcribe(req, res));
router.post('/index-project', (req, res) => aiController.indexProject(req, res));

module.exports = router;
