#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#pragma warning(disable : 4996)
using namespace std;

class Eveniment {
private:
	//va permite citirea caracteristicilor evenimentului (ex: dată, oră, denumire, etc.)
	//permite generarea de bilete nominale conform caracteristicilor dorite(ex : VIP, peluză, tribună, loje, etc.)
	int an;
	int luna;
	int zi;
	string ora;
	string denumire;
	static int nrEvenimente;
	const int vmin;
	//Locatie l;
public:
	Eveniment():vmin(18)
	{
		this->an = 0;
		this->luna = 0;
		this->zi = 0;
		this->ora = "";
		this->denumire = "";
		nrEvenimente++;
	}
	Eveniment(int an, int luna, int zi, string ora, string denumire):vmin(18) {
		//validari
		this->an = an;
		this->luna = luna;
		this->zi = zi;
		this->ora = ora;
		this->denumire = denumire;
		nrEvenimente++;
	}
	int getAn()
	{
		return this->an;
	}
	int getLuna()
	{
		return this->luna;
	}
	int getZi()
	{
		return this->zi;
	}
	void setAn(int an)
	{
		this->an = an;
	}
	void setZi(int zi)
	{
		this->zi = zi;
	}
	void setLuna(int luna)
	{
		this->luna = luna;
	}
	/*
	void setData(string data)
	{
		string format("%d/%m/%Y");
		date d;
		d = parser.parse_date(data, format, svp);
		if (data != "")
		{
			this->data = data;
		}
	}
	*/


	string getOra()
	{
		return this->ora;
	}
	void setOra(string ora)
	{
		if (ora != "")
		{
			this->ora = ora;
		}
	}
	string getDenumire()
	{
		return this->denumire;
	}
	void setDenumire(string denumire)
	{
		if (denumire != "")
		{
			this->denumire = denumire;
		}
	}
	void CrestereCitire()
	{
		nrEvenimente++;
	}
	void AfisLuna(string data)
	{
		//12.06.2022
		string a;
		if (data[3] != '0')
		{
			a = (data)+'0' + (data);
		}
		cout << a;
	}
	Eveniment& operator=(const Eveniment& e)
	{
		if (this != &e)
		{
			an = e.an;
			luna = e.luna;
			zi = e.zi;
			ora = e.ora;
			denumire = e.denumire;

			return *this;
		}
	}
	friend ostream& operator<<(ostream& out, Eveniment a);
	friend istream& operator>>(istream& in, Eveniment& a);
	//+2 operatori

};
int Eveniment::nrEvenimente = 0;
ostream& operator<<(ostream& out, Eveniment a)
{
	out << "Denumire: ";
	if (a.denumire != "")
	{
		out << a.denumire << endl;
	}
	out << "Anul: ";
	if (a.an)
	{
		out << a.an << endl;
	}
	out << "Luna: ";
	if (a.luna)
	{
		out << a.luna << endl;
	}
	out << "Zi: ";
	if (a.zi)
	{
		out << a.zi << endl;
	}

	out << "Ora: ";
	if (a.ora != "")
	{
		out << a.ora << endl;
	}
	return out;
}

istream& operator>>(istream& in, Eveniment& a)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	cout << endl << "Introduceti denumirea evenimentului: ";
	string buffer;
	getline(in, buffer);
	a.setDenumire(buffer.c_str());


	cout << "Introduceti anul in care se desfasoara evenimentul: ";
	in >> a.an;
	while (a.an < 1900 + ltm->tm_year)
	{
		cout << "Anul " << a.an << " a trecut, alegeti altul" << endl;
		in >> a.an;
	}

	cout << "Introduceti luna in care se desfasoara evenimentul: ";
	in >> a.luna;
	if (a.an == 1900 + ltm->tm_year)
	{
		while (a.luna < ltm->tm_mon + 1)
		{
			cout << "Nu se poate alege un eveniment din o luna deja terminata din anul curent" << endl;
			in >> a.luna;
		}
	}

	cout << "Introduceti ziua in care se desfasoara evenimentul: ";
	in >> a.zi;
	if (a.an == 1900 + ltm->tm_year && a.luna == 1900 + ltm->tm_mon)
		while (a.zi <= ltm->tm_mday)
		{
			if (a.zi == ltm->tm_mday)
			{
				cout << "Nu puteti alege un eveniment din ziua curenta, alegeti o zi viitoare " << endl;
			}
			else {
				cout << "Ziua este depasita, alegeti o zi viitoare " << endl;
			}
			in >> a.zi;
		}



	cout << endl << "Introduceti ora la care se desfasoara evenimentul: " << endl;
	in >> a.ora;
	int ok = 1;
	while (ok)
	{
		while(a.ora.length() != 5)
		{
			cout << "Formatul este prea lung/mic pentru ora, introduceti din nou: " << endl;
			in >> a.ora;
		}


		for (int i = 0; i < a.ora.length(); i++)
		{
			if (i == 2 && a.ora[i] == ':')
			{
				cout << "O ora este formata doar din cifre, intre ele " << ':' << ", introduceti din nou " << endl;
				in >> a.ora;
			}

			if (a.ora[i] < '0' || a.ora[i]>'9' && a.ora[0] != ':' && a.ora[1] != ':' && a.ora[3] != ':' && a.ora[4] != ':')
			{
				cout << "O ora este formata doar din cifre, intre ele " << ':' << ", introduceti din nou " << endl;
				in >> a.ora;
			}

		}
		ok = 0;
	}
	return in;

}
//corect
class Locatie {
private:
	//va permite citirea caracteristicilor locației
	//(ex: număr maxim de locuri, număr de rânduri, zone, număr/codificare scaune pe rând, etc.)
	char* locatie;
	int nrLocuri; //nr max bilet
	int* nrLocuriRandZona;
	string* zona; // vector cu numele zonelor
	int nrZone;
public:

