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

#include "application.hpp"

#include <QProcessEnvironment>

#include "directory.hpp"
#include "individual.hpp"

using namespace CutiesBook;

Application *Application::instance = 0;

Application::Application(int &argc, char *argv[]) :
	QApplication(argc, argv),
	mainWindow(0),
	file()
{

	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	file = env.value("HOME");
	file += "/.local/var/cutiesbook/directory";

	/*
	 * Load the existing book
	 */
	Directory::getInstance()->load(file);

	/*
	 * Create the main window
	 */
	this->mainWindow = MainWindow::getInstance();
	this->mainWindow->show();
}

Application::~Application()
{

	/*
	 * Clean the main window
	 */
	MainWindow::cleanInstance();

	/*
	 * Save the book
	 */
	Directory::getInstance()->save(file);
	Directory::cleanInstance();
}
