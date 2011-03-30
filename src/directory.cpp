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

#include "company.hpp"
#include "directory.hpp"
#include "individual.hpp"

#include <QFile>
#include <QTextStream>

#include <iostream>

using namespace CutiesBook;

Directory *Directory::instance = 0;

void
Directory::load(const QString &path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw IOException();
	QTextStream in(&file);
}

void
Directory::save(const QString &path)
{
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw IOException();
	QTextStream out(&file);
	out << "CONTACTS\n";
	out << "#: " << contacts.size() << "\n";
	for (QSet< Contact * >::const_iterator i = contacts.begin() ; i != contacts.end() ; ++i)
	{
		out << "CONTACT\n";
		out << "NUMBERS\n";
		out << "#: " << (*i)->getNumbers().size() << "\n";
		for (QSet< Number * >::const_iterator j = (*i)->getNumbers().begin() ; j != (*i)->getNumbers().end() ; ++j)
		{
			out << "NUMBER\n";
			out << "N: " << (*j)->getNumber();
			out << "T: " << (*j)->getType();
			out << "P: " << (*j)->isProfessionnal();
			out << "END OF NUMBER\n";
		}
		out << "END OF NUMBERS\n";
		out << "A: " << (*i)->getAddress() << "\n";
		out << "E: " << (*i)->getEmail() << "\n";
		if ((*i)->getType() == Contact::COMPANY)
		{
			out << "COMPANY\n";
			Company *c = static_cast< Company * >(*i);
			out << "S: " << c->getSiret() << "\n";
			out << "W: " << c->getWebsite() << "\n";
		}
		else
		{
			out << "INDIVIDUAL\n";
			Individual *in = static_cast< Individual * >(*i);
			out << "L: " << in->getLastName() << "\n";
			out << "F: " << in->getFirstName() << "\n";
			const QDate &date = in->getBirthday();
			out << "D: " << date.day();
			out << "M: " << date.month();
			out << "Y: " << date.year();
		}
		out << "END OF CONTACT\n";
	}
	out << "END OF CONTACTS\n";
	out << "LISTS\n";
	out << "#: " << lists.size() << "\n";
	out << "END OF LISTS\n";
	file.close();
}

void
Directory::addContact(Contact *contact)
{
	contacts.insert(contact);
}

void
Directory::deleteContact(Contact *contact)
{
	contacts.remove(contact);
	for (QSet< List * >::iterator i = lists.begin() ; i != lists.end() ; ++i)
	{
		(*i)->deleteContact(contact);
	}
	delete contact;
}

void
Directory::addList(List *list)
{
	lists.insert(list);
}

void
Directory::deleteList(List *list)
{
	lists.remove(list);
	delete list;
}

Directory::Directory() :
	QObject()
{
}

Directory::~Directory()
{
	for (QSet< Contact * >::iterator i = contacts.begin() ; i != contacts.end() ; ++i)
	{
		delete *i;
	}
	for (QSet< List * >::iterator i = lists.begin() ; i != lists.end() ; ++i)
	{
		delete *i;
	}
}
