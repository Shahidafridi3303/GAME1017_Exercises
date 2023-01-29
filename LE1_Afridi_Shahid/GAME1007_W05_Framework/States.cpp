#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){};

void TitleState::Enter()
{
	cout << "Entering TitleState!" << endl;
	// Load music track, and add it to map.
	// Add play it.
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "Changing to GamState!" << endl;
	    STMA::ChangeState(new GameState() );
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in TitleState goes here...

	State::Render(); // This invokes SDL_RenderPresent.
}

void TitleState::Exit()
{
	cout << "Exiting TitleState!" << endl;
	// Make sure to invoke Mix_FreeMusic.
}

GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GameState!" << endl;
	// Load sfx tracks, and add them to map. (x2)
	// Load music track, and add it to map.
	// Add play it.
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing to GamState!" << endl;
		// Pause the music track.
		// STMA::PushState(new PauseState());
	}
	// Parse 'X' ScanCode and change to new EndState.
	// Parse 1 key, and play first sfx.
	// Parse 2 key, and play second sfx.
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Any unique rendering in GameState goes here...

	// If the current state int the vector is the GameState.
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	cout << "Exiting TitleState!" << endl;
	// Make sure to invoke Mix_FreeMusic.
	// Make sure to invoke Mix_FreeChunk. (x2)
}

void GameState::Resume()
{
	cout << "Resuming GameState!" << endl;
	// Resume music playing track.
}