#include "sdlwidget.h"

SDLWidget::SDLWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw "SDL_Error: " + std::string(SDL_GetError());
    }

    printf("Creating SDL window\n");

    window = SDL_CreateWindowFrom(reinterpret_cast<void*>(winId()));
    if(window == NULL)
        throw "Can't create window: " + std::string(SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        throw "Can't create renderer: " + std::string(SDL_GetError());
}

void SDLWidget::resizeEvent(QResizeEvent*) {
    int x = static_cast<int>(QWidget::width());
    int y = static_cast<int>(QWidget::height());
    OnResize(x, y);
}

void SDLWidget::showEvent(QShowEvent*) {
    Init();
    /* frameTimer will send signal timeout() every 60th of a second, connect to "repaint" */
    connect(&frameTimer, &QTimer::timeout, this, &SDLWidget::SDLRepaint);
    frameTimer.setInterval(MS_PER_FRAME);
    frameTimer.start();
}

void SDLWidget::SDLRepaint() {
    Update();
    SDL_RenderPresent(renderer);
}

SDLWidget::~SDLWidget() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/* Override default system paint engine to remove flickering */
QPaintEngine* SDLWidget::paintEngine() const {
    return reinterpret_cast<QPaintEngine*>(0);
}
