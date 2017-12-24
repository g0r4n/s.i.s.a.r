#pragma once
#include "AssistFunc.h"
#include "User.h"


namespace admin
{
	class Administrator : public user::User
	{
	private:

		User createNewUser() const;
		int getNumberOfUsers(std::fstream&) const;
		void showAvailableCurrencies(std::fstream&) const;


		
		friend bool isPINokay(const string&);
		string getPIN() const;
		bool isUserNameOkay(const string,std::fstream&) const;
		string getUserName() const;
		bool isUserGroupOkay(const string) const;
		bool getUserGroup() const;
    												
	public:

		Administrator();
		Administrator(const std::tuple<string, string, string, string, bool>&);
		~Administrator();
		void userOverview(std::fstream&) const;
		void addNewUser(std::fstream&) const;
		void deleteUser(std::fstream&) const;
 		void changeCurrency(std::fstream&) const;		
		bool isLogInSuccesfull() const;
		int menu() const;
		int runIt();
	};
}

