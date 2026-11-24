#include "WaiterStates.h"
#include "Waiter.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "WaiterTasks.h"

#include <iostream>
using std::cout;
using std::vector;
using std::string;


WaiterGlobalState* WaiterGlobalState::Instance()
{
    static WaiterGlobalState instance;
    return &instance;
}

void WaiterGlobalState::Enter(Waiter* pWaiter)
{
}

void WaiterGlobalState::Execute(Waiter* pWaiter)
{
	
}

void WaiterGlobalState::Exit(Waiter* pWaiter)
{
}

bool WaiterGlobalState::OnMessage(Waiter* pWaiter, const Telegram& msg)
{
	if (pWaiter->Busy())
	{
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": Un instant, j'arrive";

		switch (msg.Msg)
		{
		case Msg_ReadyToOrder:
		{
			pWaiter->AddTask(TakingOrder, msg.Sender);
			
			break;
		}
		case Msg_OrderReady:
		{
			pWaiter->AddTask(ServingOrder,(int)(intptr_t)msg.ExtraInfo);
			break;
		}
		case Msg_BillPlease:
		{
			pWaiter->AddTask(BringingBill, msg.Sender);
			break;
		}
		default:
			return false;
		}
	}
	return true;
}


Idle* Idle::Instance()
{
	static Idle instance;
	return &instance;
}	

void Idle::Enter(Waiter* pWaiter)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	
	if (pWaiter->SizeTasks() <= 0) 
	{
		pWaiter->SetBusy(false);
	}

}

void Idle::Execute(Waiter* pWaiter)
{
	if (pWaiter->Busy())
	{
		switch (pWaiter->FirstTask())
		{
		case TakingOrder:
			pWaiter->GetFSM()->ChangeState(TakeOrder::Instance());
			break;
		case ServingOrder:
			pWaiter->GetFSM()->ChangeState(ServeDish::Instance());
			break;
		case BringingBill:
			pWaiter->GetFSM()->ChangeState(BringBill::Instance());
			break;
		default:
			break;
		}
	}
	else
	{
		cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": Je nettoye un vers au comptoir";
	}
}

void Idle::Exit(Waiter* pWaiter)
{
}

bool Idle::OnMessage(Waiter* pWaiter, const Telegram& msg)
{
	if (!pWaiter->Busy())
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		
		switch (msg.Msg)
		{
		case Msg_ReadyToOrder:
		{
			pWaiter->AddTask(TakingOrder, msg.Sender);
			pWaiter->GetFSM()->ChangeState(TakeOrder::Instance());
			break;
		}
		case Msg_OrderReady:
		{
			pWaiter->AddTask(ServingOrder, (int)(intptr_t)msg.ExtraInfo);
			pWaiter->GetFSM()->ChangeState(ServeDish::Instance());
			break;
		}
		case Msg_BillPlease:
		{
			pWaiter->AddTask(BringingBill, msg.Sender);
			pWaiter->GetFSM()->ChangeState(BringBill::Instance());
			break;
		}
		default:
			return false;
		}
		
	
	}
	return true;
}

TakeOrder* TakeOrder::Instance()
{
	static TakeOrder instance;
	return &instance;
}

void TakeOrder::Enter(Waiter* pWaiter)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": Je prends la commande de " << GetNameOfEntity(pWaiter->GetClientServing());

	pWaiter->SetBusy(true);
	pWaiter->SetBusyTime(2);
}

void TakeOrder::Execute(Waiter* pWaiter)
{


	if (pWaiter->BusyTime() > 0)
	{
		pWaiter->CountBusyTime();
	}
	else
	{
	
		pWaiter->GetFSM()->ChangeState(Idle::Instance());
	}
	
}

void TakeOrder::Exit(Waiter* pWaiter)
{
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": J'envoie la commande au chef ";
	Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY, //time delay
		pWaiter->ID(),        //sender ID
		ent_Chef,            //receiver ID
		Msg_NewOrder,		//msg
		(void*)(intptr_t)pWaiter->GetClientServing() //additional info
	);
	pWaiter->RemoveTask();
}

bool TakeOrder::OnMessage(Waiter* pWaiter, const Telegram& msg)
{
	return false;
}

ServeDish* ServeDish::Instance()
{
	static ServeDish instance;
	return &instance;
}	

void ServeDish::Enter(Waiter* pWaiter)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": Je prend le plat a " << GetNameOfEntity(pWaiter->GetClientServing());
	pWaiter->SetBusyTime(2);
	pWaiter->SetBusy(true);

}

void ServeDish::Execute(Waiter* pWaiter)
{

	if (pWaiter->BusyTime() > 0)
	{
		pWaiter->CountBusyTime();
	}
	else
	{
	
		pWaiter->GetFSM()->ChangeState(Idle::Instance());
	}
}

void ServeDish::Exit(Waiter* pWaiter)
{
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": Je sers le plat a " << GetNameOfEntity(pWaiter->GetClientServing());

	Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY, //time delay
		pWaiter->ID(),        //sender ID
		pWaiter->GetClientServing(),            //receiver ID
		Msg_FoodServed   //msg
	);
	pWaiter->RemoveTask();
}

bool ServeDish::OnMessage(Waiter* pWaiter, const Telegram& msg)
{
	return false;
}

BringBill* BringBill::Instance()
{
	static BringBill instance;
	return &instance;
}

void BringBill::Enter(Waiter* pWaiter)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": J'imprime l'addition a " << GetNameOfEntity(pWaiter->GetClientServing());


	pWaiter->SetBusy(true);
	pWaiter->SetBusyTime(1);
}

void BringBill::Execute(Waiter* pWaiter)
{

	if (pWaiter->BusyTime() > 0)
	{
		pWaiter->CountBusyTime();
	}
	else
	{
		
		pWaiter->GetFSM()->ChangeState(Idle::Instance());
	}
}

void BringBill::Exit(Waiter* pWaiter)
{
	cout << "\n" << GetNameOfEntity(pWaiter->ID()) << ": J'apporte l'addition a " << GetNameOfEntity(pWaiter->GetClientServing());

	Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY, //time delay
		pWaiter->ID(),        //sender ID
		pWaiter->GetClientServing(),            //receiver ID
		Msg_HereIsTheBill   //msg
	);

	pWaiter->RemoveTask();
}

bool BringBill::OnMessage(Waiter* pWaiter, const Telegram& msg)
{
	return false;
}


