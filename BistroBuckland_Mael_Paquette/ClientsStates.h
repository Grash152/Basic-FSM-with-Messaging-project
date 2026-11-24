#pragma once
#include "State.h"


class Clients;
struct Telegram;


class ClientsGlobalState : public State<Clients>
{
private:

	ClientsGlobalState() {}

	//copy ctor and assignment should be private
	ClientsGlobalState(const ClientsGlobalState&);
	ClientsGlobalState& operator=(const ClientsGlobalState&);

public:

	//this is a singleton
	static ClientsGlobalState* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class Outside : public State<Clients>
{
private:
	Outside() {}
	//copy ctor and assignment should be private
	Outside(const Outside&);
	Outside& operator=(const Outside&);
public:

	//this is a singleton
	static Outside* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class ReadMenu : public State<Clients>
{
private:
	ReadMenu() {}
	//copy ctor and assignment should be private
	ReadMenu(const ReadMenu&);
	ReadMenu& operator=(const ReadMenu&);
public:

	//this is a singleton
	static ReadMenu* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class WaitForFood : public State<Clients>
{
private:
	WaitForFood() {}
	//copy ctor and assignment should be private
	WaitForFood(const WaitForFood&);
	WaitForFood& operator=(const WaitForFood&);
public:

	//this is a singleton
	static WaitForFood* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class Eat : public State<Clients>
{
private:
	Eat() {}
	//copy ctor and assignment should be private
	Eat(const Eat&);
	Eat& operator=(const Eat&);
public:

	//this is a singleton
	static Eat* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class WaitForBill : public State<Clients>
{
private:
	WaitForBill() {}
	//copy ctor and assignment should be private
	WaitForBill(const WaitForBill&);
	WaitForBill& operator=(const WaitForBill&);
public:

	//this is a singleton
	static WaitForBill* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class Leave : public State<Clients>
{
private:
	Leave() {}
	//copy ctor and assignment should be private
	Leave(const Leave&);
	Leave& operator=(const Leave&);
public:

	//this is a singleton
	static Leave* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};

class LeaveAngry : public State<Clients>
{
private:
	LeaveAngry() {}
	//copy ctor and assignment should be private
	LeaveAngry(const LeaveAngry&);
	LeaveAngry& operator=(const LeaveAngry&);
public:

	//this is a singleton
	static LeaveAngry* Instance();

	virtual void Enter(Clients* pClients);

	virtual void Execute(Clients* pClients);

	virtual void Exit(Clients* pClients);

	virtual bool OnMessage(Clients* pClients, const Telegram& msg);
};