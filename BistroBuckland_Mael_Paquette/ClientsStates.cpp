
#include "ClientsStates.h"
#include "Clients.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>

using std::cout;
using std::vector;
using std::string;


ClientsGlobalState* ClientsGlobalState::Instance()
{
	static ClientsGlobalState instance;
	return &instance;
}	

void ClientsGlobalState::Enter(Clients* pClients)
{
}
void ClientsGlobalState::Execute(Clients* pClients)
{
	if (pClients->Patience() <= 0)
	{

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je n'ai plus de patience, je pars";
		pClients->GetFSM()->ChangeState(LeaveAngry::Instance());
		pClients->AddPatience();
	}
	else if (pClients->GetFSM()->isInState(*WaitForBill::Instance()) || pClients->GetFSM()->isInState(*WaitForFood::Instance()))
	{
		pClients->LowerPatience();
	}
}
void ClientsGlobalState::Exit(Clients* pClients)
{
}

bool ClientsGlobalState::OnMessage(Clients* pClients, const Telegram& msg)
{
	return false;
}

Outside* Outside::Instance()
{
	static Outside instance;
	return &instance;
}	

void Outside::Enter(Clients* pClients)
{
}

void Outside::Execute(Clients* pClients)
{
}

void Outside::Exit(Clients* pClients)
{
}

bool Outside::OnMessage(Clients* pClients, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_Arrive:
	{

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je voudrais une table";
		pClients->GetFSM()->ChangeState(ReadMenu::Instance());
		return true;
	}
	}
	return false;
}

ReadMenu* ReadMenu::Instance()
{
	static ReadMenu instance;
	return &instance;
}

void ReadMenu::Enter(Clients* pClients)
{
	pClients->SetBusyTime(2);
	
}

void ReadMenu::Execute(Clients* pClients)
{
	
	if(pClients->ReadMenu() <= 0)
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (pClients->Once())
		{
			cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je suis pret a commande";
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY, //time delay
				pClients->ID(),        //sender ID
				ent_Waiter,            //receiver ID
				Msg_ReadyToOrder   //msg
			);
			pClients->SetOnce(false);
		}
		if (pClients->BusyTime() > 0)
		{
			pClients->CountBusyTime();
		}
		else
			pClients->GetFSM()->ChangeState(WaitForFood::Instance());
	}
	else
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je lis le menu";
	}

}

void ReadMenu::Exit(Clients* pClients)
{
	
}

bool ReadMenu::OnMessage(Clients* pClients, const Telegram& msg)
{
	return false;
}

WaitForFood* WaitForFood::Instance()
{
	static WaitForFood instance;
	return &instance;
}

void WaitForFood::Enter(Clients* pClients)
{
}

void WaitForFood::Execute(Clients* pClients)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pClients->ID()) << ": J'attends mon plat";
}

void WaitForFood::Exit(Clients* pClients)
{

}

bool WaitForFood::OnMessage(Clients* pClients, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_FoodServed:
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je commence a manger";
		pClients->AddPatience();
		pClients->GetFSM()->ChangeState(Eat::Instance());
		return true;
	}
	}
	return false;
}

Eat* Eat::Instance()
{
	static Eat instance;
	return &instance;
}

void Eat::Enter(Clients* pClients)
{
}

void Eat::Execute(Clients* pClients)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (pClients->Eat() <= 0)
	{
		pClients->GetFSM()->ChangeState(WaitForBill::Instance());
	}
	else
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je mange";
}

void Eat::Exit(Clients* pClients)
{
	cout << "\n" << GetNameOfEntity(pClients->ID()) << ": J'ai fini de manger, je veux l'addition";
	Dispatcher->DispatchMsg(1, //time delay
		pClients->ID(),        //sender ID
		ent_Waiter,            //receiver ID
		Msg_BillPlease   //msg
	);
}

bool Eat::OnMessage(Clients* pClients, const Telegram& msg)
{
	return false;
}

WaitForBill* WaitForBill::Instance()
{
	static WaitForBill instance;
	return &instance;
}

void WaitForBill::Enter(Clients* pClients)
{
}

void WaitForBill::Execute(Clients* pClients)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pClients->ID()) << ": J'attends l'addition";
}

void WaitForBill::Exit(Clients* pClients)
{
}

bool WaitForBill::OnMessage(Clients* pClients, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_HereIsTheBill:
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je paye et je pars";
		pClients->GetFSM()->ChangeState(Leave::Instance());
		return true;
	}
	}
	return false;
}

Leave* Leave::Instance()
{
	static Leave instance;
	return &instance;
}

void Leave::Enter(Clients* pClients)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je quitte le restaurant";
}

void Leave::Execute(Clients* pClients)
{
}

void Leave::Exit(Clients* pClients)
{
}

bool Leave::OnMessage(Clients* pClients, const Telegram& msg)
{
	return false;
}

LeaveAngry* LeaveAngry::Instance()
{
	static LeaveAngry instance;
	return &instance;
}

void LeaveAngry::Enter(Clients* pClients)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pClients->ID()) << ": Je quitte le restaurant en colere";
}

void LeaveAngry::Execute(Clients* pClients)
{
}

void LeaveAngry::Exit(Clients* pClients)
{
}

bool LeaveAngry::OnMessage(Clients* pClients, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_FoodServed:
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pClients->ID()) << ": La nourriture a ete servie trop tard";
		return true;
	}
	}
	return false;
}