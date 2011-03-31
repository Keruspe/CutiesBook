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

#include <QDate>

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
		const QString &getLastName() const { return lastName; }
		//! Get the Individual firstName
		const QString &getFirstName() const { return firstName; }
		//! Get the Individual birthday
		const QDate &getBirthday() const { return birthday; }

		//! Set the Individual lastName
		void setLastName(QString &lastName) { this->lastName = lastName; }
		//! Set the Individual firstName
		void setFirstName(QString &firstName) { this->firstName = firstName; }
		//! Set the Individual birthday
		void setBirthday(QDate &birthday) { this->birthday = birthday; }

		Individual(QString lastName, QString firstName, QDate birthday, QString address = "", QString email = "");
		virtual ~Individual();

		ContactType getType() const { return INDIVIDUAL; }
	private:
		QString lastName;
		QString firstName;
		QDate birthday;
	};
}

#endif /* __CUTIESBOOK_INDIVIDUAL_HPP__ */
