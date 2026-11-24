#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <vector>

#include "BaseGameEntity.h"

#include "ConsoleUtils.h"
#include "WaiterStates.h"
#include "StateMachine.h"
#include "State.h"



struct Task {
	int task;
	int client;
};

class Waiter : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Waiter>* m_pStateMachine;
	std::vector<Task> m_TasksToDo;
    bool m_Busy;
	int m_BusyTime;




public:

	Waiter(int id) : m_Busy(false), BaseGameEntity(id), m_BusyTime(1)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<Waiter>(this);

        m_pStateMachine->SetCurrentState(Idle::Instance());

        m_pStateMachine->SetGlobalState(WaiterGlobalState::Instance());
    }

    ~Waiter() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Waiter>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
	virtual void AddTask(int task, int client) { m_TasksToDo.push_back({task, client}); }
	virtual void RemoveTask() { if (!m_TasksToDo.empty()) { m_TasksToDo.erase(m_TasksToDo.begin()); } }
    virtual void SetBusy(bool busy) { m_Busy = busy; }
	virtual bool Busy() { return m_Busy; }
	virtual int SizeTasks() { return m_TasksToDo.size(); }
	virtual int FirstTask() { if (!m_TasksToDo.empty()) { return m_TasksToDo.front().task; } else { return -1; } }
	virtual int GetClientServing() { return m_TasksToDo.front().client; }
	virtual void SetClientServing(int client) { m_TasksToDo.front().client = client; }
	virtual int BusyTime() { return m_BusyTime; }
	virtual void CountBusyTime() { m_BusyTime--; }
    virtual void SetBusyTime(int time) { m_BusyTime = time; }
};
