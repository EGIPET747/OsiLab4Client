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

	//Связываем сигналы с кнопок со слотами
	connect(ui.add, SIGNAL(clicked()), this, SLOT(add()));				//Добавить 10 записей
	connect(ui.Dlt, SIGNAL(clicked()), this, SLOT(dlt()));				//Удалить запись
	connect(ui.btnReturn, SIGNAL(clicked()), this, SLOT(reeturn()));	//Вернуть запись
	connect(ui.IsOk, SIGNAL(clicked()), this, SLOT(isOk()));			//Сохранить одну запись
	connect(ui.Redact, SIGNAL(clicked()), this, SLOT(redact()));		//Редактировать запись
	connect(ui.sort, SIGNAL(clicked()), this, SLOT(sort()));			//Обратить сортировку | сортировать


	//Закрепление валидатора на наименование водоёма
	QRegExp NameInput("[A-Z][a-z]+ *[A-Z][a-z]+");	//Используем регулярное выражение
	QRegExpValidator *valName = new QRegExpValidator(NameInput, this); //применяя его к валидатору
	ui.waterName->setValidator(valName);	//проверяем на корректность наименование водоёма

	//Выключение ненужных полей
	//ui.Dlt->hide();							//Скрываем кнопку удаления записи
	//ui.sort->hide();						//Скрываем кнопку сортировки
	ui.TWg->setEnabled(false);				//Отключаем табличный виджет
	ui.SqrOfSea->hide();					//Скрываем виджет площади моря
	ui.comboBoxStok->setEnabled(false);		//Отключаем комбобокс с стоками
	ui.comboBoxIstok->setEnabled(false);	//и истоками
	//ui.checkBoxIstok->setEnabled(false);	//Отключаем чекбокс наличия истока
	//ui.checkBoxStok->setEnabled(false);		//и стока
	//ui.LengthOfRiver->setEnabled(false);	//Отключаем виджет протяженности реки
	ui.comboBoxOfLake->setEnabled(false);	//и комбобокс типов озера
	ui.SqrOfWater->setEnabled(false);		//Отключаем виджет площади реки | озера
	//ui.IsOk->setEnabled(false);				//Отключаем кнопку сохранения одной записи
	//ui.btnReturn->hide();					//Скрываем кнопку возврата
	//ui.Redact->hide();						//Скрываем кнопку редактирования


	// Инициализация переменных
	pageIndex = -1;
	pageNumber = 0;


	//////////////////////////////////////////////////////////
	///////////////Запуск сервера/////////////////////////////
	spawnl(P_NOWAIT, "E:\\ProjectC++\\OsiLab4Client\\x64\\Release\\OsiLab4Server.exe", "OsiLab4Server.exe", NULL);
	/////////////Соединение сервера с клиентом////////////////
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	a = 1;	//Проблем с потоком нет
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	//Подключаемся
	Sleep(200);
	//создаем поток
	hPipe = CreateFile(L"\\\\.\\pipe\\myfirstpipe",
		GENERIC_READ | GENERIC_WRITE,		//на чтение и запись
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hPipe == INVALID_HANDLE_VALUE)		//При ошибке
	{
		//Сообщаем об ошибке
		QMessageBox msgBox;
		msgBox.setText("Error!!! Pipe not exists");
		msgBox.exec();
		a = 0;	//Ошибка
	}

	if (a == 1) //Если нет ошибок
	{
		/*QMessageBox msgBox;
		msgBox.setText("Normal");
		msgBox.exec();*/
		//Загрузить записи из памяти
		/////////////////////////////////////////////////////////////

	}
	// Приём от сервера количества страниц в бд
	ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);
	pageNumber = atoi(szBuf);

	// Заполнение браузера
	updateWidget();
}

//Деструктор
MainWindow::~MainWindow()
{
	//Сохранить все имеющиеся записи
	strcpy(szBuf, "> exit");
	WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);
	/////////////////////////////////////////////////////////////
	//Закрыть поток
	CloseHandle(hPipe);
	//вывести сообщение о закрытии потока
	QMessageBox msgBox;
	msgBox.setText("Disconnected");
	msgBox.exec();
}

//Проверка наличия стока по чекбоксу
void MainWindow::on_checkBoxStok_clicked(bool j)
{
	if (j)	//Если чек
	{
		ui.comboBoxStok->setEnabled(true);	//включить поле выбора стока
	}
	else	//Иначе
	{
		ui.comboBoxStok->setEnabled(false);	//отключить поле выбора стока
	}
}

