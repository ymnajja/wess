#include <stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>


typedef struct {
    SDL_Surface *sprite;
    SDL_Rect position;
    SDL_Rect dest;
    int frameNumber;
    int maxframe;
    int frameTimer;
    int frameDuration;
    int direction;
    int motion;
    int speed;
    int life;
} character;

void initCharacter(character *c) {
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    c->sprite = IMG_Load("/workspaces/wess*/5398530.jpg");
    c->position.x = 0;
    c->position.y = 0;
    c->position.w = 32;
    c->position.h = 32;
    c->frameNumber = 0;
    c->maxframe = 8;
    c->frameTimer = 0;
    c->frameDuration = 8;
    c->direction = 0;
    c->speed = 1;
    c->life = 100;
}
void moveCharacter(character *c, int dx, int dy,SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    c->motion = 1;
                    c->direction = 1;
                    c->dest.y +=dy;
                    break;
                case SDLK_DOWN:
                    c->motion = 1;
                    c->direction = 2;
                    c->dest.y -=dy;
                    break;
                case SDLK_LEFT:
                    c->motion = 1;
                    c->direction = 3;
                    c->dest.x +=dx;
                    break;
                case SDLK_RIGHT:
                    c->motion = 1;
                    c->direction = 4;
                    c->dest.x +=dx;
                    break;
            }
            break;
        case SDL_KEYUP:
            c->motion = 0;
            break;
    }
}

/*void updateCharacter(character *c) {
    if (c->motion) {
        c->frameTimer++;
        if (c->frameTimer >= c->frameDuration) {
            c->frameTimer = 0;
            c->frameNumber++;
            if (c->frameNumber >= c->maxframe) {
                c->frameNumber = 0;
            }
        }
        switch (c->direction) {
            case 1:
                c->position.y -= c->speed;
                break;
            case 2:
                c->position.y += c->speed;
                break;
            case 3:
                c->position.x -= c->speed;
                break;
            case 4:
                c->position.x += c->speed;
                break;
        }
    }
}*/

int main() {
    character c;
    int dx,dy;
    dx=100;
    dy=50;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Load the background image
    SDL_Surface *backgroundSurface = IMG_Load("/workspaces/wess*/Veil_Nebula_800x600.jpg");
    if (backgroundSurface == NULL) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        SDL_FreeSurface(screen);
        SDL_Quit();
        return 1;
    }

    // Load the character sprite
    c.sprite = IMG_Load("/workspaces/wess*/5398530.jpg");
    if (c.sprite == NULL) {
        printf("Failed to load character sprite: %s\n", IMG_GetError());
        SDL_FreeSurface(backgroundSurface);
        SDL_FreeSurface(screen);
        SDL_Quit();
        return 1;
    }

    // Initialize the character
    initCharacter(&c);

    // Blit the background image onto the screen
    SDL_BlitSurface(backgroundSurface, NULL, screen, NULL);

    // Update the screen
    SDL_Flip(screen);

    // Event loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            moveCharacter(&c,dx,dy, event);
        }

        // Update the character
        
        // Clear the screen
        SDL_FillRect(screen, NULL, 0);

        // Blit the background image onto the screen
        SDL_BlitSurface(backgroundSurface, NULL, screen, NULL);

        // Blit the character sprite onto the screen
        SDL_BlitSurface(c.sprite, &c.src, screen, &c.dest);

        // Update the screen
        SDL_Flip(screen);
    }

    // Clean up resources
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(c.sprite);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}