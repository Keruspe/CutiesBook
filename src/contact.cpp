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

#include "contact.hpp"

using namespace CutiesBook;

void
Contact::addNumber(Number *number)
{
	numbers.insert(number);
}

void
Contact::deleteNumber(Number *number)
{
	numbers.remove(number);
	delete number;
}

QString
Contact::getNumbersString() const
{
	QString ret("");
	for (QSet< Number * >::const_iterator i = numbers.begin(),
		e = numbers.end() ; i != e ; ++i)
	{
		ret += (*i)->toString();
		if ( i != e )
			ret += "\n";
	}
	return ret;
}

Contact::Contact(QString _address, QString _email) :
	QObject(),
	address(_address),
	email(_email)
{
}

Contact::~Contact()
{
	for (QSet< Number * >::iterator i = numbers.begin() ; i != numbers.end() ; ++i)
	{
		delete *i;
	}
}
