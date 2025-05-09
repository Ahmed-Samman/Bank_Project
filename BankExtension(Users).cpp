#include<iostream>
#include<string>
#include<cctype>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
const string ClientsFile = "BankClients.txt";
const string UsersFile = "BankUsers.txt";

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool FlagForRemoveClient = false;
};
struct stUser
{
	string UserName;
	string PassWord;
	short Permissions;
	bool FlagForRemoveUser = false;
};
struct stPermissions
{
	const short ShowClients = 1;
	const short AddNewClient = 2;
	const short DeleteClient = 4;
	const short UpdateClient = 8;
	const short FindClient = 16;
	const short Transactions = 32;
	const short ManageUsers = 64;
	const short AllPermissions = -1;
};

// declare those functions
void ShowMainMenueScreen(vector <stUser> vAllUser, vector <stClient> &vAllClients);
void TransactionsMenueScreen(vector <stUser> vAllUser, vector <stClient> &vAllClients);
void ManageUsersMenueScreen(vector <stUser> vAllUsers, vector <stClient> vAllClients);
void LogIn();
void WrongItem();

// -----------------------------------------------------------------------------

// Add Clients To Vector ( Type stClient ) 
vector <string> SplitStringClientsFromFile(string Line, string Separator)
{
	short Pos;
	string Word;
	vector <string> vClient;

	while ((Pos = Line.find(Separator)) != std::string::npos)
	{
		Word = Line.substr(0, Pos);
		if (Word != "")
		{
			vClient.push_back(Word);
		}
		Line.erase(0, Pos + Separator.length());
	}
	if (Line != "")
	{
		vClient.push_back(Line);
	}

	return vClient;
}
stClient FillClientFromVector(string Line)
{
	stClient Client;
	vector <string> vEachClient = SplitStringClientsFromFile(Line, "#//#");

	Client.AccountNumber = vEachClient[0];
	Client.PinCode = vEachClient[1];
	Client.Name = vEachClient[2];
	Client.Phone = vEachClient[3];
	Client.AccountBalance = stod(vEachClient[4]);

	return Client;
}
vector <stClient> AddAllClients()
{
	fstream MyFile;
	stClient EachClient;
	vector <stClient> vAllClients;

	MyFile.open(ClientsFile, ios::in); // Read mode

	if (MyFile.is_open())
	{
		string LineInFile;
		while (getline(MyFile, LineInFile))
		{
			EachClient = FillClientFromVector(LineInFile);
			vAllClients.push_back(EachClient);
		}
	}
	MyFile.close();

	return vAllClients;
}

// Add Users To Vector ( Type stUser ) 
vector <string> SplitStringUsersFromFile(string Line, string Separator)
{
	short Pos;
	string Word;
	vector <string> vUser;

	while ((Pos = Line.find(Separator)) != std::string::npos)
	{
		Word = Line.substr(0, Pos);
		if (Word != "")
		{
			vUser.push_back(Word);
		}
		Line.erase(0, Pos + Separator.length());
	}
	if (Line != "")
	{
		vUser.push_back(Line);
	}

	return vUser;
}
stUser FillUserFromVector(string Line)
{
	stUser User;
	vector <string> vEachUser = SplitStringUsersFromFile(Line, "#//#");

	User.UserName = vEachUser[0];
	User.PassWord = vEachUser[1];
	User.Permissions = stoi(vEachUser[2]);
	return User;
}
vector <stUser> AddAllUsers()
{
	fstream MyFile;
	stUser EachUser;
	vector <stUser> vAllUsers;

	MyFile.open(UsersFile, ios::in); // Read mode

	if (MyFile.is_open())
	{
		string LineInFile;
		while (getline(MyFile, LineInFile))
		{
			EachUser = FillUserFromVector(LineInFile);
			vAllUsers.push_back(EachUser);
		}
	}
	MyFile.close();

	return vAllUsers;
}


// -----------------------------------------------------------------------------


