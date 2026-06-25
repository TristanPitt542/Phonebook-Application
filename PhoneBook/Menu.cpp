#include "Menu.h"

Menu::Menu(PhoneBookManager manager) : m_running(true), m_manager(manager) {
	m_manager.Load();
}

void Menu::MainMenu()
{
	int choice;
	bool validInput = true;
	while (m_running)
	{
		while (validInput)
		{
			// clear console 
			system("CLS");

			std::cout << "                  PhoneBook              " << std::endl;
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "1. Add Contact" << std::endl;
			std::cout << "2. Display PhoneBook" << std::endl;
			std::cout << "3. Edit Contacts" << std::endl;
			std::cout << "4. Delete All Contacts" << std::endl;
			std::cout << "5. Exit" << std::endl;

			std::cout << "Enter your choice: " << std::endl;
			std::cin >> choice;
			std::cin.ignore(); // Clear input buffer

			// Add Contact
			if (choice == 1) {
				AddContact();
			}

			// Display Contacts
			else if (choice == 2) {
				DisplayContacts();
			}

			// Edit Contact
			else if (choice == 3) {
				EditContacts();
			}

			// Delete All Contacts
			else if (choice == 4) {
				m_manager.DeleteAllContacts();
			}
			// Exit
			else if (choice == 5) {
				m_running = false;
				return;
			}
			// Invalid Input
			else {
				std::cout << "Invalid choice. Please try again." << std::endl;
			}
		}
	}
	
	std::cout << "Exiting PhoneBook. Goodbye!" << std::endl;

}

void Menu::AddContact() {

	// clear console 
	system("CLS");

	bool running = true;
	while (running)
	{
		std::string name;
		std::string phone;
		std::cout << "Enter contact name: ";
		// Get Name
		std::getline(std::cin, name);
		if (name.empty()) {
			std::cout << "Name cannot be empty. Contact not added." << std::endl;
			continue;
		}

		// Contact already exists
		if (m_manager.ContactExists(name)) {
			std::cout << "Contact with this name already exists. Contact not added." << std::endl;
			continue;
		}

		bool validPhone = false;
		while (!validPhone) {
			// Get Phone number
			std::cout << "Enter phone number: ";
			std::getline(std::cin, phone);
			if (phone.empty()) {
				std::cout << "Phone number cannot be empty. Contact not added." << std::endl;
				continue;
			}

			if (m_manager.FindContactByPhone(phone)) {
				std::cout << "Contact with this phone number already exists. Contact not added." << std::endl;
				continue;
			}
			validPhone = true;
		}
		// Add the contact
		m_manager.AddContact(name, phone);
		running = false;
	}

}

void Menu::EditContacts()
{
	// clear console 
	system("CLS");

	std::string name;
			std::cout << "Enter the name of the contact to edit: ";
			std::getline(std::cin, name);

			if (!m_manager.ContactExists(name)) {
				std::cout << "Contact not found." << std::endl;
				return;
			}

			// Display contact's current phones
			const Contact* contact = m_manager.FindContactByName(name);
			const auto& phones = contact->GetPhones();

			std::cout << "\n--- Current Phone Numbers for " << name << " ---" << std::endl;
			for (size_t i = 0; i < phones.size(); i++) {
				std::cout << (i + 1) << ". " << phones[i] << std::endl;
			}

			std::cout << "----------------------------" << std::endl;

			std::cout << "\nWhat would you like to do?" << std::endl;
			std::cout << "1. Replace a phone number" << std::endl;
			std::cout << "2. Add a new phone number" << std::endl;
			if (phones.size() > 1 ? std::cout << "3. Remove a phone number" << std::endl : std::cout << "3. Remove Contact" << std::endl);

			std::cout << "5. Cancel" << std::endl;
			std::cout << "Choose an option: ";

			int editChoice;
			std::cin >> editChoice;
			std::cin.ignore();

			if (editChoice == 1) {
				// Replace phone number
				int phoneIndex;
				std::cout << "Enter the number (1-" << phones.size() << ") to replace: ";
				std::cin >> phoneIndex;
				std::cin.ignore();

				if (phoneIndex < 1 || phoneIndex > static_cast<int>(phones.size())) {
					std::cout << "Invalid selection." << std::endl;
					return;
				}

				std::string oldPhone = phones[phoneIndex - 1];
				std::string newPhone;
				std::cout << "Enter new phone number: ";
				std::getline(std::cin, newPhone);

				m_manager.UpdatePhoneNumber(name, oldPhone, newPhone);
			}
			else if (editChoice == 2) {
				// Add phone number
				std::string newPhone;
				std::cout << "Enter new phone number: ";
				std::getline(std::cin, newPhone);
				m_manager.AddPhoneToContact(name, newPhone);
			}
			else if (editChoice == 3) {
				// Remove phone number
				if (phones.size() == 1) {
					m_manager.DeleteContact(name);
					return;
				}

				int phoneIndex;
				std::cout << "Enter the number (1-" << phones.size() << ") to remove: ";
				std::cin >> phoneIndex;
				std::cin.ignore();

				if (phoneIndex < 1 || phoneIndex > static_cast<int>(phones.size())) {
					std::cout << "Invalid selection." << std::endl;
					return;
				}

				std::string phoneToRemove = phones[phoneIndex - 1];
				m_manager.RemovePhoneFromContact(name, phoneToRemove);
			}
			else if (editChoice == 4) {
				std::cout << "Edit cancelled." << std::endl;
			}
			else {
				std::cout << "Invalid choice." << std::endl;
			}
}

void Menu::DisplayContacts() {

	// clear console 
	system("CLS");

	bool running = true;

	while (running)
	{
		char option;

		if (m_manager.GetContactCount() == 0) {
			std::cout << "No contacts to display." << std::endl;
			std::cout << "Press any key to return to the main menu." << std::endl;
			
			std::cin.get(option);
			std::cin.ignore(); // Ignore the newline character

			if (option == '\n') {
				running = false;
			}
		}
		else
		{
			std::cout << "Sorting Options:" << std::endl;
			std::cout << "1. Sort by Name (Ascending)" << std::endl;
			std::cout << "2. Sort by Name (Descending)" << std::endl;
			std::cout << "3. Sort by Number of Phone Numbers (Ascending)" << std::endl;
			std::cout << "4. Sort by Number of Phone Numbers (Descending)" << std::endl;
			std::cout << "5. Return to Main Menu" << std::endl;

			std::cin.get(option);
			std::cin.ignore(); // Ignore the newline character

			// Sort by name (ascending)
			if (option == '1') {
				m_manager.SortContactsByName(true);
			}
			// Sort by name (descending)
			else if (option == '2') {
				m_manager.SortContactsByName(false);
			}
			// Sort by number of phone numbers (ascending)
			else if (option == '3') {
				m_manager.SortContactsByPhoneCount(true);
			}
			// Sort by number of phone numbers (descending)
			else if (option == '4') {
				m_manager.SortContactsByPhoneCount(false);
			}
			// Return to Main Menu
			else if (option == '5') {
				running = false;
			}
			else {
				std::cout << "Invalid option. Please try again." << std::endl;
				continue;
			}
		}
	}
}