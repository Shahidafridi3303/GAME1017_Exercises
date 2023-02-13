#pragma once
#ifndef __STATES_H__
#define __STATES_H__

#include <map>
#include <string>
#include <SDL_mixer.h>

//Mix_Music* m_pGuile;
//std::map<std::string, Mix_Chunk*> m_sfx;

class State // Abstract base class.
{ // No objects of state can ever be created.
public:
	virtual void Enter() = 0; // Pure virtual method.
	virtual void Update() = 0;
	virtual void Render(); // Will be defined in State.
	virtual void Exit() = 0;
	virtual void Resume() {}; // Considered defined for all subclasses.
protected: // Private but inherited.
	State () = default;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	std::map<std::string, Mix_Chunk*> m_sfx;
private:
	
	//std::map<std::string, Mix_Music*> musicTracks;
	// Map for music track goes here.
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};
//Make definition for PauseState.

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
private:
	//std::map<std::string, Mix_Music*> musicTracks;
	// Map for music track goes here.
	std::map<std::string, Mix_Chunk*> m_sfx;
	// Map for sound effects goes here.
};

class EndState : public State
{
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:
	
};
//Make definition for EndState.

#endif