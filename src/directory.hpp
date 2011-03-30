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

//! The directory class
/*!
 * This class will be used to store all the contacts
 */
namespace CutiesBook
{
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
		void load(QString &path);

		//! Save contacts and lists to disk
		void save(QString &path);

		//! Get the contacts list
		QSet< Contact * > &getContacts() { return contacts; }

		//! Add a contact
		void addContact(Contact *contact);

		//! Delete a contact
		void deleteContact(Contact *contact);

		//! Get the lists
		QSet< List * > &getLists() { return lists; }

		//! Add a list
		void addList(List *list);

		//! Delete a list
		void deleteList(List *list);

	private:
		static Directory *instance;
		QSet< Contact * > contacts;
		QSet< List * > lists;

		Directory();
		virtual ~Directory();
	};
}

#endif /* __CUTIESBOOK_DIRECTORY_HPP__ */
