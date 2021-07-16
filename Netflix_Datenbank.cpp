#define debugging 1

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;

set <string> read_set(string inString);


class date
{
public:
	date();
	~date();

private:
	int year;
	int month;
	int day;
};

date::date()
{
	year = 0;
	month = 0;
	day = 0;
}

date::~date()
{
}

class Filme
{
public:
	Filme();
	~Filme();
	int einlesen(string line);

private:
	bool Bmovie;

	string title;
	string director;
	string country;
	string description;

	set <string> actors;
	set <string> categories;

	date date_added;
	date release;

	int rating;
	int duration;
};

Filme::Filme()
{

	Bmovie = false;

	title = "uninitialised";
	director = "uninitialised";
	country = "uninitialised";
	description = "uninitialised";

	set <string> actors;
	set <string> categories;

	date_added;
	release;

	rating = 0;
	duration = 0;
}

Filme::~Filme()
{
}

int Filme::einlesen(string line)
{
	bool		inQutation = 0; //ob der Text derzeit in Anführungszeichen ist
	string		sTemp; //temp String
	string		number; //der Xte Titel
	vector <string> DatenReverse;
	vector <string> Daten;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '"')
		{
			inQutation = !inQutation;
		}
		else if ((line[i] == ',') && !inQutation) //bei Kommas, die nicht zw. Anführungszeichen stehen wird der String gepusht
		{
			DatenReverse.push_back(sTemp);
			sTemp = "";
		}
		else
		{
			sTemp = sTemp + line[i];
		}
	}
	DatenReverse.push_back(sTemp);

	for (int i = 0; i < DatenReverse.size(); i++) //der Anfang der Linie ist noch am Ende
	{
		Daten.push_back(DatenReverse[i]);
	}
	if (Daten.size() != 12)
	{
		cout << "Die Zahl der Einträge bei Titel " << Daten[0] << ", " << Daten[1] << "ist falsch, es sind " << Daten.size() << "Einträge" << endl;
	}
	//  0 show_id,
	//  1 type,
	//	2 title,
	//	3 director,
	//	4 cast,
	//	5 country,
	//	6 date_added,
	//	7 release_year,
	//	8 rating,
	//	9 duration,
	//	10 listed_in,
	//	11 description
	
	title = Daten[2];
	director = Daten[3];
	actors = read_set(Daten[4]);
	country = Daten[5];
	description = Daten[11];
	if (Daten[1] == "Movie")
	{
		Bmovie = true;
	}
	else if (Daten[1] == "TV Show")
	{
		Bmovie = false;
	}
	else
	{
		cout << number << ": " << "type is" << Daten[1] << endl;
	}


	set <string> categories;

	date date_added;
	date release;

	int rating;
	int duration;

#if debugging
	cout << Daten[0] << ":  ";
	for (auto it : actors)
	{
		cout << it << "___";
	}
	cout << endl;
#endif // debugging

	return(0);
}

set <string> read_set(string inString)
{
	set <string> Daten;
	string sTemp;
	for (int i = 0; i < inString.size(); i++)
	{

		if (inString[i] == ',')
		{
			Daten.insert(sTemp);
			sTemp = "";
		}
		else
		{
			sTemp = sTemp + inString[i];
		}
	}
	Daten.insert(sTemp);
	return(Daten);
}

date read_dates(string* linestream)
{
	return(date());
}


/*to do:
* categories, Länder, Schauspieler vielleicht auch richtig speichern / indexen
* Felermeldung / Hinweise beim Einlesen
*/
int main()
{
	vector <Filme> Sammlung;
	string temp;

	fstream Datei;
	Datei.open("netflix_titles.csv", ios::in); //open a file to perform read operation using file object
	if (Datei.is_open()) {   //checking whether the file is open
		getline(Datei, temp, '\n'); // ignoriert die 1. Zeile
		while (true)
		{// kopiert und modifiziert von https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
			Filme Ftemp;
			string line;

			getline(Datei, line);
			Ftemp.einlesen(line);
			Sammlung.push_back(Ftemp);
		}
		Datei.close();   //close the file object.
	}
	else
	{
		cout << "Fehler beim Öffnen" << endl;
	}
}