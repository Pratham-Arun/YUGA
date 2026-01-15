import { Link, useNavigate } from "react-router-dom";
import { useState, useEffect } from "react";
import { Card } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { supabase } from "@/integrations/supabase/client";
import { User } from "@supabase/supabase-js";
import { useToast } from "@/hooks/use-toast";
import { 
  Play, Code, Film, Workflow, Sparkles, Box, FolderPlus, Gamepad2, LogOut, User as UserIcon
} from "lucide-react";

const Dashboard = () => {
  const navigate = useNavigate();
  const { toast } = useToast();
  const [user, setUser] = useState<User | null>(null);
  const [profile, setProfile] = useState<{ username: string | null } | null>(null);

  useEffect(() => {
    const { data: { subscription } } = supabase.auth.onAuthStateChange((event, session) => {
      setUser(session?.user ?? null);
      if (session?.user) {
        loadProfile(session.user.id);
      }
    });

    supabase.auth.getSession().then(({ data: { session } }) => {
      setUser(session?.user ?? null);
      if (session?.user) {
        loadProfile(session.user.id);
      }
    });

    return () => subscription.unsubscribe();
  }, []);

  const loadProfile = async (userId: string) => {
    const { data } = await supabase
      .from("profiles")
      .select("username")
      .eq("id", userId)
      .maybeSingle();
    
    if (data) {
      setProfile(data);
    }
  };

  const handleSignOut = async () => {
    const { error } = await supabase.auth.signOut();
    if (error) {
      toast({
        title: "Error",
        description: error.message,
        variant: "destructive",
      });
    } else {
      toast({
        title: "Signed Out",
        description: "You've been signed out successfully.",
      });
      navigate("/auth");
    }
  };

  const tools = [
    {
      title: "Game Engine",
      description: "Unity-style 3D editor with scene hierarchy and inspector",
      icon: Gamepad2,
      path: "/engine",
      color: "primary"
    },
    {
      title: "Script Editor",
      description: "Professional code editor with syntax highlighting",
      icon: Code,
      path: "/script-editor",
      color: "accent"
    },
    {
      title: "Animation Editor",
      description: "Timeline-based animation system with keyframes",
      icon: Film,
      path: "/animation-editor",
      color: "success"
    },
    {
      title: "Visual Scripting",
      description: "Node-based programming without code",
      icon: Workflow,
      path: "/visual-scripting",
      color: "primary"
    },
    {
      title: "AI Code Assistant",
      description: "Natural language to code generation",
      icon: Sparkles,
      path: "/ai-code-assistant",
      color: "accent"
    },
    {
      title: "Asset Generator",
      description: "AI-powered 3D models and textures",
      icon: Box,
      path: "/asset-generator",
      color: "success"
    },
    {
      title: "3D Engine (Live)",
      description: "Real-time 3D scene editor with Three.js",
      icon: Box,
      path: "/engine-3d",
      color: "primary"
    }
  ];

  return (
    <div className="min-h-screen bg-background">
      <header className="border-b border-border bg-toolbar">
        <div className="container mx-auto px-6 py-4">
          <div className="flex items-center justify-between">
            <div className="flex items-center gap-3">
              <div className="w-10 h-10 rounded-lg flex items-center justify-center">
                <img src="/logo.png" alt="YUGA Logo" className="w-10 h-10 object-contain" />
              </div>
              <div>
                <h1 className="text-2xl font-bold text-foreground">YUGA</h1>
                <p className="text-xs text-muted-foreground">Yielding Unified Game Automation</p>
              </div>
            </div>
            <div className="flex items-center gap-3">
              <Link to="/new-project">
                <Button className="gap-2">
                  <FolderPlus className="w-4 h-4" />
                  New Project
                </Button>
              </Link>
              
              {user ? (
                <>
                  <div className="flex items-center gap-2 px-3 py-2 bg-accent/20 rounded-lg">
                    <UserIcon className="w-4 h-4 text-primary" />
                    <span className="text-sm font-medium">
                      {profile?.username || user.email}
                    </span>
                  </div>
                  <Button variant="outline" size="sm" onClick={handleSignOut}>
                    <LogOut className="w-4 h-4 mr-2" />
                    Sign Out
                  </Button>
                </>
              ) : (
                <Button asChild variant="outline">
                  <Link to="/auth">Sign In</Link>
                </Button>
              )}
            </div>
          </div>
        </div>
      </header>

      <main className="container mx-auto px-6 py-12">
        <div className="mb-8">
          <h2 className="text-3xl font-bold text-foreground mb-2">Welcome to YUGA</h2>
          <p className="text-muted-foreground">
            Your complete AI-powered game development suite. Choose a tool to get started.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {tools.map((tool) => (
            <Link key={tool.path} to={tool.path} className="group">
              <Card className="p-6 h-full hover:border-primary transition-all duration-200 hover:shadow-lg hover:shadow-primary/10">
                <div className="flex flex-col h-full">
                  <div className={`w-12 h-12 rounded-lg bg-${tool.color}/10 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform`}>
                    <tool.icon className={`w-6 h-6 text-${tool.color}`} />
                  </div>
                  <h3 className="text-xl font-semibold text-foreground mb-2">{tool.title}</h3>
                  <p className="text-muted-foreground text-sm flex-grow">{tool.description}</p>
                  <div className="mt-4 flex items-center gap-2 text-primary text-sm font-medium">
                    Open Tool
                    <Play className="w-4 h-4" />
                  </div>
                </div>
              </Card>
            </Link>
          ))}
        </div>

        <div className="mt-12 p-6 bg-card rounded-lg border border-border">
          <div className="flex items-start gap-4">
            <div className="w-12 h-12 rounded-lg bg-accent/10 flex items-center justify-center flex-shrink-0">
              <Sparkles className="w-6 h-6 text-accent" />
            </div>
            <div>
              <h3 className="text-lg font-semibold text-foreground mb-2">AI-Powered Development</h3>
              <p className="text-muted-foreground mb-4">
                YUGA integrates AI assistance throughout your entire development workflow. 
                Generate code, create assets, and automate repetitive tasks with natural language commands.
              </p>
              <div className="flex gap-3">
                <Link to="/ai-code-assistant">
                  <Button variant="outline" size="sm">Try AI Assistant</Button>
                </Link>
                <Link to="/asset-generator">
                  <Button variant="outline" size="sm">Generate Assets</Button>
                </Link>
              </div>
            </div>
          </div>
        </div>
      </main>
    </div>
  );
};

export default Dashboard;
