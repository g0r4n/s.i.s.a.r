#include"AssistFunc.h"
#include "Administrator.h"

void writeInvalidLogin(string username, string p)
{
	std::fstream file;
	file.open(LogFile);
	if (!file.is_open())
		return;
	file.seekg(0, std::ios::end);
	file << username << " " << p << std::endl;
	file.close();
	return;

}

std::tuple<string, string, string, string, bool> logInCheck(std::fstream& file, string username, string p)
{
	file.clear();
	file.seekg(0, std::ios::beg);
	if (!file.is_open())
		return { "-1","-1","-1","-1",0 };
	string local_n, local_ln, local_p, local_username, type;

	while (file >> local_username >> local_n >> local_ln >> local_p >> type)
	{
		if (username == local_username && p == local_p)
		{
			system("cls");
			cout << " Uspjesno logovanje!" << "\n Dobrodosli " << local_n;
			return { local_username,local_n,local_ln,local_p, std::stoi(type) };
		}

	}
	return { "-1","-1","-1","-1",0 };
}

std::tuple<string, string, string, string, bool> logIn()
{
	std::fstream file(UserDataFile);
	bool quit = false;
	string locUserName, locPw;
	std::tuple<string, string, string, string, bool> type;
	while (!quit)
	{
		cout << "Unesite korisnicko ime korisnika: ";
		getline(std::cin, locUserName);

		cout << "Unesite pristupnu sifru korisnika: ";
		getline(std::cin, locPw);

		if (locPw.length() == 4 && (std::get<0>(type = logInCheck(file, locUserName, locPw)) != "-1"))
		{
			quit = 1;
		}
		else
		{
			cout << "Neuspjesno logovanje na sistem. Pritisnite enter za ponovno unosenje podataka o korisniku, ili Esc za izlazak iz programa. \n"; //Skontati kako detektovati Esc
			writeInvalidLogin(locUserName, locPw);

			getchar();
			system("cls");
		}
	}
	return type;
}