#include "stdafx.h"
#include "mainwindow.h"
#include <QTableWidget>
#include <QString>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "water.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	flaag = true;		//
	ui.setupUi(this);

	//��������� ������� � ������ �� �������
	connect(ui.add, SIGNAL(clicked()), this, SLOT(add()));				//�������� 10 �������
	connect(ui.Dlt, SIGNAL(clicked()), this, SLOT(dlt()));				//������� ������
	connect(ui.btnReturn, SIGNAL(clicked()), this, SLOT(reeturn()));	//������� ������
	connect(ui.IsOk, SIGNAL(clicked()), this, SLOT(isOk()));			//��������� ���� ������
	connect(ui.Redact, SIGNAL(clicked()), this, SLOT(redact()));		//������������� ������
	connect(ui.sort, SIGNAL(clicked()), this, SLOT(sort()));			//�������� ���������� | �����������


	//����������� ���������� �� ������������ ������
	QRegExp NameInput("[A-Z][a-z]+ *[A-Z][a-z]+");	//���������� ���������� ���������
	QRegExpValidator *valName = new QRegExpValidator(NameInput, this); //�������� ��� � ����������
	ui.waterName->setValidator(valName);	//��������� �� ������������ ������������ ������

	//���������� �������� �����
	//ui.Dlt->hide();							//�������� ������ �������� ������
	//ui.sort->hide();						//�������� ������ ����������
	ui.TWg->setEnabled(false);				//��������� ��������� ������
	ui.SqrOfSea->hide();					//�������� ������ ������� ����
	ui.comboBoxStok->setEnabled(false);		//��������� ��������� � �������
	ui.comboBoxIstok->setEnabled(false);	//� ��������
	//ui.checkBoxIstok->setEnabled(false);	//��������� ������� ������� ������
	//ui.checkBoxStok->setEnabled(false);		//� �����
	//ui.LengthOfRiver->setEnabled(false);	//��������� ������ ������������� ����
	ui.comboBoxOfLake->setEnabled(false);	//� ��������� ����� �����
	ui.SqrOfWater->setEnabled(false);		//��������� ������ ������� ���� | �����
	//ui.IsOk->setEnabled(false);				//��������� ������ ���������� ����� ������
	//ui.btnReturn->hide();					//�������� ������ ��������
	//ui.Redact->hide();						//�������� ������ ��������������


	// ������������� ����������
	pageIndex = -1;
	pageNumber = 0;


	//////////////////////////////////////////////////////////
	///////////////������ �������/////////////////////////////
	spawnl(P_NOWAIT, "E:\\ProjectC++\\OsiLab4Client\\x64\\Release\\OsiLab4Server.exe", "OsiLab4Server.exe", NULL);
	/////////////���������� ������� � ��������////////////////
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	a = 1;	//������� � ������� ���
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	//������������
	Sleep(200);
	//������� �����
	hPipe = CreateFile(L"\\\\.\\pipe\\myfirstpipe",
		GENERIC_READ | GENERIC_WRITE,		//�� ������ � ������
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hPipe == INVALID_HANDLE_VALUE)		//��� ������
	{
		//�������� �� ������
		QMessageBox msgBox;
		msgBox.setText("Error!!! Pipe not exists");
		msgBox.exec();
		a = 0;	//������
	}

	if (a == 1) //���� ��� ������
	{
		/*QMessageBox msgBox;
		msgBox.setText("Normal");
		msgBox.exec();*/
		//��������� ������ �� ������
		/////////////////////////////////////////////////////////////

	}
	// ���� �� ������� ���������� ������� � ��
	ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);
	pageNumber = atoi(szBuf);

	// ���������� ��������
	updateWidget();
}

//����������
MainWindow::~MainWindow()
{
	//��������� ��� ��������� ������
	strcpy(szBuf, "> exit");
	WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);
	/////////////////////////////////////////////////////////////
	//������� �����
	CloseHandle(hPipe);
	//������� ��������� � �������� ������
	QMessageBox msgBox;
	msgBox.setText("Disconnected");
	msgBox.exec();
}

//�������� ������� ����� �� ��������
void MainWindow::on_checkBoxStok_clicked(bool j)
{
	if (j)	//���� ���
	{
		ui.comboBoxStok->setEnabled(true);	//�������� ���� ������ �����
	}
	else	//�����
	{
		ui.comboBoxStok->setEnabled(false);	//��������� ���� ������ �����
	}
}

//�������� ������� ������ �� ��������
void MainWindow::on_checkBoxIstok_clicked(bool i)
{
	if (i)	//���� ���
	{
		ui.comboBoxIstok->setEnabled(true);	//�������� ���� ������ ������
	}
	else	//�����
	{
		ui.comboBoxIstok->setEnabled(false);	//��������� ���� ������ ������
	}
}

