#define extra_feature true

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
using std::cout; // manchmal kam der Fehler cout is ambiguous

//Funktionen-ohne------------------------------------------------------------------------------------------------------------------------------------

// bekommt ein Sting mit Kommas und gibt die Sachen zwischen den Kommas getrennt als Set zurück
set <string> read_set(string inString)
{
	bool aftercomma = false; // Variable, ob grade ein Komma kam
	set <string> stringset;
	string sTemp;
	for (unsigned int i = 0; i < inString.size(); i++)
	{
		if (inString[i] == ',') // bei einem Komma wird das, was bisher kopiert wurde gespeichert, der Sting geleert und aftercomma auf true gesetzt
		{
			stringset.insert(sTemp);
			sTemp = "";
			aftercomma = true;
		}
		else if (aftercomma) // nach einem Komma sollte das Leerzeichen ignoriert werden und zählt nicht zum Wort
		{
			aftercomma = false;
		}
		else
		{
			sTemp = sTemp + inString[i]; // wenn es kein Komma oder direkt nach einem Komma ist wird es kopiert
		}
	}
	stringset.insert(sTemp); //am Ende kommt kein Komma wenn der große String aufhört => man muss nochmal das kopierte speichern
	return(stringset);
}

// konvertiert ein String mit Ziffern in eine gnaze Zahl
int stringToInt(string inString)
{
	int temp = 0;
	for (unsigned int i = 0; i < inString.size(); i++) // geht den String durch
	{
		// wenn es eine weitere Stelle gibt werden die bisherigen 1 Stelle nach links verschoben, also * 10 genommen und die neue wird addiert
		if (inString[i] < '0' || inString[i] > '9')
		{
			cout << "Fehler in stringToInt: Der String " << inString << "enthält Zeichen, die keine Ziffern sind" << endl;
			return -1;// wird bei checks abgefragt, weil nur positive Zahlen rauskommen können
		}
		else
		{
			temp = temp * 10 + (inString[i] - '0'); // den Wert als Ziffer eines chars bekommt man, wenn man den Wert von '0' abzieht
		}
	}
	return(temp);
}

//durchsucht einen Index, also eine map nach dem Suchwort und gibt das dazugehörige Set von ints (also Speicherstellen v. Filmen) zurück
set <int> search_index(map<string, set <int> >& index_things, string search_val)
{
	set <int> Ergebnise;
	// wenn der Suchwert existiert, wird das set kopiert, wenn es nicht existieren 
	// würde und man würde versuchen es abzufragen gäbe es einen illegalen Speicherplatzzegriff
	if (index_things.count(search_val))
	{
		Ergebnise = index_things.find(search_val)->second;
	}
	return(Ergebnise);
}

//date-----------------------------------------------------------------------------------------------------------------------------------------------

class date
{
public:
	date();
	~date();

	int set_date(int dayIn, int monthIn, int yearIn);

	int read_date(string inString); // liest ein Datum im Format in der .csv Datein ein
	string get_date_as_string(); // gibt das Datum als String aus

	// für die for Schleife in der Datums-suche
	bool operator< (const date& date2) const; // von https://www.tutorialsdate.com/cplusplus/cpp_overloading.htm

	// von https://docs.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-160
	date& operator++();       // für die for-Schleife bei der Datums-suche
	date operator++(int);     // für komplettheit

