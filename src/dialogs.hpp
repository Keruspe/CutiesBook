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

#ifndef __CUTIESBOOK_DIALOGS_HPP__
#define __CUTIESBOOK_DIALOGS_HPP__

#include <QDialog>
#include <QList>
#include <QGroupBox>
#include <QBoxLayout>
#include <QWidget>

//! The main window class
namespace CutiesBook
{
	class AddContactDialog : public QObject
	{
		Q_OBJECT

	public:
		AddContactDialog(QWidget *parent);
		~AddContactDialog();

	signals:
		void finished();

	private slots:
		void dialogFinished();

	private:
		QDialog *dialog;
		QList<QGroupBox *> boxes;
		QList<QBoxLayout *> boxesLayouts;
		QList<QWidget *> widgets;
	};
}

#endif /* __CUTIESBOOK_DIALOGS_HPP__ */
