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

#ifndef __CUTIESBOOK_MAINWINDOW_HPP__
#define __CUTIESBOOK_MAINWINDOW_HPP__

#include "widgets.hpp"

#include <QMainWindow>
#include <QToolBar>
#include <QAction>

//! The main window class
namespace CutiesBook
{
	class MainWindow : public QMainWindow
	{
	public:
		//! Instance getter
		static MainWindow *getInstance()
		{
			if ( ! MainWindow::instance )
				MainWindow::instance = new MainWindow();
			return MainWindow::instance;
		}

		//! Clean the instance
		static void cleanInstance()
		{
			if ( MainWindow::instance )
				delete MainWindow::instance;
		}

	private:
		static MainWindow *instance;

		QToolBar *toolbar;
		QAction *addContact;
		QAction *deleteContact;
		QAction *quit;
		ListWidget *centralWidget;

		MainWindow();
		~MainWindow();
	};
}

#endif /* __CUTIESBOOK_MAINWINDOW_HPP__ */
