import { useState } from "react";
import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { Textarea } from "@/components/ui/textarea";
import {
  Home, Send, Sparkles, Copy, Check, Code, FileCode, ArrowLeft
} from "lucide-react";
import { Link, useNavigate } from "react-router-dom";

const AICodeAssistant = () => {
  const navigate = useNavigate();
  const [input, setInput] = useState("");
  const [copied, setCopied] = useState(false);

  const templates = [
    {
      title: "Player Movement",
      description: "Create basic WASD movement controller",
      icon: Code
    },
    {
      title: "Inventory System",
      description: "Generate item management code",
      icon: Code
    },
    {
      title: "Enemy AI",
      description: "Build patrol and chase behavior",
      icon: Code
    },
    {
      title: "UI Manager",
      description: "Create menu navigation system",
      icon: Code
    }
  ];

  const exampleCode = `using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float moveSpeed = 5f;
    [SerializeField] private float jumpForce = 10f;
    
    private Rigidbody rb;
    private bool isGrounded;
    
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }
    
    void Update()
    {
        HandleMovement();
        HandleJump();
    }
    
    private void HandleMovement()
    {
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        
        Vector3 movement = new Vector3(horizontal, 0f, vertical).normalized;
        transform.Translate(movement * moveSpeed * Time.deltaTime);
    }
    
    private void HandleJump()
    {
        if (Input.GetKeyDown(KeyCode.Space) && isGrounded)
        {
            rb.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
            isGrounded = false;
        }
    }
    
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Ground"))
        {
            isGrounded = true;
        }
    }
}`;

  const handleCopy = () => {
    navigator.clipboard.writeText(exampleCode);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
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
          <Sparkles className="w-4 h-4 text-accent" />
          <span className="text-sm font-medium text-foreground">AI Code Assistant</span>
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
                >
                  <div className="flex items-start gap-2">
                    <div className="w-8 h-8 rounded bg-primary/10 flex items-center justify-center flex-shrink-0">
                      <template.icon className="w-4 h-4 text-primary" />
                    </div>
                    <div>
                      <h3 className="text-sm font-medium text-foreground mb-1">
                        {template.title}
                      </h3>
                      <p className="text-xs text-muted-foreground">
                        {template.description}
                      </p>
                    </div>
                  </div>
                </Card>
              ))}
            </div>
          </ScrollArea>
        </div>

        {/* Main Content */}
        <div className="flex-1 flex flex-col">
          {/* Chat Area */}
          <ScrollArea className="flex-1 p-6">
            <div className="max-w-3xl mx-auto space-y-4">
              {/* User message */}
              <div className="flex justify-end">
                <Card className="p-4 max-w-lg bg-primary/10 border-primary/20">
                  <p className="text-sm text-foreground">
                    Create a player movement script with WASD controls and jumping
                  </p>
                </Card>
              </div>

              {/* AI response */}
              <div className="flex justify-start">
                <Card className="p-4 w-full">
                  <div className="flex items-center gap-2 mb-3">
                    <div className="w-6 h-6 rounded-full bg-accent/10 flex items-center justify-center">
                      <Sparkles className="w-3 h-3 text-accent" />
                    </div>
                    <span className="text-sm font-medium text-foreground">AI Assistant</span>
                  </div>
                  <p className="text-sm text-foreground mb-4">
                    I've created a player movement script with the following features:
                  </p>
                  <ul className="text-sm text-muted-foreground space-y-1 mb-4 ml-4 list-disc">
                    <li>WASD movement controls</li>
                    <li>Spacebar jumping with ground detection</li>
                    <li>Configurable speed and jump force</li>
                    <li>Rigidbody-based physics</li>
                  </ul>

                  <div className="bg-background rounded-lg border border-border overflow-hidden">
                    <div className="bg-toolbar px-3 py-2 flex items-center justify-between border-b border-border">
                      <div className="flex items-center gap-2">
                        <FileCode className="w-4 h-4 text-muted-foreground" />
                        <span className="text-xs text-foreground font-mono">PlayerMovement.cs</span>
                      </div>
                      <Button
                        variant="ghost"
                        size="sm"
                        className="h-7"
                        onClick={handleCopy}
                      >
                        {copied ? (
                          <>
                            <Check className="w-3 h-3 mr-1" />
                            <span className="text-xs">Copied</span>
                          </>
                        ) : (
                          <>
                            <Copy className="w-3 h-3 mr-1" />
                            <span className="text-xs">Copy</span>
                          </>
                        )}
                      </Button>
                    </div>
                    <ScrollArea className="max-h-96">
                      <pre className="p-4 text-xs font-mono text-foreground">
                        <code>{exampleCode}</code>
                      </pre>
                    </ScrollArea>
                  </div>
                </Card>
              </div>
            </div>
          </ScrollArea>

          {/* Input Area */}
          <div className="border-t border-border bg-panel p-4">
            <div className="max-w-3xl mx-auto">
              <div className="flex gap-2">
                <Textarea
                  placeholder="Describe the code you want to generate..."
                  value={input}
                  onChange={(e) => setInput(e.target.value)}
                  className="min-h-20 resize-none"
                />
                <Button className="gap-2 px-6">
                  <Send className="w-4 h-4" />
                  Generate
                </Button>
              </div>
              <p className="text-xs text-muted-foreground mt-2">
                Supports C#, JavaScript, Python, and more
              </p>
            </div>
          </div>
        </div>

        {/* Settings Sidebar */}
        <div className="w-72 bg-panel border-l border-border flex flex-col">
          <div className="h-10 bg-toolbar border-b border-border flex items-center px-3">
            <span className="text-sm font-medium text-foreground">Settings</span>
          </div>
          <ScrollArea className="flex-1 p-4">
            <div className="space-y-4">
              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Language
                </label>
                <select className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground">
                  <option>C#</option>
                  <option>JavaScript</option>
                  <option>Python</option>
                  <option>C++</option>
                </select>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Code Style
                </label>
                <select className="w-full h-9 rounded-md bg-input border border-border px-3 text-sm text-foreground">
                  <option>Standard</option>
                  <option>Compact</option>
                  <option>Verbose</option>
                </select>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Include Comments
                </label>
                <div className="flex items-center gap-2">
                  <input type="checkbox" defaultChecked className="rounded" />
                  <span className="text-sm text-foreground">Add inline comments</span>
                </div>
              </div>

              <Separator />

              <div>
                <label className="text-xs font-medium text-muted-foreground mb-2 block">
                  Error Handling
                </label>
                <div className="flex items-center gap-2">
                  <input type="checkbox" defaultChecked className="rounded" />
                  <span className="text-sm text-foreground">Include try-catch blocks</span>
                </div>
              </div>
            </div>
          </ScrollArea>
        </div>
      </div>
    </div>
  );
};

export default AICodeAssistant;
