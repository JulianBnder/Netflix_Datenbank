#define debugging 1
#define debugging_old 0
#define clearscreen cout << "\033[2J\033[1;1H"

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
using std::cout;



set <string> read_set(string inString)
{
	bool aftercomma = false; // Variable, ob grade ein Komma kam
	set <string> stringset;
	string sTemp1;
	for (unsigned int i = 0; i < inString.size(); i++)
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

int stringToInt(string inString)
{
	int temp = 0;
	for (unsigned int i = 0; i < inString.size(); i++)
	{ // wenn es eine weitere Stelle gibt werden die bisherigen 1 Stelle nach links verschoben, also * 10 genommen und die neue wird addiert
		if (inString[i] < '0' || inString[i] > '9')
		{
			cout << "Fehler in stringToInt: Der String " << inString << "enthält Zeichen, die keine Ziffern sind" << endl;
			return -1;// wird bei checks abgefragt, weil nur positive Zahlen rauskommen können
		}
		else
		{
			temp = temp * 10 + (inString[i] - '0');
		}
	}
	return(temp);
}

//date-----------------------------------------------------------------------------------------------------------------------------------------------

class date
{
public:
	date();
	~date();

	int read_date(string inString);
	int set_date(int dayIn, int monthIn, int yearIn);

	bool operator< (const date& date2) const; // von https://www.tutorialsdate.com/cplusplus/cpp_overloading.htm 

	// von https://docs.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-160
	date& operator++();       // für die for-Schleife bei der Datums-suche
	date operator++(int);     // für komplettheit

	date& operator--();       // für komplettheit
	date operator--(int);     // für komplettheit

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


int date::read_date(string inString)
{
	if (inString != "")
	{
		vector <string> Datums;
		string string_date;
		for (unsigned int i = 0; i < inString.size(); i++)
		{
			if (inString[i] == ' ' || inString[i] == ',')
			{
				if (string_date != "")
				{
					Datums.push_back(string_date);
					string_date = "";
				}
			}
			else
			{
				string_date = string_date + inString[i];
			}
		}
		Datums.push_back(string_date);


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
			return -1;
		}

		day = stringToInt(Datums[1]);
		if (day < 1 || day > 31)
		{
#if debugging_old
			cout << "Tag im Monat ist " << Datums[1] << "; wurde als " << day << " gelesen werden bei Titel ";
#endif // debugging
			return -1;
		}

		year = stringToInt(Datums[2]);
		if (year < 1878/*Erster Film*/)
		{
#if debugging_old
			cout << "Jahr ist " << Datums[2] << "; konnte nicht gelesen werden bei Titel ";
#endif // debugging
			return -1;
		}
	}

	return 0;
}

int date::set_date(int dayIn, int monthIn, int yearIn)
{
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1878/*Erster Film*/)
	{
		return -1;
	}
	day = dayIn;
	month = monthIn;
	year = yearIn;
	return (0);
}


bool date::operator< (const date& date2) const // von https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
{
	if (this->year < date2.year)
	{ // wenn das Jahr kleiner ist, ist das Datum kleiner
		return true;
	}
	else if ((this->year == date2.year) && (this->month < date2.month))
	{ // wenn das Jahr gleich und der Monat kleiner ist, ist das Datum kleiner
		return true;
	}
	else if ((this->year == date2.year) && (this->month == date2.month) && (this->day < date2.day))
	{ // wenn das Jahr und Monat gleich sind und der Tag kleiner ist, ist das Datum kleiner
		return true;
	}
	else
	{ // sonst sind sie gleich oder größer
		return false;
	}

}

date& date::operator++()       // für die for-Schleife bei der Datums-suche
{
	day++;
	if (day > 31) // Monate mit 30 Tagen sind egal, es passiert nichts, wenn nach Tagen gesucht wird, die nicht existieren
	{
		month++;
		day = 1;
	}
	if (month > 12)
	{
		year++;
		month = 1;
	}
	return *this;
}

