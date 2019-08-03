#pragma once
#include <sdlwidget.h>

class Example : public SDLWidget
{
public:
    Example(QWidget* parent) : SDLWidget(parent) {}
private:
    void Init();
    void Update();
    void OnResize(int w, int h);
};