	date& operator--();       // für komplettheit
	date operator--(int);     // für komplettheit

private:
	// Nummern sind Menschenlesbar, zählen also von 1
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

// liest ein Datum im Format in der .csv Datein ein
int date::read_date(string inString)
{
	// wenn der String leer ist wird er nicht verarbeitet, um weniger Anfwand zu haben
	if (inString == "")
	{
		return -1;
	}
	else
	{
		string date_string; // ein Datumsbestandteil z.B. "January" "21" und "2004"
		vector <string> date_vector; //Vektor mit den Datumsbestandteilen, [1] ist month, [2] ist day, [3] ist year
		// für genauere Erklärung der for Schleife siehe in films::read_in()
		for (unsigned int i = 0; i < inString.size(); i++)
		{

			if (inString[i] == ' ') // Datumsbestandteile werden von Leerzeichen getrennt
			{
				date_vector.push_back(date_string);
				date_string = "";
			}
			else if (inString[i] == ',') // Nach dem Tag kommt immer ein Komma, das aussortiert wird
			{
			}
			else // alle anderen Zeichen gehören zu einem Datumsbestandteil
			{
				date_string = date_string + inString[i];
			}
		}
		date_vector.push_back(date_string); // am ende kommt kein Leerzeichen, deshalb muss nochmal so gepush werden

		//ist kein switch-case, weil das nur mit int, char und ähnlichen Variabeltypen möglich ist
		if (date_vector[0] == "January")
		{
			month = 1;
		}
		else if (date_vector[0] == "February")
		{
			month = 2;
		}
		else if (date_vector[0] == "March")
		{
			month = 3;
		}
		else if (date_vector[0] == "April")
		{
			month = 4;
		}
		else if (date_vector[0] == "May")
		{
			month = 5;
		}
		else if (date_vector[0] == "June")
		{
			month = 6;
		}
		else if (date_vector[0] == "July")
		{
			month = 7;
		}
		else if (date_vector[0] == "August")
		{
			month = 8;
		}
		else if (date_vector[0] == "September")
		{
			month = 9;
		}
		else if (date_vector[0] == "October")
		{
			month = 10;
		}
		else if (date_vector[0] == "November")
		{
			month = 11;
		}
		else if (date_vector[0] == "December")
		{
			month = 12;
		}
		else
		{
			return -1;
		}

		day = stringToInt(date_vector[1]);
		if (day < 1 || day > 31)
		{
			return -1;
		}
		year = stringToInt(date_vector[2]);
		if (year < 1878/*Erster Film*/)
		{
			return -1;
		}
	}

	return 0;
}


int date::set_date(int dayIn, int monthIn, int yearIn)
{
	day = dayIn;
	month = monthIn;
	year = yearIn;
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1878/*Erster Film*/)
	{
		return -1;
	}
	return (0);
}

// gibt das Datum als String zurück, z.B: "13.12.1969"
string date::get_date_as_string()
{
	return(to_string(day) + ". " + to_string(month) + ". " + to_string(year));
}

// für die for-Schleife bei der Datums-suche
bool date::operator< (const date& date2) const // von https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
{
	// wenn das Jahr kleiner ist, ist das Datum kleiner
	if (this->year < date2.year)
	{
		return true;
	}
	// wenn das Jahr gleich und der Monat kleiner ist, ist das Datum kleiner
	else if ((this->year == date2.year) && (this->month < date2.month))
	{
		return true;
	}
	// wenn das Jahr und Monat gleich sind und der Tag kleiner ist, ist das Datum kleiner
	else if ((this->year == date2.year) && (this->month == date2.month) && (this->day < date2.day))
	{
		return true;
	}
	// sonst ist es gleich oder größer
	else
	{
		return false;
	}
}

// für die for-Schleife bei der Datums-suche
date& date::operator++()
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

// für komplettheit
date date::operator++(int)
{
	date temp = *this;
	++* this; // erhöht temp mit x++ operator
	return temp;
}

// für komplettheit
date& date::operator--()
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

// für komplettheit
date date::operator--(int)
{
	date temp = *this;
	--* this; // erhöht temp mit x++ operator
	return temp;
}

//films----------------------------------------------------------------------------------------------------------------------------------------------

// speichert alle Daten zu jeweils einem Film
class film
{
public:
	film();
	~film();

	int read_in(string line, string& errorcorrection); //liest die Daten eines Filmes von einer Zeile in der .csv Datei ein

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
	bool isMovie; // ob es ein Film ist oder eine Serie

	string title;
	set <string> directors;
	set <string> countries; //Länder in denen der Film verfügbar ist
	string description;

	set <string> actors;
	set <string> categories;

	date date_added; // das Datum an dem der Film auf Netflix kam
	int release; // Veröffentlichungsdatum

