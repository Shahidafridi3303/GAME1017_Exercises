#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
#include <SDL_mixer.h>
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
		cout << "Changing to GameState!" << endl;
	    STMA::ChangeState(new GameState() );
		//Music background
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_Music* music = Mix_LoadMUS("../Assets/aud/music.mp3"); // my fav music
		Mix_VolumeMusic(MIX_MAX_VOLUME * 0.2f); // volume of music
		Mix_PlayMusic(music, 0);
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

PauseState::PauseState(){}

void PauseState::Enter()
{
	cout << "Entering PauseState!" << endl;
	// Pause the playing music track.
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Changing to GameState!" << endl;
		STMA::ChangeState(new GameState());
	}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Render the pause screen.
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState!" << endl;
	// Resume the paused music track.
}

GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GameState!" << endl;
	if (Mix_Init(MIX_INIT_MP3) != 0)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
		Mix_AllocateChannels(16);
		m_sfx.emplace("music1", Mix_LoadWAV("../Assets/aud/party.mp3"));
		m_sfx.emplace("music2", Mix_LoadWAV("../Assets/aud/metro.mp3"));
	}
	// Load sfx tracks, and add them to map. (x2)
	// Load music track, and add it to map.
	// Add play it.
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing to GameState!" << endl;
		// Pause the music track.
		// STMA::PushState(new PauseState());
	}

	else if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
	{
		cout << "Changing to GameState!" << endl;
		// Pause the music track.
		STMA::PushState(new PauseState());
		Mix_PlayChannel(-1, m_sfx["music1"], 0);
	}

	else if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
	{
		cout << "Changing to GameState!" << endl;
		// Pause the music track.
		STMA::PushState(new PauseState());
		Mix_PlayChannel(-1, m_sfx["music2"], 0);
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
	cout << "Exiting GameState!" << endl;
	// Make sure to invoke Mix_FreeMusic.
	// Make sure to invoke Mix_FreeChunk. (x2)
}

void GameState::Resume()
{
	cout << "Resuming GameState!" << endl;
	// Resume music playing track.
}

EndState::EndState(){}

void EndState::Enter()
{
	cout << "Entering EndState!" << endl;
	// Stop the playing music track.
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_Q))
	{
		cout << "Exiting the program!" << endl;
		STMA::Quit();
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// Render the end screen.
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting EndState!" << endl;
	// Cleanup resources.
}

/*for (auto const& i : m_sfx)
{
	Mix_FreeChunk(i.second); // second is the Mix_Chunk*.
}
or:

//Mix_FreeChunk(m_sfx["music1"]);
//Mix_FreeChunk(m_sfx["music2"]);


m_sfx.clear(); */