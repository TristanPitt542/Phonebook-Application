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
	bool load();
	bool save() const;

	// CRUD operations
	bool addContact(const std::string& name, const std::string& phone);
	bool deleteContact(const std::string& name);
	bool updatePhoneNumber(const std::string& name, const std::string& oldPhone, const std::string& newPhone);
	bool addPhoneToContact(const std::string& name, const std::string& phone);
	bool removePhoneFromContact(const std::string& name, const std::string& phone);

	// Search/Retrieve operations
	Contact* findContact(const std::string& name);
	const Contact* findContact(const std::string& name) const;
	void displayAllContacts() const;
	void searchByName(const std::string& name) const;

	// Utility
	bool contactExists(const std::string& name) const;
	int getContactCount() const;

private:
	std::map<std::string, Contact> m_contacts;
	std::string m_filename;

	// Helper functions for parsing
	void parseContactLine(const std::string& line);
};
