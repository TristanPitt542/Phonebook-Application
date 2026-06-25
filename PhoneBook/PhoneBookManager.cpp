#include "PhoneBookManager.h"
#include <vector>
#include <algorithm>

bool PhoneBookManager::Load() {
	std::ifstream file(m_filename);

	if (!file.is_open()) {
		std::cout << "No existing phonebook found. Starting with empty phonebook.\n";
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			ParseContactLine(line);
		}
	}

	file.close();
	std::cout << "Loaded " << m_contacts.size() << " contact(s).\n";
	return true;
}

bool PhoneBookManager::Save() const {
	std::ofstream file(m_filename);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file for writing: " << m_filename << "\n";
		return false;
	}

	for (const auto& [name, contact] : m_contacts) {
		file << name;
		for (const auto& phone : contact.GetPhones()) {
			file << "|" << phone;
		}
		file << "\n";
	}

	file.close();
	return true;
}

void PhoneBookManager::ParseContactLine(const std::string& line) {
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
			contact.AddPhone(phone);
		}
	}

	m_contacts[name] = contact;
}

bool PhoneBookManager::AddContact(const std::string& name, const std::string& phone) {
	if (name.empty() || phone.empty()) {
		std::cerr << "Error: Name and phone cannot be empty.\n";
		return false;
	}

	if (m_contacts.find(name) != m_contacts.end() || m_contacts.find(phone) != m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' or phone number '" + phone + "' already exists.\n";
		return false;
	}


	Contact newContact(name, phone);
	m_contacts[name] = newContact;
	Save();

	std::cout << "Contact added successfully.\n";
	return true;
}

bool PhoneBookManager::DeleteContact(const std::string& name) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	m_contacts.erase(it);
	Save();

	std::cout << "Contact deleted successfully.\n";
	return true;
}

bool PhoneBookManager::DeleteAllContacts() {
	m_contacts.clear();
	Save();
	std::cout << "All contacts deleted successfully.\n";
	return true;
}

bool PhoneBookManager::AddPhoneToContact(const std::string& name, const std::string& phone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	it->second.AddPhone(phone);
	Save();

	std::cout << "Phone number added successfully.\n";
	return true;
}

bool PhoneBookManager::RemovePhoneFromContact(const std::string& name, const std::string& phone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

		it->second.RemovePhone(phone);

		Save();
		std::cout << "Phone number removed successfully.\n";
		return true;
	}

bool PhoneBookManager::UpdatePhoneNumber(const std::string& name, const std::string& oldPhone, const std::string& newPhone) {
	auto it = m_contacts.find(name);

	if (it == m_contacts.end()) {
		std::cerr << "Error: Contact '" << name << "' not found.\n";
		return false;
	}

	it->second.UpdatePhone(oldPhone, newPhone);
	Save();

	std::cout << "Phone number updated successfully.\n";
	return true;
}

const Contact* PhoneBookManager::FindContactByName(const std::string& name) const {
	auto it = m_contacts.find(name);
	return (it != m_contacts.end()) ? &it->second : nullptr;
}

const Contact* PhoneBookManager::FindContactByPhone(const std::string& phone) const {
	for (const auto& [name, contact] : m_contacts) {
		if (contact.GetPhones().end() != std::find(contact.GetPhones().begin(), contact.GetPhones().end(), phone)) {
			return &contact;
		}
	}
	return nullptr;
}

bool PhoneBookManager::ContactExists(const std::string& name) const {
	return m_contacts.find(name) != m_contacts.end();
}

int PhoneBookManager::GetContactCount() const {
	return (int)m_contacts.size();
}

void PhoneBookManager::DisplayAllContacts(const std::vector<std::pair<std::string, Contact>>& contacts) const {
	if (contacts.empty()) {
		std::cout << "No contacts found.\n";
		return;
	}

	std::cout << "\n========== PHONEBOOK ==========\n";
	int count = 1;
	for (const auto& [name, contact] : contacts) {
		std::cout << count << ". " << name << "\n";
		for (const auto& phone : contact.GetPhones()) {
			std::cout << "   - " << phone << "\n";
		}
	}
	std::cout << "===============================\n\n";
}

// Sorting
void PhoneBookManager::SortContactsByName(bool ascending) {
	std::vector<std::pair<std::string, Contact>> vec(m_contacts.begin(), m_contacts.end());
	std::sort(vec.begin(), vec.end(), [ascending](const auto& a, const auto& b) {
		if (ascending) return a.first < b.first;
		return a.first > b.first;
	});

	this->DisplayAllContacts(vec);
}

void PhoneBookManager::SortContactsByPhoneCount(bool ascending) {
	std::vector<std::pair<std::string, Contact>> vec(m_contacts.begin(), m_contacts.end());
	std::sort(vec.begin(), vec.end(), [ascending](const auto& a, const auto& b) {
		if (ascending) return a.second.GetPhones().size() < b.second.GetPhones().size();
		return a.second.GetPhones().size() > b.second.GetPhones().size();
	});

	this->DisplayAllContacts(vec);
}