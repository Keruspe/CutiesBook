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

#include "directory.hpp"

using namespace CutiesBook;

Directory *Directory::instance = 0;

void
Directory::loadContacts(std::string path)
{
	(void) path;
	/* TODO: */
}

void
Directory::saveContacts(std::string path)
{
	(void) path;
	/* TODO: */
}

void
Directory::addContact(Contact *contact)
{
	contacts.insert(contact);
}

void
Directory::deleteContact(Contact *contact)
{
	contacts.erase(contact);
}

Directory::Directory() :
	QObject()
{
}

Directory::~Directory()
{
	for (std::set< Contact * >::iterator i = contacts.begin() ; i != contacts.end() ; ++i)
	{
		delete *i;
	}
}
