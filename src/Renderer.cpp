#include "Renderer.h"

// std
#include <stdexcept>
#include <iostream>

// libs
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Renderer::Renderer(SDL_Window* window)
{
    m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (m_Renderer == NULL)
    {
        std::cout << SDL_GetError() << "\n";
        throw std::runtime_error("Failed to create SDL_Renderer!\n");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()}; (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, m_Renderer);
    ImGui_ImplSDLRenderer2_Init(m_Renderer);
}

Renderer::~Renderer()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(m_Renderer);
}

void Renderer::Draw()
{
    currentFrame = SDL_GetTicks();
    deltaTime = (double)(currentFrame - lastFrame);
    lastFrame = SDL_GetTicks();

    // std::cout << deltaTime << "\n";

    m_Boids.Update();

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Boids Settings");
    ImGui::DragFloat("Cohesion", &m_Boids.cohesionFactor, 0.01f, 5.f);
    ImGui::DragFloat("Alignment", &m_Boids.alignmentFactor, 0.01f, 5.f);
    ImGui::DragFloat("Sepration", &m_Boids.seprationFactor, 0.01f, 5.f);
    ImGui::DragFloat("Max Speed", &m_Boids.maxSpeed, 0.1f, 5.f);
    ImGui::DragFloat("Max Neighbour Distance", &m_Boids.maxNegihbourRadius, 1.f, 20.f);
    ImGui::DragFloat("Max View Angle", &m_Boids.maxViewAngle, -1.f, 1.f);
    ImGui::DragFloat("Mouse Repel Force", &m_Boids.mouseRepelForce, 0.1f, 10.f);
    ImGui::DragFloat("Mouse Repel Radius", &m_Boids.mouseRepelRadius, 1.f, 20.f);
    ImGui::DragInt("Number of Boids", &m_Boids.numberOfBoids, 1, 500);
    if (ImGui::Button("Reset"))
    {
        m_Boids.Reset(m_Boids.numberOfBoids);
    }
    ImGui::End();

    ImGui::Render();

    SDL_RenderClear(m_Renderer);
    m_Boids.Draw(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 20, 20, 30, 255);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Renderer);

    SDL_RenderPresent(m_Renderer);
}