	Locatie()
	{
		locatie = nullptr;
		nrLocuri = 0;
		nrLocuriRandZona = nullptr;
		zona = nullptr;
		nrZone = 0;

	}
	Locatie(char* locatie, int nrLocuri, int* nrLocuriRandZona, string* zona, int nrZone)
	{
		if (locatie != nullptr)
		{
			this->locatie = new char[strlen(locatie) + 1];
			strcpy_s(this->locatie, strlen(locatie) + 1, locatie);
		}
		else {
			this->locatie = nullptr;
		}
		this->nrLocuri = nrLocuri;
		if (nrLocuriRandZona != nullptr && nrZone > 0)
		{
			this->nrZone = nrZone;
			this->nrLocuriRandZona = new int[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				this->nrLocuriRandZona[i] = nrLocuriRandZona[i];
			}
		}
		else {
			this->nrLocuriRandZona = nullptr;
			this->nrZone = 0;
		}
		if (zona != nullptr && nrZone > 0)
		{
			this->zona = new string[nrZone];
			for (int i = 0; i < nrZone; i++) {
				this->zona[i] = zona[i];
			}
		}
		else {
			this->zona = nullptr;
		}
	}
	Locatie& operator=(const Locatie& s)
	{
		if (this != &s)
		{
			if (s.locatie != nullptr && strlen(s.locatie) + 1 > 0) {
				if (locatie != nullptr)
				{
					delete[] locatie;
				}

				locatie = new char[strlen(s.locatie) + 1];
				for (int i = 0; i < strlen(s.locatie) + 1; i++)
				{
					locatie[i] = s.locatie[i];
				}

			}
			else
			{
				this->locatie = nullptr;
			}
			this->nrLocuri = s.nrLocuri;
			if (s.nrLocuriRandZona != nullptr && s.nrZone > 0) {
				if (nrLocuriRandZona != nullptr)
				{
					delete[] nrLocuriRandZona;
					nrZone = 0;
				}

				nrLocuriRandZona = new int[s.nrZone];
				for (int i = 0; i < s.nrZone; i++)
				{
					nrLocuriRandZona[i] = s.nrLocuriRandZona[i];
				}
				nrZone = s.nrZone;
			}
			else
			{
				this->nrLocuriRandZona = nullptr;
				this->nrZone = 0;
			}
			if (this->zona != nullptr)
			{
				delete[] this->zona;
			}
			if (s.zona != nullptr) {
				this->zona = new string[s.nrZone + 1];
				for (int i = 0; i < s.nrZone; i++)
				{

					this->zona[i] = s.zona[i];
				}
			}
			else {
				this->zona = nullptr;
			}

			return *this;
		}
	}
	void setBilete(int* nrLocuriRandZona, int nr)
	{
		if (nrLocuriRandZona != nullptr && nr > 0)
		{
			if (this->nrLocuriRandZona != nullptr)
			{
				delete[] this->nrLocuriRandZona;
				this->nrLocuriRandZona = nullptr;
			}
			this->nrZone = nr;
			this->nrLocuriRandZona = new int[nr];
			for (int i = 0; i < nr; i++)
			{
				this->nrLocuriRandZona[i] = nrLocuriRandZona[i];
			}
		}
	}
	int* getNrRand()
	{
		return this->nrLocuriRandZona;
	}
	int* getNrLocuriRandZona()
	{
		int* c = new int[nrZone];
		for (int i = 0; i < nrZone; i++)
		{
			c[i] = nrLocuriRandZona[i];
		}
	}

