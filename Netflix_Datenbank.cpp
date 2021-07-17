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
#include <conio.h>

using namespace std;

set <string> read_set(string inString);
int stringToInt(string inString);

class date
{
public:
	date();
	~date();
	int read_date(string inString);
	int cout_date();
private: // Nummern sind Menschenlesbar, zählen also von 1
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
	int einlesen(string line, set <string>& allcategories, string &errorcorrection);
	string get_description();
	int set_description(string setter);

private:
	bool Bmovie;

	string title;
	string director;
	string country;
	string description;

	set <string> actors;
	set <string> categories;

	date date_added;
	int release;

	string rating;
	int duration; //in Minuten bei Filmen, in Staffeln bei Serien
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
	release = 0;

	rating = "";
	duration = 0;
}

Filme::~Filme()
{
}

int Filme::einlesen(string line, set <string>& allcategories, string &errorcorrection)
{
	bool		inQutation = 0; //ob der Text derzeit in Anführungszeichen ist
	string		sTemp; //temp String
	string		number; //der Xte Titel
	vector <string> Daten;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '"')
		{
			inQutation = !inQutation;
		}
		else if ((line[i] == ',') && !inQutation) //bei Kommas, die nicht zw. Anführungszeichen stehen wird der String gepusht
		{
			Daten.push_back(sTemp);
			sTemp = "";
		}
		else
		{
			sTemp = sTemp + line[i];
		}
	}
	Daten.push_back(sTemp);


	if (Daten.size() < 12)
	{
		errorcorrection = line;
		if (Daten.size() == 1)
		{
			return(-1);
		}
		return(-2);
	}
	else
	{
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

		title = Daten[2];
		director = Daten[3];
		actors = read_set(Daten[4]);
		country = Daten[5];
		if (date_added.read_date(Daten[6]))
		{
			cout << Daten[0] << ", " << Daten[2] << endl;
		}
		release = stringToInt(Daten[7]);
		rating = Daten[8];
		sTemp = "";
		for (int i = 0; i < Daten[9].size(); i++)
		{
			if (Daten[9][i] == ' ')
			{
				break;
			}
			else
			{
				sTemp = sTemp + Daten[9][i];
			}
		}
		duration = stringToInt(sTemp);
		categories = read_set(Daten[10]);
		description = Daten[11];

		allcategories.insert(categories.begin(), categories.end());
	}





	/*
#if debugging
	cout << Daten[0] << endl;
	for (auto i : categories)
	{
		cout << i << "__";
	}
	cout << endl;
	for (auto i : allcategories)
	{
		cout << i << "__";
	}
	cout << endl;
	Sleep(1000);
#endif // debugging
*/
	return(0);
}

string Filme::get_description()
{
	return(description);
}

int Filme::set_description(string setter)
{
	description = setter;
	return(0);
}

set <string> read_set(string inString)
{
	bool aftercomma = false; // Variable, ob grade ein Komma kam
	set <string> stringset;
	string sTemp1;
	for (int i = 0; i < inString.size(); i++)
	{

		if (inString[i] == ',')
		{
			stringset.insert(sTemp1);
			sTemp1 = "";
			aftercomma = true;
		}
		else if (aftercomma) // nach einem Komma sollte das Leerzeichen ignoriert werden und zählt nicht zum Wort
		{
			aftercomma = false;
		}
		else
		{
			sTemp1 = sTemp1 + inString[i];
		}
	}
	stringset.insert(sTemp1);
	return(stringset);
}

