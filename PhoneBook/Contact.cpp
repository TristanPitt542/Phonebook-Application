#include "Contact.h"

void Contact::addPhone(const std::string& phone)
{
    if (!phone.empty() && std::find(m_phones.begin(), m_phones.end(), phone) == m_phones.end()) {
        m_phones.push_back(phone);
    }
}

void Contact::removePhone(const std::string& phone)
{
    auto it = std::find(m_phones.begin(), m_phones.end(), phone);
    if (it != m_phones.end()) {
        m_phones.erase(it);
    }
}

void Contact::updatePhone(const std::string& oldPhone, const std::string& newPhone)
{
    removePhone(oldPhone);
    addPhone(newPhone);
}
