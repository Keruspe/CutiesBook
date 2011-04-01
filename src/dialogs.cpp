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

#include "dialogs.hpp"

#include <QLineEdit>

using namespace CutiesBook;

void
AddContactDialog::dialogFinished()
{
	if ( dialog->result() == QDialog::Accepted )
	{
		// Add stuff
	}
	emit finished();
}

AddContactDialog::AddContactDialog(QWidget *parent) :
	dialog(0),
	boxes(),
	boxesLayouts(),
	widgets()
{
	dialog = new QDialog(parent);
	dialog->setModal(true);

	QBoxLayout *main = new QVBoxLayout(dialog);
	boxesLayouts.append(main);

	QGroupBox *commonBox = new QGroupBox("Common information", dialog);
	QBoxLayout *common = new QVBoxLayout(commonBox);
	boxes.append(commonBox);
	boxesLayouts.append(common);
	//QWidget *number = new NumberWidget();

	QWidget *email = new QLineEdit("Email");
	widgets.append(email);
	common->addWidget(email);

/*
	QGroupBox *specificBox = new QGroupBox("Specific information", dialog);
	QBoxLayout *specific = new QHBoxLayout(specificBox);
	boxes.append(specificBox);
	boxesLayouts.append(specific);

	QGroupBox *individualBox = new QGroupBox("Individual", specificBox);
	QBoxLayout *individual = new QVBoxLayout(individualBox);
	boxes.append(individualBox);
	boxesLayouts.append(individual);

	QGroupBox *companyBox = new QGroupBox("Company", specificBox);
	QBoxLayout *company = new QVBoxLayout(companyBox);
	boxes.append(companyBox);
	boxesLayouts.append(company);
*/

	dialog->show();

	connect(dialog, SIGNAL(accepted()), this, SLOT(dialogFinished()));
	connect(dialog, SIGNAL(rejected()), this, SLOT(dialogFinished()));
}

AddContactDialog::~AddContactDialog()
{
	while ( ! widgets.isEmpty() )
		delete widgets.takeLast();
	while ( ! boxesLayouts.isEmpty() )
		delete boxesLayouts.takeLast();
	while ( ! boxes.isEmpty() )
		delete boxes.takeLast();
	delete dialog;
}
