import { useState } from "react";
import { Button } from "@/components/ui/button";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import {
  Home, Play, Save, FolderOpen, File, ChevronRight, ChevronDown,
  Search, Settings, Terminal, AlertCircle, ArrowLeft
} from "lucide-react";
import { Link, useNavigate } from "react-router-dom";
import Editor from "@monaco-editor/react";

const sampleCode = `using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float moveSpeed = 5f;
    public float jumpForce = 10f;
    
    private Rigidbody rb;
    private bool isGrounded;
    
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }
    
    void Update()
    {
        // Movement input
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        
        Vector3 movement = new Vector3(horizontal, 0f, vertical);
        transform.Translate(movement * moveSpeed * Time.deltaTime);
        
        // Jump
        if (Input.GetKeyDown(KeyCode.Space) && isGrounded)
        {
            rb.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
            isGrounded = false;
        }
    }
    
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Ground"))
        {
            isGrounded = true;
        }
    }
}`;

const ScriptEditor = () => {
  const navigate = useNavigate();
  const [expandedFolders, setExpandedFolders] = useState<string[]>(["Scripts"]);
  const [activeFile, setActiveFile] = useState("PlayerController.cs");
  const [code, setCode] = useState(sampleCode);

  const projectFiles = [
    {
      name: "Scripts",
      type: "folder",
      children: [
        { name: "PlayerController.cs", type: "file" },
        { name: "EnemyAI.cs", type: "file" },
        { name: "GameManager.cs", type: "file" }
      ]
    },
    {
      name: "Assets",
      type: "folder",
      children: [
        { name: "Materials", type: "folder", children: [] },
        { name: "Textures", type: "folder", children: [] }
      ]
    }
  ];

  const toggleFolder = (folderName: string) => {
    setExpandedFolders(prev =>
      prev.includes(folderName)
        ? prev.filter(f => f !== folderName)
        : [...prev, folderName]
    );
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

        <Button variant="ghost" size="sm">
          <FolderOpen className="w-4 h-4 mr-2" />
          Open
        </Button>
        <Button variant="ghost" size="sm">
          <Save className="w-4 h-4 mr-2" />
          Save
        </Button>
        <Button variant="default" size="sm">
          <Play className="w-4 h-4 mr-2" />
          Run
        </Button>

        <div className="flex-1" />

        <Button variant="ghost" size="sm">
          <Search className="w-4 h-4" />
        </Button>
        <Button variant="ghost" size="sm">
          <Settings className="w-4 h-4" />
        </Button>
      </div>

      <div className="flex-1 flex overflow-hidden">
        {/* File Explorer */}
        <div className="w-64 bg-panel border-r border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Explorer</span>
          </div>
          <ScrollArea className="flex-1">
            <div className="p-2">
              {projectFiles.map((item) => (
                <div key={item.name} className="mb-1">
                  <div
                    className="flex items-center gap-1 px-2 py-1.5 rounded cursor-pointer hover:bg-muted"
                    onClick={() => item.type === "folder" && toggleFolder(item.name)}
                  >
                    {item.type === "folder" && (
                      expandedFolders.includes(item.name) ? (
                        <ChevronDown className="w-4 h-4" />
                      ) : (
                        <ChevronRight className="w-4 h-4" />
                      )
                    )}
                    <span className="text-sm text-foreground">{item.name}</span>
                  </div>
                  {item.type === "folder" && expandedFolders.includes(item.name) && item.children?.map((child) => (
                    <div
                      key={child.name}
                      className={`flex items-center gap-1 px-2 py-1.5 rounded cursor-pointer hover:bg-muted ml-4 ${
                        activeFile === child.name ? 'bg-muted' : ''
                      }`}
                      onClick={() => setActiveFile(child.name)}
                    >
                      <File className="w-4 h-4 text-muted-foreground" />
                      <span className="text-sm text-foreground">{child.name}</span>
                    </div>
                  ))}
                </div>
              ))}
            </div>
          </ScrollArea>
        </div>

        {/* Code Editor */}
        <div className="flex-1 flex flex-col">
          <div className="h-10 bg-panel border-b border-border flex items-center px-3 gap-2">
            <div className="flex items-center gap-2 px-3 py-1 bg-background rounded">
              <File className="w-3 h-3 text-muted-foreground" />
              <span className="text-sm text-foreground">{activeFile}</span>
            </div>
          </div>

          <div className="flex-1">
            <Editor
              height="100%"
              defaultLanguage="csharp"
              value={code}
              onChange={(value) => setCode(value || "")}
              theme="vs-dark"
              options={{
                minimap: { enabled: true },
                fontSize: 14,
                lineNumbers: "on",
                roundedSelection: false,
                scrollBeyondLastLine: false,
                readOnly: false,
                automaticLayout: true,
              }}
            />
          </div>

          {/* Output Console */}
          <div className="h-32 bg-panel border-t border-border">
            <div className="h-8 bg-toolbar border-b border-border flex items-center px-3 gap-4">
              <div className="flex items-center gap-2">
                <Terminal className="w-4 h-4 text-muted-foreground" />
                <span className="text-sm font-medium text-foreground">Output</span>
              </div>
              <button className="text-xs text-muted-foreground hover:text-foreground">Problems</button>
              <button className="text-xs text-muted-foreground hover:text-foreground">Debug Console</button>
            </div>
            <ScrollArea className="h-24 p-2">
              <div className="text-xs font-mono space-y-1">
                <div className="flex items-center gap-2 text-success">
                  <span>✓</span>
                  <span>Build succeeded</span>
                </div>
                <div className="text-muted-foreground">Ready to debug</div>
              </div>
            </ScrollArea>
          </div>
        </div>

        {/* Properties Panel */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Properties</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <h3 className="text-sm font-medium text-foreground mb-2">File Info</h3>
                <div className="space-y-2 text-xs">
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Language:</span>
                    <span className="text-foreground">C#</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Lines:</span>
                    <span className="text-foreground">41</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Size:</span>
                    <span className="text-foreground">1.2 KB</span>
                  </div>
                </div>
              </div>

              <Separator />

              <div>
                <h3 className="text-sm font-medium text-foreground mb-2">AI Suggestions</h3>
                <div className="space-y-2">
                  <div className="p-3 bg-accent/10 rounded border border-accent/20">
                    <div className="flex items-start gap-2">
                      <AlertCircle className="w-4 h-4 text-accent flex-shrink-0 mt-0.5" />
                      <div className="text-xs">
                        <p className="text-foreground font-medium mb-1">Performance Tip</p>
                        <p className="text-muted-foreground">
                          Cache GetComponent calls in Start() to improve performance
                        </p>
                      </div>
                    </div>
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

export default ScriptEditor;
