#include<iostream>
#include<string>
#include<cctype>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cmath>
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

stClient ClientLogin;

// Declare Functions
void LogIn();
void GoBackToMainMenu(vector <stClient> vAllClients);
void ShowATMMainMenueScreen(vector <stClient>& vAllClients);
void ShowQuickWithdrawMenue(vector <stClient>& vAllClients);



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

// Fill Update Clients  Info In File
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
void SavingClientsToFile(string ClientsFile, vector <stClient> vAllClients)
{
	fstream MyFile;

	MyFile.open(ClientsFile, ios::out);

	if (MyFile.is_open())
	{
		string Line;
		for (stClient& C : vAllClients)
		{
			if (C.AccountNumber == ClientLogin.AccountNumber) 
			{
				C.AccountBalance = ClientLogin.AccountBalance;	// This is fast way
			}
			Line = ConvertRecordToString(C);
			MyFile << Line << endl;
		}
	}
	MyFile.close();
} 


char AskClientToSubWithDraw()
{
	char Perform = 'Y';
	cout << "\nAre you sure you want perform this transaction? y/n ? ";
	cin >> Perform;

	return toupper(Perform);
}
void NewWithdrawOrDepositInFile(char Operator, short WithDraw, vector <stClient>& vAllClients)
{

	if (AskClientToSubWithDraw() == 'Y')
	{
		if (Operator == '-')
		{
			ClientLogin.AccountBalance -= WithDraw; // This is fast way
		}
		else if (Operator == '+')
		{
			ClientLogin.AccountBalance += WithDraw; // This is fast way
		}
		SavingClientsToFile(ClientsFile, vAllClients);// save new withdraw in file

		cout << "\nDone successfuly. New balance is: " << ClientLogin.AccountBalance << endl;
	}
	else
	{
		cout << "\nYou did not any change in your account balance!\n";
	}

}



// [1] Quick Withdraw
void PrintQuickHeadWithDrawScreen()
{
	system("cls");
	cout << "\n======================================\n";
	cout << "\tQuick WithDraw Screen";
	cout << "\n======================================\n";
}
void WrongWithDrawItem()
{
	cout << "\nYou choce wrong item :-( please, try again.\n";
	system("pause>0");
}
short ReadQuickWithDraw()
{
	short QuickWithdraw;

	cout << "\nChoose what to withdraw from [1] to [9]? ";
	cin >> QuickWithdraw;

	return QuickWithdraw;
}
void QuickWithdrawMenue(short Withdraw, vector <stClient>& vAllClients)
{


	if (Withdraw > ClientLogin.AccountBalance)
	{
		cout << "\nThe amount Exceeds Your balance [" << ClientLogin.AccountBalance << "], make anuother choice!\n";
		cout << "Press anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawMenue(vAllClients);
	}
	else
	{
		NewWithdrawOrDepositInFile('-', Withdraw, vAllClients);
	}
	
}
void ChoiceWhatWithDraw(vector <stClient> vAllClients)
{
	short QuickWithDraw = ReadQuickWithDraw();

	switch (QuickWithDraw)
	{
	case 1:
		QuickWithdrawMenue(20, vAllClients);
		break;

	case 2:
		QuickWithdrawMenue(50, vAllClients);
		break;

	case 3:
		QuickWithdrawMenue(100, vAllClients);
		break;

	case 4:
		QuickWithdrawMenue(200, vAllClients);
		break;

	case 5:
		QuickWithdrawMenue(400, vAllClients);
		break;

	case 6:
		QuickWithdrawMenue(600, vAllClients);
		break;

	case 7:
		QuickWithdrawMenue(800, vAllClients);
		break;

	case 8:
		QuickWithdrawMenue(1000, vAllClients);
		break;

	case 9:
		break;

	default:
	{
		WrongWithDrawItem();
		ShowQuickWithdrawMenue(vAllClients);
		break;
	}
	}
}
void ShowQuickWithdrawMenue(vector <stClient>& vAllClients)
{
	PrintQuickHeadWithDrawScreen();

	cout << "\t[1] 20 " << " \t[2] 50\n";

	cout << "\t[3] 100 " << " \t[4] 200\n";

	cout << "\t[5] 400 " << " \t[6] 600\n";

	cout << "\t[7] 800 " << " \t[8] 1000\n";

	cout << "\t[9] Exit\n";
	cout << "======================================\n";

	cout << "Your Balance is " << ClientLogin.AccountBalance;

	ChoiceWhatWithDraw(vAllClients);
}


