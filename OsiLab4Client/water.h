#ifndef WATER_H
#define WATER_H
#include <QString>

class water
{
public:
	water();
	~water();

	QString Name;
	int WaterType;
	QString WaterTypeText;
	bool Stok;
	int NameStok;
	bool Istok;
	int NameIstok;
	int Length;
	int LakeType;
	int WaterSqr;
	int SeaSqr;
	int ID;

	//bool operator!= (const water &page) const;		// Оператор !=
	//bool operator== (const water &page) const;		// Оператор ==
	//bool operator> (const water &page) const;			// Оператор >
	//bool operator>= (const water &page) const;		// Оператор >=
	//bool operator< (const water &page) const;			// Оператор <
	//bool operator<= (const water &page) const;		// Оператор <=
};

#endif // WATER_H

