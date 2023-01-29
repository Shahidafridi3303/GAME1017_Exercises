// #pragma once       // Added files
#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
using namespace std;

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60

class Engine
{
public: // Put public heading first so you ALWAYS question why things are public!
	Engine(); // What? What is this?
	int Run();
	bool KeyDown(SDL_Scancode);
	double deltaTime;
	SDL_Renderer* GetRenderer();  // Getter for Renderer.
	static Engine& Instance();  // Static Instance method for Singleton.

private:
	// For fixed timestep.
	chrono::time_point<chrono::steady_clock> m_start, m_end;
	chrono::duration<double> m_diff;
	double m_fps; // Changed to double.

	const Uint8* m_pKeystates;
	SDL_Window* m_pWindow; // Pointers are normal variables that hold addresses.
	SDL_Renderer* m_pRenderer; // Pointer to "back buffer"
	bool m_isRunning;

	// Example-specific properties.

	chrono::time_point<chrono::steady_clock> lastFrameTime, thisFrameTime; // Cleaned this up.
	chrono::duration<double> lastFrameDuration;

	int Init(const char*, const int, const int, const int, const int, const int);
	void HandleEvents();
	void Wake();
	void Update();
	void Sleep();
	void Render();
	void Clean();	
};

#endif