date date::operator++(int)     // für komplettheit
{
	date temp = *this;
	++* this;
	return temp;
}

date& date::operator--()     // für komplettheit
{
	day--;
	if (day < 1)
	{
		month--;
		day = 31; // Monate mit 30 Tagen sind egal, es passiert nichts, wenn nach Tagen gesucht wird, die nicht existieren
	}
	if (month < 1)
	{
		year--;
		month = 12;
	}
	return *this;
}

date date::operator--(int)     // für komplettheit
{
	date temp = *this;
	--* this;
	return temp;
}


//Filme----------------------------------------------------------------------------------------------------------------------------------------------

class Filme
{
public:
	Filme();
	~Filme();

	int einlesen(string line, string& errorcorrection);

	int set_description(string setter);

	bool get_isMovie();
	string get_title();
	set <string> get_directors();
	set <string> get_actors();
	date get_date_added();
	int get_release();
	set <string> get_categories();
	string get_description();

private:
	bool isMovie;

	string title;
	set <string> directors;
	set <string> countries;
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
	isMovie = false;
	release = 0;
	duration = 0;

	title = "uninitialised";
	rating = "uninitialised";
	description = "uninitialised";
}

Filme::~Filme()
{
}


int Filme::einlesen(string line, string& errorcorrection)
{
	bool		inQutation = false; //ob der Text derzeit in Anführungszeichen ist
	string		sTemp; //temp String
	vector <string> Daten;
	for (unsigned int i = 0; i < line.size(); i++)
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


	if (Daten.size() != 12)
	{
		errorcorrection = line;
		if (Daten.size() == 1)
		{
			return -1;
		}
		return -2;
	}
	else
	{

		if (Daten[1] == "Movie")
		{
			isMovie = true;
		}
		else if (Daten[1] == "TV Show")
		{
			isMovie = false;
		}
#if debugging_old
		else
		{
			cout << Daten[0] << ": " << "type is" << Daten[1] << endl;
		}
#endif // debugging

		title = Daten[2];
		directors = read_set(Daten[3]);
		actors = read_set(Daten[4]);
		countries = read_set(Daten[5]);
		date_added.read_date(Daten[6]);
		release = stringToInt(Daten[7]);
		rating = Daten[8];
		sTemp = "";
		for (unsigned int i = 0; i < Daten[9].size(); i++)
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
	}


#if debugging_old
	cout << Daten[0];
	cout << country;
	cout << endl;
	Sleep(100);
#endif // debugging

	return 0;
}


int Filme::set_description(string setter)
{
	description = setter;
	return 0;
}


bool Filme::get_isMovie()
{
	return(isMovie);
}

string Filme::get_title()
{
	return(title);
}

set <string> Filme::get_directors()
{
	return(directors);
}

set <string> Filme::get_actors()
{
	return(actors);
}

date Filme::get_date_added()
{
	return(date_added);
}

int Filme::get_release()
{
	return release;
}

set <string> Filme::get_categories()
{
	return(categories);
}

string Filme::get_description()
{
	return(description);
}

//Funktionen ohne Klasse-----------------------------------------------------------------------------------------------------------------------------

set <int> search_index(map<string, set <int> >& index_things, string suchwert)
{
	set <int> ergebnisse;
	if (index_things.count(suchwert))
	{
		for (auto number : index_things.find(suchwert)->second)
		{
			ergebnisse.insert(number);
		}
	}
	return(ergebnisse);
}

