#include "PhoneBook.hpp"

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
            std::cout << BLUE_TEXT << "Enter First Name: " << RESET_TEXT;
            if (!std::getline(std::cin, firstName) || firstName.empty()) {
                std::cout << RED_TEXT << "First Name cannot be empty." << RESET_TEXT << std::endl;
                continue;
            }
            std::cout << BLUE_TEXT << "Enter Last Name: " << RESET_TEXT;
            if (!std::getline(std::cin, lastName) || lastName.empty()) {
                std::cout << RED_TEXT << "Last Name cannot be empty." << RESET_TEXT << std::endl;
                continue;
            }
            std::cout << BLUE_TEXT << "Enter Nickname: " << RESET_TEXT;
            if (!std::getline(std::cin, nickname) || nickname.empty()) {
                std::cout << RED_TEXT << "Nickname cannot be empty." << RESET_TEXT << std::endl;
                continue;
            }
            std::cout << BLUE_TEXT << "Enter Phone Number: " << RESET_TEXT;
            if (!std::getline(std::cin, phoneNumber) || phoneNumber.empty()) {
                std::cout << RED_TEXT << "Phone Number cannot be empty." << RESET_TEXT << std::endl;
                continue;
            }
            std::cout << BLUE_TEXT << "Enter Darkest Secret: " << RESET_TEXT;
            if (!std::getline(std::cin, darkestSecret) || darkestSecret.empty()) {
                std::cout << RED_TEXT << "Darkest Secret cannot be empty." << RESET_TEXT << std::endl;
                continue;
            }
            Contact newContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
            phoneBook.addContact(newContact);
        }
        else if (command == "SEARCH") {
            phoneBook.displayContacts();

            int index;
            std::cout << BLUE_TEXT << "Enter the index of the contact to display: " << RESET_TEXT;
            if (!(std::cin >> index)) {
								if (std::cin.eof()) {
									std::cout << "EXIT" << std::endl;
									break;
								}
                std::cout << RED_TEXT << "Invalid index." << RESET_TEXT << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
