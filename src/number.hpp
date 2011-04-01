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

#ifndef __CUTIESBOOK_NUMBER_HPP__
#define __CUTIESBOOK_NUMBER_HPP__

#include <QObject>
#include <QString>
#include <QAbstractItemDelegate>

//! The number class
/*!
 * This class will be used to store informations
 * about a phone number (the number itself and it type)
 */
namespace CutiesBook
{
	class Number : public QObject
	{
	public:
		//! Enum to store the phone type
		enum PhoneType
		{
			FIXE,
			MOBILE,
			FAX
		};

		//! Set this number as professionnal
		void setProfessional() { professionnal = true; }
		//! Set this number as personnal
		void setPersonnal() { professionnal = false; }

		//! Is this number professionnal ?
		bool isProfessionnal() const { return professionnal; }
		//! Is this number personnal ?
		bool isPersonnal() const { return !professionnal; }

		//! Get the number
		const QString &getNumber() const { return number; }
		//! Get the type of this phone number
		PhoneType getType() const { return type; }

		//! Set the number
		void setNumber(QString &number) { this->number = number; }
		//! Set the type of this phone number
		void setType(PhoneType type) { this->type = type; }

		//! Get the number as \a QString
		QString toString() const;

		Number(QString number, PhoneType type, bool professional = false);
		virtual ~Number();
	private:
		QString number; // Can contain signs like "+"
		PhoneType type;
		bool professionnal; // false for personnal
	};
}

#endif /* __CUTIESBOOK_NUMBER_HPP__ */
