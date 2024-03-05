#define SDL_MAIN_HANDLED
#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "headers/Render.h"
#include "headers/Window.h"
#include "headers/Entity.h"
#include "headers/Utils.h"

const int UPDATE_PER_SECOND = 60;
const double UPDATE_DELAY = 1/UPDATE_PER_SECOND;
double updateTimer;

SDL_Texture* groundTexture;
SDL_Rect ground;
SDL_Rect groundDst;

void draw_bg(SDL_Renderer *renderer, int tileSize)
{
    for (int y=0; y < 50; y++)
    {
        for (int x=0; x < 50; x++)
        {
            if ((x+y) % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, 196, 164, 132, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 125, 87, 61, 255);
            }

            SDL_Rect rect {x * tileSize, y * tileSize, tileSize, tileSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "Failed to initialize video, error : " << SDL_GetError() << std::endl;
    }

    Window window("Hello SDL", 800, 600);
    Render renderer(window.get_Window());
    Utils utils;

    SDL_Texture* player_tex = renderer.loadTexture("res/sprites/player/Idle/Idle_0.png");
    Entity player(player_tex, 32,32,400,300);
    
    groundTexture = renderer.loadTexture("res/sprites/Tiles/ground.png");
    ground.h=44;
    ground.w=44;
    groundDst.h=ground.h*2;
    groundDst.w=ground.w*2;
    groundDst.x = player.getX();
    groundDst.y = player.getY() + 80;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window.get_Window(), renderer.get_Renderer());
    ImGui_ImplSDLRenderer2_Init(renderer.get_Renderer());
    
    bool running = true;
    SDL_Event e;
    updateTimer = 1;
    while (running)
    {
        updateTimer -= UPDATE_DELAY;
        if (updateTimer <= UPDATE_DELAY)
        {
            updateTimer = 1;
        }

        if (updateTimer >= UPDATE_DELAY)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT) running = false;
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_a)
                    {
                        player.setX(player.getX()-5);
                    }
                    if (e.key.keysym.sym == SDLK_d)
                    {
                        player.setX(player.getX()+5);
                    }
                }
                ImGui_ImplSDL2_ProcessEvent(&e);
            }

            if (!utils.rect_collision(player.getRect(), groundDst))
            {
                player.setY(player.getY()+1);
            }

            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Cutomize");
            ImGui::Text("Hello Working?");
            ImGui::End();

            ImGui::Render();


            renderer.clear();
            draw_bg(renderer.get_Renderer(), 30);
            player.renderEntity(renderer);
            renderer.renderTexture(groundTexture, &ground, &groundDst);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            renderer.display();
        }
    }

    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();

    window.cleanUp();
    renderer.cleanUp();
    SDL_Quit();
}