// (1) show All Calients On A Screen
void PrintEachClient(stClient Client)
{
	cout << "| " << left << setw(20) << Client.AccountNumber;
	cout << "| " << left << setw(20) << Client.PinCode;
	cout << "| " << left << setw(25) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountBalance;
}
void ShowAllClientsOnScreen(vector <stClient> vAllClients)
{
	system("cls");
	cout << "\t\t\t\tClient List (" << vAllClients.size() << ") Client(s).\n";
	cout << "__________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(20) << "Pin Code";
	cout << "| " << left << setw(25) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Balance";
	cout << "\n__________________________________________________________________________________________________\n\n";

	for (stClient& C : vAllClients)
	{
		PrintEachClient(C);
		cout << endl;
	}

	cout << "\n__________________________________________________________________________________________________\n\n";
}

// (2) Add New A Client
void PrintAddClientHead()
{
	cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
	cout << "\nAdding New Client:\n\n";
}
bool SerchAccountNumber(stClient Client, vector <stClient> vAllClients)
{
	for (stClient& C : vAllClients)
	{
		if (Client.AccountNumber == C.AccountNumber)
		{
			cout << "Client With [" << Client.AccountNumber << "] already exists, ";
			return true;
		}
	}
	return false;
}
stClient FillClientsInRecord(vector <stClient> vAllClients)
{
	stClient Client;
	do
	{
		cout << "Please Enter Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);

	} while (SerchAccountNumber(Client, vAllClients));

	cout << "Please Enter A Pin Code ? ";
	getline(cin, Client.PinCode);

	cout << "Please Enter A Name ? ";
	getline(cin, Client.Name);

	cout << "Please Enter A Phone ? ";
	getline(cin, Client.Phone);

	cout << "Please Enter An Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}
string ConvertRecordToString(vector <stClient> vAllClients, string Separator = "#//#")
{
	string Line;
	stClient Client = FillClientsInRecord(vAllClients);

	Line += Client.AccountNumber + Separator;
	Line += Client.PinCode + Separator;
	Line += Client.Name + Separator;
	Line += Client.Phone + Separator;
	Line += to_string(Client.AccountBalance);

	return Line;
}
void AddClientToFile(vector <stClient>& vAllClients)
{
	fstream MyFile;
	string Line = ConvertRecordToString(vAllClients);

	MyFile.open(ClientsFile, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;
	}
	MyFile.close();

}
void AddNewClient(vector <stClient>& vAllClients)
{
	char User = 'Y';
	do
	{
		system("cls");
		PrintAddClientHead();
		AddClientToFile(vAllClients);

		cout << "\n\nClient Added Seccessfully, do You Want To Add A New Client? ";
		cin >> User;

	} while (toupper(User) == 'Y');

	vAllClients = AddAllClients();
}

// (3) Delete A Client
void PrintDeleteClientHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "-----------------------------------\n";
}
string AskUserAccountNumber()
{
	string AccountNum;

	cout << "\nPlease enter Account Number? ";
	cin >> AccountNum;

	return AccountNum;
}
void PrintClient(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "------------------------------------\n";
}
bool SearchClientWithAccountNumber(stClient& Client, string AccountNum, vector <stClient> vAllClients)
{

	for (stClient& C : vAllClients)
	{
		if (C.AccountNumber == AccountNum)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
string ConvertRecordToString(stClient Client, string Separator = "#//#")
{
	string Line;

	Line += Client.AccountNumber + Separator;
	Line += Client.PinCode + Separator;
	Line += Client.Name + Separator;
	Line += Client.Phone + Separator;
	Line += to_string(Client.AccountBalance);

	return Line;
}
void MarkOnClient(string AccountNum, vector <stClient>& vAllClients)
{

	for (stClient& C : vAllClients)
	{

		if (C.AccountNumber == AccountNum)
		{
			C.FlagForRemoveClient = true;
		}
	}
}
void SavingClientsToFile(string ClientsFile, vector <stClient> vAllClients)
{
	fstream MyFile;

	MyFile.open(ClientsFile, ios::out);

	if (MyFile.is_open())
	{
		string Line;
		for (stClient& C : vAllClients)
		{
			if (C.FlagForRemoveClient == false)
			{
				Line = ConvertRecordToString(C);
				MyFile << Line << endl;
			}
		}
	}
	MyFile.close();
}
void DeleteClientFromFile(vector <stClient>& vAllClients)
{
	PrintDeleteClientHead();

	char AskUser = 'Y';
	stClient Client;
	string AccountNum = AskUserAccountNumber();

	if (SearchClientWithAccountNumber(Client, AccountNum, vAllClients))
	{
		PrintClient(Client);

		cout << "\n\nDo you want to delete this client? Y / N ? ";
		cin >> AskUser;

		if (toupper(AskUser) == 'Y')
		{
			MarkOnClient(AccountNum, vAllClients);
			SavingClientsToFile(ClientsFile, vAllClients);
		}
		cout << "\n\nClient Deleted Successfuly.\n\n";

		vAllClients = AddAllClients();
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNum << ") is not found!\n";
	}
}

// (4) Update Client Info
void PrintUpdateHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "-------------------------------------\n";
}
stClient FillClientsInRecord(string AccountNum)
{
	stClient Client;

	Client.AccountNumber = AccountNum;

	cout << "\nPlease Enter A Pin Code ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Please Enter A Name ? ";
	getline(cin, Client.Name);

	cout << "Please Enter A Phone ? ";
	getline(cin, Client.Phone);

	cout << "Please Enter An Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}
void UpdateClientInfo(vector <stClient>& vAllClients)
{
	PrintUpdateHead();

	char AskUser = 'Y';
	stClient Client;
	string AccountNum = AskUserAccountNumber();

	if (SearchClientWithAccountNumber(Client, AccountNum, vAllClients))
	{
		PrintClient(Client);

		cout << "\n\nDo you want to update this client? Y / N ? ";
		cin >> AskUser;

		if (toupper(AskUser) == 'Y')
		{
			for (stClient& C : vAllClients)
			{
				if (C.AccountNumber == AccountNum)
				{
					C = FillClientsInRecord(AccountNum);
					break;
				}
			}
			SavingClientsToFile(ClientsFile, vAllClients);
			cout << "\n\nClient Updated Successfully.\n\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNum << ") is not found!\n";
	}
}

// (5) Find A Client
void PrintClientInfoHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tFind Client Info Screen\n";
	cout << "-----------------------------------\n";
}
void FoundClientInRecord(vector <stClient> vAllClients)
{
	PrintClientInfoHead();

	stClient Client;
	string AccounNum = AskUserAccountNumber();

	if (SearchClientWithAccountNumber(Client, AccounNum, vAllClients))
	{
		PrintClient(Client);

	}
	else
	{
		cout << "\nThis Client (" << AccounNum << ") is not found!\n";
	}
}


// -----------------------------------------------------------------------------


// New Featuer
// (6) Transactions
enum enTrasactions { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4 };

// [1] Deposit Client
void PrintDepositScreen()
{
	system("cls");
	cout << "\n- - - - - - - - - - - - - - - - - -\n";
	cout << "\tDeposit Screen\n";
	cout << "- - - - - - - - - - - - - - - - - -\n";
}
double AddDepositAccount()
{
	double Deposit = 0;
	cout << "\nPlease enter deposit acount? ";
	cin >> Deposit;

	return Deposit;
}
char AskUserToAddDeposit()
{
	char Perform = 'Y';
	cout << "Are you sure you want perform this transaction? y/n ? ";
	cin >> Perform;

	return toupper(Perform);
}
void AddNewDepositInFile(stClient Client, string AccountNum, vector <stClient>& vAllClients)
{
	double Deposit = AddDepositAccount();

	if (AskUserToAddDeposit() == 'Y')
	{
		for (stClient& C : vAllClients)
		{
			if (C.AccountNumber == AccountNum)
			{
				C.AccountBalance += Deposit;
				break;
			}
		}
		SavingClientsToFile(ClientsFile, vAllClients); // save new deposit in file

		cout << "\nDone successfuly new balance is: " << Client.AccountBalance + Deposit << endl;
	}
	else
	{
		cout << "\nYou did not any change in account balance for this client!\n";
	}
}
void AddDipositToClient(vector <stClient>& vAllClients)
{
	PrintDepositScreen();

	stClient Client;
	string AccountNum;

	bool Try = false;
	do
	{
		// Check AccountNubmer for client
		AccountNum = AskUserAccountNumber();
		Try = SearchClientWithAccountNumber(Client, AccountNum, vAllClients);

		if (!Try)
		{
			cout << "\nClient with [" << AccountNum << "] does not exist.\n";
		}

	} while (!Try);

	PrintClient(Client);


	// Add New Deposit To Client in File
	AddNewDepositInFile(Client, AccountNum, vAllClients);

}

// [2] Withdraw
void PrintWithDrawScreen()
{
	system("cls");
	cout << "\n- - - - - - - - - - - - - - - - - -\n";
	cout << "\nWithDraw Screen\n";
	cout << "- - - - - - - - - - - - - - - - - -\n";
}
double SubWithDrawAcount(stClient Client)
{
	double Deposit = 0;

	cout << "\nPlease enter withdraw acount? ";
	cin >> Deposit;

	while (Deposit > Client.AccountBalance)
	{

		cout << "\nAmount Exceeds the balanc, you cannot withdraw up to : " << Client.AccountBalance << endl;

		cout << "\nPlease enter anouther acount? ";
		cin >> Deposit;

	}
	return Deposit;
}
char AskUserToSubWithDraw()
{
	char Perform = 'Y';
	cout << "\nAre you sure you want perform this transaction? y/n ? ";
	cin >> Perform;

	return toupper(Perform);
}
void SubNewDepositInFile(stClient Client, string AccountNum, vector <stClient>& vAllClients)
{

	double Deposit = SubWithDrawAcount(Client);

	if (AskUserToSubWithDraw() == 'Y')
	{
		for (stClient& C : vAllClients)
		{
			if (C.AccountNumber == AccountNum)
			{
				C.AccountBalance -= Deposit;
				break;
			}
		}
		SavingClientsToFile(ClientsFile, vAllClients);// save new withdraw in file

		cout << "\nDone successfuly new balance is: " << Client.AccountBalance - Deposit << endl;
	}
	else
	{
		cout << "\nYou did not any change in account balance for this client!\n";
	}
}
void SubWithdrawToClient(vector <stClient>& vAllClients)
{
	PrintDepositScreen();

	stClient Client;
	string AccountNum;

	bool Try = false;
	do
	{
		// Check AccountNubmer for client
		AccountNum = AskUserAccountNumber();
		Try = SearchClientWithAccountNumber(Client, AccountNum, vAllClients);

		if (!Try)
		{
			cout << "\nClient with [" << AccountNum << "] does not exist.\n";
		}

	} while (!Try);

	PrintClient(Client);

	// Sub New Withdraw To Client in File
	SubNewDepositInFile(Client, AccountNum, vAllClients);
}

// [3] Total Balances
void PrintEachBalanceForClient(stClient Client)
{
	cout << "| " << left << setw(30) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(30) << Client.AccountBalance;

}
double SumTotalBalanceForClients(stClient Client)
{
	double TotalBalances = 0;
	TotalBalances += Client.AccountBalance;

	return TotalBalances;
}
void PrintBalancesScreen(vector <stClient> vAllClients)
{
	system("cls");
	cout << "\n\t\tBalances List (" << vAllClients.size() << ") Client(s).\n";
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(30) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(30) << "Balance";
	cout << "\n--------------------------------------------------------------------------------------\n";

	double TotalBalances = 0;

	for (stClient& C : vAllClients)
	{
		PrintEachBalanceForClient(C);
		TotalBalances += SumTotalBalanceForClients(C);

		cout << endl;
	}
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << right << setw(75) << "Total Balances = " << TotalBalances << endl;
}

// Return to Transactions Menue
void GoBackToTransactionsMenue(vector <stUser> vAllUsers, vector <stClient> vAllClients)
{
	cout << "\nPress any key to go back to Transactions Menue...";
	system("pause>0");

	TransactionsMenueScreen(vAllUsers, vAllClients);
}

// Choose from Transaction menue
enTrasactions ChoiceUserFromTransactions()
{
	short User = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> User;

	return enTrasactions(User);
}
void ChoiceInTransactionMenue(vector <stUser> vAllUsers, vector <stClient>& vAllClients)
{

	enTrasactions Trans = ChoiceUserFromTransactions();

	switch (Trans)
	{
	case enTrasactions::Deposit:
	{
		AddDipositToClient(vAllClients);
		GoBackToTransactionsMenue(vAllUsers, vAllClients);
		break;
	}
	case enTrasactions::Withdraw:
	{
		SubWithdrawToClient(vAllClients);
		GoBackToTransactionsMenue(vAllUsers, vAllClients);
		break;
	}
	case enTrasactions::TotalBalances:
	{
		PrintBalancesScreen(vAllClients);
		GoBackToTransactionsMenue(vAllUsers, vAllClients);
		break;
	}
	case enTrasactions::MainMenue:
	{
		ShowMainMenueScreen(vAllUsers, vAllClients);
		break;
	}
	default:
	{
		WrongItem();
		GoBackToTransactionsMenue(vAllUsers, vAllClients);
		break;
	}

	}
}
void TransactionsMenueScreen(vector <stUser> vAllUsers, vector <stClient>& vAllClients)
{
	system("cls");
	cout << "===========================================\n";
	cout << "\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "=========================================\n";

	ChoiceInTransactionMenue(vAllUsers, vAllClients);

}


// -----------------------------------------------------------------------------


// New Featuer
//  (7) Manage Users
enum enManageUsers { ListUsers = 1, AddNewUsers = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainList = 6 };

// [1] Show List Users
void PrintListUser(stUser Users)
{
	cout << "| " << left << setw(20) << Users.UserName;
	cout << "| " << left << setw(20) << Users.PassWord;
	cout << "| " << left << setw(25) << Users.Permissions;
}
void ShowAllUsersOnScreen()
{
	system("cls");

	vector <stUser> vAllUsers = AddAllUsers();
	cout << "\t\t\t\tUsers List (" << vAllUsers.size() << ") User(s).\n";
	cout << "__________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(20) << "PassWord";
	cout << "| " << left << setw(25) << "Permissions";
	cout << "\n__________________________________________________________________________________________________\n\n";

	

	for (stUser& U : vAllUsers)
	{
		PrintListUser(U);
		cout << endl;
	}

	cout << "\n__________________________________________________________________________________________________\n\n";
}

// [2] Add New User
void PrintAddUserHead()
{
	cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n";
	cout << "\tAdd New User Screen\n";
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
	cout << "\nAdding New User:\n\n";
}
bool SerchUserName(stUser User, vector <stUser> vAllUsers)
{
	for (stUser& U : vAllUsers)
	{
		if (User.UserName == U.UserName)
		{
			cout << "User With [" << User.UserName << "] already exists, ";
			return true;
		}
	}
	return false;
}
bool SerchPassWord(stUser User, vector <stUser> vAllUsers)
{
	for (stUser& U : vAllUsers)
	{
		if (User.PassWord == U.PassWord)
		{
			cout << "User With [" << User.PassWord << "] already exists, ";
			return true;
		}
	}
	return false;
}
short GiveUserAllPermissions()
{
	short AllPermissions = 0;
	char FullAccess = 'Y';

	cout << "\nDo you want to give full access? y/n? ";
	cin >> FullAccess;

	if (toupper(FullAccess) == 'Y')
	{
		AllPermissions = -1;
	}
	return AllPermissions;
}
short GiveUserSomePermissions()
{
	stPermissions UserPer;
	short Permissions = 0;
	char Access = 'Y';

	if (GiveUserAllPermissions() == -1)
		return Permissions += UserPer.AllPermissions;
	
	else
	{
		cout << "\nDo you want to give access to :";
		cout << "\nShow Clients List? y/n? ";
		cin >> Access;

		if (toupper(Access) == 'Y')
			Permissions += UserPer.ShowClients;
		
		cout << "\nAdd New Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += UserPer.AddNewClient;

		cout << "\nDelete Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += UserPer.DeleteClient;

		cout << "\nFind Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += UserPer.FindClient;

		cout << "\nTransactions? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += UserPer.Transactions;

		cout << "\nManage Users? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += UserPer.ManageUsers;
	}
	return Permissions;
}
stUser FillUsersInRecord(vector <stUser> vAllUsers)
{
	stUser User;
	do
	{
		cout << "Enter UserNumber? ";
		getline(cin >> ws, User.UserName);

	} while (SerchUserName(User, vAllUsers));

	do
	{
		cout << "Enter PassWord? ";
		getline(cin, User.PassWord);

	} while (SerchPassWord(User, vAllUsers));

	User.Permissions = GiveUserSomePermissions();

	return User;
}
string ConvertRecordToString(vector <stUser> vAllUsers, string Separator = "#//#")
{
	string Line;
	stUser User = FillUsersInRecord(vAllUsers);

	Line += User.UserName + Separator;
	Line += User.PassWord + Separator;
	Line += to_string(User.Permissions);

	return Line;
}
void AddUserToFile(vector <stUser>& vAllUsers)
{
	fstream MyFile;
	string Line = ConvertRecordToString(vAllUsers);

	MyFile.open(UsersFile, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;
	}
	MyFile.close();

}
void AddNewUser(vector <stUser> &vAllUsers)
{
	char User = 'Y';
	do
	{
		system("cls");
		PrintAddUserHead();
		AddUserToFile(vAllUsers);

		cout << "\n\nUser Added Seccessfully, do You Want To Add A New User? ";
		cin >> User;

	} while (toupper(User) == 'Y');

	vAllUsers = AddAllUsers();
}

// [3] Delete User
void PrintDeleteUserHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tDelete User Screen\n";
	cout << "-----------------------------------\n";
}
string AskUserName()
{
	string UserName;

	cout << "\nPlease enter UserName? ";
	cin >> UserName;

	return UserName;
}
void PrintUser(stUser User)
{
	cout << "\nThe following are the User details:\n";
	cout << "------------------------------------\n";
	cout << "UserName    : " << User.UserName << endl;
	cout << "PassWord    : "   << User.PassWord << endl;
	cout << "Permissions : "   << User.Permissions << endl;
	cout << "------------------------------------\n";
}
bool SearchUserWithUserName(stUser& User, string UserName, vector <stUser> vAllUsers)
{

	for (stUser& U : vAllUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
string ConvertRecordToString(stUser User, string Separator = "#//#")
{
	string Line;

	Line += User.UserName + Separator;
	Line += User.PassWord + Separator;
	Line += to_string(User.Permissions);

	return Line;
}
void MarkOnUser(string UserName, vector <stUser> &vAllUsers)
{

	for (stUser& U : vAllUsers)
	{

		if (U.UserName == UserName)
		{
			U.FlagForRemoveUser = true;
		}
	}
}
void SavingUsersToFile(string UsersFile, vector <stUser> vAllUsers)
{
	fstream MyFile;

	MyFile.open(UsersFile, ios::out);

	if (MyFile.is_open())
	{
		string Line;
		for (stUser& U : vAllUsers)
		{
			if (U.FlagForRemoveUser == false)
			{
				Line = ConvertRecordToString(U);
				MyFile << Line << endl;
			}
		}
	}
	MyFile.close();
}
void DeleteUserFromFile(vector <stUser> &vAllUsers)
{
	PrintDeleteUserHead();

	char AskUser = 'Y';
	stUser User;
	string UserName = AskUserName();

	if (UserName == "Admin")
	{
		cout << "\nYou Cannot Delete This User.";
	}
	else
	{
		if (SearchUserWithUserName(User, UserName, vAllUsers))
		{
			PrintUser(User);

			cout << "\n\nDo you want to delete this User? Y / N ? ";
			cin >> AskUser;

			if (toupper(AskUser) == 'Y')
			{
				MarkOnUser(UserName, vAllUsers);
				SavingUsersToFile(UsersFile, vAllUsers);
			}
			cout << "\n\nUser Deleted Successfuly.\n\n";

			vAllUsers = AddAllUsers();
		}
		else
		{
			cout << "\nUser with UserName (" << UserName << ") is not found!\n";
		}
	}
	
}

// [4] Update User Permissions
void PrintUserUpdateHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tUpdate User Info Screen\n";
	cout << "-------------------------------------\n";
}
stUser FillUsersInRecord(string UserName, vector <stUser> vAllUsers)
{
	stUser User;
	
	User.UserName = UserName;

	do
	{
		cout << "\nEnter PassWord? ";
		getline(cin >> ws, User.PassWord);

	} while (SerchPassWord(User, vAllUsers));

	User.Permissions = GiveUserSomePermissions();

	return User;
}
void UpdateUserInfo(vector <stUser>& vAllUsers)
{
	PrintUserUpdateHead();

	char AskUser = 'Y';
	stUser User;
	string UserName = AskUserName();

	if (UserName == "Admin")
		cout << "\nYou Cannot Update This User.";
	
	else
	{
		if (SearchUserWithUserName(User, UserName, vAllUsers))
		{
			PrintUser(User);

			cout << "\n\nDo you want to update this User? Y / N ? ";
			cin >> AskUser;

			if (toupper(AskUser) == 'Y')
			{
				for (stUser& U : vAllUsers)
				{
					if (U.UserName == UserName)
					{
						U = FillUsersInRecord(UserName, vAllUsers);
						break;
					}
				}
				SavingUsersToFile(UsersFile, vAllUsers);
				cout << "\n\nUser Updated Successfully.\n\n";
			}
		}
		else
		{
			cout << "\nUser with Account Number (" << UserName << ") is not found!\n";
		}
	}
}

// [5] Find User
void PrintUserInfoHead()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tFind User Info Screen\n";
	cout << "-----------------------------------\n";
}
void FoundUserInRecord(vector <stUser> vAllUsers)
{
	PrintUserInfoHead();

	stUser User;
	string UserName = AskUserName();

	if (SearchUserWithUserName(User, UserName, vAllUsers))
		PrintUser(User);

	else
		cout << "\nThis User (" << UserName << ") is not found!\n";
}


