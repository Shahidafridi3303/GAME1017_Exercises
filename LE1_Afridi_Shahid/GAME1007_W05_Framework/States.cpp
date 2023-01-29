#include "States.h"
#include "Engine.h"

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

// In a  subclass to invoke the Render above, we just do:
// State::Render();