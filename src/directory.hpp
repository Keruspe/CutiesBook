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

#ifndef __CUTIESBOOK_DIRECTORY_HPP__
#define __CUTIESBOOK_DIRECTORY_HPP__

#include "list.hpp"

#include <QTextStream>

//! The directory class
/*!
 * This class will be used to store all the contacts
 */
namespace CutiesBook
{
	class IOException {};

	class Directory : public QObject
	{
	public:
		//! Instance getter
		static Directory *getInstance()
		{
			if ( ! Directory::instance )
				Directory::instance = new Directory();
			return Directory::instance;
		}

		//! Clean the instance
		static void cleanInstance()
		{
			if ( Directory::instance )
				delete Directory::instance;
		}

		//! Load contacts ans lists from disk
		void load(const QString &path);

		//! Save contacts and lists to disk
		void save(const QString &path);

		//! Get the contacts list
		const QSet< Contact * > &getContacts() const { return contacts; }

		//! Add a contact
		void addContact(Contact *contact);

		//! Delete a contact
		void deleteContact(Contact *contact);

		//! Get the lists
		const QSet< List * > &getLists() const { return lists; }

		//! Add a list
		void addList(List *list);

		//! Delete a list
		void deleteList(List *list);

	private:
		static Directory *instance;
		QSet< Contact * > contacts;
		QSet< List * > lists;

		void writeContact(QTextStream &out, const Contact *contact) const;
		void writeContacts(QTextStream &out, const QSet< Contact * > &contacts) const;

		Directory();
		virtual ~Directory();
	};
}

#endif /* __CUTIESBOOK_DIRECTORY_HPP__ */
