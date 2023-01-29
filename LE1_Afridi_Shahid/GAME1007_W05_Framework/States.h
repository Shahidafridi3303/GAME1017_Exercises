#pragma once
#ifndef __STATES_H__
#define __STATES_H__
#include <map>
#include <SDL_mixer.h>
#include <string>

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
	virtual void Resume();
private:
	// Map for music track goes here.
	// std::map<std::string, Mix_Music*> m_music;
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
	// Map for music track goes here.
	//std::map<std::string, Mix_Music*> m_music;// Map for sound effects goes here.
};

//Make definition for EndState.

#endif