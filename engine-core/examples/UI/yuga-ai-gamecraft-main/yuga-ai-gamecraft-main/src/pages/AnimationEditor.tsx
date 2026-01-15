import { useState } from "react";
import { Button } from "@/components/ui/button";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Slider } from "@/components/ui/slider";
import {
  Home, Play, Pause, SkipBack, SkipForward, Plus,
  Eye, EyeOff, Lock, Unlock
} from "lucide-react";
import { Link } from "react-router-dom";

const AnimationEditor = () => {
  const [isPlaying, setIsPlaying] = useState(false);
  const [currentFrame, setCurrentFrame] = useState(0);
  const [visibleLayers, setVisibleLayers] = useState<string[]>(["Position", "Rotation", "Scale"]);

  const animationLayers = [
    { id: "position", name: "Position", color: "primary", keyframes: [0, 30, 60, 90] },
    { id: "rotation", name: "Rotation", color: "accent", keyframes: [15, 45, 75] },
    { id: "scale", name: "Scale", color: "success", keyframes: [0, 40, 80] }
  ];

  const toggleLayerVisibility = (layerName: string) => {
    setVisibleLayers(prev =>
      prev.includes(layerName)
        ? prev.filter(l => l !== layerName)
        : [...prev, layerName]
    );
  };

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

        <div className="flex gap-1">
          <Button variant="ghost" size="sm">
            <SkipBack className="w-4 h-4" />
          </Button>
          <Button
            variant={isPlaying ? "ghost" : "default"}
            size="sm"
            onClick={() => setIsPlaying(!isPlaying)}
          >
            {isPlaying ? <Pause className="w-4 h-4" /> : <Play className="w-4 h-4" />}
          </Button>
          <Button variant="ghost" size="sm">
            <SkipForward className="w-4 h-4" />
          </Button>
        </div>

        <Separator orientation="vertical" className="h-6" />

        <div className="flex items-center gap-2">
          <span className="text-sm text-muted-foreground">Frame:</span>
          <span className="text-sm font-mono text-foreground w-12">{currentFrame}</span>
          <span className="text-sm text-muted-foreground">/ 120</span>
        </div>

        <div className="flex-1" />

        <Button variant="ghost" size="sm">
          <Plus className="w-4 h-4 mr-2" />
          Add Keyframe
        </Button>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* Preview */}
        <div className="flex-1 flex flex-col">
          <div className="flex-1 bg-background flex items-center justify-center">
            <div className="w-64 h-64 border-2 border-dashed border-border rounded-lg flex items-center justify-center">
              <div className="text-center">
                <div className="w-16 h-16 bg-primary/20 rounded-lg mx-auto mb-4" />
                <p className="text-sm text-muted-foreground">Animation Preview</p>
              </div>
            </div>
          </div>

          {/* Timeline */}
          <div className="h-64 bg-panel border-t border-border flex flex-col">
            <div className="h-10 bg-toolbar border-b border-border flex items-center px-4">
              <span className="text-sm font-medium text-foreground">Timeline</span>
            </div>

            <div className="flex-1 flex">
              {/* Layer Names */}
              <div className="w-48 bg-panel border-r border-border">
                <div className="h-10 border-b border-border" />
                {animationLayers.map((layer) => (
                  <div
                    key={layer.id}
                    className="h-12 border-b border-border flex items-center px-3 gap-2"
                  >
                    <button onClick={() => toggleLayerVisibility(layer.name)}>
                      {visibleLayers.includes(layer.name) ? (
                        <Eye className="w-4 h-4 text-muted-foreground" />
                      ) : (
                        <EyeOff className="w-4 h-4 text-muted-foreground" />
                      )}
                    </button>
                    <span className="text-sm text-foreground">{layer.name}</span>
                  </div>
                ))}
              </div>

              {/* Timeline Grid */}
              <ScrollArea className="flex-1">
                <div className="relative h-full">
                  {/* Frame markers */}
                  <div className="h-10 border-b border-border flex">
                    {Array.from({ length: 121 }, (_, i) => (
                      <div
                        key={i}
                        className={`flex-shrink-0 w-8 border-l border-border flex items-center justify-center ${
                          i % 10 === 0 ? 'border-l-2' : ''
                        }`}
                      >
                        {i % 10 === 0 && (
                          <span className="text-xs text-muted-foreground">{i}</span>
                        )}
                      </div>
                    ))}
                  </div>

                  {/* Animation tracks */}
                  {animationLayers.map((layer) => (
                    <div
                      key={layer.id}
                      className="h-12 border-b border-border relative"
                    >
                      <div className="absolute inset-0 flex">
                        {Array.from({ length: 121 }, (_, i) => (
                          <div
                            key={i}
                            className="flex-shrink-0 w-8 border-l border-border/50"
                          />
                        ))}
                      </div>
                      {/* Keyframes */}
                      {visibleLayers.includes(layer.name) &&
                        layer.keyframes.map((frame) => (
                          <div
                            key={frame}
                            className={`absolute top-1/2 -translate-y-1/2 w-3 h-3 rounded-full bg-${layer.color} border-2 border-background`}
                            style={{ left: `${frame * 8 + 12}px` }}
                          />
                        ))}
                    </div>
                  ))}

                  {/* Playhead */}
                  <div
                    className="absolute top-0 bottom-0 w-0.5 bg-accent pointer-events-none"
                    style={{ left: `${currentFrame * 8 + 16}px` }}
                  >
                    <div className="absolute -top-2 left-1/2 -translate-x-1/2 w-3 h-3 bg-accent rotate-45" />
                  </div>
                </div>
              </ScrollArea>
            </div>

            {/* Playback Controls */}
            <div className="h-12 bg-toolbar border-t border-border flex items-center px-4 gap-4">
              <Slider
                value={[currentFrame]}
                onValueChange={(value) => setCurrentFrame(value[0])}
                max={120}
                step={1}
                className="flex-1"
              />
            </div>
          </div>
        </div>

        {/* Properties */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Keyframe Properties</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Interpolation
                </label>
                <select className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground">
                  <option>Linear</option>
                  <option>Ease In</option>
                  <option>Ease Out</option>
                  <option>Ease In-Out</option>
                </select>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Value
                </label>
                <input
                  type="number"
                  className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground"
                  placeholder="0.0"
                />
              </div>

              <Separator />

              <div className="space-y-2">
                <div className="flex items-center justify-between">
                  <span className="text-xs text-muted-foreground">Lock Layer</span>
                  <Lock className="w-4 h-4 text-muted-foreground" />
                </div>
                <div className="flex items-center justify-between">
                  <span className="text-xs text-muted-foreground">Show Curve</span>
                  <Eye className="w-4 h-4 text-muted-foreground" />
                </div>
              </div>
            </div>
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default AnimationEditor;
