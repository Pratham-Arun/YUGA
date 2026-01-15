#include "UI/UICanvas.h"
#include "Core/Log.h"

namespace YUGA {

// UIText Implementation
void UIText::Render() {
    if (!visible) return;
    
    // TODO: Implement text rendering using ImGui or custom text renderer
    // ImGui::SetCursorPos(ImVec2(position.x, position.y));
    // ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), "%s", text.c_str());
}

// UIImage Implementation
void UIImage::Render() {
    if (!visible) return;
    
    // TODO: Implement image rendering
    // ImGui::SetCursorPos(ImVec2(position.x, position.y));
    // ImGui::Image(textureID, ImVec2(size.x, size.y), ImVec2(0,0), ImVec2(1,1), ImVec4(color.x, color.y, color.z, color.w));
}

// UIButton Implementation
void UIButton::Render() {
    if (!visible) return;
    
    // TODO: Implement button rendering with hover/press states
    // ImGui::SetCursorPos(ImVec2(position.x, position.y));
    // if (ImGui::Button(text.c_str(), ImVec2(size.x, size.y))) {
    //     if (onClick) onClick();
    // }
}

// UICanvas Implementation
UICanvas::UICanvas(int width, int height)
    : width(width)
    , height(height)
{
}

void UICanvas::Update(float deltaTime) {
    for (auto& element : elements) {
        if (element) {
            element->Update(deltaTime);
        }
    }
}

void UICanvas::Render() {
    for (auto& element : elements) {
        if (element && element->visible) {
            element->Render();
            
            // Render children
            for (auto& child : element->GetChildren()) {
                if (child && child->visible) {
                    child->Render();
                }
            }
        }
    }
}

void UICanvas::AddElement(std::shared_ptr<UIElement> element) {
    if (element) {
        elements.push_back(element);
    }
}

void UICanvas::RemoveElement(std::shared_ptr<UIElement> element) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        elements.erase(it);
    }
}

} // namespace YUGA
