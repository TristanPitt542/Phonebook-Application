#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Contact {
public:
    Contact() : m_name("") {}

    Contact(const std::string& name, const std::string& phone)
        : m_name(name) {
        if (!phone.empty()) {
            m_phones.push_back(phone);
        }
    }

	// Getters
    const std::string& GetName() const { return m_name; }
    const std::vector<std::string>& GetPhones() const { return m_phones; }

    void AddPhone(const std::string& phone);

    void RemovePhone(const std::string& phone);

    void UpdatePhone(const std::string& oldPhone, const std::string& newPhone);

private:
    std::string m_name;
    std::vector<std::string> m_phones;
};
