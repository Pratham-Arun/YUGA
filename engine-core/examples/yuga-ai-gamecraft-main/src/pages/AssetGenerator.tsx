import { useState } from "react";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Textarea } from "@/components/ui/textarea";
import {
  Home, Sparkles, Download, Box, Palette, User, Zap, ArrowLeft, Loader2
} from "lucide-react";
import { useNavigate } from "react-router-dom";

interface Asset {
  id: number;
  name: string;
  type: string;
  status: string;
  preview?: string;
}

const AssetGenerator = () => {
  const navigate = useNavigate();
  const [prompt, setPrompt] = useState("");
  const [assetType, setAssetType] = useState("3d-model");
  const [generating, setGenerating] = useState(false);
  const [assets, setAssets] = useState<Asset[]>([
    { id: 1, name: "Sci-Fi Crate", type: "3D Model", status: "Ready", preview: "🎁" },
    { id: 2, name: "Stone Texture", type: "Texture", status: "Ready", preview: "🧱" },
    { id: 3, name: "Magic Effect", type: "VFX", status: "Ready", preview: "✨" }
  ]);

  const assetTypes = [
    { id: "3d-model", label: "3D Model", icon: Box, color: "bg-blue-500/20 border-blue-500" },
    { id: "texture", label: "Texture", icon: Palette, color: "bg-green-500/20 border-green-500" },
    { id: "character", label: "Character", icon: User, color: "bg-purple-500/20 border-purple-500" },
    { id: "effect", label: "VFX", icon: Zap, color: "bg-orange-500/20 border-orange-500" }
  ];

  const templates = [
    { title: "Sci-Fi Crate", type: "3D Model", prompt: "Futuristic metal storage crate with glowing edges", icon: "🎁" },
    { title: "Stone Wall", type: "Texture", prompt: "Medieval stone wall texture with moss", icon: "🧱" },
    { title: "Fantasy Warrior", type: "Character", prompt: "Armored knight character with sword", icon: "⚔️" },
    { title: "Magic Particles", type: "VFX", prompt: "Blue magical particle effect with sparkles", icon: "✨" },
    { title: "Wooden Barrel", type: "3D Model", prompt: "Old wooden barrel with metal bands", icon: "🛢️" },
    { title: "Grass Texture", type: "Texture", prompt: "Realistic grass texture with flowers", icon: "🌿" }
  ];

  const handleGenerate = () => {
    if (!prompt.trim()) return;
    
    setGenerating(true);
    
    // Simulate generation
    setTimeout(() => {
      const newAsset: Asset = {
        id: Date.now(),
        name: prompt.substring(0, 30),
        type: assetTypes.find(t => t.id === assetType)?.label || "Asset",
        status: "Ready",
        preview: ["🎨", "🎁", "⚡", "🌟", "💎"][Math.floor(Math.random() * 5)]
      };
      
      setAssets([newAsset, ...assets]);
      setPrompt("");
      setGenerating(false);
    }, 2000);
  };

  const useTemplate = (template: any) => {
    setPrompt(template.prompt);
  };

  return (
    <div className="h-screen bg-background flex flex-col">
      {/* Toolbar */}
      <div className="h-12 bg-toolbar border-b border-border flex items-center px-4 gap-2">
        <Button variant="ghost" size="sm" onClick={() => navigate("/")}>
          <ArrowLeft className="w-4 h-4 mr-2" />
          Back
        </Button>
        <Separator orientation="vertical" className="h-6" />

        <div className="flex items-center gap-2">
          <Sparkles className="w-4 h-4 text-accent" />
          <span className="text-sm font-medium text-foreground">AI Asset Generator</span>
        </div>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* Templates Sidebar */}
        <div className="w-64 bg-panel border-r border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Templates</span>
          </div>
          <ScrollArea className="flex-1">
            <div className="p-3 space-y-2">
              {templates.map((template, i) => (
                <Card
                  key={i}
                  className="p-3 cursor-pointer hover:border-primary transition-colors"
                  onClick={() => useTemplate(template)}
                >
                  <div className="flex items-start gap-2">
                    <div className="text-2xl">{template.icon}</div>
                    <div className="flex-1">
                      <h3 className="text-sm font-medium text-foreground mb-1">
                        {template.title}
                      </h3>
                      <p className="text-xs text-muted-foreground">
                        {template.type}
                      </p>
                    </div>
                  </div>
                </Card>
              ))}
            </div>
          </ScrollArea>
        </div>

        {/* Main Content */}
        <div className="flex-1 flex flex-col">
          {/* Generation Area */}
          <div className="border-b border-border bg-panel p-6">
            <div className="max-w-3xl mx-auto space-y-4">
              <div>
                <label className="text-sm font-medium text-foreground mb-2 block">
                  Asset Type
                </label>
                <div className="grid grid-cols-4 gap-2">
                  {assetTypes.map((type) => (
                    <Card
                      key={type.id}
                      className={`p-3 cursor-pointer transition-all ${
                        assetType === type.id
                          ? type.color + " border-2"
                          : "hover:border-primary"
                      }`}
                      onClick={() => setAssetType(type.id)}
                    >
                      <div className="flex flex-col items-center gap-2">
                        <type.icon className="w-5 h-5" />
                        <span className="text-xs font-medium">{type.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <div>
                <label className="text-sm font-medium text-foreground mb-2 block">
                  Describe Your Asset
                </label>
                <Textarea
                  placeholder="E.g., 'A futuristic sci-fi weapon with glowing blue energy'"
                  value={prompt}
                  onChange={(e) => setPrompt(e.target.value)}
                  className="min-h-24 resize-none"
                />
              </div>

              <Button
                className="w-full gap-2"
                size="lg"
                onClick={handleGenerate}
                disabled={generating || !prompt.trim()}
              >
                {generating ? (
                  <>
                    <Loader2 className="w-4 h-4 animate-spin" />
                    Generating...
                  </>
                ) : (
                  <>
                    <Sparkles className="w-4 h-4" />
                    Generate Asset
                  </>
                )}
              </Button>
            </div>
          </div>

          {/* Generated Assets */}
          <ScrollArea className="flex-1 p-6">
            <div className="max-w-5xl mx-auto">
              <h2 className="text-lg font-semibold text-foreground mb-4">
                Generated Assets ({assets.length})
              </h2>
              <div className="grid grid-cols-3 gap-4">
                {assets.map((asset) => (
                  <Card key={asset.id} className="p-4">
                    <div className="aspect-square bg-muted rounded-lg flex items-center justify-center mb-3 text-6xl">
                      {asset.preview}
                    </div>
                    <h3 className="text-sm font-medium text-foreground mb-1">
                      {asset.name}
                    </h3>
                    <p className="text-xs text-muted-foreground mb-3">
                      {asset.type}
                    </p>
                    <div className="flex gap-2">
                      <Button variant="outline" size="sm" className="flex-1">
                        <Download className="w-3 h-3 mr-1" />
                        Download
                      </Button>
                      <Button variant="outline" size="sm" className="flex-1">
                        Preview
                      </Button>
                    </div>
                  </Card>
                ))}
              </div>

              {assets.length === 0 && (
                <Card className="p-12 text-center">
                  <Sparkles className="w-16 h-16 text-muted-foreground mx-auto mb-4" />
                  <h3 className="text-lg font-medium text-foreground mb-2">
                    No Assets Yet
                  </h3>
                  <p className="text-sm text-muted-foreground">
                    Describe an asset above and click Generate to create your first AI-powered asset!
                  </p>
                </Card>
              )}
            </div>
          </ScrollArea>
        </div>

        {/* Settings Sidebar */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Settings</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Quality
                </label>
                <select className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground">
                  <option>High (Slower)</option>
                  <option>Medium</option>
                  <option>Low (Faster)</option>
                </select>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Style
                </label>
                <select className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground">
                  <option>Realistic</option>
                  <option>Stylized</option>
                  <option>Low Poly</option>
                  <option>Cartoon</option>
                </select>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Options
                </label>
                <div className="space-y-2">
                  <div className="flex items-center gap-2">
                    <input type="checkbox" defaultChecked className="rounded" />
                    <span className="text-sm text-foreground">Auto-optimize</span>
                  </div>
                  <div className="flex items-center gap-2">
                    <input type="checkbox" defaultChecked className="rounded" />
                    <span className="text-sm text-foreground">Generate LODs</span>
                  </div>
                  <div className="flex items-center gap-2">
                    <input type="checkbox" className="rounded" />
                    <span className="text-sm text-foreground">Include textures</span>
                  </div>
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">
                  Generation Stats
                </h3>
                <div className="space-y-2 text-xs">
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Total Generated:</span>
                    <span className="text-foreground">{assets.length}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">This Session:</span>
                    <span className="text-foreground">{assets.length}</span>
                  </div>
                </div>
              </div>
            </div>
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default AssetGenerator;
