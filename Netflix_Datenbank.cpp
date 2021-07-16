// Netflix_Datenbank.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

/*to do:
* categories richtig speichern / indexen
* Felermeldung / Hinweise beim Einlesen
*/
int main()
{

    fstream Datei;
    Datei.open("t8shakespeare.txt", ios::in); //open a file to perform read operation using file object
    if (Datei.is_open()) {   //checking whether the file is open
        while (Datei >> wort)
        {
            string temp = "";
            for (int i = 0; i < wort.size(); ++i)
            {
                if ((wort[i] >= 'a' && wort[i] <= 'z'))
                {
                    temp = temp + wort[i];
                }
                else if (wort[i] >= 'A' && wort[i] <= 'Z')
                {
                    temp = temp + ((char)((int)wort[i] + 32));
                }
            }
            wort = temp;
            if (wort == "")
            {
            }
            else if (Wörter.find(wort) != Wörter.end()) {
                Wörter[wort] ++;
            }
            else {
                Wörter.insert(make_pair(wort, 1));
            }
            cout << wort << "\n";   //print the data of the string
        }
        Datei.close();   //close the file object.
    }
    else
    {
        cout << "Fehler beim Öffnen" << endl;
    }
}

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
}

date::~date()
{
}


class Filme
{
public:
	Filme();
	~Filme();

private:
	bool movie;

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
}

Filme::~Filme()
{
}
