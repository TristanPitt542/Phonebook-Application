#include "Menu.h"

Menu::Menu(PhoneBookManager manager) : m_running(true), m_manager(manager) {
	m_manager.load();
}

void Menu::MainMenu()
{
	int choice;
	bool validInput = true;
	while (validInput)
	{
		// clear console 
		system("CLS");

		std::cout << "                  PhoneBook              " << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "1. Add Contact" << std::endl;
		std::cout << "2. Display PhoneBook" << std::endl;
		std::cout << "3. Edit Contact" << std::endl;
		std::cout << "4. Exit" << std::endl;

		std::cout << "Enter your choice: " << std::endl;
		std::cin >> choice;
		std::cin.ignore(); // Clear input buffer

		// clear console 
		system("CLS");

		// Add Contact
		if (choice == 1) {
			std::string name, phoneNumber;
			std::cout << "Enter Name: ";
			std::getline(std::cin, name);
			std::cout << "Enter Phone Number: ";
			std::getline(std::cin, phoneNumber);
			m_manager.addContact(name, phoneNumber);
		}
		// Display Contacts
		else if (choice == 2) {
			m_manager.displayAllContacts();
		}

		// Edit Contact
		else if (choice == 3) {
			std::string name;
			std::cout << "Enter the name of the contact to edit: ";
			std::getline(std::cin, name);

			if (!m_manager.contactExists(name)) {
				std::cout << "Contact not found." << std::endl;
				continue;
			}

			// Display contact's current phones
			Contact* contact = m_manager.findContact(name);
			const auto& phones = contact->getPhones();

			std::cout << "\n--- Current Phone Numbers for " << name << " ---" << std::endl;
			for (size_t i = 0; i < phones.size(); i++) {
				std::cout << (i + 1) << ". " << phones[i] << std::endl;
			}
			std::cout << "----------------------------" << std::endl;

			std::cout << "\nWhat would you like to do?" << std::endl;
			std::cout << "1. Replace a phone number" << std::endl;
			std::cout << "2. Add a new phone number" << std::endl;
			if (phones.size() > 1)
				std::cout << "3. Remove a phone number" << std::endl;
			else
				std::cout << "3. Remove Contact " << std::endl;

			std::cout << "4. Cancel" << std::endl;
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
					continue;
				}

				std::string oldPhone = phones[phoneIndex - 1];
				std::string newPhone;
				std::cout << "Enter new phone number: ";
				std::getline(std::cin, newPhone);

				m_manager.updatePhoneNumber(name, oldPhone, newPhone);
			}
			else if (editChoice == 2) {
				// Add phone number
				std::string newPhone;
				std::cout << "Enter new phone number: ";
				std::getline(std::cin, newPhone);
				m_manager.addPhoneToContact(name, newPhone);
			}
			else if (editChoice == 3) {
				// Remove phone number
				if (phones.size() == 1) {
					m_manager.deleteContact(name);
					continue;
				}

				int phoneIndex;
				std::cout << "Enter the number (1-" << phones.size() << ") to remove: ";
				std::cin >> phoneIndex;
				std::cin.ignore();

				if (phoneIndex < 1 || phoneIndex > static_cast<int>(phones.size())) {
					std::cout << "Invalid selection." << std::endl;
					continue;
				}

				std::string phoneToRemove = phones[phoneIndex - 1];
				m_manager.removePhoneFromContact(name, phoneToRemove);
			}
			else if (editChoice == 4) {
				std::cout << "Edit cancelled." << std::endl;
			}
			else {
				std::cout << "Invalid choice." << std::endl;
			}
		}

		// Exit
		else if (choice == 4) {
			return;
		}
		// Invalid Input
		else {
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	}
}
