#include "Contact.h"

void Contact::AddPhone(const std::string& phone)
{
    if (!phone.empty() && std::find(m_phones.begin(), m_phones.end(), phone) == m_phones.end()) {
        m_phones.push_back(phone);
    }
}

void Contact::RemovePhone(const std::string& phone)
{
    auto it = std::find(m_phones.begin(), m_phones.end(), phone);
    if (it != m_phones.end()) {
        m_phones.erase(it);
    }
}

void Contact::UpdatePhone(const std::string& oldPhone, const std::string& newPhone)
{
    RemovePhone(oldPhone);
    AddPhone(newPhone);
}
