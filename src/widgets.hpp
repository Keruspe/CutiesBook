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

#ifndef __CUTIESBOOK_WIDGETS_HPP__
#define __CUTIESBOOK_WIDGETS_HPP__

#include <QTableView>
#include <QWidget>

#include "directory.hpp"

//! The list widget
namespace CutiesBook
{
	class ListWidget : public QTableView
	{
		Q_OBJECT

	public:
		//! Constructor
		ListWidget(QWidget *window);
		~ListWidget();

	public slots:
		void deleteContacts();

	private:
		Directory *directory;
	};
}

#endif /* __CUTIESBOOK_WIDGETS_HPP__ */
