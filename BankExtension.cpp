#include<iostream>
#include<string>
#include<cctype>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
const string ClientsFile = "BankClients.txt";
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool FlagForRemoveClient = false;
};

enum enMainMenu { ShowAllClients = 1, AddClient = 2, DeletClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, EndProgram = 7 };

// declare those functions
void ShowMainMenueScreen(vector <stClient>& vAllClients);
void TransactionsMenueScreen(vector <stClient>& vAllClients);


// Add String To Vector ( Type stClient ) 
vector <string> SplitStringFromFile(string Line, string Separator)
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
stClient FillRecordFromVector(string Line)
{
	stClient Client;
	vector <string> vEachClient = SplitStringFromFile(Line, "#//#");

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
	stClient EacClient;
	vector <stClient> vAllClients;

	MyFile.open(ClientsFile, ios::in); // Read mode

	if (MyFile.is_open())
	{
		string LineInFile;
		while (getline(MyFile, LineInFile))
		{
			EacClient = FillRecordFromVector(LineInFile);
			vAllClients.push_back(EacClient);
		}
	}
	MyFile.close();

	return vAllClients;
}


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
void PrintAddHead()
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
	MyFile.clear();

}
void AddNewClient(vector <stClient>& vAllClients)
{
	char User = 'Y';
	do
	{
		system("cls");
		PrintAddHead();
		AddClientToFile(vAllClients);

		cout << "\n\nClient Added Seccessfully, do You Want To Add A New Client? ";
		cin >> User;

	} while (toupper(User) == 'Y');

	vAllClients = AddAllClients();
}



// (3) Delete A Client
void PrintDeleteHead()
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
	PrintDeleteHead();

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
void GoBackToTransactionsMenue(vector <stClient> vAllClients)
{
	cout << "\nPress any key to go back to Transactions Menue...";
	system("pause>0");

	TransactionsMenueScreen(vAllClients);
}


// Choose from Transaction menue
enTrasactions ChoiceUserFromTransactions()
{
	short User = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> User;

	return enTrasactions(User);
}
void ChoiceInMenueTransaction(vector <stClient> &vAllClients)
{

	enTrasactions Trans = ChoiceUserFromTransactions();

	switch (Trans)
	{
	case enTrasactions::Deposit:
	{
		AddDipositToClient(vAllClients);
		GoBackToTransactionsMenue(vAllClients);
		break;
	}
	case enTrasactions::Withdraw:
	{
		SubWithdrawToClient(vAllClients);
		GoBackToTransactionsMenue(vAllClients);
		break;
	}
	case enTrasactions::TotalBalances:
	{
		PrintBalancesScreen(vAllClients);
		GoBackToTransactionsMenue(vAllClients);
		break;
	}
	case enTrasactions::MainMenue:
	{
		ShowMainMenueScreen(vAllClients);
	}
	}
}
void TransactionsMenueScreen(vector <stClient>& vAllClients)
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
	
	ChoiceInMenueTransaction(vAllClients);
	
}




// (7) Finish Program
void PrintFinishProgram()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tProgram Ends :-) \n";
	cout << "-----------------------------------\n";
}



 // Return to main menue
void GoBackToMainMenu(vector <stClient> vAllClients)
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenueScreen(vAllClients);
}

// Chooce From Main Menue
enMainMenu Choices()
{
	short User = 0;
	cout << "Chooce what do you want to do? [1 to 7]? ";
	cin >> User;
	return enMainMenu(User);
}
void ChoiceUser(vector <stClient> &vAllClients)
{
	enMainMenu Ask = Choices();

	switch (Ask)
	{
	case enMainMenu::ShowAllClients:
	{
		ShowAllClientsOnScreen(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enMainMenu::AddClient:
	{
		AddNewClient(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enMainMenu::DeletClient:
	{
		DeleteClientFromFile(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enMainMenu::UpdateClient:
	{
		UpdateClientInfo(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enMainMenu::FindClient:
	{
		FoundClientInRecord(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enMainMenu::Transactions: // 6 Transactions
	{
		TransactionsMenueScreen(vAllClients);
		break;
	}
	case enMainMenu::EndProgram:
	{
		PrintFinishProgram();
		break;
	}
	}
}
void ShowMainMenueScreen(vector <stClient>& vAllClients)
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t  Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Fined Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";

	ChoiceUser(vAllClients);

}




int main()
{
	vector <stClient> vAllClients = AddAllClients();

	ShowMainMenueScreen(vAllClients);



	system("pause>0");

	return 0;

}