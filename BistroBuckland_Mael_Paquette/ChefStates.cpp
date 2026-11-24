
#include "ChefStates.h"
#include "Chef.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>

using std::cout;
using std::vector;
using std::string;

ChefGlobalState* ChefGlobalState::Instance()
{
	static ChefGlobalState instance;
	return &instance;
}

void ChefGlobalState::Enter(Chef* pChef)
{

}
void ChefGlobalState::Execute(Chef* pChef)
{

}
void ChefGlobalState::Exit(Chef* pChef)
{

}



bool ChefGlobalState::OnMessage(Chef* pChef, const Telegram& msg)
{

    switch (msg.Msg)
    {
    case Msg_NewOrder:
    {

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(pChef  ->ID()) <<
            ": Je rajoute la commande dans ma liste";

        pChef->AddDishToCook((int)(intptr_t)msg.ExtraInfo);
    }

    return true;

    }

    return false;
}

WaitForOrder* WaitForOrder::Instance()
{
	static WaitForOrder instance;
	return &instance;
}

void WaitForOrder::Enter(Chef* pChef)
{
}	

void WaitForOrder::Execute(Chef* pChef)
{
	if (pChef->DishesToCook() > 0)
	{
		pChef->GetFSM()->ChangeState(CookDish::Instance());
	}
	else
	{
		cout << "\n" << GetNameOfEntity(pChef->ID()) << ": J'attends une commande, Je vais nettoyer un peu";
	}
}

void WaitForOrder::Exit(Chef* pChef)
{

}

bool WaitForOrder::OnMessage(Chef* pChef, const Telegram& msg)
{
	return false;
}


CookDish* CookDish::Instance()
{
	static CookDish instance;
	return &instance;
}

void CookDish::Enter(Chef* pChef)
{
	if (pChef->GetStock() == 0)
	{
		cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je dois me reapprovisionner";
		pChef->GetFSM()->ChangeState(Restock::Instance());
	}
    else
    {
        if (!pChef->Cooking())
        {
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je commence a cuisiner";
            pChef->CookDish();
            Dispatcher->DispatchMsg(3, //time delay
                pChef->ID(),        //sender ID
                pChef->ID(),            //receiver ID
                Msg_DishCooked   //msg
                
            );
			pChef->SetCooking(true);
        }
    }
}

void CookDish::Execute(Chef* pChef)
{
	cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je cuisine un plat";
}

void CookDish::Exit(Chef* pChef)
{

}

bool CookDish::OnMessage(Chef* pChef, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_DishCooked:
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pChef->ID()) <<
			": Plat sur la passe";
	
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			pChef->ID(),
			ent_Waiter,
			Msg_OrderReady,
			(void*)(intptr_t)pChef->NextOrder()
		);
		pChef->DishDone();
		pChef->SetCooking(false);
		pChef->GetFSM()->ChangeState(WaitForOrder::Instance());
	}
	return true;
	}
	return false;
}

Restock* Restock::Instance()
{
	static Restock instance;
	return &instance;
}

void Restock::Enter(Chef* pChef)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je vais me reapprovisionner";
}

void Restock::Execute(Chef* pChef)
{
	cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je me reapprovisionne";
	pChef->GettingStock();
	if (pChef->GetStock() == 3)
	{
		pChef->GetFSM()->RevertToPreviousState();
	}
}

void Restock::Exit(Chef* pChef)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pChef->ID()) << ": Je suis reapprovisionner";
}

bool Restock::OnMessage(Chef* pChef, const Telegram& msg)
{
	return false;
}