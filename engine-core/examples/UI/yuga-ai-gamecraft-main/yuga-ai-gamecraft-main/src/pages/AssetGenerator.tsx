import { useState } from "react";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Textarea } from "@/components/ui/textarea";
import {
  Home, Sparkles, Download, Box, Palette, User, Zap
} from "lucide-react";
import { Link } from "react-router-dom";

const AssetGenerator = () => {
  const [prompt, setPrompt] = useState("");
  const [assetType, setAssetType] = useState("3d-model");

  const assetTypes = [
    { id: "3d-model", label: "3D Model", icon: Box },
    { id: "texture", label: "Texture", icon: Palette },
    { id: "character", label: "Character", icon: User },
    { id: "effect", label: "VFX", icon: Zap }
  ];

  const templates = [
    { title: "Sci-Fi Crate", type: "3D Model", prompt: "Futuristic metal storage crate with glowing edges" },
    { title: "Stone Wall", type: "Texture", prompt: "Medieval stone wall texture with moss" },
    { id: "fantasy-warrior", title: "Fantasy Warrior", type: "Character", prompt: "Armored knight character" },
    { title: "Magic Particles", type: "VFX", prompt: "Blue magical particle effect" }
  ];

  const generatedAssets = [
    { id: 1, name: "Sci-Fi Crate", type: "3D Model", status: "Ready" },
    { id: 2, name: "Stone Texture", type: "Texture", status: "Ready" },
    { id: 3, name: "Magic Effect", type: "VFX", status: "Generating..." }
  ];

  return (
    <div className="h-screen bg-background flex flex-col">
      {/* Toolbar */}
      <div className="h-12 bg-toolbar border-b border-border flex items-center px-4 gap-2">
        <Link to="/">
          <Button variant="ghost" size="sm">
            <Home className="w-4 h-4" />
          </Button>
        </Link>
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
                  onClick={() => setPrompt(template.prompt)}
                >
                  <div>
                    <h3 className="text-sm font-medium text-foreground mb-1">
                      {template.title}
                    </h3>
                    <p className="text-xs text-muted-foreground mb-2">
                      {template.type}
                    </p>
                    <p className="text-xs text-muted-foreground italic">
                      "{template.prompt}"
                    </p>
                  </div>
                </Card>
              ))}
            </div>
          </ScrollArea>
        </div>

        {/* Main Content */}
        <div className="flex-1 flex flex-col">
          {/* Preview Area */}
          <div className="flex-1 bg-background flex items-center justify-center p-6">
            <div className="w-full max-w-2xl">
              <Card className="p-8">
                <div className="aspect-square border-2 border-dashed border-border rounded-lg flex items-center justify-center mb-6">
                  <div className="text-center">
                    <Box className="w-16 h-16 text-muted-foreground mx-auto mb-4" />
                    <p className="text-sm text-muted-foreground">
                      Generated asset preview
                    </p>
                    <p className="text-xs text-muted-foreground mt-1">
                      Describe your asset to generate
                    </p>
                  </div>
                </div>

                <div className="flex items-center justify-between">
                  <div className="text-sm text-muted-foreground">
                    No asset generated yet
                  </div>
                  <Button variant="outline" disabled>
                    <Download className="w-4 h-4 mr-2" />
                    Download
                  </Button>
                </div>
              </Card>
            </div>
          </div>

          {/* Input Area */}
          <div className="border-t border-border bg-panel p-4">
            <div className="max-w-3xl mx-auto space-y-3">
              <div className="flex gap-2">
                {assetTypes.map((type) => (
                  <Button
                    key={type.id}
                    variant={assetType === type.id ? "default" : "outline"}
                    size="sm"
                    onClick={() => setAssetType(type.id)}
                    className="gap-2"
                  >
                    <type.icon className="w-4 h-4" />
                    {type.label}
                  </Button>
                ))}
              </div>

              <div className="flex gap-2">
                <Textarea
                  placeholder="Describe the asset you want to generate... (e.g., 'Futuristic energy shield with blue glow')"
                  value={prompt}
                  onChange={(e) => setPrompt(e.target.value)}
                  className="min-h-20 resize-none"
                />
                <Button className="gap-2 px-6">
                  <Sparkles className="w-4 h-4" />
                  Generate
                </Button>
              </div>

              <div className="flex items-center justify-between text-xs text-muted-foreground">
                <span>Style: Realistic</span>
                <span>Quality: High</span>
                <span>Format: FBX, PNG</span>
              </div>
            </div>
          </div>
        </div>

        {/* Generated Assets Sidebar */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Generated Assets</span>
          </div>
          <ScrollArea className="flex-1 p-3">
            <div className="space-y-2">
              {generatedAssets.map((asset) => (
                <Card key={asset.id} className="p-3">
                  <div className="flex items-start justify-between mb-2">
                    <div>
                      <h3 className="text-sm font-medium text-foreground">
                        {asset.name}
                      </h3>
                      <p className="text-xs text-muted-foreground">{asset.type}</p>
                    </div>
                    {asset.status === "Ready" && (
                      <Button variant="ghost" size="sm" className="h-6 w-6 p-0">
                        <Download className="w-3 h-3" />
                      </Button>
                    )}
                  </div>
                  <div className="flex items-center gap-2">
                    {asset.status === "Ready" ? (
                      <div className="flex items-center gap-1 text-xs text-success">
                        <div className="w-2 h-2 rounded-full bg-success" />
                        Ready
                      </div>
                    ) : (
                      <div className="flex items-center gap-1 text-xs text-accent">
                        <div className="w-2 h-2 rounded-full bg-accent animate-pulse" />
                        {asset.status}
                      </div>
                    )}
                  </div>
                </Card>
              ))}
            </div>
          </ScrollArea>

          <div className="p-3 border-t border-border">
            <div className="text-xs text-muted-foreground space-y-1">
              <div className="flex justify-between">
                <span>Credits remaining:</span>
                <span className="text-foreground font-medium">250</span>
              </div>
              <div className="flex justify-between">
                <span>Assets generated:</span>
                <span className="text-foreground font-medium">12</span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default AssetGenerator;
