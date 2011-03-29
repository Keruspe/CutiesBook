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

#ifndef __CUTIESBOOK_INDIVIDUAL_HPP__
#define __CUTIESBOOK_INDIVIDUAL_HPP__

#include "contact.hpp"

//! The individual class
/*!
 * This class will be used to store informations
 * about the contacts of type Individual
 */
namespace CutiesBook
{
	class Individual : public Contact
	{
	public:
		//! Get the Individual lastName
		std::string getLastName() { return lastName; }
		//! Get the Individual firstName
		std::string getFirstName() { return firstName; }
		//! Get the Individual birthday
		std::string getBirthday() { return lastName; }

		//! Set the Individual lastName
		void setLastName(std::string lastName) { this->lastName = lastName; }
		//! Set the Individual firstName
		void setFirstName(std::string firstName) { this->firstName = firstName; }
		//! Set the Individual birthday
		void setBirthday(std::string birthday) { this->birthday = birthday; }

		Individual(std::string lastName, std::string firstName, std::string birthday, std::set< Number * > numbers, std::string address = "", std::string email = "");
		virtual ~Individual();
	private:
		std::string lastName;
		std::string firstName;
		std::string birthday; /* TODO: date */
		void makeMeAbstractPlease() {}
	};
}

#endif /* __CUTIESBOOK_INDIVIDUAL_HPP__ */
