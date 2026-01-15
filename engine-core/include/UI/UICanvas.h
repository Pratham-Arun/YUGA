#pragma once
#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include <string>
#include <vector>
#include <memory>

namespace YUGA {

enum class UIAnchor {
    TopLeft,
    TopCenter,
    TopRight,
    MiddleLeft,
    MiddleCenter,
    MiddleRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

class UIElement {
public:
    UIElement() : position(0, 0), size(100, 100), anchor(UIAnchor::TopLeft), visible(true) {}
    virtual ~UIElement() = default;
    
    virtual void Update(float deltaTime) {}
    virtual void Render() = 0;
    
    // Transform
    Vector2 position;
    Vector2 size;
    UIAnchor anchor;
    
    // State
    bool visible;
    
    // Hierarchy
    void AddChild(std::shared_ptr<UIElement> child) { children.push_back(child); }
    const std::vector<std::shared_ptr<UIElement>>& GetChildren() const { return children; }
    
protected:
    std::vector<std::shared_ptr<UIElement>> children;
};

class UIText : public UIElement {
public:
    std::string text;
    Vector4 color;
    float fontSize;
    
    UIText() : text(""), color(1, 1, 1, 1), fontSize(16.0f) {}
    void Render() override;
};

class UIImage : public UIElement {
public:
    std::string texturePath;
    Vector4 color;
    
    UIImage() : texturePath(""), color(1, 1, 1, 1) {}
    void Render() override;
};

class UIButton : public UIElement {
public:
    std::string text;
    Vector4 normalColor;
    Vector4 hoverColor;
    Vector4 pressedColor;
    
    UIButton() 
        : text("Button")
        , normalColor(0.8f, 0.8f, 0.8f, 1.0f)
        , hoverColor(0.9f, 0.9f, 0.9f, 1.0f)
        , pressedColor(0.7f, 0.7f, 0.7f, 1.0f)
    {}
    
    void Render() override;
    
    // Events
    void (*onClick)() = nullptr;
};

class UICanvas {
public:
    UICanvas(int width, int height);
    ~UICanvas() = default;
    
    void Update(float deltaTime);
    void Render();
    
    void AddElement(std::shared_ptr<UIElement> element);
    void RemoveElement(std::shared_ptr<UIElement> element);
    
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    
private:
    int width;
    int height;
    std::vector<std::shared_ptr<UIElement>> elements;
};

} // namespace YUGA
