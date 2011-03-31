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

using namespace CutiesBook;

Directory *Directory::instance = 0;

void
Directory::load(const QString &path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw IOException();
	QTextStream in(&file);
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("CONTACTS") == 0)
			readContacts(in);
		else if (line.compare("LISTS") == 0)
			readLists(in);
		else
			throw MalformedFileException();
	}
}

void
Directory::save(const QString &path)
{
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw IOException();
	QTextStream out(&file);
	writeContacts(out, contacts);
	out << "LISTS\n";
	out << "#: " << lists.size() << "\n";
	for (QSet< List * >::const_iterator i = lists.begin() ; i != lists.end() ; ++i)
	{
		out << "LIST\n";
		out << "N: " << (*i)->getName() << "\n";
		writeContacts(out, (*i)->getContacts());
		out << "END OF LIST\n";
	}
	out << "END OF LISTS\n";
	file.close();
}

void
Directory::writeNumber(QTextStream &out, const Number *number) const
{
	out << "NUMBER\n";
	out << "N: " << number->getNumber();
	out << "T: " << number->getType();
	out << "P: " << number->isProfessionnal();
	out << "END OF NUMBER\n";
}

void
Directory::writeNumbers(QTextStream &out, const QSet< Number *> &numbers) const
{
	out << "NUMBERS\n";
	for (QSet< Number * >::const_iterator i = numbers.begin() ; i != numbers.end() ; ++i)
	{
		writeNumber(out, *i);
	}
	out << "END OF NUMBERS\n";
}

void
Directory::writeDate(QTextStream &out, const QDate &date) const
{
	out << "D: " << date.day();
	out << "M: " << date.month();
	out << "Y: " << date.year();
}

void
Directory::writeContact(QTextStream &out, const Contact *contact) const
{
	out << "CONTACT\n";
	writeNumbers(out, contact->getNumbers());
	out << "A: " << contact->getAddress() << "\n";
	out << "E: " << contact->getEmail() << "\n";
	if (contact->getType() == Contact::COMPANY)
	{
		out << "COMPANY\n";
		const Company *c = static_cast< const Company * >(contact);
		out << "S: " << c->getSiret() << "\n";
		out << "W: " << c->getWebsite() << "\n";
	}
	else
	{
		out << "INDIVIDUAL\n";
		const Individual *i = static_cast< const Individual * >(contact);
		out << "L: " << i->getLastName() << "\n";
		out << "F: " << i->getFirstName() << "\n";
		writeDate(out, i->getBirthday());
	}
	out << "END OF CONTACT\n";
}

void
Directory::writeContacts(QTextStream &out, const QSet< Contact * > &contacts) const
{
	out << "CONTACTS\n";
	out << "#: " << contacts.size() << "\n";
	for (QSet< Contact * >::const_iterator i = contacts.begin() ; i != contacts.end() ; ++i)
	{
		writeContact(out, *i);
	}
	out << "END OF CONTACTS\n";
}

void
Directory::readContact(QTextStream &in)
{
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		throw MalformedFileException();
	}
}

void
Directory::readContacts(QTextStream &in)
{
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("CONTACT") == 0)
			readContact(in);
		else if (line.compare("END OF CONTACT") != 0)
			throw MalformedFileException();
	}
}

void
Directory::readLists(QTextStream &in)
{
	(void) in;
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
