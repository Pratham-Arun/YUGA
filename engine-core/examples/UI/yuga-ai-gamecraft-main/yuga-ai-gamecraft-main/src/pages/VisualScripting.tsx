import { useState } from "react";
import { Button } from "@/components/ui/button";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Card } from "@/components/ui/card";
import {
  Home, Play, Plus, Zap, Code, Calculator, GitBranch
} from "lucide-react";
import { Link } from "react-router-dom";

interface Node {
  id: string;
  type: string;
  label: string;
  x: number;
  y: number;
  icon: any;
  color: string;
}

const VisualScripting = () => {
  const [nodes, setNodes] = useState<Node[]>([
    { id: "1", type: "event", label: "On Start", x: 100, y: 100, icon: Zap, color: "success" },
    { id: "2", type: "action", label: "Move Forward", x: 350, y: 100, icon: Code, color: "primary" },
    { id: "3", type: "condition", label: "If Health > 0", x: 600, y: 100, icon: GitBranch, color: "accent" }
  ]);

  const nodeLibrary = [
    { type: "event", label: "On Start", icon: Zap, color: "success" },
    { type: "event", label: "On Update", icon: Zap, color: "success" },
    { type: "event", label: "On Collision", icon: Zap, color: "success" },
    { type: "action", label: "Move", icon: Code, color: "primary" },
    { type: "action", label: "Rotate", icon: Code, color: "primary" },
    { type: "action", label: "Destroy", icon: Code, color: "primary" },
    { type: "condition", label: "If", icon: GitBranch, color: "accent" },
    { type: "condition", label: "While", icon: GitBranch, color: "accent" },
    { type: "math", label: "Add", icon: Calculator, color: "muted" },
    { type: "math", label: "Multiply", icon: Calculator, color: "muted" }
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

        <Button variant="default" size="sm">
          <Play className="w-4 h-4 mr-2" />
          Execute
        </Button>

        <div className="flex-1 text-center">
          <span className="text-sm font-medium text-foreground">Visual Script</span>
        </div>

        <Button variant="ghost" size="sm">
          <Plus className="w-4 h-4" />
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
                <div className="space-y-2">
                  {nodeLibrary.filter(n => n.type === "event").map((node, i) => (
                    <Card
                      key={i}
                      className="p-3 cursor-pointer hover:border-primary transition-colors"
                      draggable
                    >
                      <div className="flex items-center gap-2">
                        <div className={`w-8 h-8 rounded bg-${node.color}/10 flex items-center justify-center`}>
                          <node.icon className={`w-4 h-4 text-${node.color}`} />
                        </div>
                        <span className="text-sm text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Actions</h3>
                <div className="space-y-2">
                  {nodeLibrary.filter(n => n.type === "action").map((node, i) => (
                    <Card
                      key={i}
                      className="p-3 cursor-pointer hover:border-primary transition-colors"
                      draggable
                    >
                      <div className="flex items-center gap-2">
                        <div className={`w-8 h-8 rounded bg-${node.color}/10 flex items-center justify-center`}>
                          <node.icon className={`w-4 h-4 text-${node.color}`} />
                        </div>
                        <span className="text-sm text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Logic</h3>
                <div className="space-y-2">
                  {nodeLibrary.filter(n => n.type === "condition").map((node, i) => (
                    <Card
                      key={i}
                      className="p-3 cursor-pointer hover:border-primary transition-colors"
                      draggable
                    >
                      <div className="flex items-center gap-2">
                        <div className={`w-8 h-8 rounded bg-${node.color}/10 flex items-center justify-center`}>
                          <node.icon className={`w-4 h-4 text-${node.color}`} />
                        </div>
                        <span className="text-sm text-foreground">{node.label}</span>
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-xs font-medium text-muted-foreground mb-2">Math</h3>
                <div className="space-y-2">
                  {nodeLibrary.filter(n => n.type === "math").map((node, i) => (
                    <Card
                      key={i}
                      className="p-3 cursor-pointer hover:border-primary transition-colors"
                      draggable
                    >
                      <div className="flex items-center gap-2">
                        <div className="w-8 h-8 rounded bg-muted flex items-center justify-center">
                          <node.icon className="w-4 h-4 text-muted-foreground" />
                        </div>
                        <span className="text-sm text-foreground">{node.label}</span>
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
                linear-gradient(hsl(var(--border)) 1px, transparent 1px),
                linear-gradient(90deg, hsl(var(--border)) 1px, transparent 1px)
              `,
              backgroundSize: '20px 20px'
            }}
          />

          {/* Nodes */}
          <div className="relative w-full h-full">
            {nodes.map((node) => (
              <Card
                key={node.id}
                className="absolute p-4 cursor-move hover:border-primary transition-colors"
                style={{ left: node.x, top: node.y }}
              >
                <div className="flex items-center gap-3">
                  <div className={`w-10 h-10 rounded bg-${node.color}/10 flex items-center justify-center`}>
                    <node.icon className={`w-5 h-5 text-${node.color}`} />
                  </div>
                  <div>
                    <div className="text-xs text-muted-foreground uppercase">{node.type}</div>
                    <div className="text-sm font-medium text-foreground">{node.label}</div>
                  </div>
                </div>
                <div className="mt-3 flex justify-between">
                  <div className="w-3 h-3 rounded-full bg-primary border-2 border-background" />
                  <div className="w-3 h-3 rounded-full bg-primary border-2 border-background" />
                </div>
              </Card>
            ))}

            {/* Connection lines */}
            <svg className="absolute inset-0 pointer-events-none">
              <line
                x1={nodes[0].x + 100}
                y1={nodes[0].y + 60}
                x2={nodes[1].x}
                y2={nodes[1].y + 60}
                stroke="hsl(var(--primary))"
                strokeWidth="2"
              />
              <line
                x1={nodes[1].x + 100}
                y1={nodes[1].y + 60}
                x2={nodes[2].x}
                y2={nodes[2].y + 60}
                stroke="hsl(var(--primary))"
                strokeWidth="2"
              />
            </svg>
          </div>
        </div>

        {/* Properties */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Node Properties</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Node Type
                </label>
                <div className="text-sm text-foreground">Event</div>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Label
                </label>
                <input
                  type="text"
                  className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground"
                  defaultValue="On Start"
                />
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Description
                </label>
                <textarea
                  className="w-full min-h-20 rounded-md bg-input border border-border px-3 py-2 text-sm text-foreground"
                  placeholder="Add node description..."
                />
              </div>

              <Separator />

              <div className="space-y-2">
                <h3 className="text-xs font-medium text-muted-foreground">Connections</h3>
                <div className="text-xs text-foreground">
                  <div className="flex justify-between py-1">
                    <span className="text-muted-foreground">Input:</span>
                    <span>None</span>
                  </div>
                  <div className="flex justify-between py-1">
                    <span className="text-muted-foreground">Output:</span>
                    <span>Move Forward</span>
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

export default VisualScripting;
