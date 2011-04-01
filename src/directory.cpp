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

#include <QFile>
#include <QSize>

#include <cstdlib>

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
		{
			QSet< Contact * > *tmp = readContacts(in);
			for (QSet< Contact * >::iterator i = tmp->begin() ; i != tmp->end() ; ++i)
			{
				contacts.insert(*i);
			}
			delete tmp;
		}
		else if (line.compare("LISTS") == 0)
		{
			QSet< List * > *tmp = readLists(in);
			for (QSet< List * >::iterator i = tmp->begin() ; i != tmp->end() ; ++i)
			{
				lists.insert(*i);
			}
			delete tmp;
		}
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
	writeLists(out, lists);
	file.close();
}

void
Directory::writeNumber(QTextStream &out, const Number *number) const
{
	out << "NUMBER\n";
	out << "N: " << number->getNumber() << "\n";
	out << "T: " << number->getType() << "\n";
	out << "P: " << number->isProfessionnal() << "\n";
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
	out << "DATE\n";
	out << "D: " << date.day() << "\n";
	out << "M: " << date.month() << "\n";
	out << "Y: " << date.year() << "\n";
	out << "END OF DATE\n";
}

void
Directory::writeCompany(QTextStream &out, const Company *company) const
{
	out << "COMPANY\n";
	out << "S: " << company->getSiret() << "\n";
	out << "W: " << company->getWebsite() << "\n";
}

void
Directory::writeIndividual(QTextStream &out, const Individual *individual) const
{
	out << "INDIVIDUAL\n";
	out << "L: " << individual->getLastName() << "\n";
	out << "F: " << individual->getFirstName() << "\n";
	writeDate(out, individual->getBirthday());
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
		writeCompany(out, static_cast< const Company * >(contact));
	}
	else
	{
		writeIndividual(out, static_cast< const Individual * >(contact));
	}
	out << "END OF CONTACT\n";
}

void
Directory::writeContacts(QTextStream &out, const QSet< Contact * > &contacts) const
{
	out << "CONTACTS\n";
	for (QSet< Contact * >::const_iterator i = contacts.begin() ; i != contacts.end() ; ++i)
	{
		writeContact(out, *i);
	}
	out << "END OF CONTACTS\n";
}

void
Directory::writeList(QTextStream &out, const List *list) const
{
	out << "LIST\n";
	out << "N: " << list->getName() << "\n";
	writeContacts(out, list->getContacts());
	out << "END OF LIST\n";
}

void
Directory::writeLists(QTextStream &out, const QSet< List * > &lists) const
{
	out << "LISTS\n";
	for (QSet< List * >::const_iterator i = lists.begin() ; i != lists.end() ; ++i)
	{
		writeList(out, *i);
	}
	out << "END OF LISTS\n";
}

Number *
Directory::readNumber(QTextStream &in) const
{
	QString line;
	Number::PhoneType type;
	QString number;
	bool professionnal;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("END OF NUMBER") == 0)
			break;
		else
		{
			const char *str = line.toAscii().constData();
			switch (str[0])
			{
			case 'N':
				number = line.mid(3);
				break;
			case 'T':
				type = static_cast<Number::PhoneType>(atoi(str + 3));
				break;
			case 'P':
				professionnal = atoi(str + 3);
				break;
			default:
				throw MalformedFileException();
			}
		}
	}
	return new Number(number, type, professionnal);
}

QSet< Number * > *
Directory::readNumbers(QTextStream &in) const
{
	QSet< Number * > *numbers = new QSet< Number * >();
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("NUMBER") == 0)
			numbers->insert(readNumber(in));
		else if (line.compare("END OF NUMBERS") == 0)
			break;
		else
			throw MalformedFileException();
	}
	return numbers;
}

QDate
Directory::readDate(QTextStream &in) const
{
	QString line;
	int day;
	int month;
	int year;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("END OF DATE") == 0)
			break;
		else
		{
			const char *str = line.toAscii().constData();
			switch (str[0])
			{
			case 'D':
				day = atoi(str + 3);
				break;
			case 'M':
				month = atoi(str + 3);
				break;
			case 'Y':
				year = atoi(str + 3);
				break;
			default:
				throw MalformedFileException();
			}
		}
	}
	return QDate(year, month, day);
}

Company *
Directory::readCompany(QTextStream &in, QString address, QString email) const
{
	QString line;
	int siret;
	QString website;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("END OF CONTACT") == 0)
			break;
		else
		{
			const char *str = line.toAscii().constData();
			switch (str[0])
			{
			case 'W':
				website = line.mid(3);
				break;
			case 'S':
				siret = atoi(str + 3);
				break;
			default:
				throw MalformedFileException();
			}
		}
	}
	Company *company = new Company(siret, website, address, email);
	return company;
}

Individual *
Directory::readIndividual(QTextStream &in, QString address, QString email) const
{
	QString line;
	QString lastName, firstName;
	QDate birthday;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("DATE") == 0)
			birthday = readDate(in);
		else if (line.compare("END OF CONTACT") == 0)
			break;
		else
		{
			switch (line.at(0).toAscii())
			{
			case 'L':
				lastName = line.mid(3);
				break;
			case 'F':
				firstName = line.mid(3);
				break;
			default:
				throw MalformedFileException();
			}
		}
	}
	Individual *individual = new Individual(lastName, firstName, birthday, address, email);
	return individual;
}