	string rating; //Altersbeschränkung
	int duration; //in Minuten bei Filmen, in Staffeln bei Serien
};

film::film()
{
	isMovie = false;
	release = 0;
	duration = 0;

	title = "uninitialised";
	rating = "uninitialised";
	description = "uninitialised";
}

film::~film()
{
}

// liest einen Film aus einer Zeile in der .csv Datein ein
int film::read_in(string line, string& errorcorrection)
{
	bool		inQutation = false; // ob der Text derzeit in Anführungszeichen ist
	string		sTemp; // temp String
	vector <string> Film_data; // Vektor für alle Daten zu einem Film als Strings (z.B: "[DirektorInnen]","[Dauer]" also "95" u.s.w.)

	//geht die Zeile durch und teilt sie in Daten auf
	for (unsigned int i = 0; i < line.size(); i++)
	{
		// Kommas innerhalb eines Datenpunktes (z.B. SchauspielerInnen) sollen nicht als Trennung zw. 
		// Daten gewertet werden. Deshalb wird am Anfang bei den Anführungzeichen eine Variable gesetzt, 
		// damit sie nicht gezählt werden, die am Ende der Anführungzeichen wieder zurückgesetzt wird
		if (line[i] == '"')
		{
			inQutation = !inQutation; // bei Anführungzeichen wird die Variable negiert, also auch nicht mitkopiert
		}
		else if ((line[i] == ',') && !inQutation) //bei Kommas, die nicht zw. Anführungszeichen stehen wird der String gepusht
		{
			//wenn ein Kommma kommt, das Daten trennt wird der jetztige Datenpunkt in den Vektor gepusht und der String für die Daten wird geleert
			Film_data.push_back(sTemp);
			sTemp = "";
		}
		else
		{
			sTemp = sTemp + line[i]; // ansonsten wird das char in String gespeichert
		}
	}
	Film_data.push_back(sTemp); // am Ende kommt kein Komma => Man muss nochmal den Datenpunk in den Vektor pushen

	// wenn keine 12 Datenpunkte gelesesn wurden ist die Zeile korumpiert
	if (Film_data.size() != 12)
	{
		errorcorrection = line; //Zeile wird für Weiterverarbeitung gespeichert, 
		// wenn es nur ein Datenpunkt ist muss die Zeile davor 12 Datenpunkte haben, d.h. die Beschreibung ist unvollsändig
		if (Film_data.size() == 1)
		{
			return -1;
		}
		// ansonsten merkt man es in der 1. Korrumpierten Zeile und fügt dann die nächste an
		return -2;
	}
	else //sonst kann sie normal verarbeitet werden
	{
		if (Film_data[1] == "Movie")
		{
			isMovie = true;
		}

		title = Film_data[2];
		directors = read_set(Film_data[3]);
		actors = read_set(Film_data[4]);
		countries = read_set(Film_data[5]);
		date_added.read_date(Film_data[6]);
		release = stringToInt(Film_data[7]);
		rating = Film_data[8];

		//film_data[9] also die Dauer hat das Format "[minuten] min" oder "[Staffelanzahl] Seasons" 
		// => man muss nur die Zahl speichern, weil Film_data[0] speichert, ob es ein Film oder Serie ist 
		sTemp = "";
		for (unsigned int i = 0; i < Film_data[9].size(); i++)
		{
			if (Film_data[9][i] == ' ')
			{
				break;
			}
			else
			{
				sTemp = sTemp + Film_data[9][i];
			}
		}
		duration = stringToInt(sTemp);

		categories = read_set(Film_data[10]);
		description = Film_data[11];
	}
	return 0;
}

int film::set_description(string setter)
{
	description = setter;
	return 0;
}

bool film::get_isMovie()
{
	return(isMovie);
}

string film::get_title()
{
	return(title);
}

set <string> film::get_directors()
{
	return(directors);
}

set <string> film::get_actors()
{
	return(actors);
}

date film::get_date_added()
{
	return(date_added);
}

int film::get_release()
{
	return release;
}