	string* getZona()
	{
		if (zona != nullptr && nrZone > 0)
		{
			string* copy = new string[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				copy[i] = zona[i];
			}
			return copy;
		}
		else return nullptr;

	}
	void setZona(string* zona, int nrZone)
	{

		if (nrZone > 0 && zona != nullptr) {
			if (this->zona != nullptr) {
				delete[] this->zona;
			}
			this->nrZone = nrZone;
			this->zona = new string[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				this->zona[i] = zona[i];
			}
		}
		else {
			cout << "Nu s-au putut seta zonele" << endl;
		}

	}
	int getNrZone()
	{
		int copy = this->nrZone;
		return copy;
	}
	void setNrZone(int nr)
	{
		if (nr > 0)
		{
			this->nrZone = nr;
		}
	}
	int getNrLocuri()
	{
		return nrLocuri;
	}
	char* getLocatie()
	{
		if (locatie != nullptr)
		{
			char* copy = new char[strlen(locatie) + 1];
			strcpy_s(copy, strlen(locatie) + 1, locatie);
			return copy;
		}
		return nullptr;
	}
	void setLocatie(const char* locatie)
	{
		if (locatie != nullptr)
		{
			if (this->locatie != nullptr)
			{
				delete[] this->locatie;
			}
			this->locatie = new char[strlen(locatie) + 1];
			strcpy_s(this->locatie, strlen(locatie) + 1, locatie);
		}
	}
	~Locatie()
	{
		delete[] locatie;
		delete[]nrLocuriRandZona;
		delete[] zona;
	}
	friend ostream& operator<<(ostream& out, Locatie a);
	friend istream& operator>>(istream& in, Locatie& a);
};
ostream& operator<<(ostream& out, Locatie a)
{
	out << "Locatie: ";
	if (a.locatie != "")
	{
		out << a.locatie << endl;
	}
	out << "Numar maxim de locuri: ";
	if (a.nrLocuri > 0)
	{
		out << a.nrLocuri << endl;
	}

	out << "Numar zone: ";
	out << a.nrZone << endl;

	for (int i = 0; i < a.nrZone; i++)
	{
		cout << "Numele zonei " << i + 1 << ": ";
		out << a.zona[i];
	}




	return out;
}
istream& operator>>(istream& in, Locatie& a)
{
	string ala;
	cout << endl << "Introduceti locatia dorita: ";
	string buffer;
	getline(in, buffer);
	a.setLocatie(buffer.c_str());


	cout << "Numar maxim de locuri: ";
	in >> a.nrLocuri;

	cout << "Numar zone: ";
	in >> a.nrZone;
	while (a.nrZone < 1)
	{
		cout << "Locatia trebuie sa aiba macar o zona, introduceti o valoare numerica diferita de 0 ";
		in >> a.nrZone;
	}
	getline(in, ala);



	string zona;
	a.zona = new string[a.nrZone];
	for (int i = 0; i < a.nrZone; i++)
	{
		cout << "Zona " << i + 1 << ": ";
		getline(in, zona);
		if (zona == "") {
			i--;
			cout << "Zona introdusa invalida!" << endl;
		}
		else {
			a.zona[i] = zona;
		}
	}



	/*
	for (int i = 0; i < a.nrZone; i++)
	{
		cout << "Introduceti numele zonei " << i + 1<<": ";
		getline(in,buffer);
		a.setZona(buffer,i);
	}
	if (a.nrLocuriRandZona !=nullptr)
	{
		delete[] a.nrLocuriRandZona;
		a.nrLocuriRandZona = nullptr;
	}
	a.nrLocuriRandZona = new int[a.nrZone];
	*/

	return in;
}
class Bilet {
private:
	int idBilet;
	string tipBilet; //zona biletului
	int nrBileteDorite;
	int loc;
	Eveniment e;
	Locatie l;
	//constant/static
public:
	Bilet()
	{
		idBilet = 0;
		tipBilet = "";
		nrBileteDorite = 0;
		loc = 0;
		

	}
	Bilet(string tipBilet, int loc, Locatie& l)
	{
		this->tipBilet = tipBilet;
		this->loc = loc;
		this->l = l;
	}
	//operator egal
	int getIdBilet()
	{
		return this->idBilet;
	}
	int getNrBileteDorite()
	{
		return this->nrBileteDorite;
	}
	string getTipBilet()
	{
		return this->tipBilet;
	}
	int getLoc()
	{
		return this->loc;
	}
	void setIdBilet(int idBilet)
	{
		if (idBilet != 0) //de fct validare 
		{
			this->idBilet = idBilet;
		}
	}
	void setGetNrBileteDorite(int nr)
	{
		if (nr)
		{
			this->nrBileteDorite = nr;
		}
	}
	void setTipBilet(string tip)
	{
		if (tip != "") {
			this->tipBilet = tip;
		}
	}
	void setLoc(int loc)
	{
		if (loc != 0)
		{
			this->loc = loc;
		}
	}
	Locatie getLocatie()
	{
		return l;
	}

