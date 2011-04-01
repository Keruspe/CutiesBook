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

#include "mainwindow.hpp"

#include <QMenuBar>
#include <QMenu>

using namespace CutiesBook;

MainWindow *MainWindow::instance = 0;

MainWindow::MainWindow() :
	QMainWindow(0),
	toolbar(0),
	addContact(0),
	deleteContact(0),
	quit(0)
{
	toolbar = new QToolBar("Tools", this);
	addToolBar(toolbar);

	addContact = new QAction(tr("&New Contact"), this);
	addContact->setStatusTip(tr("Add a new contact"));
	connect(addContact, SIGNAL(triggered()), this, SLOT(addContact()));
	toolbar->addAction(addContact);

	deleteContact = new QAction(tr("&Delete Contact"), this);
	deleteContact->setStatusTip(tr("Delete a contact"));
	connect(deleteContact, SIGNAL(triggered()), this, SLOT(removeContact()));
	toolbar->addAction(deleteContact);

	quit = new QAction(tr("&Quit"), this);
	quit->setShortcuts(QKeySequence::Quit);
	quit->setStatusTip(tr("Quit the application"));
	connect(quit, SIGNAL(triggered()), this, SLOT(close()));
	toolbar->addAction(quit);

	centralWidget = new ListWidget(this);
	setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
	delete centralWidget;
	delete addContact;
	delete deleteContact;
	delete quit;
}
