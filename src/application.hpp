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

#ifndef __CUTIESBOOK_APPLICATION_HPP__
#define __CUTIESBOOK_APPLICATION_HPP__

#include "mainwindow.hpp"

#include <QApplication>
#include <QString>

//! The main application class
/*!
 * This class handle the whole application process
 * This includes loading the config, the existing repository
 * and the window creation.
 *
 */
namespace CutiesBook
{
	class Application : public QApplication
	{
	public:
		//! Instance getter
		static Application *getInstance(int &argc, char *argv[])
		{
			if ( ! Application::instance )
				Application::instance = new Application(argc, argv);
			return Application::instance;
		}

		//! Clean the instance
		static void cleanInstance()
		{
			if ( Application::instance )
				delete Application::instance;
		}

	private:
		static Application *instance;
		MainWindow *mainWindow;
		QString file;

		Application(int &argc, char *argv[]);
		~Application();
	};
}

#endif /* __CUTIESBOOK_APPLICATION_HPP__ */
