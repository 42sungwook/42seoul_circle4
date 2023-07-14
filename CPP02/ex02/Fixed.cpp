#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int value)
{
	_value = value << _bits;
}

Fixed::Fixed(const float value)
{
	_value = (int)roundf(value * (1 << _bits));
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

int Fixed::getRawBits(void) const
{
	return _value;
}

void Fixed::setRawBits(int const raw)
{
	_value = raw;
}

Fixed &Fixed::operator=(const Fixed &object)
{
	_value = object.getRawBits();
	return *this;
}

Fixed::~Fixed() {}

float Fixed::toFloat(void) const
{
	return (float)_value / (1 << _bits);
}

int Fixed::toInt(void) const
{
	return _value >> _bits;
}

std::ostream &operator<<(std::ostream &os, const Fixed &object)
{
	os << object.toFloat();
	return os;
}

Fixed Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

bool Fixed::operator<(const Fixed &object) const
{
	return _value < object.getRawBits();
}

bool Fixed::operator>(const Fixed &object) const
{
	return _value > object.getRawBits();
}

bool Fixed::operator<=(const Fixed &object) const
{
	return _value <= object.getRawBits();
}

bool Fixed::operator>=(const Fixed &object) const
{
	return _value >= object.getRawBits();
}

bool Fixed::operator==(const Fixed &object) const
{
	return _value == object.getRawBits();
}

bool Fixed::operator!=(const Fixed &object) const
{
	return _value != object.getRawBits();
}

Fixed Fixed::operator+(const Fixed &object) const
{
	return Fixed(toFloat() + object.toFloat());
}

Fixed Fixed::operator-(const Fixed &object) const
{
	return Fixed(toFloat() - object.toFloat());
}

Fixed Fixed::operator*(const Fixed &object) const
{
	return Fixed(toFloat() * object.toFloat());
}

Fixed Fixed::operator/(const Fixed &object) const
{
	return Fixed(toFloat() / object.toFloat());
}

Fixed &Fixed::operator++(void)
{
	_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	operator++();
	return tmp;
}

Fixed &Fixed::operator--(void)
{
	_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	operator--();
	return tmp;
}
