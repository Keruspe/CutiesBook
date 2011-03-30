/*
 * CutiesBook - Get a trace of passed dates
 *
 * Copyright © 2011 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "contact.hpp"

using namespace CutiesBook;

void
Contact::addNumber(Number *number)
{
	numbers.insert(number);
}

void
Contact::deleteNumber(Number *number)
{
	numbers.erase(number);
	delete number;
}

Contact::Contact(std::set< Number * > &_numbers, std::string &_address, std::string &_email) :
	QObject(),
	numbers(_numbers),
	address(_address),
	email(_email)
{
}

Contact::~Contact()
{
	for (std::set< Number * >::iterator i = numbers.begin() ; i != numbers.end() ; ++i)
	{
		delete *i;
	}
}
