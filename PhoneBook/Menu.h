#pragma once
#include <iostream>
#include "PhoneBookManager.h"

class Menu
{
private:
	bool m_running;
	PhoneBookManager m_manager;

public:
	Menu(PhoneBookManager manager);

	void MainMenu();

	void AddContact();

	void EditContacts();

	void DisplayContacts();

	void Exit();

	
};