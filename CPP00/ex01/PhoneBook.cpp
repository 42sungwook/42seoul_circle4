#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// ANSI escape sequences for console color formatting
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_TEXT "\033[0m"

class Contact {
public:
    Contact() {}
    Contact(const std::string& firstName, const std::string& lastName, const std::string& nickname,
            const std::string& phoneNumber, const std::string& darkestSecret)
        : firstName(firstName), lastName(lastName), nickname(nickname),
          phoneNumber(phoneNumber), darkestSecret(darkestSecret) {}

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getNickname() const { return nickname; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getDarkestSecret() const { return darkestSecret; }

private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;
};

class PhoneBook {
public:
    PhoneBook() : contactCount(0) {}

    void addContact(const Contact& contact) {
        if (contactCount >= MAX_CONTACTS) {
            // Replace the oldest contact by shifting all contacts
            for (int i = 0; i < MAX_CONTACTS - 1; ++i) {
                contacts[i] = contacts[i + 1];
            }
            contactCount = MAX_CONTACTS - 1;
        }
        contacts[contactCount] = contact;
        ++contactCount;
    }

	void displayContacts() const {
		std::cout << std::setw(10) << "Index" << "|"
				<< std::setw(10) << "First Name" << "|"
				<< std::setw(10) << "Last Name" << "|"
				<< std::setw(10) << "Nickname" << std::endl;

		for (int i = 0; i < contactCount; ++i) {
			std::cout << std::setw(10) << (i + 1) << "|"
					<< std::setw(10) << truncateText(contacts[i].getFirstName()) << "|"
					<< std::setw(10) << truncateText(contacts[i].getLastName()) << "|"
					<< std::setw(10) << truncateText(contacts[i].getNickname()) << std::endl;
		}
	}

    void searchContact(int index) const {
        if (index >= 0 && index < contactCount) {
            std::cout << "First Name: " << contacts[index].getFirstName() << std::endl;
            std::cout << "Last Name: " << contacts[index].getLastName() << std::endl;
            std::cout << "Nickname: " << contacts[index].getNickname() << std::endl;
            std::cout << "Phone Number: " << contacts[index].getPhoneNumber() << std::endl;
            std::cout << "Darkest Secret: " << contacts[index].getDarkestSecret() << std::endl;
        } else {
            std::cout << "Invalid contact index." << std::endl;
        }
    }

private:
    static const int MAX_CONTACTS = 8;
    Contact contacts[MAX_CONTACTS];
    int contactCount;

    std::string truncateText(const std::string& text) const {
        std::string truncatedText = text;
        if (truncatedText.length() > 10) {
            truncatedText.resize(9);
            truncatedText += ".";
        }
        return truncatedText;
    }
};

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (true) {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";

        // Check for end of input stream
        if (!std::getline(std::cin, command)) {
            break;  // Exit the loop if end of input is reached or input is empty
        }
        if (command == "ADD") {
            std::string firstName, lastName, nickname, phoneNumber, darkestSecret;
            std::cout << BLUE_TEXT << "Enter First Name: " << RESET_TEXT;
            if (!std::getline(std::cin, firstName)) {
                break;  // Exit the loop if end of input is reached
            }
            std::cout << BLUE_TEXT << "Enter Last Name: " << RESET_TEXT;
            if (!std::getline(std::cin, lastName)) {
                break;  // Exit the loop if end of input is reached
            }
            std::cout << BLUE_TEXT << "Enter Nickname: " << RESET_TEXT;
            if (!std::getline(std::cin, nickname)) {
                break;  // Exit the loop if end of input is reached
            }
            std::cout << BLUE_TEXT << "Enter Phone Number: " << RESET_TEXT;
            if (!std::getline(std::cin, phoneNumber)) {
                break;  // Exit the loop if end of input is reached
            }
            std::cout << BLUE_TEXT << "Enter Darkest Secret: " << RESET_TEXT;
            if (!std::getline(std::cin, darkestSecret)) {
                break;  // Exit the loop if end of input is reached
            }

            Contact newContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
            phoneBook.addContact(newContact);
        } else if (command == "SEARCH") {
            phoneBook.displayContacts();

            int index;
            std::cout << BLUE_TEXT << "Enter the index of the contact to display: " << RESET_TEXT;
            if (!(std::cin >> index)) {
                std::cout << RED_TEXT << "Invalid index." << RESET_TEXT << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            phoneBook.searchContact(index);
        } else if (command == "EXIT") {
            break;
        } else {
			if (!command.empty())
				std::cout << RED_TEXT << "Invalid command." << RESET_TEXT << std::endl;
            continue;
        }
    }
    return 0;
}
