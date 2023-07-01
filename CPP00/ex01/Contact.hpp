#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    Contact() {}
    Contact(const std::string& firstName, \
						const std::string& lastName, \
						const std::string& nickname, \
						const std::string& phoneNumber, \
						const std::string& darkestSecret): \
						firstName(firstName), \
						lastName(lastName), \
						nickname(nickname), \
						phoneNumber(phoneNumber), \
						darkestSecret(darkestSecret) {}

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getNickname() const { return nickname; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getDarkestSecret() const { return darkestSecret; }
};

#endif