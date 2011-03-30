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

#ifndef __CUTIESBOOK_COMPANY_HPP__
#define __CUTIESBOOK_COMPANY_HPP__

#include "contact.hpp"

//! The company class
/*!
 * This class will be used to store informations
 * about the contacts of type Company
 */
namespace CutiesBook
{
	class Company : public Contact
	{
	public:
		//! Get the Company SIRET
		long getSiret() const { return siret; }
		//! Get the Company website
		const QString &getWebsite() const { return website; }

		//! Set the Company SIRET
		void setSiret(long siret) { this->siret = siret; }
		//! Set the Company website
		void setWebsite(QString &website) { this->website = website; }

		Company(long siret, QString &website, QSet< Number * > &numbers, QString address = "", QString email = "");
		virtual ~Company();
	private:
		long siret;
		QString website;
		void makeMeAbstractPlease() {}
	};
}

#endif /* __CUTIESBOOK_COMPANY_HPP__ */
