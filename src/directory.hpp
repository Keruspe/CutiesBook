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

#include "company.hpp"
#include "individual.hpp"
#include "list.hpp"

#include <QAbstractTableModel>
#include <QTextStream>

//! The directory class
/*!
 * This class will be used to store all the contacts
 */
namespace CutiesBook
{
	class IOException {};
	class MalformedFileException {};

	class Directory : public QAbstractTableModel
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
		const QList< Contact * > &getContacts() const { return contacts; }

		//! Add a contact
		void addContact(Contact *contact);

		//! Delete a contact
		void deleteContact(Contact *contact);

		//! Get the lists
		const QList< List * > &getLists() const { return lists; }

		//! Add a list
		void addList(List *list);

		//! Delete a list
		void deleteList(List *list);


		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;
		void sort(int column, Qt::SortOrder order);

	private:
		enum {
			FIRSTNAME = 0,
			LASTNAME,
			DATE,
			SIRET,
			WEBSITE,
			NUMBERS,
			ADDRESS,
			EMAIL,
			COLUMNS_COUNT
		} Columns;

		static Directory *instance;
		QList< Contact * > contacts;
		QList< List * > lists;

		void writeNumber(QTextStream &out, const Number *number) const;
		void writeNumbers(QTextStream &out, const QSet< Number *> &numbers) const;
		void writeDate(QTextStream &out, const QDate &date) const;
		void writeCompany(QTextStream &out, const Company *company) const;
		void writeIndividual(QTextStream &out, const Individual *individual) const;
		void writeContact(QTextStream &out, const Contact *contact) const;
		void writeContacts(QTextStream &out, const QList< Contact * > &contacts) const;
		void writeList(QTextStream &out, const List *list) const;
		void writeLists(QTextStream &out, const QList< List * > &lists) const;

		Number *readNumber(QTextStream &in) const;
		QSet< Number * > *readNumbers(QTextStream &in) const;
		QDate readDate(QTextStream &in) const;
		Company *readCompany(QTextStream &in, QString address, QString email) const;
		Individual *readIndividual(QTextStream &in, QString address, QString email) const;
		Contact *readContact(QTextStream &in) const;
		QList< Contact * > *readContacts(QTextStream &in) const;
		List *readList(QTextStream &in) const;
		QList< List * > *readLists(QTextStream &in) const;

		Directory();
		virtual ~Directory();
	};
}

#endif /* __CUTIESBOOK_DIRECTORY_HPP__ */