int date::read_date(string inString)
{
	if (inString != "")
	{
		vector <string> Datums;
		string string;
		for (int i = 0; i < inString.size(); i++)
		{
			if (inString[i] == ' ' || inString[i] == ',')
			{
				if (string != "")
				{
					Datums.push_back(string);
					string = "";
				}
			}
			else
			{
				string = string + inString[i];
			}
		}
		Datums.push_back(string);


		if (Datums[0] == "January")
		{
			month = 1;
		}
		else if (Datums[0] == "February")
		{
			month = 2;
		}
		else if (Datums[0] == "March")
		{
			month = 3;
		}
		else if (Datums[0] == "April")
		{
			month = 4;
		}
		else if (Datums[0] == "May")
		{
			month = 5;
		}
		else if (Datums[0] == "June")
		{
			month = 6;
		}
		else if (Datums[0] == "July")
		{
			month = 7;
		}
		else if (Datums[0] == "August")
		{
			month = 8;
		}
		else if (Datums[0] == "September")
		{
			month = 9;
		}
		else if (Datums[0] == "October")
		{
			month = 10;
		}
		else if (Datums[0] == "November")
		{
			month = 11;
		}
		else if (Datums[0] == "December")
		{
			month = 12;
		}
		else
		{
			cout << "Der Monat ist " << Datums[0] << "; konnte nicht gelesen werden bei Titel ";
			return(-1);
		}
		//Januar
		//Febuar
		//März
		//April
		//Juni
		//Juli
		//August
		//September
		//Oktober
		//November
		//Dezember

		day = stringToInt(Datums[1]);
		if (day < 1 || day > 31)
		{
			cout << "Tag im Monat ist " << Datums[1] << "; wurde als " << day << " gelesen werden bei Titel ";
			return(-1);
		}

		year = stringToInt(Datums[2]);
		if (year < 1878/*Erster Film*/)
		{
			cout << "Jahr ist " << Datums[2] << "; konnte nicht gelesen werden bei Titel ";
			return(-1);
		}
	}

	return(0);
}

int date::cout_date()
{
	cout << day << '.' << month << '.' << year;
	return(0);
}

int stringToInt(string inString)
{
	int temp = 0;
	for (int i = 0; i < inString.size(); i++)
	{ // wenn es eine weitere Stelle gibt werden die bisherigen 1 Stelle nach links verschoben, also * 10 genommen und die neue wird addiert
		if (inString[i] < '0' || inString[i] > '9')
		{
			cout << "Fehler in stringToInt: Der String " << inString << "enthält Zeichen, die keine Ziffern sind" << endl;
			return(-1);// wird bei checks abgefragt, weil nur positive Zahlen rauskommen können
		}
		else
		{
			temp = temp * 10 + (inString[i] - '0');
		}
	}
	return(temp);
}

/*to do:
*categories, Länder, Schauspieler vielleicht auch richtig speichern / indexen
*Felermeldung / Hinweise beim Einlesen
*Vergleichsdingens für date schreiben
*Menue
*	Schauspieler
*	Direktor
*	Ketegorien (vllt mehrere)
*	zw Datum x und y
* 
*Funktionen unter Klasses definieren
* Klassen mit Strichen trennen
* Kommentare schreiben (deutsch)
* Variabelnamen englisch oder Deutsch machen
* Funktionen sortieren, damit man sie oben nicht 2 mal definieren muss
*/
int main()
{
	vector <Filme> Sammlung;
	string errorcorrection;
	set <string> allcategories;
	fstream Datei;
	Datei.open("netflix_titles.csv", ios::in); //öffnet eine Datei um sie zu lesen
	if (!Datei.is_open())
	{
		cout << "Fehler beim Öffnen" << endl;
	}
	else
	{
		string line;
		getline(Datei, line); // ignoriert die 1. Zeile
		while (getline(Datei, line))
		{// kopiert und modifiziert von https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c (1. Antwort)
			Filme Ftemp;

			switch (Ftemp.einlesen(line, allcategories, errorcorrection))
			{
			case 0:
				break;
			case -1:
				Sammlung[Sammlung.size() - 1].set_description(Sammlung[Sammlung.size() - 1].get_description() + errorcorrection);
#if debugging
				cout << "Bei s" << Sammlung.size() << " ist die Beschreibung" << Sammlung[Sammlung.size() - 1].get_description() << endl << endl;
#endif // debugging
				break;
			case -2:
				getline(Datei, line);
				Ftemp.einlesen((errorcorrection + " "/*Leerzeichen wird durch Zeilenumbruch korrumpiert*/ + line), allcategories, errorcorrection);
#if debugging
				cout << "Bei s" << Sammlung.size() << " ist die Zeile " << (errorcorrection + " " + line) << endl << endl;
#endif // debugging
				break;
			default:
				cout << "Ftemp.einlesen hat ungültiger errorcode erzeugt bei: " << endl << line << endl;
				break;
			}
			
			Sammlung.push_back(Ftemp);
		}
		Datei.close();
	}

	cout << "\033[2J\033[1;1H"; // kopiert von https://stackoverflow.com/questions/17335816/clear-screen-using-c (1. Antwort)



	for (auto i : allcategories)
	{
		cout << i << endl;
	}

}