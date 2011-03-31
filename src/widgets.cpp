/*
 * CutiesBook - Get a trace of passed dates
 *
 * Copyright © 2011 Sardem FF7
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

#include "widgets.hpp"

#include "mainwindow.hpp"
#include "directory.hpp"

#include <QString>
#include <QDebug>

using namespace CutiesBook;

ListWidget::ListWidget(QWidget *window) :
	QTableView(window),
	header(0),
	contacts()
{
	setSortingEnabled(true);

	header = new QHeaderView(Qt::Vertical, this);
	setVerticalHeader(header);

	setModel(Directory::getInstance());
}

ListWidget::~ListWidget()
{
	while ( ! contacts.isEmpty() )
	{
		delete contacts.first();
		contacts.pop_front();
	}
}
