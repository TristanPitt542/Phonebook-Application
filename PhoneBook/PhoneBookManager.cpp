#include "PhoneBookManager.h"

bool PhoneBookManager::load() {
	std::ifstream file(m_filename);

	if (!file.is_open()) {
		std::cout << "No existing phonebook found. Starting with empty phonebook.\n";
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			parseContactLine(line);
		}
	}

	file.close();
	std::cout << "Loaded " << m_contacts.size() << " contact(s).\n";
	return true;
}

bool PhoneBookManager::save() const {
	std::ofstream file(m_filename);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file for writing: " << m_filename << "\n";
		return false;
	}

	for (const auto& [name, contact] : m_contacts) {
		file << name;
		for (const auto& phone : contact.getPhones()) {
			file << "|" << phone;
		}
		file << "\n";
	}

	file.close();
	return true;
}

void PhoneBookManager::parseContactLine(const std::string& line) {
	std::stringstream ss(line);
	std::string name, phone;

	// Get name (before first |)
	std::getline(ss, name, '|');

	if (name.empty()) {
		return; // Skip malformed lines
	}

	Contact contact(name, "");

	// Get all phone numbers
	while (std::getline(ss, phone, '|')) {
		if (!phone.empty()) {
			contact.addPhone(phone);
		}
	}

	m_contacts[name] = contact;
}

bool PhoneBookManager::addContact(const std::string& name, const std::string& phone) {
	if (name.empty() || phone.empty()) {
		std::cerr << "Error: Name and phone cannot be empty.\n";
		return false;
	}

	if (m_contacts.find(name) != m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' already exists.\n";
		return false;
	}


	Contact newContact(name, phone);
	m_contacts[name] = newContact;
	save();

	std::cout << "Contact added successfully.\n";
	return true;
}

bool PhoneBookManager::deleteContact(const std::string& name) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	m_contacts.erase(it);
	save();

	std::cout << "Contact deleted successfully.\n";
	return true;
}

bool PhoneBookManager::addPhoneToContact(const std::string& name, const std::string& phone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	it->second.addPhone(phone);
	save();

	std::cout << "Phone number added successfully.\n";
	return true;
}

bool PhoneBookManager::removePhoneFromContact(const std::string& name, const std::string& phone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	it->second.removePhone(phone);

	if (it->second.getPhones().empty()) {
		std::cout << "Warning: Contact has no phone numbers left. Consider deleting the contact.\n";
	}

	save();
	std::cout << "Phone number removed successfully.\n";
	return true;
}

bool PhoneBookManager::updatePhoneNumber(const std::string& name, const std::string& oldPhone, const std::string& newPhone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	it->second.updatePhone(oldPhone, newPhone);
	save();

	std::cout << "Phone number updated successfully.\n";
	return true;
}

Contact* PhoneBookManager::findContact(const std::string& name) {
	auto it = m_contacts.find(name);
	return (it != m_contacts.end()) ? &it->second : nullptr;
}

const Contact* PhoneBookManager::findContact(const std::string& name) const {
	auto it = m_contacts.find(name);
	return (it != m_contacts.end()) ? &it->second : nullptr;
}

bool PhoneBookManager::contactExists(const std::string& name) const {
	return m_contacts.find(name) != m_contacts.end();
}

int PhoneBookManager::getContactCount() const {
	return (int)m_contacts.size();
}

void PhoneBookManager::displayAllContacts() const {
	if (m_contacts.empty()) {
		std::cout << "No contacts found.\n";
		return;
	}

	std::cout << "\n========== PHONEBOOK ==========\n";
	int count = 1;
	for (const auto& [name, contact] : m_contacts) {
		std::cout << count << ". " << name << "\n";
		for (const auto& phone : contact.getPhones()) {
			std::cout << "   - " << phone << "\n";
		}
	}
	std::cout << "===============================\n\n";
}

void PhoneBookManager::searchByName(const std::string& name) const {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cout << "Contact '" << name << "' not found.\n";
		return;
	}

	const Contact& contact = it->second;
	std::cout << "\n--- Contact Found ---\n";
	std::cout << "Name: " << contact.getName() << "\n";
	std::cout << "Phone Numbers:\n";
	for (const auto& phone : contact.getPhones()) {
		std::cout << "  - " << phone << "\n";
	}
	std::cout << "---------------------\n\n";
}
