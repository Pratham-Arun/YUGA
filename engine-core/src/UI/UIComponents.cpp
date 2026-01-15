#include "UI/UIComponents.h"
#include "Math/MathUtils.h"
#include "Core/Log.h"

namespace YUGA {
namespace UI {

// UITheme Implementation
UITheme UITheme::Dark() {
    UITheme theme;
    theme.backgroundColor = Vector4(0.12f, 0.12f, 0.12f, 1.0f);
    theme.surfaceColor = Vector4(0.18f, 0.18f, 0.18f, 1.0f);
    theme.primaryColor = Vector4(0.2f, 0.6f, 1.0f, 1.0f);
    theme.textColor = Vector4(0.95f, 0.95f, 0.95f, 1.0f);
    return theme;
}

UITheme UITheme::Light() {
    UITheme theme;
    theme.backgroundColor = Vector4(0.95f, 0.95f, 0.95f, 1.0f);
    theme.surfaceColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    theme.primaryColor = Vector4(0.2f, 0.5f, 0.9f, 1.0f);
    theme.textColor = Vector4(0.1f, 0.1f, 0.1f, 1.0f);
    return theme;
}

UITheme UITheme::Blue() {
    UITheme theme = Dark();
    theme.primaryColor = Vector4(0.1f, 0.5f, 1.0f, 1.0f);
    theme.accentColor = Vector4(0.3f, 0.7f, 1.0f, 1.0f);
    return theme;
}

UITheme UITheme::Purple() {
    UITheme theme = Dark();
    theme.primaryColor = Vector4(0.6f, 0.3f, 0.9f, 1.0f);
    theme.accentColor = Vector4(0.8f, 0.4f, 1.0f, 1.0f);
    return theme;
}

// ModernButton Implementation
ModernButton::ModernButton(const std::string& text)
    : text(text)
    , normalColor(0.3f, 0.3f, 0.3f, 1.0f)
    , hoverColor(0.4f, 0.4f, 0.4f, 1.0f)
    , pressedColor(0.2f, 0.2f, 0.2f, 1.0f)
    , disabledColor(0.2f, 0.2f, 0.2f, 0.5f)
    , currentColor(normalColor)
{
    size = Vector2(120, 36);
}

void ModernButton::Render() {
    if (!visible) return;
    
    // Determine current color based on state
    Vector4 targetColor = normalColor;
    if (!enabled) {
        targetColor = disabledColor;
    } else if (isPressed) {
        targetColor = pressedColor;
    } else if (isHovered) {
        targetColor = hoverColor;
    }
    
    // Smooth color transition
    currentColor = Vector4::Lerp(currentColor, targetColor, 0.1f);
    
    // TODO: Render button with ImGui or custom renderer
    // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(currentColor.x, currentColor.y, currentColor.z, currentColor.w));
    // ImGui::SetCursorPos(ImVec2(position.x, position.y));
    // if (ImGui::Button(text.c_str(), ImVec2(size.x, size.y)) && enabled && onClick) {
    //     onClick();
    // }
    // ImGui::PopStyleColor();
}

void ModernButton::Update(float deltaTime) {
    animationTime += deltaTime;
    
    // Update hover/press states based on mouse input
    // This would be implemented with actual input system
}

// ModernText Implementation
ModernText::ModernText(const std::string& text)
    : text(text)
    , color(1.0f, 1.0f, 1.0f, 1.0f)
    , fontSize(14.0f)
{
}

void ModernText::Render() {
    if (!visible) return;
    
    // TODO: Render text with formatting
    // ImGui::SetCursorPos(ImVec2(position.x, position.y));
    // ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color.x, color.y, color.z, color.w));
    // if (bold) ImGui::PushFont(boldFont);
    // ImGui::Text("%s", text.c_str());
    // if (bold) ImGui::PopFont();
    // ImGui::PopStyleColor();
}

// ProgressBar Implementation
ProgressBar::ProgressBar()
    : value(0.0f)
    , targetValue(0.0f)
    , fillColor(0.2f, 0.6f, 1.0f, 1.0f)
    , backgroundColor(0.2f, 0.2f, 0.2f, 1.0f)
{
    size = Vector2(200, 24);
}

void ProgressBar::Render() {
    if (!visible) return;
    
    // TODO: Render progress bar
    // Draw background
    // Draw fill based on value
    // Draw percentage text if showPercentage
}

void ProgressBar::Update(float deltaTime) {
    if (animated && value != targetValue) {
        float diff = targetValue - value;
        value += diff * animationSpeed * deltaTime;
        
        // Snap to target if close enough
        if (Math::Abs(diff) < 0.01f) {
            value = targetValue;
        }
    }
}

// Slider Implementation
Slider::Slider(float min, float max)
    : value((min + max) * 0.5f)
    , minValue(min)
    , maxValue(max)
    , trackColor(0.3f, 0.3f, 0.3f, 1.0f)
    , thumbColor(0.2f, 0.6f, 1.0f, 1.0f)
{
    size = Vector2(200, 24);
}

void Slider::Render() {
    if (!visible) return;
    
    // TODO: Render slider
    // Draw track
    // Draw thumb at position based on value
    // Draw value text if showValue
}

void Slider::Update(float deltaTime) {
    // Handle dragging
    if (isDragging) {
        // Update value based on mouse position
        // Call onValueChanged if value changed
    }
}

// InputField Implementation
InputField::InputField(const std::string& placeholder)
    : placeholder(placeholder)
    , textColor(1.0f, 1.0f, 1.0f, 1.0f)
    , placeholderColor(0.5f, 0.5f, 0.5f, 1.0f)
    , borderColor(0.3f, 0.3f, 0.3f, 1.0f)
    , focusedBorderColor(0.2f, 0.6f, 1.0f, 1.0f)
{
    size = Vector2(200, 32);
}

void InputField::Render() {
    if (!visible) return;
    
    // TODO: Render input field
    // Draw border (different color if focused)
    // Draw text or placeholder
    // Draw cursor if focused
}

void InputField::Update(float deltaTime) {
    // Handle text input
    // Handle cursor blinking
    // Handle selection
}

// Checkbox Implementation
Checkbox::Checkbox(const std::string& label)
    : label(label)
    , checkColor(0.2f, 0.6f, 1.0f, 1.0f)
    , boxColor(0.3f, 0.3f, 0.3f, 1.0f)
{
    size = Vector2(20, 20);
}

void Checkbox::Render() {
    if (!visible) return;
    
    // TODO: Render checkbox
    // Draw box
    // Draw checkmark if checked
    // Draw label
}

// Dropdown Implementation
Dropdown::Dropdown()
    : dropdownColor(0.2f, 0.2f, 0.2f, 1.0f)
    , selectedColor(0.3f, 0.3f, 0.3f, 1.0f)
{
    size = Vector2(200, 32);
}

void Dropdown::Render() {
    if (!visible) return;
    
    // TODO: Render dropdown
    // Draw main button showing selected item
    // If open, draw dropdown list
}

void Dropdown::Update(float deltaTime) {
    // Handle opening/closing
    // Handle item selection
}

void Dropdown::AddItem(const std::string& item) {
    items.push_back(item);
}

void Dropdown::RemoveItem(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items.erase(items.begin() + index);
    }
}

void Dropdown::Clear() {
    items.clear();
    selectedIndex = -1;
}

std::string Dropdown::GetSelectedItem() const {
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(items.size())) {
        return items[selectedIndex];
    }
    return "";
}