Contact *
Directory::readContact(QTextStream &in) const
{
	Contact::ContactType type = Contact::NONE;
	QString line;
	QSet< Number * > *numbers = 0;
	QString address, email;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("INDIVIDUAL") == 0)
		{
			type = Contact::INDIVIDUAL;
			break;
		}
		else if (line.compare("COMPANY") == 0)
		{
			type = Contact::COMPANY;
			break;
		}
		else if (line.compare("NUMBERS") == 0)
			numbers = readNumbers(in);
		else if (line.compare("END OF CONTACT") == 0)
			break;
		else
		{
			switch (line.at(0).toAscii())
			{
			case 'A':
				address = line.mid(3);
				break;
			case 'E':
				email = line.mid(3);
				break;
			default:
				throw MalformedFileException();
			}
		}
	}
	Contact *contact;
	if (type == Contact::COMPANY)
		contact = readCompany(in, address, email);
	else if (type == Contact::INDIVIDUAL)
		contact = readIndividual(in, address, email);
	else
		throw MalformedFileException();
	if (numbers)
	{
		for (QSet< Number * >::iterator i = numbers->begin() ; i != numbers->end() ; ++i)
		{
			contact->addNumber(*i);
		}
		delete numbers;
	}
	return contact;
}

QSet< Contact * > *
Directory::readContacts(QTextStream &in) const
{
	QSet< Contact * > *contacts = new QSet< Contact * >();
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("CONTACT") == 0)
			contacts->insert(readContact(in));
		else if (line.compare("END OF CONTACTS") == 0)
			break;
		else
			throw MalformedFileException();
	}
	return contacts;
}

List *
Directory::readList(QTextStream &in) const
{
	QString line;
	QString name;
	QSet< Contact * > *tmp = 0;

	while (!(line = in.readLine()).isNull())
	{
		if (line.at(0).toAscii() == 'N')
		{
			name = QString(line.toAscii().constData() + 3);
		}
		else if (line.compare("CONTACTS") == 0)
		{
			tmp = readContacts(in);
		}
		else if (line.compare("END OF LIST") == 0)
			break;
		else
			throw MalformedFileException();
	}

	List *list = new List(name);
	if (tmp)
	{
		for (QSet< Contact * >::iterator i = tmp->begin() ; i != tmp->end() ; ++i)
		{
			list->addContact(*i);
		}
		delete tmp;
	}
	return list;
}

QSet< List * > *
Directory::readLists(QTextStream &in) const
{
	QSet< List * > *lists = new QSet< List * >();
	QString line;
	while (!(line = in.readLine()).isNull())
	{
		if (line.compare("LIST") == 0)
			lists->insert(readList(in));
		else if (line.compare("END OF LISTS") == 0)
			break;
		else
			throw MalformedFileException();
	}
	return lists;
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

int
Directory::rowCount(const QModelIndex &) const
{
	return contacts.size();
}

int
Directory::columnCount(const QModelIndex &) const
{
	return COLUMNS_COUNT;
}

QVariant
Directory::data(const QModelIndex &index, int role) const
{
	if ( ( ! index.isValid() ) || ( role != Qt::DisplayRole ) )
		return QVariant();
	Contact *contact = contacts.toList().at(index.row());
	Individual *individual = 0;
	Company *company = 0;
	switch ( contact->getType() )
	{
		case Contact::INDIVIDUAL:
			individual = (Individual *)contact;
		break;
		case Contact::COMPANY:
			company = (Company *)contact;
		break;
		case Contact::NONE:
		break;
	}
	QString na("N/A");
	switch ( index.column() )
	{
		/* Individual */
		case FIRSTNAME:
			if ( !individual )
				return na;
			return individual->getFirstName();
		case LASTNAME:
			if ( !individual )
				return na;
			return individual->getLastName();
		case DATE:
			if ( !individual )
				return na;
			return individual->getBirthday();
		/* Company */
		case SIRET:
			if ( !company )
				return na;
			return company->getSiret();
		case WEBSITE:
			if ( !company )
				return na;
			return company->getWebsite();
		/* Common */
		case NUMBERS:
			return contact->getNumbersString();
		case ADDRESS:
			return contact->getAddress();
		case EMAIL:
			return contact->getEmail();
	}
	return QVariant();
}

QVariant
Directory::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch ( role )
	{
		case Qt::DisplayRole:
			if ( orientation == Qt::Horizontal )
			{
				switch ( section )
				{
					/* Individual */
					case FIRSTNAME:
						return QString("First Name");
					case LASTNAME:
						return QString("Last Name");
					case DATE:
						return QString("Birthday");
					/* Company */
					case SIRET:
						return QString("SIRET");
					return QVariant();
					case WEBSITE:
						return QString("Web Site");
					/* Common */
					case NUMBERS:
						return QString("Numbers");
					case ADDRESS:
						return QString("Address");
					case EMAIL:
						return QString("E-Mail");
				}
			}
		case Qt::SizeHintRole:
			if ( orientation == Qt::Vertical )
				return QSize(0, 0); // There is probably a better way to do …
		default:
		return QVariant();
	}
}

Directory::Directory() :
	QAbstractTableModel()
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
