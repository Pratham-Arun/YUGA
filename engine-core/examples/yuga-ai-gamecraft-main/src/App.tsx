import { Toaster } from "@/components/ui/toaster";
import { Toaster as Sonner } from "@/components/ui/sonner";
import { TooltipProvider } from "@/components/ui/tooltip";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Dashboard from "./pages/Dashboard";
import GameEngine from "./pages/GameEngine";
import GameEngine3D from "./pages/GameEngine3D";
import ScriptEditor from "./pages/ScriptEditor";
import AnimationEditor from "./pages/AnimationEditor";
import VisualScripting from "./pages/VisualScripting";
import AICodeAssistant from "./pages/AICodeAssistant";
import AssetGenerator from "./pages/AssetGenerator";
import NewProject from "./pages/NewProject";
import NotFound from "./pages/NotFound";
import Auth from "./pages/Auth";

const queryClient = new QueryClient();

const App = () => (
  <QueryClientProvider client={queryClient}>
    <TooltipProvider>
      {/* Background Logo Watermark */}
      <div className="fixed inset-0 flex items-center justify-center pointer-events-none z-0">
        <img 
          src="/logo.png" 
          alt="YUGA Background" 
          className="w-[50vw] max-w-[800px] h-auto opacity-10"
        />
      </div>
      <div className="relative z-10">
        <Toaster />
        <Sonner />
        <BrowserRouter>
          <Routes>
            <Route path="/" element={<Dashboard />} />
            <Route path="/engine" element={<GameEngine />} />
            <Route path="/engine-3d" element={<GameEngine3D />} />
            <Route path="/script-editor" element={<ScriptEditor />} />
            <Route path="/animation-editor" element={<AnimationEditor />} />
            <Route path="/visual-scripting" element={<VisualScripting />} />
            <Route path="/ai-code-assistant" element={<AICodeAssistant />} />
            <Route path="/asset-generator" element={<AssetGenerator />} />
            <Route path="/new-project" element={<NewProject />} />
            <Route path="/auth" element={<Auth />} />
            {/* ADD ALL CUSTOM ROUTES ABOVE THE CATCH-ALL "*" ROUTE */}
            <Route path="*" element={<NotFound />} />
          </Routes>
        </BrowserRouter>
      </div>
    </TooltipProvider>
  </QueryClientProvider>
);

export default App;
