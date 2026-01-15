#pragma once
#include "UICanvas.h"
#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include <string>
#include <functional>
#include <vector>

namespace YUGA {
namespace UI {

// Modern UI Theme
struct UITheme {
    // Colors
    Vector4 primaryColor = Vector4(0.2f, 0.6f, 1.0f, 1.0f);      // Blue
    Vector4 secondaryColor = Vector4(0.4f, 0.4f, 0.4f, 1.0f);    // Gray
    Vector4 backgroundColor = Vector4(0.15f, 0.15f, 0.15f, 1.0f); // Dark
    Vector4 surfaceColor = Vector4(0.2f, 0.2f, 0.2f, 1.0f);      // Lighter dark
    Vector4 textColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);         // White
    Vector4 accentColor = Vector4(0.3f, 0.8f, 0.3f, 1.0f);       // Green
    Vector4 errorColor = Vector4(0.9f, 0.2f, 0.2f, 1.0f);        // Red
    Vector4 warningColor = Vector4(0.9f, 0.7f, 0.2f, 1.0f);      // Yellow
    
    // Sizes
    float borderRadius = 4.0f;
    float padding = 8.0f;
    float spacing = 4.0f;
    float fontSize = 14.0f;
    float titleFontSize = 18.0f;
    float headerFontSize = 24.0f;
    
    // Effects
    float shadowOpacity = 0.3f;
    float hoverBrightness = 1.2f;
    float pressedBrightness = 0.8f;
    
    static UITheme Dark();
    static UITheme Light();
    static UITheme Blue();
    static UITheme Purple();
};

// Advanced Button with states
class ModernButton : public UIElement {
public:
    ModernButton(const std::string& text = "Button");
    
    void Render() override;
    void Update(float deltaTime) override;
    
    // Properties
    std::string text;
    Vector4 normalColor;
    Vector4 hoverColor;
    Vector4 pressedColor;
    Vector4 disabledColor;
    bool enabled = true;
    bool isHovered = false;
    bool isPressed = false;
    
    // Icon support
    std::string iconPath;
    bool showIcon = false;
    
    // Callbacks
    std::function<void()> onClick;
    std::function<void()> onHover;
    std::function<void()> onPress;
    
private:
    float animationTime = 0.0f;
    Vector4 currentColor;
};

// Modern Text with formatting
class ModernText : public UIElement {
public:
    ModernText(const std::string& text = "");
    
    void Render() override;
    
    std::string text;
    Vector4 color;
    float fontSize;
    enum class Alignment { Left, Center, Right } alignment = Alignment::Left;
    bool bold = false;
    bool italic = false;
    bool shadow = false;
    bool outline = false;
};

// Progress Bar
class ProgressBar : public UIElement {
public:
    ProgressBar();
    
    void Render() override;
    void Update(float deltaTime) override;
    
    float value = 0.0f;        // 0.0 to 1.0
    float targetValue = 0.0f;
    float animationSpeed = 2.0f;
    Vector4 fillColor;
    Vector4 backgroundColor;
    bool showPercentage = true;
    bool animated = true;
};

// Slider
class Slider : public UIElement {
public:
    Slider(float min = 0.0f, float max = 1.0f);
    
    void Render() override;
    void Update(float deltaTime) override;
    
    float value;
    float minValue;
    float maxValue;
    Vector4 trackColor;
    Vector4 thumbColor;
    bool showValue = true;
    
    std::function<void(float)> onValueChanged;
    
private:
    bool isDragging = false;
};

// Input Field
class InputField : public UIElement {
public:
    InputField(const std::string& placeholder = "");
    
    void Render() override;
    void Update(float deltaTime) override;
    
    std::string text;
    std::string placeholder;
    Vector4 textColor;
    Vector4 placeholderColor;
    Vector4 borderColor;
    Vector4 focusedBorderColor;
    bool isFocused = false;
    bool isPassword = false;
    int maxLength = 256;
    
    std::function<void(const std::string&)> onTextChanged;
    std::function<void()> onSubmit;
};

// Checkbox
class Checkbox : public UIElement {
public:
    Checkbox(const std::string& label = "");
    
    void Render() override;
    
    bool checked = false;
    std::string label;
    Vector4 checkColor;
    Vector4 boxColor;
    
    std::function<void(bool)> onChanged;
};

// Dropdown/ComboBox
class Dropdown : public UIElement {
public:
    Dropdown();
    
    void Render() override;
    void Update(float deltaTime) override;
    
    std::vector<std::string> items;
    int selectedIndex = -1;
    bool isOpen = false;
    Vector4 dropdownColor;
    Vector4 selectedColor;
    