set <string> film::get_categories()
{
	return(categories);
}

string film::get_description()
{
	return(description);
}

//main-----------------------------------------------------------------------------------------------------------------------------------------------

// liest erst die .csv Datein ein, indexiert sie dann mit verschiedenen 
// Schlüsseln und erlaubt dem User dann die Datenbankzu durchsuchen
int main()
{
	// Variabeln für das Einlesen und speichern der Filme
	string line = ""; //eine Zeile in der Datei
	vector <film> collection; // Vektor für Filme
	string errorCorrection = ""; // String, um korrumpierte Zeilen zu speichern
	fstream file; // inputstream für die Datei

	// Variabeln für die Indizes, jeweils benannt nach dem Schlüssel
	set <int> setWithI; // für die Indexe, enthält immer nur die Nummer des aktuellen Titels
	map <string, int> index_title;
	map <int, set <int > > index_release;
	map <date, set <int> > index_date_added;
	map<string, set <int> > index_categories;
	map<string, set <int> > index_actors;
	map<string, set <int> > index_directors;

	// Variablen für Kontrollfluss in der UI
	int input = 0; // entscheidet, nach was gesucht wird, also ob nach SchauspielerInnen, Titel oder Datum z.B.
	bool retake_search = true; // Kontrollfluss, ob die Suche (nochmal) gestartet werden soll
	bool input_worked = false;

	//Variabeln für Benutzereingaben in der UI
	int i = 0; // Iterator für Kategorienauswahl
	string output_searchValue = ""; // gibt bei der Ausgabe an, welche Filme ausgegeben werden (also z.B. "von DirektorIn Goerge Lucas")
	string searchValue = ""; //nach was gesucht wird
	int date_input[3] = { 0,0,0 }; // Tag, Monat und Jahr der Daten zw. denen gesucht wird bei date_added
	int releaseMin, releaseMax = 0; // Jahre, zwischen und in denen die gesuchten Filme veröffentlicht wurden
	date dateMin, dateMax; // Daten zwischen und während denen die gesuchten Filme auf Netflix kamen
	set <int> results; // die SuchErgebnise

	//Datei einlesen
	file.open("netflix_titles.csv", ios::in); //öffnet eine Datei im Lesemodus
	if (!file.is_open()) // Wenn sie nicht erfolgreich geöffnet wurde
	{
		cout << "Fehler beim Öffnen" << endl;
	}
	else
	{
		getline(file, line); // ignoriert die 1. Zeile, wo die Bezeichungen der Daten drinnsteht und kein Film
		//während es Zeilen gibt
		while (getline(file, line)) // kopiert und modifiziert von https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c (1. Antwort)
		{
			film fTemp;

			//switch um korrumpierte Zeilen verarbeiten zu können
			switch (fTemp.read_in(line, errorCorrection))
			{
			case 0: // wenn alles funktioniert wird der Film abgespeichert
				collection.push_back(fTemp);
				break;
			case -1: // wenn es nur einen Datenpunkt gibt hat die Zeile davor nicht die gesammte Beschreibung
				// Der letzte gespeicherte Film wird genommen und der Beschreibung die neue kaputte Zeile hinzugefügt. Ftemp wird nichte gespeichert, weil es leer ist
				collection[collection.size() - 1].set_description(collection[collection.size() - 1].get_description() + errorCorrection);
				break;
			case -2: // wenn es zw. 1 und 12 Datenpunkte sind merkt man schon in der 1. Zeile den Fehler und kann dann die nächste Zeile einlesen und fTemp von der Summe der beiden Teile aufrufen
				getline(file, line);
				fTemp.read_in((errorCorrection + " "/*Leerzeichen wird durch Zeilenumbruch korrumpiert*/ + line), errorCorrection);
				collection.push_back(fTemp);
				break;
			}
		}
		file.close();
	}

	//indexing
	for (unsigned int j = 0; j < collection.size(); j++) // geht alle Filme in der Sammlung durch
	{
		setWithI.insert(j); // Set mit der Nummer des derzeitigen Films

		// macht bei jedem Film den Schpeicherplatz zum Index mit der Kategorie, SchauspielerIn u.s.w. als Schlüssel, die zum Film gehören
		// , damit man alle Filme zu den Kategorien / DirektorInnen schnell findet
		for (auto category : collection[j].get_categories()) // geht alle Kategorien vom Film durch
		{
			if (index_categories.count(category)) // wenn die Kategorie schon vorhanden ist
			{
				index_categories.find(category)->second.insert(j); // füge dem Set von Titeln dieser Kategorie diesen Film (als Zahl) hinzu
			}
			else // sonst
			{
				index_categories.insert({ category, setWithI }); // füge in die map die Kategorie mit einem Set mit nur diesem Film ein
			}
		}
		for (auto actor : collection[j].get_actors()) // wie bei Kategorie
		{
			if (index_actors.count(actor))
			{
				index_actors.find(actor)->second.insert(j);
			}
			else
			{
				index_actors.insert({ actor, setWithI });
			}
		}
		for (auto director : collection[j].get_directors()) // wie bei Kategorie
		{
			if (index_directors.count(director))
			{
				index_directors.find(director)->second.insert(j);
			}
			else
			{
				index_directors.insert({ director, setWithI });
			}
		}
		// es gibt pro Film nur ein Netflix-Datum => keine for Schleife, ansonsten wie bei Kategorie
		if (index_date_added.count(collection[j].get_date_added()))
		{
			index_date_added.find(collection[j].get_date_added())->second.insert(j);
		}
		else
		{
			index_date_added.insert({ collection[j].get_date_added(), setWithI });
		}
		// nur ein Veröffentlichungsdatum pro Film
		if (index_release.count(collection[j].get_release()))
		{
			index_release.find(collection[j].get_release())->second.insert(j);
		}
		else
		{
			index_release.insert({ collection[j].get_release(), setWithI });
		}



		index_title.insert({ collection[j].get_title(), j }); // Namen sind einzigartig => man muss nicht testen ob der Film schon drin ist

		setWithI.erase(j); // j wird aus dem Set gelöscht, damit es wieder leer ist und beim nächsten Film wieder nur der aktuelle Film drinsteht
	}

	//UI und suche
	while (retake_search)
	{
		//Suchkriterium wählen, dannach ist eingabe >= 1 und <= 5
		while (input == 0)
		{
			cout << "Wie moechten Sie nach Filmen und Serien suchen?" << endl << endl;

			cout << "1 Titel" << endl;
			cout << "2 DirektorIn" << endl;
			cout << "3 SchauspielerIn" << endl;
			cout << "4 Kategorie" << endl;
			cout << "5 Veröffentlichungsdatum" << endl << endl;
			if (extra_feature)
			{
				cout << "6 Erscheinungsdatum auf Neflix" << endl << endl;
			}
			cin >> input;
			cout << endl;
			if (extra_feature)
			{
				if (input < 1 || input > 6)
				{
					input = 0;
					cout << "ungueltiger Eingabewert, bitte eine Zahl zw. 1 und 6 eingeben." << endl << endl;
				}
			}
			else if (input < 1 || input > 5)
			{
				input = 0;
				cout << "ungueltiger Eingabewert, bitte eine Zahl zw. 1 und 5 eingeben." << endl << endl;
			}
		}

		// leert die Konsole
		cout << "\033[2J\033[1;1H"; // kopiert von https://stackoverflow.com/questions/17335816/clear-screen-using-c (1. Antwort)

		//jeweils die Suchparameter einlesen, die jeweiligen Indizes durchsuchen und Ergebnis im set Ergebnis speichern
		switch (input)
		{
		case 1: // Suche nach Titel
		{
			cout << "Bitte Titel eingeben" << endl << endl;
			cin.ignore(); //braucht man nach cin >> val; um den Buffer zu leeren
			getline(cin, searchValue);
			//wenn der Name existiert wird die Nummer abgefragragt, wenn man die Nummer eines nichtexistenten Films abfratgt kommt illegal memory acces violation
			if (index_title.count(searchValue))
			{
				results.insert(index_title.find(searchValue)->second); // fügt die Nummer des Films dem Ergebnis hinzu
			}
			output_searchValue = "mit dem Titel " + searchValue; //beschreibt wie die Filme gesucht wurden für die Ausgabe
		}
		break;
		case 2: // Suche nach DirektorIn
		{
			cout << "Bitte DirektorIn eingeben" << endl << endl;
			cin.ignore(); //braucht man nach cin >> val; um den Buffer zu leeren
			getline(cin, searchValue);
			results = search_index(index_directors, searchValue); //durchsucht den Index und gibt die Filme dazu zurück
			output_searchValue = "von der DirektorIn " + searchValue; //beschreibt wie die Filme gesucht wurden für die Ausgabe
		}
		break;
		case 3: // Suche nach SchauspielerIn, wie case 2
		{
			cout << "Bitte SchauspielerIn eingeben" << endl << endl;
			cin.ignore();
			getline(cin, searchValue);
			results = search_index(index_actors, searchValue);
			output_searchValue = "mit der SchauspielerIn " + searchValue;
		}
		break;
		case 4:
		{
			cout << "Um eine Kategorie zu waehlen bitte Zahl eingeben:" << endl;

			// um die Kategorien auszuwählen wird daneben ein Zähler angezeigt
			for (auto category : index_categories)
			{
				i++; // zeigt eine Zahl  von jeder Kategorie, muss manuell sein, weil man mit einem normalen for-loop nicht durch maps iterieren kann
				if (i < 10) //wenn der Zähler einstellig ist kommt ein Leerzeichen davor, um die Stellen gleich zu halten
				{
					cout << " ";
				}
				cout << i << ": " << category.first << endl;
				Sleep(30); //weils cool ausshieht
			}
			cout << endl;

			// liest die Nummer ein
			while (!input_worked)
			{
				cin >> i;
				if (i < 1 || i > index_categories.size()) // wenn i nicht innerhalb der Range der map ist
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

			// zählt runter; wenn j 0 ist wurde so oft runtergezählt wie oben hochgezählt => es ist die gleicht Kategorie
			for (auto category : index_categories)
			{
				i--;
				if (i == 0)
				{
					searchValue = category.first;
				}
			}
			i = 0; // resetten

			// wie bei case 2
			results = search_index(index_categories, searchValue);
			output_searchValue = "in der Kategorie " + searchValue;
		}
		break;
		case 5: // Suche nach Veröffentlichungsdatum
		{
			// Daten einlesen
			while (!input_worked)
			{
				input_worked = true;
				cout << "Bitte Zeitramen in dem die Filme und Serien gedreht wurden in folgendem Format eingeben:" << endl;
				cout << "yyyyy  yyyyy   (Anfang  Ende)" << endl << endl;
				cin >> releaseMin >> releaseMax;
				if (releaseMin > releaseMax)
				{
					input_worked = 0;
					cout << endl << "Das Ende kann nicht vor dem Anfang sein, bitte nochmal versuchen" << endl << endl;
				}
			}

			//geht alle Jahre dazwischen (einschlieslich Ränder) durch
			for (int j = releaseMin; j <= releaseMax; j++)
			{
				if (index_release.count(j)) // checken ob in dem Jahr etwas veröffentlicht wurde, damit es keine illegal memeory access violation gibt
				{
					for (auto film : index_release.find(j)->second)
					{
						results.insert(film); // fügt die Filme in das Ergebnis ein
					}
				}
			}

			//beschreibt wie die Filme gesucht wurden für die Ausgabe
			output_searchValue = "die zwischen und einschlieslich ";
			output_searchValue = output_searchValue + to_string(releaseMin);
			output_searchValue = output_searchValue + " und ";
			output_searchValue = output_searchValue + to_string(releaseMax);
			output_searchValue = output_searchValue + " veroeffentlicht wurden";
		}
		break;
		case 6:
		{
			// Daten einlesen
			while (!input_worked)
			{
				input_worked = true; // wenn nichts schiefgeht kann man aus der Schleife
				cout << "Bitte Zeitramen, wann die Filmen und Serien in den Katalog kamen in folgendem Format eingeben:" << endl;
				cout << "dd mm yyyyy" << endl;
				cout << "dd mm yyyyy" << endl << endl;

				cin >> date_input[0] >> date_input[1] >> date_input[2];
				if (dateMin.set_date(date_input[0], date_input[1], date_input[2]))
				{
					input_worked = 0;
					cout << endl << "Eingabeformat fehlerhaft, bitte nochmal versuchen" << endl << endl;
				}

				cin >> date_input[0] >> date_input[1] >> date_input[2];
				if (dateMax.set_date(date_input[0], date_input[1], date_input[2]))
				{
					input_worked = 0;
					cout << endl << "Eingabeformat fehlerhaft, bitte nochmal versuchen" << endl << endl;
				}

				if (dateMax < dateMin)
				{
					input_worked = 0;
					cout << endl << "Das Ende kann nicht vor dem Anfang sein, bitte nochmal versuchen" << endl << endl;
				}
			}
			date_input[0] = date_input[1] = date_input[2] = 0;

			//geht alle Daten durch und fügt die jeweiligen Filme dem Ergebnis hinzu
			dateMax++; // es gibt kein <= Operator, nur ein < Operator 
			for (date j = dateMin; j < dateMax; j++)
			{
				//wenn der Name existiert wird die Nummer abgefragragt, wenn man die Nummer eines nichtexistenten Films abfratgt kommt illegal memory acces violation
				if (index_date_added.count(j))
				{
					for (auto film : index_date_added.find(j)->second)
					{
						results.insert(film);
					}
				}
			}

			//beschreibt wie die Filme gesucht wurden für die Ausgabe
			output_searchValue = "die zwischen und einschlieslich ";
			output_searchValue = output_searchValue + dateMin.get_date_as_string();
			output_searchValue = output_searchValue + " und ";
			output_searchValue = output_searchValue + dateMax.get_date_as_string();
			output_searchValue = output_searchValue + " auf Netflix kamen";
		}
		break;
		}
		input = 0;
		// wenn nichts gefunden wurde
		if (results.size() == 0)
		{
			cout << "keine Filmen und Serien " << output_searchValue/*siehe oben z.B. in Zeile 785*/ << " bei Netflix verfuegbar" << endl << endl;
		}
		else // wenn etwas gefunden wurde
		{
			cout << "Folgende Filmen und Serien " << output_searchValue << " sind bei Netflix verfuegbar: " << endl << endl;

			for (auto film : results)
			{
				Sleep(10); //weils cool aussieht
				cout << collection[film].get_title() << endl;
			}
		}

		//leitet einen auf die Seite einer Google suche nach dem Titel weiter
		if (extra_feature)
		{
			/*
			//von https://stackoverflow.com/questions/45759764/redirecting-to-a-webpage-in-c (1. Anwort)
			ShellExecute(NULL, L"open", L"https://stackoverflow.com/questions/45759764/redirecting-to-a-webpage-in-c", nullptr, nullptr, SW_SHOWNORMAL);
			*/
		}

		//bricht die Schleife mit der Suche ab oder resetet alle Variabeln
		while (input == 0)
		{
			cout << endl << "Wollen Sie noch nach etwas anderem suchen?" << endl;
			cout << "Ja(1) oder Nein(2)" << endl << endl;
			cin >> input;

			switch (input)
			{
			case 1: //reset
				cout << "\033[2J\033[1;1H";
				searchValue = "";
				dateMin.set_date(0, 0, 0);
				dateMax.set_date(0, 0, 0);
				releaseMin = releaseMax = 0;
				input_worked = 0;
				results.clear();
				bool input_worked = false;
				break;
			case 2: //beendet Programm
				retake_search = false;
				break;
			default:
				input = 0;
				cout << "ungueltiger Eingabewert, bitte 1 oder 2 eingeben." << endl;
				break;
			}
		}
		input = 0;
	}
}