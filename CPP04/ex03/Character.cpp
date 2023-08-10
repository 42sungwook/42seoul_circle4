#include "Character.hpp"

Character::Character(std::string const& name) : _name(name), _inventory() {}

Character::Character(Character const& object) { *this = object; }

Character::~Character() {
  for (int i = 0; i < _inventory.size(); i++) {
    delete _inventory[i];
  }
}

Character& Character::operator=(Character const& object) {
  if (this != &object) {
    _name = object._name;
    for (int i = 0; i < _inventory.size(); i++) {
      delete _inventory[i];
    }
    _inventory.clear();
    for (int i = 0; i < object._inventory.size(); i++) {
      _inventory.push_back(object._inventory[i]->clone());
    }
  }
  return *this;
}

std::string const& Character::getName() const { return _name; }

void Character::equip(AMateria* m) {
  if (_inventory.size() < 4) {
    _inventory.push_back(m);
  }
}

void Character::unequip(int idx) {
  if (idx >= 0 && idx < _inventory.size()) {
    _inventory.erase(_inventory.begin() + idx);
  }
}

void Character::use(int idx, ICharacter& target) {
  if (idx >= 0 && idx < _inventory.size()) {
    _inventory[idx]->use(target);
  }
}