    std::function<void(int)> onSelectionChanged;
    
    void AddItem(const std::string& item);
    void RemoveItem(int index);
    void Clear();
    std::string GetSelectedItem() const;
};

// Panel/Container
class Panel : public UIElement {
public:
    Panel();
    
    void Render() override;
    
    Vector4 backgroundColor;
    Vector4 borderColor;
    float borderWidth = 1.0f;
    float borderRadius = 4.0f;
    bool hasShadow = true;
    bool scrollable = false;
    
    // Layout
    enum class LayoutType { None, Vertical, Horizontal, Grid } layout = LayoutType::None;
    float spacing = 8.0f;
    float padding = 8.0f;
};

// Tab Control
class TabControl : public UIElement {
public:
    struct Tab {
        std::string title;
        std::shared_ptr<UIElement> content;
        bool enabled = true;
    };
    
    TabControl();
    
    void Render() override;
    void Update(float deltaTime) override;
    
    void AddTab(const std::string& title, std::shared_ptr<UIElement> content);
    void RemoveTab(int index);
    void SetActiveTab(int index);
    int GetActiveTab() const { return activeTabIndex; }
    
private:
    std::vector<Tab> tabs;
    int activeTabIndex = 0;
    Vector4 tabColor;
    Vector4 activeTabColor;
};

// Tooltip
class Tooltip : public UIElement {
public:
    Tooltip(const std::string& text = "");
    
    void Render() override;
    void Show(const Vector2& position);
    void Hide();
    
    std::string text;
    Vector4 backgroundColor;
    Vector4 textColor;
    float fadeTime = 0.2f;
    
private:
    bool isVisible = false;
    float alpha = 0.0f;
};

// Notification/Toast
class Notification : public UIElement {
public:
    enum class Type { Info, Success, Warning, Error };
    
    Notification(const std::string& message, Type type = Type::Info);
    
    void Render() override;
    void Update(float deltaTime) override;
    
    std::string message;
    Type type;
    float duration = 3.0f;
    bool autoHide = true;
    
private:
    float timeAlive = 0.0f;
    float slideProgress = 0.0f;
    Vector4 GetColorForType() const;
};

// Context Menu
class ContextMenu : public UIElement {
public:
    struct MenuItem {
        std::string label;
        std::string shortcut;
        bool enabled = true;
        bool separator = false;
        std::function<void()> onClick;
    };
    
    ContextMenu();
    
    void Render() override;
    void Show(const Vector2& position);
    void Hide();
    
    void AddItem(const std::string& label, std::function<void()> onClick, const std::string& shortcut = "");
    void AddSeparator();
    void Clear();
    
private:
    std::vector<MenuItem> items;
    bool isVisible = false;
    int hoveredIndex = -1;
};

// Modern Window/Dialog
class ModernWindow : public UIElement {
public:
    ModernWindow(const std::string& title = "Window");
    
    void Render() override;
    void Update(float deltaTime) override;
    
    std::string title;
    bool closeable = true;
    bool minimizable = true;
    bool maximizable = true;
    bool resizable = true;
    bool draggable = true;
    
    Vector4 titleBarColor;
    Vector4 contentColor;
    
    std::function<void()> onClose;
    
    void SetContent(std::shared_ptr<UIElement> content);
    
private:
    std::shared_ptr<UIElement> content;
    bool isDragging = false;
    bool isResizing = false;
    Vector2 dragOffset;
};

// Icon Button
class IconButton : public UIElement {
public:
    IconButton(const std::string& iconPath = "");
    
    void Render() override;
    
    std::string iconPath;
    Vector4 iconColor;
    Vector4 hoverColor;
    float iconSize = 24.0f;
    bool circular = false;
    
    std::function<void()> onClick;
};

// Badge/Label
class Badge : public UIElement {
public:
    Badge(const std::string& text = "");
    
    void Render() override;
    
    std::string text;
    Vector4 backgroundColor;
    Vector4 textColor;
    bool pill = true; // Rounded ends
};

// Separator/Divider
class Separator : public UIElement {
public:
    Separator(bool vertical = false);
    
    void Render() override;
    
    bool vertical;
    Vector4 color;
    float thickness = 1.0f;
};

// Loading Spinner
class LoadingSpinner : public UIElement {
public:
    LoadingSpinner();
    
    void Render() override;
    void Update(float deltaTime) override;
    
    Vector4 color;
    float size = 32.0f;
    float speed = 2.0f;
    
private:
    float rotation = 0.0f;
};

} // namespace UI
} // namespace YUGA
