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

	//bool operator!= (const water &page) const;		// �������� !=
	//bool operator== (const water &page) const;		// �������� ==
	//bool operator> (const water &page) const;			// �������� >
	//bool operator>= (const water &page) const;		// �������� >=
	//bool operator< (const water &page) const;			// �������� <
	//bool operator<= (const water &page) const;		// �������� <=
};

#endif // WATER_H