//����� ���� ������ � ��������� ��������������� �����
void MainWindow::on_comboBoxTypeOfWater_activated(int index)
{
	if ((index == 0) || (index == 1)) //���� ������� ���� ��� �����
	{
		ui.checkBoxStok->setEnabled(true);	//�������� ������� �����
		ui.SqrOfWater->setEnabled(true);	//� ������ ������� ������
	}
	else    //�����
	{
		ui.checkBoxStok->setEnabled(false);	//��������� �������
		ui.SqrOfWater->setEnabled(false);	//� ������ ������� ������
	};

	if (index == 0) //���� ������� ����
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//������� "Nope" � ���������� ������
		ui.comboBoxStok->setCurrentIndex(0);	//������� "Nope" � ���������� �����
		ui.checkBoxIstok->setChecked(false);	//������ ������� � �������� ������
		ui.checkBoxStok->setChecked(false);		//� �����
		ui.comboBoxIstok->setEnabled(false);	//��������� ��������� ������
		ui.comboBoxStok->setEnabled(false);		//� �����
		ui.checkBoxIstok->setEnabled(true);		//�������� ������� ������
		ui.LengthOfRiver->setEnabled(true);		//�������� ������ ������������� ����
	}
	else    //����� �� ������ ����
	{
		ui.checkBoxIstok->setEnabled(false);	//��������� ������� ������
		ui.LengthOfRiver->setEnabled(false);	//��������� ������ ������������� ����
	};

	if (index == 1) //���� ������� �����
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//������� "Nope" � ���������� ������
		ui.comboBoxStok->setCurrentIndex(0);	//������� "Nope" � ���������� �����
		ui.checkBoxIstok->setChecked(false);	//������ ������� � �������� ������
		ui.checkBoxStok->setChecked(false);		//� �����
		ui.comboBoxIstok->setEnabled(false);	//��������� ��������� ������
		ui.comboBoxStok->setEnabled(false);		//� �����
		ui.comboBoxOfLake->setEnabled(true);	//�������� ��������� ���� �����
	}
	else    //����� �� ������ �����
	{
		ui.comboBoxOfLake->setEnabled(false);	//��������� ��������� ���� �����
	};

	if (index == 2) //������� ����
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//������� "Nope" � ���������� ������
		ui.comboBoxStok->setCurrentIndex(0);	//������� "Nope" � ���������� �����
		ui.checkBoxIstok->setChecked(false);	//������ ������� � �������� ������
		ui.checkBoxStok->setChecked(false);		//� �����
		ui.comboBoxIstok->setEnabled(false);	//��������� ��������� ������
		ui.comboBoxStok->setEnabled(false);		//� �����
		ui.SqrOfSea->show();					//�������� ������ ������� ����
	}
	else    //����� �� ������ ����
	{
		ui.SqrOfSea->hide();					//��������� ������ ������� ����
	}
}

//���������� ������ + ���������� � ����� � ���� (������� �� ���� �������)
//���� - ����, �����
//����� - ����, �����
//���������� ����������, ���� ����� ��� ���������� � ����� �� ��������� �������
//���������� � ���� � �����, � ��� ������, ���� ��� ���������� �������� � �������
void MainWindow::isOk()
{
	pageIndex = -1;
	save();

	//���� ����� ��������, �� �������� ���
	//if ((ui.comboBoxTypeOfWater->currentText() == "River") || (ui.comboBoxTypeOfWater->currentText() == "Lake"))
	//{
	//	if (ui.comboBoxIstok->findText(ui.waterName->text()) == -1)
	//	{
	//		ui.comboBoxIstok->addItem(ui.waterName->text());
	//	}
	//}

	////���� ���� ��������, �� �������� ���
	//if (ui.comboBoxStok->findText(ui.waterName->text()) == -1)
	//{
	//	ui.comboBoxStok->addItem(ui.waterName->text());
	//}

	/*ui.ObrSort->show();*/
	ui.Redact->show();
	ui.btnReturn->show();
	ui.sort->show();
	ui.Dlt->show();
	updateWidget();
}




//������� ��������� ������ P.S. �������� ����� ������� ����
void MainWindow::reeturn()
{
	R_W = 1;	//���� � ��������� ��������
	ui.TWg->setEnabled(true);	//�������� ��������� ������
}


