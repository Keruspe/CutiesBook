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

void
MainWindow::addContactSlot()
{
	/*
	if ( addContactDialog != 0 )
		return;
	addContactDialog = new AddContactDialog(this);
	connect(addContactDialog, SIGNAL(finished()), this, SLOT(addContactFinishedSlot()));
	*/
	addContactFinishedSlot();
}

void
MainWindow::addContactFinishedSlot()
{
	/*
	delete addContactDialog;
	addContactDialog = 0;
	*/
	Directory *directory = Directory::getInstance();
	for ( int i = 0 ; i < 30 ; ++i )
	{
		QString last("Contact");
		QString first("Number ");
		first += QString::number(i);
		QDate date(1970, 1, 1);
		QString add("Nowhere");
		QString email("plop@example.com");
		Individual *in = new Individual(last, first, date, add, email);
		Number *n = new Number("555-9574", Number::MOBILE, true);
		Number *n2 = new Number("++555-9574", Number::FIXE, false);
		in->addNumber(n);
		in->addNumber(n2);
		directory->addContact(in);
	}

	for ( int i = 0 ; i < 30 ; ++i )
	{
		QString website("foobar.");
		website += QString::number(i);
		int siret = i;
		directory->addContact(new Company(siret, website));
	}
}

MainWindow::MainWindow() :
	QMainWindow(0),
	addContactDialog(0),
	toolbar(0),
	addContact(0),
	deleteContact(0),
	quit(0)
{
	centralWidget = new ListWidget(this);
	setCentralWidget(centralWidget);

	toolbar = new QToolBar("Tools", this);
	addToolBar(toolbar);

	addContact = new QAction(tr("&New Contact"), this);
	addContact->setStatusTip(tr("Add a new contact"));
	connect(addContact, SIGNAL(triggered()), this, SLOT(addContactSlot()));
	toolbar->addAction(addContact);

	deleteContact = new QAction(tr("&Delete Contact"), this);
	deleteContact->setStatusTip(tr("Delete a contact"));
	connect(deleteContact, SIGNAL(triggered()), centralWidget, SLOT(deleteContacts()));
	toolbar->addAction(deleteContact);

	quit = new QAction(tr("&Quit"), this);
	quit->setShortcuts(QKeySequence::Quit);
	quit->setStatusTip(tr("Quit the application"));
	connect(quit, SIGNAL(triggered()), this, SLOT(close()));
	toolbar->addAction(quit);
}

MainWindow::~MainWindow()
{
	delete centralWidget;
	delete addContact;
	delete deleteContact;
	delete quit;
}