//Проверка наличия истока по чекбоксу
void MainWindow::on_checkBoxIstok_clicked(bool i)
{
	if (i)	//Если чек
	{
		ui.comboBoxIstok->setEnabled(true);	//включить поле выбора истока
	}
	else	//Иначе
	{
		ui.comboBoxIstok->setEnabled(false);	//отключить поле выбора истока
	}
}

//Выбор типа водоёма и включение соответствующих полей
void MainWindow::on_comboBoxTypeOfWater_activated(int index)
{
	if ((index == 0) || (index == 1)) //Если выбрана река или озеро
	{
		ui.checkBoxStok->setEnabled(true);	//включаем чекбокс стока
		ui.SqrOfWater->setEnabled(true);	//и виджет площади водоёма
	}
	else    //Иначе
	{
		ui.checkBoxStok->setEnabled(false);	//выключаем чекбокс
		ui.SqrOfWater->setEnabled(false);	//и виджет площади водоёма
	};

	if (index == 0) //Если выбрана река
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе истока
		ui.comboBoxStok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе стока
		ui.checkBoxIstok->setChecked(false);	//убрать галочку с чекбокса истока
		ui.checkBoxStok->setChecked(false);		//и стока
		ui.comboBoxIstok->setEnabled(false);	//выключить комбобокс истока
		ui.comboBoxStok->setEnabled(false);		//и стока
		ui.checkBoxIstok->setEnabled(true);		//включить чекбокс истока
		ui.LengthOfRiver->setEnabled(true);		//включить виджет протяженности реки
	}
	else    //Откат от выбора реки
	{
		ui.checkBoxIstok->setEnabled(false);	//выключить чекбокс истока
		ui.LengthOfRiver->setEnabled(false);	//выключить виджет протяженности реки
	};

	if (index == 1) //Если выбрано озеро
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе истока
		ui.comboBoxStok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе стока
		ui.checkBoxIstok->setChecked(false);	//убрать галочку с чекбокса истока
		ui.checkBoxStok->setChecked(false);		//и стока
		ui.comboBoxIstok->setEnabled(false);	//выключить комбобокс истока
		ui.comboBoxStok->setEnabled(false);		//и стока
		ui.comboBoxOfLake->setEnabled(true);	//включить комбобокс типа озера
	}
	else    //Откат от выбора озера
	{
		ui.comboBoxOfLake->setEnabled(false);	//отключить комбобокс типа озера
	};

	if (index == 2) //Выбрано море
	{
		ui.comboBoxIstok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе истока
		ui.comboBoxStok->setCurrentIndex(0);	//выбрать "Nope" в комбобоксе стока
		ui.checkBoxIstok->setChecked(false);	//убрать галочку с чекбокса истока
		ui.checkBoxStok->setChecked(false);		//и стока
		ui.comboBoxIstok->setEnabled(false);	//выключить комбобокс истока
		ui.comboBoxStok->setEnabled(false);		//и стока
		ui.SqrOfSea->show();					//показать виджет площади моря
	}
	else    //Откат от выбора моря
	{
		ui.SqrOfSea->hide();					//отключить виджет площади моря
	}
}

//Сохранение записи + добавление в исток и сток (зависит от типа водоема)
//Сток - море, озеро
//Исток - река, озеро
//Сохранение происходит, если ранее нет сохранений с таким же названием водоема
//Добавление в сток и исток, в том случае, если нет повторения названия в перечне
void MainWindow::isOk()
{
	pageIndex = -1;
	save();

	//Если исток уникален, то добавить его
	//if ((ui.comboBoxTypeOfWater->currentText() == "River") || (ui.comboBoxTypeOfWater->currentText() == "Lake"))
	//{
	//	if (ui.comboBoxIstok->findText(ui.waterName->text()) == -1)
	//	{
	//		ui.comboBoxIstok->addItem(ui.waterName->text());
	//	}
	//}

	////Если сток уникален, то добавить его
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




//Возврат выбранной записи P.S. работает через двойной клик
void MainWindow::reeturn()
{
	R_W = 1;	//флаг в положение возврата
	ui.TWg->setEnabled(true);	//включить табличный виджет
}


//Включение полей при вводе наименования водоёма
void MainWindow::on_waterName_cursorPositionChanged(int, int)
{
	if (flaag)	//если не включено
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
		flaag = false;	//используем флаг для предотвращения повторных включений
	}
}


