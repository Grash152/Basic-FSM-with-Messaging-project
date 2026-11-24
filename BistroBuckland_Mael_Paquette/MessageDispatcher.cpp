#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "CrudeTimer.h"

#include <iostream>

//uncomment to print messaging info (IDs and numbers only, nothing game-specific)
//#define SHOW_MESSAGING_INFO

MessageDispatcher* MessageDispatcher::Instance()
{
    static MessageDispatcher instance;
    return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity* pReceiver, const Telegram& telegram)
{
    if (!pReceiver->HandleMessage(telegram))
    {
#ifdef SHOW_MESSAGING_INFO
        std::cout << "\nMessage not handled";
#endif
    }
}

void MessageDispatcher::DispatchMsg(double delay, int sender, int receiver,
    int msg, void* ExtraInfo)
{
    BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(receiver);

    Telegram telegram(0, sender, receiver, msg, ExtraInfo);

    if (delay <= 0.0)
    {
#ifdef SHOW_MESSAGING_INFO
        std::cout << "\nTelegram sent at " << Clock->GetCurrentTime()
            << " from " << sender << " to " << receiver << " msg " << msg;
#endif
        Discharge(pReceiver, telegram);
    }
    else
    {
        telegram.DispatchTime = Clock->GetCurrentTime() + delay;
        PriorityQ.insert(telegram);
#ifdef SHOW_MESSAGING_INFO
        std::cout << "\nDelayed telegram recorded at " << Clock->GetCurrentTime()
            << " from " << sender << " to " << receiver << " msg " << msg;
#endif
    }
}

void MessageDispatcher::DispatchDelayedMessages()
{
    double CurrentTime = Clock->GetCurrentTime();

    while (!PriorityQ.empty() &&
        (PriorityQ.begin()->DispatchTime < CurrentTime) &&
        (PriorityQ.begin()->DispatchTime > 0))
    {
        const Telegram& telegram = *PriorityQ.begin();
        BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(telegram.Receiver);
        Discharge(pReceiver, telegram);
        PriorityQ.erase(PriorityQ.begin());
    }
}