//��������� ����� ��� ����� ������������ ������
void MainWindow::on_waterName_cursorPositionChanged(int, int)
{
	if (flaag)	//���� �� ��������
	{
		ui.IsOk->setEnabled(true);
		ui.checkBoxStok->setEnabled(true);
		ui.SqrOfWater->setEnabled(true);
		ui.comboBoxIstok->setCurrentIndex(0);
		ui.comboBoxIstok->setCurrentIndex(0);
		ui.comboBoxIstok->setCurrentIndex(0);
		ui.comboBoxStok->setCurrentIndex(0);
		ui.checkBoxIstok->setChecked(false);
		ui.checkBoxStok->setChecked(false);
		ui.comboBoxIstok->setEnabled(false);
		ui.comboBoxStok->setEnabled(false);
		ui.checkBoxIstok->setEnabled(true);
		ui.LengthOfRiver->setEnabled(true);
		flaag = false;	//���������� ���� ��� �������������� ��������� ���������
	}
}


//������� ������ ��� �������������� �� �������� �����
void MainWindow::on_TWg_cellDoubleClicked(int row, int column)
{
	pageIndex = row;
	//���� ���� � ��������� ��������
	if (R_W == 1)
	{
		R_W = 0;	//���������� ���� � ����������� ���������
		ui.TWg->setEnabled(false);	//��������� ��������� ������
		//������� ������������ ������ � ������ ���� �� ������
		char *pch;
		strcpy(szBuf, "> ret");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// �������� ID ������
		sprintf(szBuf, "%d", row);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// ���� ������ � ������
		ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);

		pch = strtok(szBuf, "|");
		ui.waterName->setText(QString(pch));
		pch = strtok(NULL, "|");
		ui.comboBoxTypeOfWater->setCurrentText(QString(pch));
		pch = strtok(NULL, "|");
		ui.checkBoxStok->setChecked(atoi(pch));
		pch = strtok(NULL, "|");
		ui.checkBoxIstok->setChecked(atoi(pch));
		pch = strtok(NULL, "|");
		ui.comboBoxStok->setCurrentText(pch);
		pch = strtok(NULL, "|");
		ui.comboBoxIstok->setCurrentText(pch);
		pch = strtok(NULL, "|");
		ui.LengthOfRiver->setValue(atoi(pch));
		pch = strtok(NULL, "|\n");
		ui.SqrOfWater->setValue(atoi(pch));
		pch = strtok(NULL, "|\n");
		ui.SqrOfSea->setValue(atoi(pch));
		pch = strtok(NULL, "|\n");
		pch = strtok(NULL, "|\n");
		ui.comboBoxOfLake->setCurrentIndex(atoi(pch));
	}

	//���� ���� � ��������� ��������������
	if (R_W == 2)
	{
		R_W = 0;	//���������� ���� � ����������� ���������
		bool flag = true;	//���� ������������ ������
		ui.TWg->setEnabled(false);	//��������� ��������� ������
		if (flag)	//���� ������ ���������
		{
			pageIndex = row;
			save();

			//	if ((ui.comboBoxTypeOfWater->currentText() == "River") || (ui.comboBoxTypeOfWater->currentText() == "Lake"))
			//	{
			//		if (ui.comboBoxIstok->findText(ui.waterName->text()) == -1)
			//		{
			//			ui.comboBoxIstok->addItem(ui.waterName->text());
			//		}
			//	}


			//	if (ui.comboBoxStok->findText(ui.waterName->text()) == -1)
			//	{
			//		ui.comboBoxStok->addItem(ui.waterName->text());
			//	}
		}
	}

	//���� ���� � ��������� �������� � � ������ ���� ������
	///////////////////////////////////////////////////////////
	if ((R_W == 3) && (ui.TWg->rowCount() > 1))
	{
		R_W = 0;
		ui.TWg->setEnabled(false);
		// �������� ������� ������ �������� ������
		strcpy(szBuf, "> del");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// �������� ID ��������� ������
		sprintf(szBuf, "%d", row);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);
		pageNumber--;

		int tmp = pageIndex;
		// �������� �� ��������
		ui.TWg->removeRow(row);
		pageIndex = tmp;
	}
	Sleep(200);
	updateWidget();
}


//�������������� (���������� ��������� ������ �� �������� ���������)
void MainWindow::redact()
{
	R_W = 2;	//���������� ���� � ��������� ��������������
	this->ui.TWg->setEnabled(true);		//�������� ��������� ������
}


//���������� QTable
void MainWindow::sort()
{

	strcpy(szBuf, "> sort");
	Sleep(10);

}


void MainWindow::dlt()
{
	R_W = 3;
	this->ui.TWg->setEnabled(true);
}

