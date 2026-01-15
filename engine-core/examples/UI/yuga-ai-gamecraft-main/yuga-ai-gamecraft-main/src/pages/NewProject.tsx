import { useState } from "react";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import {
  Home, Gamepad2, Sparkles, Box, Palette, ArrowRight
} from "lucide-react";
import { Link, useNavigate } from "react-router-dom";

const NewProject = () => {
  const navigate = useNavigate();
  const [projectName, setProjectName] = useState("My Game");
  const [selectedTemplate, setSelectedTemplate] = useState("blank");

  const templates = [
    {
      id: "blank",
      title: "Blank Project",
      description: "Start from scratch with an empty scene",
      icon: Box,
      color: "primary"
    },
    {
      id: "fps",
      title: "First Person Shooter",
      description: "FPS template with player controller and weapons",
      icon: Gamepad2,
      color: "accent"
    },
    {
      id: "platformer",
      title: "2D Platformer",
      description: "Side-scrolling platformer with physics",
      icon: Gamepad2,
      color: "success"
    },
    {
      id: "puzzle",
      title: "Puzzle Game",
      description: "Grid-based puzzle game framework",
      icon: Gamepad2,
      color: "primary"
    },
    {
      id: "racing",
      title: "Racing Game",
      description: "Vehicle physics and track system",
      icon: Gamepad2,
      color: "accent"
    },
    {
      id: "rpg",
      title: "RPG",
      description: "Role-playing game with inventory and quests",
      icon: Gamepad2,
      color: "success"
    }
  ];

  const handleCreate = () => {
    // Navigate to the engine after project creation
    navigate("/engine");
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

        <div className="flex items-center gap-2">
          <Sparkles className="w-4 h-4 text-accent" />
          <span className="text-sm font-medium text-foreground">New Project</span>
        </div>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* Main Content */}
        <div className="flex-1 flex flex-col">
          <ScrollArea className="flex-1">
            <div className="container max-w-5xl mx-auto p-8">
              <div className="mb-8">
                <h1 className="text-3xl font-bold text-foreground mb-2">
                  Create New Project
                </h1>
                <p className="text-muted-foreground">
                  Choose a template to get started quickly, or start from scratch
                </p>
              </div>

              {/* Project Settings */}
              <Card className="p-6 mb-6">
                <h2 className="text-lg font-semibold text-foreground mb-4">
                  Project Settings
                </h2>
                <div className="space-y-4">
                  <div>
                    <label className="text-sm font-medium text-foreground mb-2 block">
                      Project Name
                    </label>
                    <Input
                      value={projectName}
                      onChange={(e) => setProjectName(e.target.value)}
                      placeholder="Enter project name"
                    />
                  </div>

                  <div>
                    <label className="text-sm font-medium text-foreground mb-2 block">
                      Location
                    </label>
                    <div className="flex gap-2">
                      <Input
                        value="/Projects/MyGame"
                        readOnly
                        className="flex-1"
                      />
                      <Button variant="outline">Browse</Button>
                    </div>
                  </div>
                </div>
              </Card>

              {/* Templates */}
              <div className="mb-6">
                <h2 className="text-lg font-semibold text-foreground mb-4">
                  Select Template
                </h2>
                <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
                  {templates.map((template) => (
                    <Card
                      key={template.id}
                      className={`p-4 cursor-pointer transition-all hover:border-primary ${
                        selectedTemplate === template.id ? 'border-primary bg-primary/5' : ''
                      }`}
                      onClick={() => setSelectedTemplate(template.id)}
                    >
                      <div className="flex items-start gap-3">
                        <div className={`w-12 h-12 rounded-lg bg-${template.color}/10 flex items-center justify-center flex-shrink-0`}>
                          <template.icon className={`w-6 h-6 text-${template.color}`} />
                        </div>
                        <div className="flex-1">
                          <h3 className="text-sm font-semibold text-foreground mb-1">
                            {template.title}
                          </h3>
                          <p className="text-xs text-muted-foreground">
                            {template.description}
                          </p>
                        </div>
                        {selectedTemplate === template.id && (
                          <div className="w-5 h-5 rounded-full bg-primary flex items-center justify-center">
                            <div className="w-2 h-2 rounded-full bg-primary-foreground" />
                          </div>
                        )}
                      </div>
                    </Card>
                  ))}
                </div>
              </div>

              {/* AI Generation Option */}
              <Card className="p-6 bg-gradient-to-r from-accent/5 to-primary/5 border-accent/20">
                <div className="flex items-start gap-4">
                  <div className="w-12 h-12 rounded-lg bg-accent/10 flex items-center justify-center flex-shrink-0">
                    <Sparkles className="w-6 h-6 text-accent" />
                  </div>
                  <div className="flex-1">
                    <h3 className="text-lg font-semibold text-foreground mb-2">
                      AI-Generated Project
                    </h3>
                    <p className="text-sm text-muted-foreground mb-4">
                      Describe your game idea, and let AI generate a custom project template
                      with scripts, assets, and game mechanics tailored to your vision.
                    </p>
                    <div className="flex gap-2">
                      <Input
                        placeholder="E.g., 'A space shooter with power-ups and boss fights'"
                        className="flex-1"
                      />
                      <Button variant="outline" className="gap-2">
                        <Sparkles className="w-4 h-4" />
                        Generate
                      </Button>
                    </div>
                  </div>
                </div>
              </Card>
            </div>
          </ScrollArea>

          {/* Bottom Bar */}
          <div className="h-16 bg-panel border-t border-border flex items-center px-8">
            <div className="container max-w-5xl mx-auto flex items-center justify-between">
              <div className="text-sm text-muted-foreground">
                {selectedTemplate !== "blank" && (
                  <span>Selected: {templates.find(t => t.id === selectedTemplate)?.title}</span>
                )}
              </div>
              <div className="flex gap-3">
                <Link to="/">
                  <Button variant="outline">Cancel</Button>
                </Link>
                <Button onClick={handleCreate} className="gap-2">
                  Create Project
                  <ArrowRight className="w-4 h-4" />
                </Button>
              </div>
            </div>
          </div>
        </div>

        {/* Preview Sidebar */}
        <div className="w-96 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Template Preview</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            {selectedTemplate && (
              <div className="space-y-4">
                <div className="aspect-video bg-background rounded-lg border border-border flex items-center justify-center">
                  <Palette className="w-12 h-12 text-muted-foreground" />
                </div>

                <div>
                  <h3 className="text-sm font-semibold text-foreground mb-2">
                    {templates.find(t => t.id === selectedTemplate)?.title}
                  </h3>
                  <p className="text-xs text-muted-foreground mb-4">
                    {templates.find(t => t.id === selectedTemplate)?.description}
                  </p>
                </div>

                <Separator />

                <div>
                  <h4 className="text-xs font-medium text-foreground mb-2">Includes:</h4>
                  <ul className="text-xs text-muted-foreground space-y-1 ml-4 list-disc">
                    <li>Pre-configured scenes</li>
                    <li>Sample scripts and components</li>
                    <li>Asset packages</li>
                    <li>Documentation</li>
                  </ul>
                </div>

                <Separator />

                <div>
                  <h4 className="text-xs font-medium text-foreground mb-2">Requirements:</h4>
                  <div className="text-xs text-muted-foreground space-y-1">
                    <div className="flex justify-between">
                      <span>Disk Space:</span>
                      <span className="text-foreground">~500 MB</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Platform:</span>
                      <span className="text-foreground">All</span>
                    </div>
                  </div>
                </div>
              </div>
            )}
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default NewProject;