//[2] Normal Withdraw
void PrintNormalHeadWithDrawScreen()
{
	system("cls");
	cout << "\n======================================\n";
	cout << "\tNormal WithDraw Screen";
	cout << "\n======================================\n";

	cout << "Your Balance is " << ClientLogin.AccountBalance << endl;
}
int ReadNormalWithDraw()
{
	int WithDraw = 0;

	do
	{
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> WithDraw;

		if (WithDraw < 1)
		{
			cout << "\nWrong! Please try agin.\n";
		}

	} while (WithDraw < 1);

	return WithDraw;
}
void NormalWithDraw(vector <stClient> vAllClients)
{
	PrintNormalHeadWithDrawScreen();
	int WithDraw;
	
	do
	{
		
		WithDraw = ReadNormalWithDraw();

		if ((WithDraw % 5 == 0))

			if (ClientLogin.AccountBalance > WithDraw)
				break;
			else
				cout << "\nThe amount Exceeds Your balance [" << ClientLogin.AccountBalance << "], make anuother amount!\n";

	} while (true);

	NewWithdrawOrDepositInFile('-', WithDraw, vAllClients);
}


//[3] Deposit
void PrintNormalHeadDepositScreen()
{
	system("cls");
	cout << "\n======================================\n";
	cout << "\tDeposit Screen";
	cout << "\n======================================\n";
	cout << "Your Balance is " << ClientLogin.AccountBalance << endl;
}
int ReadDeposit()
{
	int Deposit = 0;

	do
	{
		cout << "\nEnter a positive Deposit Amount ? ";
		cin >> Deposit;

		if (Deposit < 1)
		{
			cout << "\nWrong! Please try agin.\n";
		}

	} while (Deposit < 1);

	return Deposit;
}
void NormalDposit(vector <stClient> vAllClients)
{
	PrintNormalHeadDepositScreen();

	int Deposit = ReadDeposit();

	while ((Deposit % 5) != 0)
	{
		Deposit = ReadDeposit();
	}
	NewWithdrawOrDepositInFile('+', Deposit, vAllClients);
}


// [4] Ckeck Balance
void PrintBalanceScreen()
{
	system("cls");
	cout << "\n- - - - - - - - - - - - - - - - - -\n";
	cout << "\tCkeck Balance Screen\n";
	cout << "- - - - - - - - - - - - - - - - - -\n";
}
void ShowClientBalance()
{
	PrintBalanceScreen();
	cout << "Your Balance is " << ClientLogin.AccountBalance << "\n\n";
}


// (6) Finish Program
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


// Return to main ATM menue
void GoBackToMainMenu(vector <stClient> vAllClients)
{
	cout << "\n\nPress any key to go back to ATM Main Menue...";
	system("pause>0");
	ShowATMMainMenueScreen(vAllClients);
}


enum enATMMainMenue{ QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, 
	CheckBalance = 4, LogOut = 5 , FinishProgram = 6 };
enATMMainMenue Choices(vector <stClient> vAllClients)
{
	short Client = 0;
	cout << "Chooce what do you want to do? [1 to 6]? ";
	cin >> Client;

	return (enATMMainMenue)Client;
}
void ChoiceClient(vector <stClient>& vAllClients)
{
	enATMMainMenue Ask = Choices(vAllClients);

	switch (Ask)
	{
	case enATMMainMenue::QuickWithdraw:
	{
		ShowQuickWithdrawMenue(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enATMMainMenue::NormalWithdraw:
	{
		NormalWithDraw(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enATMMainMenue::Deposit:
	{
		NormalDposit(vAllClients);
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enATMMainMenue::CheckBalance:
	{
		ShowClientBalance();
		GoBackToMainMenu(vAllClients);
		break;
	}
	case enATMMainMenue::LogOut:
	{
		LogIn();
		break;
	}
	case enATMMainMenue::FinishProgram:
	{
		PrintFinishProgram();
		break;
	}
	default:
	{
		WrongItem();
		GoBackToMainMenu(vAllClients);
		break;
	}
	}
}


void ShowATMMainMenueScreen(vector <stClient>& vAllClients)
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t  ATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] LogOut.\n";
	cout << "\t[6] Finish Program.\n";
	cout << "===========================================\n";

	ChoiceClient(vAllClients);
}


void ShowLoginScreen()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "\tLogin Screen\n";
	cout << "-------------------------------------\n";
}
stClient FillUserDataToLogin()
{

	stClient ClientData;

	cout << "Enter Account Number? ";
	getline(cin >> ws, ClientData.AccountNumber);

	cout << "Enter PinCode? ";
	getline(cin, ClientData.PinCode);

	return ClientData;
}
bool CheckToLogin(vector <stClient> vAllClients)
{
	stClient UserData = FillUserDataToLogin();

	for (stClient& C : vAllClients)
	{
		if ((UserData.AccountNumber == C.AccountNumber) && (UserData.PinCode == C.PinCode))
		{
			ClientLogin = C;
			return true;
		}
	}
	return false;
}
void LogIn()
{
	vector <stClient> vAllClients = AddAllClients();
	ShowLoginScreen();

	bool IsClient;
	do
	{
		IsClient = CheckToLogin(vAllClients);

		if (!IsClient)
		{
			ShowLoginScreen();
			cout << "Invalaid AccountNumber/PinCode!\n";
		}

	} while (!IsClient);

	ShowATMMainMenueScreen(vAllClients);
}



int main()
{

	LogIn();


	return 0;
}