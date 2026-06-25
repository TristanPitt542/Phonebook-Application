#pragma once
#include "Contact.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

class PhoneBookManager {
public:
	PhoneBookManager(const std::string& filename = "contacts.txt") 
		: m_filename(filename) {}

	// File I/O operations
	bool Load();
	bool Save() const;

	// CRUD operations
	bool AddContact(const std::string& name, const std::string& phone);
	bool DeleteContact(const std::string& name);
	bool DeleteAllContacts();
	bool UpdatePhoneNumber(const std::string& name, const std::string& oldPhone, const std::string& newPhone);
	bool AddPhoneToContact(const std::string& name, const std::string& phone);
	bool RemovePhoneFromContact(const std::string& name, const std::string& phone);

	// Search/Retrieve operations
	const Contact* FindContactByName(const std::string& name) const;
	const Contact* FindContactByPhone(const std::string& phone) const;

	void DisplayAllContacts(const std::vector<std::pair<std::string, Contact>>& contacts) const;
	
	//void SearchByName(const std::string& name) const;

	// Sort operations
	void SortContactsByName(bool ascending);
	void SortContactsByPhoneCount(bool ascending);

	// Utility
	bool ContactExists(const std::string& name) const;
	int GetContactCount() const;

private:
	std::map<std::string, Contact> m_contacts;
	std::string m_filename;

	// Helper functions for parsing
	void ParseContactLine(const std::string& line);
};
