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

#ifndef __CUTIESBOOK_CONTACT_HPP__
#define __CUTIESBOOK_CONTACT_HPP__

#include "number.hpp"

#include <QSet>

//! The contact class
/*!
 * This class will be used to store informations
 * about the contacts
 */
namespace CutiesBook
{
	class Contact : public QObject
	{
	public:
		//! Add a number to the contact
		void addNumber(Number *number);
		//! Delete a number from the contact
		void deleteNumber(Number *number);

		//! Get the contact address
		QString &getAddress() { return address; }
		//! Get the contact email
		QString &getEmail() { return email; }

		//! Set the contact address
		void setAddress(QString &address) { this->address = address; }
		//! Set the contact email
		void setEmail(QString &email) { this->email = email; }

		Contact(QSet< Number * > &numbers, QString &address, QString &email);
		virtual ~Contact();
	private:
		QSet< Number * > numbers;
		QString address;
		QString email;
		virtual void makeMeAbstractPlease() = 0;
	};
}

#endif /* __CUTIESBOOK_CONTACT_HPP__ */
