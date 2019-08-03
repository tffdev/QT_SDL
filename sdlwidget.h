#pragma once
#include <QWidget>
#include <QTimer>
#include <SDL2/SDL.h>

#define FRAME_RATE 60
#define MS_PER_FRAME 1000/FRAME_RATE

class SDLWidget : public QWidget
{
public :
    SDLWidget(QWidget* parent);
    virtual ~SDLWidget() override;

public slots:
    void SDLRepaint();

protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
private:
    /* To be overridden by child classes */
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void OnResize(int w, int h) = 0;

    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent*) override;
    void createWindow();
    QPaintEngine* paintEngine() const override;

    QTimer frameTimer;
};