// Panel Implementation
Panel::Panel()
    : backgroundColor(0.18f, 0.18f, 0.18f, 1.0f)
    , borderColor(0.3f, 0.3f, 0.3f, 1.0f)
{
    size = Vector2(300, 400);
}

void Panel::Render() {
    if (!visible) return;
    
    // TODO: Render panel
    // Draw background
    // Draw border
    // Draw shadow if enabled
    // Render children with layout
}

// Notification Implementation
Notification::Notification(const std::string& message, Type type)
    : message(message)
    , type(type)
{
    size = Vector2(300, 60);
}

void Notification::Render() {
    if (!visible) return;
    
    Vector4 color = GetColorForType();
    
    // TODO: Render notification
    // Slide in animation
    // Draw background with type color
    // Draw message
    // Draw close button
}

void Notification::Update(float deltaTime) {
    timeAlive += deltaTime;
    
    if (autoHide && timeAlive >= duration) {
        visible = false;
    }
    
    // Update slide animation
    if (slideProgress < 1.0f) {
        slideProgress += deltaTime * 3.0f;
        slideProgress = Math::Clamp(slideProgress, 0.0f, 1.0f);
    }
}

Vector4 Notification::GetColorForType() const {
    switch (type) {
        case Type::Info:    return Vector4(0.2f, 0.6f, 1.0f, 1.0f);
        case Type::Success: return Vector4(0.3f, 0.8f, 0.3f, 1.0f);
        case Type::Warning: return Vector4(0.9f, 0.7f, 0.2f, 1.0f);
        case Type::Error:   return Vector4(0.9f, 0.2f, 0.2f, 1.0f);
    }
    return Vector4(0.5f, 0.5f, 0.5f, 1.0f);
}

// LoadingSpinner Implementation
LoadingSpinner::LoadingSpinner()
    : color(0.2f, 0.6f, 1.0f, 1.0f)
{
    size = Vector2(32, 32);
}

void LoadingSpinner::Render() {
    if (!visible) return;
    
    // TODO: Render spinning circle
    // Use rotation for animation
}

void LoadingSpinner::Update(float deltaTime) {
    rotation += speed * deltaTime * Math::TWO_PI;
    if (rotation > Math::TWO_PI) {
        rotation -= Math::TWO_PI;
    }
}

// Separator Implementation
Separator::Separator(bool vertical)
    : vertical(vertical)
    , color(0.3f, 0.3f, 0.3f, 1.0f)
{
    if (vertical) {
        size = Vector2(1, 100);
    } else {
        size = Vector2(100, 1);
    }
}

void Separator::Render() {
    if (!visible) return;
    
    // TODO: Render line
}

// Badge Implementation
Badge::Badge(const std::string& text)
    : text(text)
    , backgroundColor(0.9f, 0.2f, 0.2f, 1.0f)
    , textColor(1.0f, 1.0f, 1.0f, 1.0f)
{
    size = Vector2(40, 20);
}

void Badge::Render() {
    if (!visible) return;
    
    // TODO: Render badge
    // Draw rounded background
    // Draw text centered
}

} // namespace UI
} // namespace YUGA
