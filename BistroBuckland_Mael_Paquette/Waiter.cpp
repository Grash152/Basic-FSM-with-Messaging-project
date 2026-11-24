#include "Waiter.h"
#include "State.h"

bool Waiter::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Waiter::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}