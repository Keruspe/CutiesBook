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

#include "individual.hpp"

using namespace CutiesBook;

Individual::Individual(std::string _lastName, std::string _firstName, std::string _birthday, std::set< Number * > numbers, std::string address, std::string email) :
	Contact(numbers, address, email),
	lastName(_lastName),
	firstName(_firstName),
	birthday(_birthday)
{
}

Individual::~Individual()
{
}