//main-----------------------------------------------------------------------------------------------------------------------------------------------
/*to do:
*
* Datumseinlesefunktion reparieren (cin schein nicht zu funktionieren, suchwert ist anscheinend	 nur "January" und nicht "January 1, 2000") https://www.geeksforgeeks.org/cin-in-c/
* andere Suchfunktionen ausprobieren
* es gibt Index für date_added and release, man sollte noch nach release sortieren können
*
* Kommentare schreiben (deutsch oder englisch), die Elementnamen in for loops muss man noch anpassen
* Variabelnamen englisch oder Deutsch machen
* Wenn das Erscheinungsjahr gefragt ist, kann man einfach ints benutzen statt dates lol, vielleicht können wir dann nach auf_Netflix_ab sortieren
*
* vielleicht das Indexen noch debuggen, damit es sicher funktioniert
*
* das "verfügbare Titel wegmachen und bei jeder Option sagen, was es ist, also "verfügbare " << suchwert;
* beim Indexen vielleicht (auto element : Sammlung) statt normalem for loop machen, damit es leserlicher ist, wenn man die Zahl vom Film rausbekommen kann
* Bei den Filmen die Informationen geben (nur wenn sie existieren) (rating, verfügbare Länder, Dauer, hochladedatum)
* Vielleicht an googlesuche zu dem Titel weiterleiten, den man raussucht
* 
*/
int main()
{
	string line;
	vector <Filme> Sammlung;
	string errorCorrection;
	fstream Datei;

	set <int> setWithI; // für die Indexe, enthält immer nur die Nummer des aktuellen Titels
	map <string, int> index_name;
	map <int, set <int > > index_release;
	map <date, set <int> > index_date_added;
	map<string, set <int> > index_categories;
	map<string, set <int> > index_actors;
	map<string, set <int> > index_directors;

	int eingabe = 0;
	int i = 0; // Iterator für Kategorienauswahl
	string suchwert = "";
	int datum_eingabe[3];
	date dateMin, dateMax;
	bool abbruchbedingung = false;
	bool input_worked = false;
	bool moviesAndSeries = false;
	bool isMovie = false;
	set <int> ergebnisse;


	Datei.open("netflix_titles.csv", ios::in); //öffnet eine Datei um sie zu lesen
	if (!Datei.is_open())
	{
		cout << "Fehler beim Öffnen" << endl;
	}
	else
	{
		getline(Datei, line); // ignoriert die 1. Zeile
		while (getline(Datei, line))
		{// kopiert und modifiziert von https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c (1. Antwort)
			Filme Ftemp;

			switch (Ftemp.einlesen(line, errorCorrection))
			{
			case 0:
				Sammlung.push_back(Ftemp);
				break;
			case -1:
				Sammlung[Sammlung.size() - 1].set_description(Sammlung[Sammlung.size() - 1].get_description() + errorCorrection);
#if debugging_old
				cout << "Bei s" << Sammlung.size() << " ist die Beschreibung" << Sammlung[Sammlung.size() - 1].get_description() << endl << endl;
#endif // debugging
				break;
			case -2:
				getline(Datei, line);
				Ftemp.einlesen((errorCorrection + " "/*Leerzeichen wird durch Zeilenumbruch korrumpiert*/ + line), errorCorrection);
				Sammlung.push_back(Ftemp);
#if debugging_old
				cout << "Bei s" << Sammlung.size() << " ist die Zeile " << (errorCorrection + " " + line) << endl << endl;
#endif // debugging
				break;
			default:
				cout << "Ftemp.einlesen hat ungueltiger errorcode erzeugt bei: " << endl << line << endl;
				break;
			}

		}
		Datei.close();
	}

	for (unsigned int i = 0; i < Sammlung.size(); i++)
	{
		setWithI.insert(i);

		// macht bei jedem Titel der/der Titel zur category / actor / director, die relevant sind
		// , damit man alle Filme/Serien die relevant sind schnell findet
		for (auto category : Sammlung[i].get_categories()) // geht alle categories von Titel durch
		{
			if (index_categories.count(category)) // wenn die category schon vorhanden ist
			{
				index_categories.find(category)->second.insert(i); // füge dem Set von Titeln dieser category diesen Titel hinzu
			}
			else // sonst
			{
				index_categories.insert({ category, setWithI }); // mache eine map mit der category und einem Set mit diesem Titel
			}
		}
		for (auto actor : Sammlung[i].get_actors())
		{
			if (index_actors.count(actor))
			{
				index_actors.find(actor)->second.insert(i);
			}
			else
			{
				index_actors.insert({ actor, setWithI });
			}
		}
		for (auto director : Sammlung[i].get_directors())
		{
			if (index_directors.count(director))
			{
				index_directors.find(director)->second.insert(i);
			}
			else
			{
				index_directors.insert({ director, setWithI });
			}
		}
		if (index_date_added.count(Sammlung[i].get_date_added()))
		{
			index_date_added.find(Sammlung[i].get_date_added())->second.insert(i);
		}
		else
		{
			index_date_added.insert({ Sammlung[i].get_date_added(), setWithI });
		}
		if (index_release.count(Sammlung[i].get_release()))
		{
			index_release.find(Sammlung[i].get_release())->second.insert(i);
		}
		else
		{
			index_release.insert({ Sammlung[i].get_release(), setWithI });
		}

#if debugging_old //um zu testen, ob es Namen 2 mal gibt, dann hätte man set <int> für index_name nemen müssen statt int
		if (index_name.count(Sammlung[i].get_title()))
		{
			cout << "Folgenden Titel gibt es 2 mal: " << Sammlung[i].get_title() << endl;
		}
#endif // debugging

		index_name.insert({ Sammlung[i].get_title(), i });

		setWithI.erase(i);
	}

	while (abbruchbedingung == false)
	{
		clearscreen; // kopiert von https://stackoverflow.com/questions/17335816/clear-screen-using-c (1. Antwort)
		while (eingabe == 0)
		{
			cout << "Moechten Sie Filme(1) , Serien(2) oder beides(3) schauen?" << endl << endl;
			cin >> eingabe;
			switch (eingabe)
			{
			case 1:
				isMovie = true;
				break;
			case 2:
				// ist die Grundeinstellung
				break;
			case 3:
				moviesAndSeries = true;
				break;
			default:
				cout << "ungueltiger Eingabewert, bitte eine Zahl zw. 1 und 3 eingeben." << endl << endl;
				eingabe = 0;
				break;
			}
		}
		eingabe = 0; // resetten
		clearscreen;

		while (eingabe == 0) //Suchkriterium wählen, dannach ist eingabe >= 1 und <= 5
		{
			cout << "Wie moechten Sie nach ";
			if (isMovie || moviesAndSeries)
			{
				cout << "Filme";
			}
			if (moviesAndSeries)
			{
				cout << " und ";
			}
			if (!isMovie || moviesAndSeries)
			{
				cout << "Serien";
			}
			cout << " suchen?" << endl << endl;

			cout << "1 Titel" << endl;
			cout << "2 DirektorIn" << endl;
			cout << "3 SchauspielerIn" << endl;
			cout << "4 Kategorie" << endl;
			cout << "5 Erscheinungsdatum" << endl << endl;
			cin >> eingabe;
			if (eingabe < 1 || eingabe > 5)
			{
				eingabe = 0;
				cout << "ungueltiger Eingabewert, bitte eine Zahl zw. 1 und 5 eingeben." << endl << endl;
			}
		}

		clearscreen;
		switch (eingabe)
		{
		case 1:
			cout << "Bitte Titel eingeben" << endl << endl;
			cin >> suchwert;
			if (index_name.count(suchwert))
			{
				ergebnisse.insert(index_name.find(suchwert)->second);
			}
			break;
		case 2:
			cout << "Bitte DirectorIn eingeben" << endl << endl;
			cin >> suchwert;
			ergebnisse = search_index(index_directors, suchwert);
			break;
		case 3:
			cout << "Bitte SchauspielerIn eingeben" << endl << endl;
			cin >> suchwert;
			ergebnisse = search_index(index_actors, suchwert);
			break;
		case 4:
			cout << "Um eine Kategorie zu wählen bitte Zahl eingeben:" << endl;
			for (auto category : index_categories)
			{
				i++; // zeigt eine Zahl  von jeder Kategorie, muss manuell sein, weil man mit einem normalen for-loop nicht durch ma iterieren kann
				if ( i < 10)
				{
					cout << " ";
				}
				cout << i << ": " << category.first << endl;
				Sleep(50); //weils cool ausshieht
			}
			cout << endl;
			while (!input_worked)
			{
				cin >> i;
				if (i < 1 || i > index_categories.size()) // i muss innerhalb der Grösse der map sein
				{
					cout << endl << "ungueltiger Eingabewert, bitte eine Zahl zw. 1 und " << index_categories.size() << " eingeben." << endl << endl;
					//testen, ob es klappt wenn man die höchste Zahl und die eins drüber eingibt
				}
				else
				{
					input_worked = true;
				}
			}
			input_worked = false; //resetten
			for (auto category : index_categories)
			{
				i--; // bei dem Wert, der bei der Kategorie stand, wird die Kategorie eingelesen
				if (i == 0)
				{
					suchwert = category.first;
				}
			}
			i = 0; // resetten
			ergebnisse = search_index(index_categories, suchwert);
			break;
		case 5:
			while (!input_worked)
			{
				input_worked = true;
				cout << "Bitte Zeitramen in folgendem Format eingeben und jeweils 3 mal Enter drücken:" << endl;
				cout << "dd mm yyyyy" << endl;
				cout << "dd mm yyyyy" << endl << endl;
				cin >> datum_eingabe[0] >> datum_eingabe[1] >> datum_eingabe[2];
				if (dateMin.set_date(datum_eingabe[0], datum_eingabe[1], datum_eingabe[2]))
				{
					input_worked = 0;
					cout << endl << endl << "eingabeformat fehlerhaft, bitte nochmal versuchen" << endl << endl;
				}
#if debugging
				cout << "Datum wird interpretiert als " << datum_eingabe[0] << ". " << datum_eingabe[1] << ". " << datum_eingabe[2] << endl;
#endif // debugging
				cin >> datum_eingabe[0] >> datum_eingabe[1] >> datum_eingabe[2];
				if (dateMax.set_date(datum_eingabe[0], datum_eingabe[1], datum_eingabe[2]))
				{
					input_worked = 0;
					cout << endl << endl << "Eingabeformat fehlerhaft, bitte nochmal versuchen" << endl << endl;
				}
#if debugging
				cout << "Datum wird interpretiert als " << datum_eingabe[0] << ". " << datum_eingabe[1] << ". " << datum_eingabe[2] << endl;
#endif // debugging
			}

			dateMax++;
			for (date i = dateMin; i < dateMax; i++)
			{
				if (index_date_added.count(i))
				{
					for (auto title : index_date_added.find(i)->second)
					{
						ergebnisse.insert(title);
					}
				}
			}
			break;
		default:
			break;
		}
		eingabe = 0;
		if (ergebnisse.size() == 0)
		{
			cout << "Keine Ergebnisse gefunden" << endl << endl;
		}
		else
		{
			cout << "verfuegbare Titel: " << endl;
			for (auto number : ergebnisse)
			{
				if (moviesAndSeries || Sammlung[number].get_isMovie() == isMovie)
				{
					cout << Sammlung[number].get_title() << endl;
				}
			}
		}

		while (eingabe == 0)
		{
			cout << endl << "Wollen Sie noch nach etwas anderem suchen?" << endl;
			cout << "Ja(1) oder Nein(2)" << endl << endl;
			cin >> eingabe;
			switch (eingabe)
			{
			case 1:
				clearscreen;
				suchwert = "";
				dateMin.set_date(0, 0, 0);
				dateMax.set_date(0, 0, 0);
				abbruchbedingung = false;
				input_worked = 0;
				moviesAndSeries = false;
				isMovie = false;
				ergebnisse.clear();
				break;
			case 2:
				abbruchbedingung = true;
				break;
			default:
				eingabe = 0;
				cout << "ungueltiger Eingabewert, bitte 1 oder 2 eingeben." << endl << endl;
				break;
			}
		}
		eingabe = 0;
	}
}
