#include "Analiticar.h"
#include "Bill.h"
#include <string.h>
#include<iomanip>
analiticar::Analiticar::Analiticar() {}

analiticar::Analiticar::Analiticar(const std::tuple<string, string, string, string, bool>& userInfo) : user::User(userInfo) {}

analiticar::Analiticar::~Analiticar() {}

Bill::Date returnDateFromReadString(string input)
{
	string d, m, g;
	d += input[0]; d += input[1];
	m += input[3]; m += input[4];
	g += input[6]; g += input[7]; g += input[8]; g += input[9];
	Bill::Date that(std::stoi(d), std::stoi(m), std::stoi(g));
	return that;
}



Bill returnBillFromReadString(string input)
{
	string customer, productS, ammountStr, priceStr;	//string->bill converter dd/mm/gggg.#buyer#product 123#ammount#price#total
	int buy = 12, prod, amm, pri;
	for (; input[buy] != '#'; buy++)
		customer += input[buy];
	prod = buy + 1;
	for (; input[prod] != '#'; prod++)
		productS += input[prod];
	amm = prod + 1;
	for (; input[amm] != '#'; amm++)
		ammountStr += input[amm];
	pri = amm + 1;
	for (; input[pri] != '#'; pri++)
		priceStr += input[pri];
	std::vector<Bill::Product> temp; temp.push_back(Bill::Product(productS, std::stod(ammountStr), std::stod(priceStr), std::stod(priceStr)*std::stod(ammountStr)));
	return Bill(customer, returnDateFromReadString(input), temp);

}

void analiticar::Analiticar::billsDateOverview()
{
	string d, m, g;
	bool quit = 0;
	while (!quit)
	{
		cout << "Unesite pocetni datum u obliku dd/mm/gg:"<<endl;
		std::getline(std::cin, d, (char)'/');
		std::getline(std::cin, m, (char)'/'); 
		std::getline(std::cin, g);
		//if((std::stoi(d)>=31)||(std::stoi(d)<1)||(std::)			ubaciti test za validan datum
		quit = 1;
	}
	cout << endl<<endl;
	Bill::Date start(std::stoi(d), std::stoi(m), std::stoi(g)); quit = 0;
	while (!quit)
	{
		cout << "Unesite krajnji datum u obliku dd/mm/gg:"<<endl;
		std::getline(std::cin, d, (char)'/'); std::getline(std::cin, m, (char)'/'); std::getline(std::cin, g); //isto rijesiti validnost datuma!
		quit = 1;
	}
	Bill::Date finish(std::stoi(d), std::stoi(m), std::stoi(g));
	if (finish < start)
	{
		cout << "Uneseni datumi nisu ispravni"<<endl; return;
	}
	system("cls");
	std::fstream file; file.open("Racuni za ispis.txt");
	if (!file.is_open())
		return;
	string current;

	cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo
	cout 
		<< std::setw(15) 
		<< "Datum" 
		<< std::setw(12) 
		<< "Kupac"
		<< std::setw(19) 
		<< "Proizvod"
		<< std::setw(10) 
		<< "Cijena"
		<< std::setw(10)
		<< "Kolicina"
		<< std::setw(10)
		<< "Ukupno"
		<< endl;

	while (std::getline(file, current))
		{
			
			auto t = returnBillFromReadString(current);
			std::vector<std::string> vec;
			Bill::split(current, '#', vec);
			Bill::Date date = vec[0];
			if (date > start && date < finish)
			{
				cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
				cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo
				cout
					<< std::setw(15)
					<< vec[0]
					<< std::setw(12)
					<< vec[1]
					<< std::setw(19)
					<< vec[2]
					<< std::setw(10)
					<< vec[3]
					<< std::setw(10)
					<< vec[4]
					<< std::setw(10)
					<< std::atof(vec[3].c_str()) * std::atof(vec[4].c_str())  // c_str se koristi zato sto funkcija atof trazi kao argument const char*, a c_str omogucava konverziju string->const char*
					<< endl;
			}

	}

	}





int analiticar::Analiticar::menu()
{
	Bill::billClassification();
	bool quit = 0;
	std::string choice;
	while (!quit)
	{
		cout << endl << "1.Pregled racuna po periodu izdavanja" << endl << "2.Pregled racuna po kupcu" << endl << "3.Pregled racuna po proizvodu" << endl <<  "4.Odjava korisnika" << endl << "5.Izlazak iz programa" << endl;
		cout << "Izaberite jednu od ponudjenih opcija: ";	getline(cin, choice);
		if (isdigit(choice[0]))
		{
			switch (std::stoi(choice))
			{
			case 1:
			{
				system("cls");
				this->billsDateOverview();
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 2:
			{
				system("cls");
				// pregled racuna po kupcu
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 3:
			{
				system("cls");
				//pregled racuna po proizvodu
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 4:
			{
				system("cls");
				return 0;
			} break;
			case 5:
			{   
				return 1;
			}	
			default:
			{
				system("cls");
				quit = 0;
			}

			}
		}
		else system("cls");
	}
}