//Возврат записи или редактирование по двойному клику
void MainWindow::on_TWg_cellDoubleClicked(int row, int column)
{
	pageIndex = row;
	//Если флаг в положении возврата
	if (R_W == 1)
	{
		R_W = 0;	//установить флаг в нейтральное положение
		ui.TWg->setEnabled(false);	//выключить табличный виджет
		//вернуть наименование водоёма и другие поля из памати
		char *pch;
		strcpy(szBuf, "> ret");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// Передача ID записи
		sprintf(szBuf, "%d", row);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// Приём данных о записи
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

	//Если флаг в положении редактирования
	if (R_W == 2)
	{
		R_W = 0;	//установить флаг в нейтральное положение
		bool flag = true;	//флаг корректности записи
		ui.TWg->setEnabled(false);	//выключить табличный виджет
		if (flag)	//если запись корректна
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

	//Если флаг в положении удаления и в памяти есть записи
	///////////////////////////////////////////////////////////
	if ((R_W == 3) && (ui.TWg->rowCount() > 1))
	{
		R_W = 0;
		ui.TWg->setEnabled(false);
		// Передать серверу сигнал удаления записи
		strcpy(szBuf, "> del");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// Передача ID удаляемой записи
		sprintf(szBuf, "%d", row);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);
		pageNumber--;

		int tmp = pageIndex;
		// Удаление из браузера
		ui.TWg->removeRow(row);
		pageIndex = tmp;
	}
	Sleep(200);
	updateWidget();
}


//Редактирование (сохранение выбранной записи по текущему состоянию)
void MainWindow::redact()
{
	R_W = 2;	//установить флаг в положение редактирования
	this->ui.TWg->setEnabled(true);		//включить табличный виджет
}


//Сортировка QTable
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

	// Приём от сервера количества страниц в бд
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


	// Заполнение браузера
	for (int i = 0; i < pageNumber; i++)
	{
		// Передать серверу сигнал формирования браузера
		strcpy(szBuf, "> browser");
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// Добавить строку в браузер (если нужно)
		if (pageNumber > (ui.TWg->rowCount())) {
			ui.TWg->insertRow(i);
		}

		// Передача индекса записи
		sprintf(szBuf, "%d", i);
		WriteFile(hPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL);

		// Чтения необходимых данных о записи
		ReadFile(hPipe, szBuf, 1024, &cbRead, NULL);

		pch = strtok(szBuf, "|");

		// Установка наименования водоёма
		QTableWidgetItem* itm0 = new QTableWidgetItem;
		itm0->setFlags(Qt::ItemIsEnabled);
		itm0->setText(QString::fromLocal8Bit(pch));
		ui.TWg->setItem(i, 0, itm0);

		pch = strtok(NULL, "|");

		// Установка типа водоёма
		QTableWidgetItem* itm1 = new QTableWidgetItem;
		itm1->setFlags(Qt::ItemIsEnabled);
		itm1->setText(QString::fromLocal8Bit(pch));
		ui.TWg->setItem(i, 1, itm1);
	}
}

void MainWindow::load() {
	// Если необходимый индекс входит в размерность массива записей, то:
	if ((ui.TWg->currentRow()) >= 0 && (ui.TWg->currentRow()) < pageNumber)
	{
		//pageIndex = ui.TWg->currentRow();
		reeturn();
		ui.Dlt->setEnabled(true);
	}
}


void MainWindow::save() {
	bool yep = true;		//флаг корректности записи

							//Совпадает имя водоема со стоком или истоком?
	if ((ui.waterName->text() == ui.comboBoxStok->currentText()) || (ui.waterName->text() == ui.comboBoxIstok->currentText())) //Если совпадает имя водоема со стоком или истоком
	{
		QMessageBox::critical(this, "Error", "Name == Source of the river or River runoff"); //показать сообщение об ошибке
		yep = false;		//ошибка записи
	}

	//Совпадает сток и исток?
	if ((ui.comboBoxStok->currentText() != "Nope") || (ui.comboBoxIstok->currentText() != "Nope")) //Если не "Nope"
	{
		if (ui.comboBoxStok->currentText() == ui.comboBoxIstok->currentText())  //Если совпадает сток и исток
		{
			QMessageBox::critical(this, "Error", "Source of the river == River runoff");	//показать сообщение об ошибке
			yep = false;	//ошибка записи
		}
	}

	//Совпадает имя водоема с одним из имен в памяти?
	for (int a = ui.TWg->rowCount(); a >= 0; a--) //для каждого имени в памяти
	{
		QString check;
		QTableWidgetItem *item = ui.TWg->item(a, 0);
		if (NULL != item) {
			check = item->text();
		}
		if (check == ui.waterName->text()) //если совпадает название водоема с именем в памяти
		{
			QMessageBox::critical(this, "Error", "Record already exists"); //показать сообщение об ошибке
			yep = false;	//ошибка записи
			break;			//остановить цикл
		}
	}

	//Сохраняем в память через сервер
	///////////////////////////////////////////////////////////
	if (yep)	//если не прошло ни одно из условий
	{
		// Передать серверу сигнал сохранения записи
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

		// Передача ID записи
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