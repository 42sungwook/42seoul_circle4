#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) {
  std::cout << "ScavTrap copy constructor called" << std::endl;
  *this = other;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
  std::cout << "ScavTrap copy assignment operator called" << std::endl;
  _name = other._name;
  _hitPoints = other._hitPoints;
  _energyPoints = other._energyPoints;
  _attackDamage = other._attackDamage;
  return *this;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ScavTrap" << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ScavTrap " << _name << " attacks " << target << ", causing "
            << _attackDamage << " points of damage!" << std::endl;
  _energyPoints--;
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << _name << " has entered in Gate keeper mode"
            << std::endl;
}

void ScavTrap::takeDamage(unsigned int amount) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ScavTrap" << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ScavTrap " << _name << " takes " << amount
            << " points of damage!" << std::endl;

  if (_hitPoints - amount < 0)
    _hitPoints = 0;
  else
    _hitPoints -= amount;

  _energyPoints--;
}

void ScavTrap::beRepaired(unsigned int amount) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ScavTrap" << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ScavTrap " << _name << " is repaired " << amount
            << " points of damage!" << std::endl;
  _hitPoints += amount;
  _energyPoints--;
}

std::ostream &operator<<(std::ostream &out, const ScavTrap &scavTrap) {
  out << scavTrap.getName();
  return out;
}