// Return to Mange Users menue
void GoBackToManageUsersMenu(vector <stUser> vAllUsers, vector <stClient> vAllClients)
{
	cout << "\n\nPress any key to go back to Manage Users Menue...";
	system("pause>0");
	ManageUsersMenueScreen(vAllUsers, vAllClients);
}


// Choose from Manage Users menue
enManageUsers ChoiceUserFromManageUsers()
{
	short User = 0;
	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> User;

	return enManageUsers(User);
}
void ChoiceInManageUsersMenue(vector <stUser> &vAllUsers, vector <stClient> vAllClients)
{
	
	enManageUsers ManageUser = ChoiceUserFromManageUsers();

	switch (ManageUser)
	{
	case enManageUsers::ListUsers:
	{
		ShowAllUsersOnScreen();
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	case enManageUsers::AddNewUsers:
	{
		AddNewUser(vAllUsers);
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	case enManageUsers::DeleteUser:
	{
		DeleteUserFromFile(vAllUsers);
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	case enManageUsers::UpdateUser:
	{
		UpdateUserInfo(vAllUsers);
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	case enManageUsers::FindUser:
	{
		FoundUserInRecord(vAllUsers);
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	case enManageUsers::MainList:
	{
		ShowMainMenueScreen(vAllUsers, vAllClients);
		break;
	}
	default:
	{
		WrongItem();
		GoBackToManageUsersMenu(vAllUsers, vAllClients);
		break;
	}
	}
}
void ManageUsersMenueScreen(vector <stUser> vAllUsers, vector <stClient> vAllClients)
{
	system("cls");
	cout << "===========================================\n";
	cout << "\tManage Users Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New Users.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "=========================================\n";

	ChoiceInManageUsersMenue(vAllUsers, vAllClients);

}


// -----------------------------------------------------------------------------


// (9) Finish Program
void PrintFinishProgram()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tProgram Ends :-) \n";
	cout << "-----------------------------------\n";
}


// Choce wrong item
void WrongItem()
{

	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tYou Choce wrong item :-( \n";
	cout << "\tPlease, Enter right item!";
	cout << "\n------------------------------------\n";

}


// Return to main menue
void GoBackToMainMenu(vector <stUser> vAllUsers, vector <stClient> vAllClients)
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenueScreen(vAllUsers, vAllClients);
}



//Permissions
string UserLogin = ""; // In this a global variable I will add a User, when i do LogIn with him/er
short TakeNumOfPermission(short User)
{
	stPermissions Perm;

	short NumPerm = 0;
	User == 1 ? NumPerm = Perm.ShowClients : User == 2 ? NumPerm = Perm.AddNewClient : User == 3 ? NumPerm = Perm.DeleteClient :
		User == 4 ? NumPerm = Perm.UpdateClient : User == 5 ? NumPerm = Perm.FindClient : User == 6 ? NumPerm = Perm.Transactions :
		User == 7 ? NumPerm = Perm.ManageUsers : false;

	return NumPerm;
}
bool IsPermissions(vector <stUser> vAllUsers, short User)
{

	short NumPerm = TakeNumOfPermission(User);

	for(stUser &U : vAllUsers)
	{
		if (UserLogin == U.UserName)
			return (U.Permissions & NumPerm) == NumPerm;
	}
	return false;
}
void PrintAccessDenied()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You don't have permission to do this,\n";
	cout << "Pleas contact your admin.\n";
	cout << "------------------------------------\n";
}


// Chooce From Main Menue
enum enMainMenue { ShowAllClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, LogOut = 8, FinishProgram = 9 };
enMainMenue Choices(vector <stUser> vAllUsers, vector <stClient> vAllClients)
{
	short User = 0;
	cout << "Chooce what do you want to do? [1 to 9]? ";
	cin >> User;

	if (IsPermissions(vAllUsers, User))
		return enMainMenue(User);
	
	else
	{
		PrintAccessDenied();
		GoBackToMainMenu(vAllUsers, vAllClients);
	}
}
void ChoiceUser(vector <stUser> vAllUsers, vector <stClient>& vAllClients)
{
	enMainMenue Ask = Choices(vAllUsers, vAllClients);

	switch (Ask)
	{
	case enMainMenue::ShowAllClients:
	{
		ShowAllClientsOnScreen(vAllClients);
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::AddClient:
	{
		AddNewClient(vAllClients);
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::DeleteClient:
	{
		DeleteClientFromFile(vAllClients);
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::UpdateClient:
	{
		UpdateClientInfo(vAllClients);
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::FindClient:
	{
		FoundClientInRecord(vAllClients);
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::Transactions: // 6 Transactions
	{
		TransactionsMenueScreen(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::ManageUsers: // 7 Manage Users
	{
		ManageUsersMenueScreen(vAllUsers, vAllClients);
		break;
	}
	case enMainMenue::LogOut:
	{
		LogIn();
		break;
	}
	case enMainMenue::FinishProgram:
	{
		PrintFinishProgram();
		break;
	}
	default:
	{
		WrongItem();
		GoBackToMainMenu(vAllUsers, vAllClients);
		break;
	}

	}
}


void ShowMainMenueScreen(vector <stUser> vAllUser, vector <stClient>& vAllClients)
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t  Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] LogOut.\n";
	cout << "\t[9] Finish Program.\n";
	cout << "===========================================\n";

	ChoiceUser(vAllUser, vAllClients);
}


// Log in
void ShowLoginScreen()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tLogin Screen\n";
	cout << "-------------------------------------\n";
}
stUser FillUserDataToLogin()
{
	
	stUser UserData;
	
	cout << "Enter UserName? ";
	getline(cin >> ws, UserData.UserName);

	cout << "Enter PassWord? ";
	getline(cin, UserData.PassWord);

	return UserData;
}
bool CheckToLogin(vector <stUser> vAllUser)
{
	stUser UserData = FillUserDataToLogin();

	for (stUser& U : vAllUser)
	{
		if ((UserData.UserName == U.UserName) && (UserData.PassWord == U.PassWord))
		{
			UserLogin = U.UserName;
			return true;
		}
	}
	return false;
}
void LogIn()
{
	vector <stClient> vAllClients = AddAllClients();
	vector <stUser> vAllUser = AddAllUsers();
	ShowLoginScreen();

	bool IsUser;
	do
	{
		IsUser = CheckToLogin(vAllUser);

		if (!IsUser)
		{
			ShowLoginScreen();
			cout << "Invalaid UserName/PassWord!\n";
		}

	} while (!IsUser);

	ShowMainMenueScreen(vAllUser, vAllClients);
}


int main()
{
	

	LogIn();



	system("pause>0");

	return 0;

}