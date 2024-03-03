#define SDL_MAIN_HANDLED
#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "headers/Render.h"
#include "headers/Window.h"
#include "headers/Entity.h"

int map[] = {
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
};
int mapS = 88;
int mapY = 8;
int mapX = 11;


SDL_Texture* groundTexture;
SDL_Rect ground;
SDL_Rect groundDst;


void load_map(Render renderer)
{
    for (int x=0; x<mapX; x++)
    {
        for (int y=0; y<mapY; y++)
        {
            if (map[y*mapX+x]==1)
            {
                groundDst.x=x*mapS;
                groundDst.y=y*mapS;
                renderer.renderTexture(groundTexture, &ground, &groundDst);
            }
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

    SDL_Texture* player_tex = renderer.loadTexture("res/sprites/player/Idle/Idle_0.png");
    Entity player(player_tex, 32,32,400,375);
    
    groundTexture = renderer.loadTexture("res/sprites/Tiles/ground.png");
    ground.h=44;
    ground.w=44;
    groundDst.h=ground.h*2;
    groundDst.w=ground.w*2;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window.get_Window(), renderer.get_Renderer());
    ImGui_ImplSDLRenderer2_Init(renderer.get_Renderer());
    
    bool running = true;
    SDL_Event e;
    while (running)
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

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Cutomize");
        ImGui::Text("Hello Working?");
        ImGui::End();

        ImGui::Render();


        renderer.clear();
        player.renderEntity(renderer);
        load_map(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        renderer.display();
    }

    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();

    window.cleanUp();
    renderer.cleanUp();
    SDL_Quit();
}