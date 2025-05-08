#include <SDL2/SDL.h>
#include <stdio.h>

#define MAX_RECT_COUNT 100
#define PALETTE_SIZE 6
#define PALETTE_WIDTH 50
#define PALETTE_HEIGHT 50
#define PALETTE_X 10
#define PALETTE_Y 10

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    Point topLeft;
    Point bottomRight;
    RGB color;
} Rectangle;

void drawRectangle(SDL_Renderer* renderer, Rectangle rect) {
    SDL_SetRenderDrawColor(renderer, rect.color.r, rect.color.g, rect.color.b, 255);
    SDL_Rect sdlRect = {
        (int)rect.topLeft.x,
        (int)rect.topLeft.y,
        (int)(rect.bottomRight.x - rect.topLeft.x),
        (int)(rect.bottomRight.y - rect.topLeft.y)
    };
    SDL_RenderFillRect(renderer, &sdlRect);
}

void drawPalette(SDL_Renderer* renderer, RGB colors[PALETTE_SIZE]) {
    for (int i = 0; i < PALETTE_SIZE; ++i) {
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
        SDL_Rect rect = {PALETTE_X + (i * PALETTE_WIDTH), PALETTE_Y, PALETTE_WIDTH, PALETTE_HEIGHT};
        SDL_RenderFillRect(renderer, &rect);
    }
}

int isPointInRect(int px, int py, SDL_Rect rect) {
    return px >= rect.x && px <= rect.x + rect.w && py >= rect.y && py <= rect.y + rect.h;
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Rectangle Drawer",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800,
                                          600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL window error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL renderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Color palette
    RGB paletteColors[PALETTE_SIZE] = {
        {255, 0, 0},    // Red
        {0, 255, 0},    // Green
        {0, 0, 255},    // Blue
        {255, 255, 0},  // Yellow
        {255, 0, 255}   // Magenta
    };

    // Selected color
    RGB selectedColor = paletteColors[0];

    // Track rectangles and rectangle count
    Rectangle rectangles[MAX_RECT_COUNT];
    int rectCount = 0;
    Point firstClick = {0, 0};
    int waitingForSecondClick = 0;

    // Main loop
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the click is within the palette
                SDL_Rect paletteRect = {PALETTE_X, PALETTE_Y, PALETTE_WIDTH * PALETTE_SIZE, PALETTE_HEIGHT};
                if (isPointInRect(x, y, paletteRect)) {
                    int colorIndex = (x - PALETTE_X) / PALETTE_WIDTH;
                    if (colorIndex >= 0 && colorIndex < PALETTE_SIZE) {
                        selectedColor = paletteColors[colorIndex];
                    }
                } else {
                    if (rectCount < MAX_RECT_COUNT) {
                        if (!waitingForSecondClick) {
                            // First click, store top-left point
                            firstClick.x = x;
                            firstClick.y = y;
                            waitingForSecondClick = 1;
                        } else {
                            // Second click, store bottom-right point and create rectangle
                            Rectangle newRect;
                            newRect.topLeft = firstClick;
                            newRect.bottomRight.x = x;
                            newRect.bottomRight.y = y;
                            newRect.color = selectedColor;

                            rectangles[rectCount++] = newRect;
                            waitingForSecondClick = 0;
                        }
                    }
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Draw the palette
        drawPalette(renderer, paletteColors);

        // Draw all rectangles
        for (int i = 0; i < rectCount; ++i) {
            drawRectangle(renderer, rectangles[i]);
            drawPalette(renderer, paletteColors);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
