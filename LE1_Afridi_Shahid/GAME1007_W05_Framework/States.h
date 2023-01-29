#pragma once
#ifndef __STATES_H__
#define __STATES_H__

class State // Abstract base class.
{ // No objects of state can ever be created.
public:
	virtual void Enter() = 0; // Pure virtual method.
	virtual void Update() = 0;
	void Render(); // Make a definition for Renderer();
	virtual void Exit() = 0;
	void Resume() {};
protected: // Private but inherited.
	State () = default;
};

#endif