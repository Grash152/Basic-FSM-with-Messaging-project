#include "Chef.h"
#include "State.h"


bool Chef::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Chef::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}