#include <iostream>
#include "Menu.h"


int main() {
	PhoneBookManager manager;
	Menu menu(manager);
	menu.MainMenu();
}