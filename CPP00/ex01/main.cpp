#include "PhoneBook.hpp"

std::string getInput(const std::string& message, const std::string& errorMessage) {
    std::string input;
		
    std::cout << BLUE_TEXT << message << RESET_TEXT;
    if (!std::getline(std::cin, input) || input.empty()) {
        std::cout << RED_TEXT << errorMessage << RESET_TEXT << std::endl;
        return "";
    }
    return input;
}

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (true) {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";

        if (!std::getline(std::cin, command)) {
            std::cout << "EXIT" << std::endl;
            break;
        }

        if (command == "ADD") {
            std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

            firstName = getInput("Enter First Name: ", "First Name cannot be empty.");
            if (firstName.empty()) continue;

            lastName = getInput("Enter Last Name: ", "Last Name cannot be empty.");
            if (lastName.empty()) continue;

            nickname = getInput("Enter Nickname: ", "Nickname cannot be empty.");
            if (nickname.empty()) continue;

            phoneNumber = getInput("Enter Phone Number: ", "Phone Number cannot be empty.");
            if (phoneNumber.empty()) continue;

            darkestSecret = getInput("Enter Darkest Secret: ", "Darkest Secret cannot be empty.");
            if (darkestSecret.empty()) continue;

            Contact newContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
            phoneBook.addContact(newContact);
        }
				else if (command == "SEARCH") {
						phoneBook.displayContacts();

						std::string indexStr;
						int index;

						std::cout << BLUE_TEXT << "Enter the index of the contact to display: " << RESET_TEXT;
						if (!std::getline(std::cin, indexStr)) {
								std::cout << RED_TEXT << "Invalid index." << RESET_TEXT << std::endl;
								continue;
						}
						try {
								index = std::stoi(indexStr);
						} catch (const std::invalid_argument&) {
								std::cout << RED_TEXT << "Invalid index." << RESET_TEXT << std::endl;
								continue;
						}
						phoneBook.searchContact(index - 1);
				}
        else if (command == "EXIT") {
            break;
        }
        else {
            if (!command.empty())
                std::cout << RED_TEXT << "Invalid command." << RESET_TEXT << std::endl;
        }
    }

    return 0;
}
