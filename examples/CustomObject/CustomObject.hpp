#pragma once

class CustomObject : public GUI::Container
{
private:
    uint32_t countButton;

    GUI::Panel* mainPanel;
    GUI::Layout* layout;

    void handleInput() override;

    GUI::Button* createButton(float x, float y, uint32_t width, uint32_t height);
public:
    CustomObject(GUI::Workspace* workspace);
    ~CustomObject();
};