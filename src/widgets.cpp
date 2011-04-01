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

#include <QSet>
#include <QList>
#include <QtAlgorithms>

using namespace CutiesBook;


void
ListWidget::deleteContacts()
{
	QModelIndexList list = selectedIndexes();
	QSet<int> indexes;
	for ( int i = 0, e = list.size() ; i < e ; ++i )
	{
		indexes.insert(list.at(i).row());
	}
	QList<int> listIndexes(indexes.toList());
	qSort(listIndexes.begin(), listIndexes.end(), qGreater<int>());
	while ( ! listIndexes.isEmpty() )
		directory->deleteContactAt(listIndexes.takeFirst());
}

ListWidget::ListWidget(QWidget *window) :
	QTableView(window),
	directory(Directory::getInstance())
{
	setSortingEnabled(true);

	setModel(directory);

	directory->sort(0, Qt::AscendingOrder);

	connect(directory, SIGNAL(sorted()), this, SLOT(reset()));
}

ListWidget::~ListWidget()
{
}
