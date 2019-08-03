#include "example.h"

/*
 * TilePicker
 * ~> Only needs one loaded texture
 */
void Example::Init() {
    printf("example init called\n");
}

void Example::Update() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, new SDL_Rect{0,0,500,200} );
}

void Example::OnResize(int, int) {
    printf("example resize called\n");
}
