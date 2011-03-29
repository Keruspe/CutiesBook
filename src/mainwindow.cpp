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

#include <QAction>
#include <QMenuBar>
#include <QMenu>

using namespace CutiesBook;

MainWindow *MainWindow::instance = 0;

MainWindow::MainWindow() :
	QMainWindow(0)
{
	QAction *quit = new QAction(tr("&Quit"), this);
	quit->setShortcuts(QKeySequence::Quit);
	quit->setStatusTip(tr("Quit the application"));
	connect(quit, SIGNAL(triggered()), this, SLOT(close()));
	QMenu *menu = menuBar()->addMenu("&CutiesBook");
	menu->addAction(quit);
}

MainWindow::~MainWindow()
{
}
