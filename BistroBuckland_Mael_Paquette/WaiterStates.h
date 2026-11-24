#pragma once
#include "State.h"

class Waiter;
struct Telegram;


class WaiterGlobalState : public State<Waiter>
{
private:

	WaiterGlobalState() {}

	//copy ctor and assignment should be private
	WaiterGlobalState(const WaiterGlobalState&);
	WaiterGlobalState& operator=(const WaiterGlobalState&);

public:

	//this is a singleton
	static WaiterGlobalState* Instance();

	virtual void Enter(Waiter* pWaiter);

	virtual void Execute(Waiter* pWaiter);

	virtual void Exit(Waiter* pWaiter);

	virtual bool OnMessage(Waiter* pWaiter, const Telegram& msg);
};

class Idle : public State<Waiter>
{
private:

	Idle() {}

	//copy ctor and assignment should be private
	Idle(const Idle&);
	Idle& operator=(const Idle&);

public:

	//this is a singleton
	static Idle* Instance();

	virtual void Enter(Waiter* pWaiter);

	virtual void Execute(Waiter* pWaiter);

	virtual void Exit(Waiter* pWaiter);

	virtual bool OnMessage(Waiter* pWaiter, const Telegram& msg);
};

class TakeOrder : public State<Waiter>
{
private:

	TakeOrder() {}

	//copy ctor and assignment should be private
	TakeOrder(const TakeOrder&);
	TakeOrder& operator=(const TakeOrder&);

public:

	//this is a singleton
	static TakeOrder* Instance();

	virtual void Enter(Waiter* pWaiter);

	virtual void Execute(Waiter* pWaiter);

	virtual void Exit(Waiter* pWaiter);

	virtual bool OnMessage(Waiter* pWaiter, const Telegram& msg);
};

class ServeDish : public State<Waiter>
{
private:

	ServeDish() {}

	//copy ctor and assignment should be private
	ServeDish(const ServeDish&);
	ServeDish& operator=(const ServeDish&);

public:

	//this is a singleton
	static ServeDish* Instance();

	virtual void Enter(Waiter* pWaiter);

	virtual void Execute(Waiter* pWaiter);

	virtual void Exit(Waiter* pWaiter);

	virtual bool OnMessage(Waiter* pWaiter, const Telegram& msg);
};


class BringBill : public State<Waiter>
{
private:

	BringBill() {}

	//copy ctor and assignment should be private
	BringBill(const BringBill&);
	BringBill& operator=(const BringBill&);

public:

	//this is a singleton
	static BringBill* Instance();

	virtual void Enter(Waiter* pWaiter);

	virtual void Execute(Waiter* pWaiter);

	virtual void Exit(Waiter* pWaiter);

	virtual bool OnMessage(Waiter* pWaiter, const Telegram& msg);
};