	void Trecere(Locatie l)
	{
		this->l = l;
	}

	Bilet& operator=(const Bilet& b)
	{
		if (this != &b)
		{
			idBilet = b.idBilet;
			tipBilet = b.tipBilet;
			nrBileteDorite = b.nrBileteDorite;
			loc = b.loc;
			l = b.l;
			e = b.e;
		}

		return *this;
	}
	friend ostream& operator<<(ostream& out, Bilet b);
	friend istream& operator>>(istream& in, Bilet& b);


	//setteri getteri

	// metoda scadere din nr total bilete, nr cumparat
	// 
};
ostream& operator<<(ostream& out, Bilet b)
{
	out << b.idBilet;

	out << b.tipBilet;

	out << b.nrBileteDorite;

	out << b.loc;

	out << b.e;

	out << b.l;

	return out;
}
istream& operator>>(istream& in, Bilet& b)
{

	cout << "Introduceti numarul de bilete dorite: ";
	in >> b.nrBileteDorite;

	while (b.nrBileteDorite < 1 || b.nrBileteDorite > b.l.getNrLocuri())
	{
		if (b.nrBileteDorite < 1) {

			cout << "Numarul de bilete dorite trebuie sa fie minim 1, introduceti din nou :";
		}
		else cout << "Numarul acesta de bilete nu este disponibil" << endl;
		cout << "Introduceti alt numarul de bilete :" << endl;
		in >> b.nrBileteDorite;
	}
	cout << "Ati ales " << b.nrBileteDorite << " bilete" << endl;
	string buffer;
	getline(in, buffer); //trebuie citit enter


	//cout << b.l.getNrZone() <<"nu" << endl;
	int nr1 = b.l.getNrZone();
	//cout << nr1 <<"asta e"<< endl;
	string* copie = new string[nr1];
	copie = b.l.getZona();


	/*for (int i = 0; i < b.l.getNrZone(); i++)
	{
		cout << b.l.getZona()[i] << endl;
	}*/


	cout << "Alegeti una din zonele introduse mai sus" << endl;
	for (int i = 0; i < nr1; i++)
	{
		cout << copie[i] << endl;
	}


	string buffer2;
	cout << "Introduceti zona dorita: ";
	getline(in, buffer2);
	b.tipBilet = buffer2;

	//tip bilet trb sa se regaseasca in zone din bilet

	int ok = 0;
	int zona_ok = 0;
	//while (zona_ok == 0) {
	//	//while (i < b.tipBilet.length())
	////	{

	//	for (int i = 0; nr1; i++)
	//	{
	//		if (b.tipBilet == copie[i])
	//		{
	//			cout << "Ati ales zona " << b.tipBilet << endl;
	//			i = nr1;
	//			zona_ok = 1;
	//		}
	//	}
	//	ok = 1;


		//if(b.tipBilet!=l.zona[])
		/*if (b.tipBilet[i] == ' ')
			if (!((b.tipBilet[i] >= 'a' && b.tipBilet[i] <= 'z') || (b.tipBilet[i] >= 'A' && b.tipBilet[i] <= 'Z')))
			{
				ok = 1;
				i = b.tipBilet.length();
			}
			*/
			//	i++;
		//	}
		/*if (ok == 1)
		{
			cout << "Zona aleasa nu exista, alegeti alta valida: " << endl;
			getline(in, buffer);
			b.tipBilet = buffer;
			zona_ok = 0;
		}*/

	


	return in;
}

int main()
{

	Locatie a;
	cin >> a;
	//cout << a.getNrLocuri();
	Eveniment c;
	cin >> c;
	Bilet b;
	b.Trecere(a);
	cin >> b;
	//cout << b.getLocatie();
	/*
	int a[5] = { 3,2,5,6 };
	string b[5] = {"pela"};
	char c[6] = { "arena" };
	Locatie l1(c , 15 , a , b, 1);
	Bilet b("ala", 5, l1);
	*/
}