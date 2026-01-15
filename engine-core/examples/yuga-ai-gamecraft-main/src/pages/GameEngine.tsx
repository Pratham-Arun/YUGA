import { useState } from "react";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import {
  Play, Pause, Square, Home, ChevronRight, ChevronDown, 
  Box, Plus, Trash2, Eye, Settings, Code, Terminal
} from "lucide-react";
import { Link } from "react-router-dom";

const GameEngine = () => {
  const [isPlaying, setIsPlaying] = useState(false);
  const [selectedObject, setSelectedObject] = useState("Main Camera");
  const [expandedNodes, setExpandedNodes] = useState<string[]>(["Scene"]);

  const sceneHierarchy = [
    { id: "main-camera", name: "Main Camera", type: "Camera", children: [] },
    { id: "directional-light", name: "Directional Light", type: "Light", children: [] },
    { 
      id: "game-objects", 
      name: "GameObjects", 
      type: "Folder",
      children: [
        { id: "player", name: "Player", type: "GameObject", children: [] },
        { id: "enemy", name: "Enemy", type: "GameObject", children: [] }
      ]
    }
  ];

  const toggleNode = (nodeName: string) => {
    setExpandedNodes(prev => 
      prev.includes(nodeName) 
        ? prev.filter(n => n !== nodeName)
        : [...prev, nodeName]
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
          <Button 
            variant={isPlaying ? "ghost" : "default"} 
            size="sm"
            onClick={() => setIsPlaying(!isPlaying)}
          >
            <Play className="w-4 h-4" />
          </Button>
          <Button variant="ghost" size="sm">
            <Pause className="w-4 h-4" />
          </Button>
          <Button variant="ghost" size="sm" onClick={() => setIsPlaying(false)}>
            <Square className="w-4 h-4" />
          </Button>
        </div>

        <Separator orientation="vertical" className="h-6" />
        
        <div className="flex-1 text-center">
          <span className="text-sm font-medium text-foreground">Game View</span>
        </div>

        <Button variant="ghost" size="sm">
          <Settings className="w-4 h-4" />
        </Button>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* Scene Hierarchy */}
        <div className="w-64 bg-panel border-r border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3 justify-between">
            <span className="text-sm font-medium text-foreground">Hierarchy</span>
            <Button variant="ghost" size="sm" className="h-6 w-6 p-0">
              <Plus className="w-3 h-3" />
            </Button>
          </div>
          <ScrollArea className="flex-1">
            <div className="p-2">
              {sceneHierarchy.map((item) => (
                <div key={item.id} className="mb-1">
                  <div 
                    className={`flex items-center gap-1 px-2 py-1.5 rounded cursor-pointer hover:bg-muted ${
                      selectedObject === item.name ? 'bg-muted' : ''
                    }`}
                    onClick={() => setSelectedObject(item.name)}
                  >
                    {item.children.length > 0 && (
                      <button onClick={(e) => { e.stopPropagation(); toggleNode(item.name); }}>
                        {expandedNodes.includes(item.name) ? (
                          <ChevronDown className="w-4 h-4" />
                        ) : (
                          <ChevronRight className="w-4 h-4" />
                        )}
                      </button>
                    )}
                    <Box className="w-4 h-4 text-muted-foreground" />
                    <span className="text-sm text-foreground">{item.name}</span>
                  </div>
                  {expandedNodes.includes(item.name) && item.children.map((child) => (
                    <div 
                      key={child.id}
                      className={`flex items-center gap-1 px-2 py-1.5 rounded cursor-pointer hover:bg-muted ml-4 ${
                        selectedObject === child.name ? 'bg-muted' : ''
                      }`}
                      onClick={() => setSelectedObject(child.name)}
                    >
                      <Box className="w-4 h-4 text-muted-foreground" />
                      <span className="text-sm text-foreground">{child.name}</span>
                    </div>
                  ))}
                </div>
              ))}
            </div>
          </ScrollArea>
        </div>

        {/* Scene View */}
        <div className="flex-1 flex flex-col">
          <div className="flex-1 bg-background flex items-center justify-center relative">
            <div className="absolute inset-4 border-2 border-dashed border-border rounded-lg flex items-center justify-center">
              <div className="text-center">
                <Box className="w-16 h-16 text-muted-foreground mx-auto mb-4" />
                <p className="text-muted-foreground">Scene View</p>
                <p className="text-xs text-muted-foreground mt-1">
                  {isPlaying ? "Game Running..." : "Press Play to start"}
                </p>
              </div>
            </div>
          </div>

          {/* Console */}
          <div className="h-32 bg-panel border-t border-border">
            <div className="h-8 bg-toolbar border-b border-border flex items-center px-3">
              <Terminal className="w-4 h-4 mr-2 text-muted-foreground" />
              <span className="text-sm font-medium text-foreground">Console</span>
            </div>
            <ScrollArea className="h-24 p-2">
              <div className="text-xs font-mono text-muted-foreground">
                <p>Ready to play...</p>
              </div>
            </ScrollArea>
          </div>
        </div>

        {/* Inspector */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Inspector</span>
          </div>
          <ScrollArea className="flex-1">
            <div className="p-4 space-y-4">
              <div>
                <label className="text-xs font-medium text-foreground mb-2 block">
                  {selectedObject}
                </label>
                <Input placeholder="Tag" className="mb-2" />
                <Input placeholder="Layer" />
              </div>

              <Separator />

              <div>
                <div className="flex items-center justify-between mb-2">
                  <span className="text-sm font-medium text-foreground">Transform</span>
                  <Eye className="w-4 h-4 text-muted-foreground" />
                </div>
                <div className="space-y-2">
                  <div>
                    <label className="text-xs text-muted-foreground">Position</label>
                    <div className="grid grid-cols-3 gap-2 mt-1">
                      <Input placeholder="X" defaultValue="0" className="h-8" />
                      <Input placeholder="Y" defaultValue="0" className="h-8" />
                      <Input placeholder="Z" defaultValue="0" className="h-8" />
                    </div>
                  </div>
                  <div>
                    <label className="text-xs text-muted-foreground">Rotation</label>
                    <div className="grid grid-cols-3 gap-2 mt-1">
                      <Input placeholder="X" defaultValue="0" className="h-8" />
                      <Input placeholder="Y" defaultValue="0" className="h-8" />
                      <Input placeholder="Z" defaultValue="0" className="h-8" />
                    </div>
                  </div>
                  <div>
                    <label className="text-xs text-muted-foreground">Scale</label>
                    <div className="grid grid-cols-3 gap-2 mt-1">
                      <Input placeholder="X" defaultValue="1" className="h-8" />
                      <Input placeholder="Y" defaultValue="1" className="h-8" />
                      <Input placeholder="Z" defaultValue="1" className="h-8" />
                    </div>
                  </div>
                </div>
              </div>

              <Separator />

              <Button variant="outline" size="sm" className="w-full gap-2">
                <Plus className="w-4 h-4" />
                Add Component
              </Button>
            </div>
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default GameEngine;
