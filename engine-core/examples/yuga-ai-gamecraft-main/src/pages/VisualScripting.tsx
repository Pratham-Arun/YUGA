import { useState } from "react";
import { Button } from "@/components/ui/button";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Card } from "@/components/ui/card";
import {
  Home, Play, Plus, Zap, Code, Calculator, GitBranch, ArrowLeft, Trash2
} from "lucide-react";
import { useNavigate } from "react-router-dom";

interface Node {
  id: string;
  type: string;
  label: string;
  x: number;
  y: number;
  color: string;
}

const VisualScripting = () => {
  const navigate = useNavigate();
  const [nodes, setNodes] = useState<Node[]>([
    { id: "1", type: "event", label: "On Start", x: 100, y: 150, color: "bg-green-500/20 border-green-500" },
    { id: "2", type: "action", label: "Move Forward", x: 350, y: 150, color: "bg-blue-500/20 border-blue-500" },
    { id: "3", type: "condition", label: "If Health > 0", x: 600, y: 150, color: "bg-orange-500/20 border-orange-500" }
  ]);

  const nodeLibrary = [
    { type: "event", label: "On Start", icon: Zap, color: "bg-green-500/20 border-green-500" },
    { type: "event", label: "On Update", icon: Zap, color: "bg-green-500/20 border-green-500" },
    { type: "event", label: "On Collision", icon: Zap, color: "bg-green-500/20 border-green-500" },
    { type: "action", label: "Move", icon: Code, color: "bg-blue-500/20 border-blue-500" },
    { type: "action", label: "Rotate", icon: Code, color: "bg-blue-500/20 border-blue-500" },
    { type: "action", label: "Destroy", icon: Code, color: "bg-blue-500/20 border-blue-500" },
    { type: "condition", label: "If", icon: GitBranch, color: "bg-orange-500/20 border-orange-500" },
    { type: "condition", label: "While", icon: GitBranch, color: "bg-orange-500/20 border-orange-500" },
    { type: "math", label: "Add", icon: Calculator, color: "bg-purple-500/20 border-purple-500" },
    { type: "math", label: "Multiply", icon: Calculator, color: "bg-purple-500/20 border-purple-500" }
  ];

  const addNode = (template: any) => {
    const newNode: Node = {
      id: Date.now().toString(),
      type: template.type,
      label: template.label,
      x: 100 + Math.random() * 300,
      y: 100 + Math.random() * 300,
      color: template.color
    };
    setNodes([...nodes, newNode]);
  };

  const deleteNode = (id: string) => {
    setNodes(nodes.filter(n => n.id !== id));
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
          <GitBranch className="w-4 h-4 text-primary" />
          <span className="text-sm font-medium text-foreground">Visual Scripting</span>
        </div>

        <div className="flex-1" />

        <Button variant="default" size="sm">
          <Play className="w-4 h-4 mr-2" />
          Execute
        </Button>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* Node Library */}
        <div className="w-64 bg-panel border-r border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Node Library</span>
          </div>
          <ScrollArea className="flex-1">
            <div className="p-3 space-y-3">
              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Events</h3>
                <div className="space-y-1">
                  {nodeLibrary.filter(n => n.type === "event").map((node, i) => (
                    <Card
                      key={i}
                      className="p-2 cursor-pointer hover:border-primary transition-colors"
                      onClick={() => addNode(node)}
                    >
                      <div className="flex items-center gap-2">
                        <div className="w-6 h-6 rounded bg-green-500/10 flex items-center justify-center">
                          <node.icon className="w-3 h-3 text-green-500" />
                        </div>
                        <span className="text-xs text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Actions</h3>
                <div className="space-y-1">
                  {nodeLibrary.filter(n => n.type === "action").map((node, i) => (
                    <Card
                      key={i}
                      className="p-2 cursor-pointer hover:border-primary transition-colors"
                      onClick={() => addNode(node)}
                    >
                      <div className="flex items-center gap-2">
                        <div className="w-6 h-6 rounded bg-blue-500/10 flex items-center justify-center">
                          <node.icon className="w-3 h-3 text-blue-500" />
                        </div>
                        <span className="text-xs text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Logic</h3>
                <div className="space-y-1">
                  {nodeLibrary.filter(n => n.type === "condition").map((node, i) => (
                    <Card
                      key={i}
                      className="p-2 cursor-pointer hover:border-primary transition-colors"
                      onClick={() => addNode(node)}
                    >
                      <div className="flex items-center gap-2">
                        <div className="w-6 h-6 rounded bg-orange-500/10 flex items-center justify-center">
                          <node.icon className="w-3 h-3 text-orange-500" />
                        </div>
                        <span className="text-xs text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Math</h3>
                <div className="space-y-1">
                  {nodeLibrary.filter(n => n.type === "math").map((node, i) => (
                    <Card
                      key={i}
                      className="p-2 cursor-pointer hover:border-primary transition-colors"
                      onClick={() => addNode(node)}
                    >
                      <div className="flex items-center gap-2">
                        <div className="w-6 h-6 rounded bg-purple-500/10 flex items-center justify-center">
                          <node.icon className="w-3 h-3 text-purple-500" />
                        </div>
                        <span className="text-xs text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>
            </div>
          </ScrollArea>
        </div>

        {/* Canvas */}
        <div className="flex-1 bg-background relative overflow-hidden">
          {/* Grid background */}
          <div 
            className="absolute inset-0" 
            style={{
              backgroundImage: `
                linear-gradient(to right, rgba(255,255,255,0.05) 1px, transparent 1px),
                linear-gradient(to bottom, rgba(255,255,255,0.05) 1px, transparent 1px)
              `,
              backgroundSize: '20px 20px'
            }}
          />

          {/* Nodes */}
          <div className="relative w-full h-full">
            {nodes.map((node) => (
              <Card
                key={node.id}
                className={`absolute p-3 ${node.color} border-2 cursor-move hover:shadow-lg transition-shadow`}
                style={{ left: node.x, top: node.y, minWidth: '150px' }}
              >
                <div className="flex items-center justify-between mb-2">
                  <span className="text-sm font-medium text-foreground">{node.label}</span>
                  <Button
                    variant="ghost"
                    size="sm"
                    className="h-5 w-5 p-0"
                    onClick={() => deleteNode(node.id)}
                  >
                    <Trash2 className="w-3 h-3" />
                  </Button>
                </div>
                <div className="flex gap-2">
                  <div className="w-2 h-2 rounded-full bg-foreground/50" title="Input" />
                  <div className="flex-1" />
                  <div className="w-2 h-2 rounded-full bg-foreground/50" title="Output" />
                </div>
              </Card>
            ))}
          </div>

          {/* Instructions */}
          {nodes.length === 0 && (
            <div className="absolute inset-0 flex items-center justify-center">
              <Card className="p-6 text-center max-w-md">
                <Plus className="w-12 h-12 text-muted-foreground mx-auto mb-4" />
                <h3 className="text-lg font-medium text-foreground mb-2">
                  Start Building Your Logic
                </h3>
                <p className="text-sm text-muted-foreground">
                  Click nodes from the library to add them to the canvas.
                  Connect nodes to create game logic without code!
                </p>
              </Card>
            </div>
          )}
        </div>

        {/* Properties Panel */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Properties</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <h3 className="text-sm font-medium text-foreground mb-2">Graph Info</h3>
                <div className="space-y-2 text-xs">
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Nodes:</span>
                    <span className="text-foreground">{nodes.length}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Connections:</span>
                    <span className="text-foreground">0</span>
                  </div>
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-sm font-medium text-foreground mb-2">Quick Actions</h3>
                <div className="space-y-2">
                  <Button variant="outline" size="sm" className="w-full justify-start">
                    <Plus className="w-4 h-4 mr-2" />
                    Add Variable
                  </Button>
                  <Button variant="outline" size="sm" className="w-full justify-start">
                    <Code className="w-4 h-4 mr-2" />
                    Export Code
                  </Button>
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-sm font-medium text-foreground mb-2">Tips</h3>
                <div className="text-xs text-muted-foreground space-y-2">
                  <p>• Click nodes in the library to add them</p>
                  <p>• Drag nodes to reposition</p>
                  <p>• Connect output to input ports</p>
                  <p>• Use Execute to run your logic</p>
                </div>
              </div>
            </div>
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default VisualScripting;
