import { NavLink } from "@/components/NavLink";
import { 
  Gamepad2, Code, Film, Workflow, Sparkles, Box, User as UserIcon, LogOut 
} from "lucide-react";
import { User } from "@supabase/supabase-js";
import {
  Sidebar,
  SidebarContent,
  SidebarGroup,
  SidebarGroupContent,
  SidebarGroupLabel,
  SidebarMenu,
  SidebarMenuItem,
  SidebarMenuButton,
  SidebarFooter,
  useSidebar,
} from "@/components/ui/sidebar";
import { Button } from "@/components/ui/button";
import { Separator } from "@/components/ui/separator";

const tools = [
  {
    title: "Game Engine",
    icon: Gamepad2,
    path: "/engine",
  },
  {
    title: "Script Editor",
    icon: Code,
    path: "/script-editor",
  },
  {
    title: "Animation Editor",
    icon: Film,
    path: "/animation-editor",
  },
  {
    title: "Visual Scripting",
    icon: Workflow,
    path: "/visual-scripting",
  },
  {
    title: "AI Code Assistant",
    icon: Sparkles,
    path: "/ai-code-assistant",
  },
  {
    title: "Asset Generator",
    icon: Box,
    path: "/asset-generator",
  },
];

interface AppSidebarProps {
  user: User | null;
  profile: { username: string | null } | null;
  onSignOut: () => void;
}

export function AppSidebar({ user, profile, onSignOut }: AppSidebarProps) {
  const { open } = useSidebar();

  return (
    <Sidebar collapsible="icon">
      <SidebarContent>
        <SidebarGroup>
          <SidebarGroupLabel>Tools</SidebarGroupLabel>
          <SidebarGroupContent>
            <SidebarMenu>
              {tools.map((tool) => (
                <SidebarMenuItem key={tool.path}>
                  <SidebarMenuButton asChild>
                    <NavLink 
                      to={tool.path} 
                      className="hover:bg-sidebar-accent"
                      activeClassName="bg-sidebar-accent text-sidebar-primary font-medium"
                    >
                      <tool.icon className="h-4 w-4" />
                      <span>{tool.title}</span>
                    </NavLink>
                  </SidebarMenuButton>
                </SidebarMenuItem>
              ))}
            </SidebarMenu>
          </SidebarGroupContent>
        </SidebarGroup>
      </SidebarContent>

      <SidebarFooter>
        {user && (
          <div className="space-y-2">
            <Separator />
            <div className="flex items-center gap-2 px-2 py-1.5">
              <UserIcon className="h-4 w-4 text-sidebar-primary" />
              {open && (
                <span className="text-sm font-medium truncate">
                  {profile?.username || user.email}
                </span>
              )}
            </div>
            <Button 
              variant="outline" 
              size="sm" 
              onClick={onSignOut}
              className="w-full justify-start"
            >
              <LogOut className="h-4 w-4" />
              {open && <span className="ml-2">Sign Out</span>}
            </Button>
          </div>
        )}
      </SidebarFooter>
    </Sidebar>
  );
}
