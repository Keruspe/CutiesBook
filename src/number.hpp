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

#ifndef __CUTIESBOOK_NUMBER_HPP__
#define __CUTIESBOOK_NUMBER_HPP__

#include <QObject>

//! The number class
/*!
 * This class will be used to store informations
 * about a phone number (the number itself and it type)
 */
namespace CutiesBook
{
	class Number : public QObject
	{
	public:
		//! Enum to store the phone type
		enum phoneType {
			FIXE,
			MOBILE,
			FAX
		};

		//! Set this number as professionnal
		void setProfessional() { professionnal = true; }
		//! Set this number as personnal
		void setPersonnal() { professionnal = false; }

		//! Is this number professionnal ?
		bool isProfessionnal() { return professionnal; }
		//! Is this number personnal ?
		bool isPersonnal() { return !professionnal; }

		//! Get the number
		std::string &getNumber() { return number; }
		//! Get the type of this phone number
		phoneType getType() { return type; }

		//! Set the number
		void setNumber(std::string &number) { this->number = number; }
		//! Set the type of this phone number
		void setType(phoneType type) { this->type = type; }

		Number(std::string &number, Number::phoneType type, bool professional = false);
		virtual ~Number();
	private:
		std::string number; // Can contain signs like "+"
		phoneType type;
		bool professionnal; // false for personnal
	};
}

#endif /* __CUTIESBOOK_NUMBER_HPP__ */
