#include <fstream>
#include <time.h>

#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "Chef.h"
#include "Waiter.h"
#include "Clients.h"
#include "State.h"
#include "MessageTypes.h"
using std::cout;

std::ofstream os;

int main()
{

    //seed random number generator
    srand((unsigned)time(NULL));


    Chef* chef = new Chef(ent_Chef);
	Waiter* waiter = new Waiter(ent_Waiter);
	Clients* Steve = new Clients(ent_Client1, 4);
	Clients* Sophie = new Clients(ent_Client2, 50);


    //register them with the entity manager
    EntityMgr->RegisterEntity(chef);
    EntityMgr->RegisterEntity(waiter);
    EntityMgr->RegisterEntity(Steve);
    EntityMgr->RegisterEntity(Sophie);

    Dispatcher->DispatchMsg(0.1, //time delay
        SENDER_ID_IRRELEVANT,        //sender ID
        ent_Client1,            //receiver ID
        Msg_Arrive   //msg
    );
    Dispatcher->DispatchMsg(1, //time delay
        SENDER_ID_IRRELEVANT,        //sender ID
        ent_Client2,            //receiver ID
        Msg_Arrive   //msg
    );

    for (int i = 0; i < 35; ++i)
    {
        chef->Update();
        waiter->Update();
        Steve->Update();
        Sophie->Update();
	
	
	

        //dispatch any delayed messages
        Dispatcher->DispatchDelayedMessages();

        Sleep(600);
    }

    //tidy up
    delete chef;
    delete waiter;
    delete Steve;
    delete Sophie;


    //wait for a keypress before exiting
    PressAnyKeyToContinue();


    return 0;
}






