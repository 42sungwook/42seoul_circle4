#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
  std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
  std::cout << "ClapTrap name constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &obj) {
  std::cout << "ClapTrap copy constructor called" << std::endl;
  *this = obj;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &obj) {
  std::cout << "ClapTrap copy assignment operator called" << std::endl;
  _name = obj._name;
  _hitPoints = obj._hitPoints;
  _energyPoints = obj._energyPoints;
  _attackDamage = obj._attackDamage;
  return *this;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ClapTrap " << _name << " attacks " << target << ", causing "
            << _attackDamage << " points of damage!" << std::endl;
  _energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
  std::cout << "ClapTrap " << _name << " takes " << amount
            << " points of damage!" << std::endl;

  if (_hitPoints - amount < 0)
    _hitPoints = 0;
  else
    _hitPoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ClapTrap " << _name << " is repaired " << amount
            << " points of damage!" << std::endl;
  _hitPoints += amount;
  _energyPoints--;
}
