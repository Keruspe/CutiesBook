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

#ifndef __CUTIESBOOK_LIST_HPP__
#define __CUTIESBOOK_LIST_HPP__

#include "contact.hpp"

//! The list class
/*!
 * This class will be used to store a list of contacts
 */
namespace CutiesBook
{
	class List : public QObject
	{
	public:
		//! Get the contacts list
		const QSet< Contact * > &getContacts() const { return contacts; }

		//! Add a contact
		void addContact(Contact *contact);

		//! Delete a contact
		void deleteContact(Contact *contact);

		//! Set the list name
		void setName(QString &name) { this->name = name; }
		void setName(const char *name) { this->name = QString(name); }

		//! Get the list name
		const QString &getName() const { return name; }

		List(QString &name);
		List();
		virtual ~List();

	private:
		QString name;
		QSet< Contact * > contacts;
	};
}

#endif /* __CUTIESBOOK_LIST_HPP__ */
