#ifndef MainWindow_H
#define MainWindow_H
#include "water.h"
#include <QtWidgets/QMainWindow>
#include <windows.h>
#include "ui_mainwindow.h"
#include <process.h>
#include <string.h>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDialog>
#include <QVector>
#include <QTimer>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	//water Save[100];

	int R_W;
	bool flaag;
	bool flag1;
	int a;
	HANDLE hPipe;
	HANDLE hConfig;
	char   szBuf[1024];
	DWORD  cbRead;
	DWORD  cbWritten;

	int ProcessedID;					// Обрабатываемый ID
	int pageIndex;						// Индекс записи
	int pageNumber;						// Счётчик записей
	int currentIndex;					// Индекс текущей записи
	QString str;						// Вспомогательная строка для браузера

private:
	Ui::MainWindowClass ui;

	private slots:
	void add();
	void dlt();
	void sort();
	void redact();
	void on_TWg_cellDoubleClicked(int row, int column);
	void reeturn();
	void isOk();
	void updateWidget();
	void on_waterName_cursorPositionChanged(int, int);
	void on_comboBoxTypeOfWater_activated(int index);
	void on_checkBoxIstok_clicked(bool i);
	void on_checkBoxStok_clicked(bool j);
	void load();
	//void create();
	void save();
};

#endif // MAINWINDOW_H