void MainWindow::add()
{
	strcpy(szBuf, "> fill");
	WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

	// ���� �� ������� ���������� ������� � ��
	ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);
	pageNumber = atoi(szBuf);

	ui.Redact->show();
	ui.btnReturn->show();
	ui.sort->show();
	ui.Dlt->show();
	//ui.ObrSort->show();
	updateWidget();
}


void MainWindow::updateWidget() {
	char *pch;


	// ���������� ��������
	for (int i = 0; i < pageNumber; i++)
	{
		// �������� ������� ������ ������������ ��������
		strcpy(szBuf, "> browser");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// �������� ������ � ������� (���� �����)
		if (pageNumber > (ui.TWg->rowCount())) {
			ui.TWg->insertRow(i);
		}

		// �������� ������� ������
		sprintf(szBuf, "%d", i);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// ������ ����������� ������ � ������
		ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);

		pch = strtok(szBuf, "|");

		// ��������� ������������ ������
		QTableWidgetItem* itm0 = new QTableWidgetItem;
		itm0->setFlags(Qt::ItemIsEnabled);
		itm0->setText(QString::fromLocal8Bit(pch));
		ui.TWg->setItem(i, 0, itm0);

		pch = strtok(NULL, "|");

		// ��������� ���� ������
		QTableWidgetItem* itm1 = new QTableWidgetItem;
		itm1->setFlags(Qt::ItemIsEnabled);
		itm1->setText(QString::fromLocal8Bit(pch));
		ui.TWg->setItem(i, 1, itm1);
	}
}

void MainWindow::load() {
	// ���� ����������� ������ ������ � ����������� ������� �������, ��:
	if ((ui.TWg->currentRow()) >= 0 && (ui.TWg->currentRow()) < pageNumber)
	{
		//pageIndex = ui.TWg->currentRow();
		reeturn();
		ui.Dlt->setEnabled(true);
	}
}


void MainWindow::save() {
	bool yep = true;		//���� ������������ ������

							//��������� ��� ������� �� ������ ��� �������?
	if ((ui.waterName->text() == ui.comboBoxStok->currentText()) || (ui.waterName->text() == ui.comboBoxIstok->currentText())) //���� ��������� ��� ������� �� ������ ��� �������
	{
		QMessageBox::critical(this, "Error", "Name == Source of the river or River runoff"); //�������� ��������� �� ������
		yep = false;		//������ ������
	}

	//��������� ���� � �����?
	if ((ui.comboBoxStok->currentText() != "Nope") || (ui.comboBoxIstok->currentText() != "Nope")) //���� �� "Nope"
	{
		if (ui.comboBoxStok->currentText() == ui.comboBoxIstok->currentText())  //���� ��������� ���� � �����
		{
			QMessageBox::critical(this, "Error", "Source of the river == River runoff");	//�������� ��������� �� ������
			yep = false;	//������ ������
		}
	}

	//��������� ��� ������� � ����� �� ���� � ������?
	for (int a = ui.TWg->rowCount(); a >= 0; a--) //��� ������� ����� � ������
	{
		QString check;
		QTableWidgetItem *item = ui.TWg->item(a, 0);
		if (NULL != item) {
			check = item->text();
		}
		if (check == ui.waterName->text()) //���� ��������� �������� ������� � ������ � ������
		{
			QMessageBox::critical(this, "Error", "Record already exists"); //�������� ��������� �� ������
			yep = false;	//������ ������
			break;			//���������� ����
		}
	}

	//��������� � ������ ����� ������
	///////////////////////////////////////////////////////////
	if (yep)	//���� �� ������ �� ���� �� �������
	{
		// �������� ������� ������ ���������� ������
		strcpy(szBuf, "> save");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		int ProcessedID = pageIndex;
		if (pageIndex == -1)
		{
			pageNumber++;
		}
		QString Name = ui.waterName->text();
		if (Name == "")
			Name = " ";
		QString WaterType = ui.comboBoxTypeOfWater->currentText();
		if (WaterType == "")
			WaterType = " ";

		// �������� ID ������
		sprintf(szBuf, "%d|%s|%s|%d|%d|%d|%d|%d|%d|%d|%d|\r\n", ProcessedID,
			Name.toLocal8Bit().toStdString().c_str(),
			WaterType.toLocal8Bit().toStdString().c_str(),
			(int)ui.checkBoxStok->isChecked(),
			(int)ui.checkBoxIstok->isChecked(),
			ui.comboBoxStok->currentIndex(),
			ui.comboBoxIstok->currentIndex(),
			ui.LengthOfRiver->value(),
			ui.SqrOfWater->value(),
			ui.SqrOfSea->value(),
			ui.comboBoxOfLake->currentIndex());

		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);
	}
	Sleep(200);
	updateWidget();
	ui.TWg->setEnabled(false);
}