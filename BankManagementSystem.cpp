#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<limits>
#include<cstdlib>
#include<ctime>
using namespace std;

class Account {
private:
	string name, accountNumber, address, contact;
	vector<string> accountType;
	float balance = 0.0;

	
public:
	//getters

	virtual float calculateInterest(float amount) const{
		return 0.0f;
	}

	string getAccountNumber() const {
		return accountNumber;
	}
	string getName() const {
		return name;
	}
	string getContact() const {
		return contact;
	}

	string getAddress() const {
		return address;
	}
	float getBalance() const {
		return balance;
	}

	vector<string> getAccountType() const {
		return accountType;
	}

	//setters
	void setAccountNumber(string acc) {
		accountNumber = acc;
	}
	void setName(const string& n) {
		name = n;
	}
	void setContact(const string& c) {
		contact = c;
	}
	void setAddress(const string& a) {
		address = a;
	}
	void setBalance(float b) {
		balance = b;
	}
	void setAccountType(const string& types) {
		accountType.push_back(types);
	}

	//overloading += operator
	Account& operator+=(float amount){
		if (amount <= 0.0f) {
			cout << "\nInvalid deposit amount!";
			return *this;
		}
		float interest = calculateInterest(amount);
		balance += (amount + interest);
		if (interest > 0.0f) {
			cout << "\nInterest added:" << interest << " Rs";
		}
		cout << "\ndeposit amount:" << amount<< " Rs";
		return *this;
	}
	//overloading -= operator
	Account& operator-=(float amount) {
		if (amount <= 0.0f) {
			cout << "Invalid wihtdrawal amount";
			return *this;
		}
		if (amount > balance) {
			cout << "Insufficient funds";
			return *this;
		}
		if ((getBalance() - amount) < 1000.f) {
			cout << "\nMinimum Balance should be 1000Rs. Withdrawal cancelled!";
			return *this;
		}
		balance -= amount;
	
		cout << "\nwithdrawn amount:" << amount << "\nYour new balance:" << balance;
		return *this;
	}

	void displayInfo() const{
			cout << "\nAccount Type:";
			vector<string> typ = getAccountType();
			for (const string& type : typ) {
				cout << " " << type;
			}
			cout << "\nAccount Number:" << getAccountNumber();
			cout << "\nName:" << getName();
			cout << "\nAccount Balance:" << getBalance();
			cout << "\nContact:" << getContact();
			cout << "\nAddress:" << getAddress();
		
	}

	void loadAccount(string accNo) {
		ifstream rd_file("user_acc_details.txt");
		vector<string> lines;
		string line;

		while (getline(rd_file, line)) {
			lines.push_back(line);
		}
		rd_file.close();

		bool found = false;

		for (size_t i = 0; i < lines.size(); i++) {
			if (lines[i].find("Account Number:" + accNo) != string::npos) {
				found = true;
				setAccountNumber(accNo);

				for (int j = i; j >= 0; j--) {
					if (lines[j].find("Account Type:") != string::npos) {
						accountType.clear();
						setAccountType(lines[j].substr(13));
						break;
					}
				}
				for (size_t j = i; j < lines.size(); j++) {
					if (lines[j].find("User:") != string::npos && j != i) {
						break;
					}
					if (line.find("Account Number:") != string::npos) {
						string acc_fil = line.substr(15);
						if (acc_fil == accNo) {
							setAccountNumber(acc_fil);
							found = true;
						}
					}
					else if (lines[j].find("Name:") != string::npos) {
						setName(lines[j].substr(5));
					}
					else if (lines[j].find("Contact:") != string::npos) {
						setContact(lines[j].substr(8));
					}
					else if (lines[j].find("Address:") != string::npos) {
						setAddress(lines[j].substr(8));
					}
					else if (lines[j].find("Balance:") != string::npos) {
						string l_str = lines[j].substr(8);
						if (!l_str.empty()) {
							setBalance(stof(l_str));
							break;
						}
					}
				}
				break;
			}
		}

		if (!found) {
			cout << "Account not found!";
		}
	}

	bool getAgreement() {
		char agree;
		cout << "\nDo you agree with our Terms and Conditions?(Y/N):";
		cin >> agree;

		if (agree == 'Y' || agree == 'y') {
			return true;
		}
		else if (agree == 'N' || agree == 'n') {
			return false;
		}
		else {
			cerr << "\nInvalid Input!";
			return false;
		}

	}

	void createAccount() {
		string temp;
		int userCount = 0;
		ifstream infile("user_acc_details.txt");
		string text;
		while (getline(infile, text)) {
			if (text.find("User:") != string::npos) {
				userCount++;
			}
		}
		infile.close();

		ofstream file("user_acc_details.txt", ios::app);

		cout << "\nEnter your full name:";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, temp);
		setName(temp);
		cout << "\nEnter contact no:";
		cin >> temp;
		setContact(temp);
		cout << "\nEnter your address:";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, temp);
		setAddress(temp);

		srand(static_cast<unsigned int>(time(0)));// seeding or starting no
		auto accGen = []() {   // lambda function to generate random account number
			string acc = "";
			for (int i = 0; i < 12; i++) {
				acc += to_string(rand() % 9 + 1);
			}
			return acc;
			};

		if (!getAgreement()) {
			cout << "\nAccount creation cancelled.\n";
			return;
		}
		cout << "-----------Note your Account Number---------";
		string accNum;
		setAccountNumber("PK" + accGen());
		cout << "\nGenerated Account number -->" << getAccountNumber() << endl;
		cout << "--------------------------------------------";

		if (file.is_open()) {
			file << "\nUser:" << (userCount + 1);
			vector<string> types = getAccountType();
			for (string& t : types) {
				file << "\nAccount Type:" << t;
			}
			file << "\nAccount Number:" << getAccountNumber();
			file << "\nName:" << getName();
			file << "\nContact:" << getContact();
			file << "\nAddress:" << getAddress();


			cout << "\n----------------Account Details-----------------";

			cout << "\nYour Name:" << getName();
			cout << "\nYour Contact no:" << getContact();
			cout << "\nYour Address:" << getAddress();
			cout << "\nYour Account no:" << getAccountNumber() << endl;

			float dep;
			cout << "Enter amount to deposit:";
			cin >> dep;

			setBalance(dep);


			file << "\nBalance:" << getBalance() << " Rs";
			file << "\n--------------------";
			cout << "\nCongratulations your account is created!";
			file.close();

		}
		else {
			cerr << "Error: Unable to open the file";
		}
	}

	//Get account type by index
	string getAccountTypeAt(int index) const {
		if (index >= 0 && index < accountType.size()) {
			return accountType[index];
		}
		return "";
	}



	

	void deposit() {
		string n;
		
		if (!accountNumber.empty()) {
			n = accountNumber;
			cout << "Account Number found..";
		}
		else {
			cout << "Account Number:";
			cin >> n;
		}

		loadAccount(n);

		if (getAccountNumber() != n) {
			return;
		}

		//getting all the lines of file and storing it in a vector
		ifstream infile("user_acc_details.txt");
		vector<string> lines;
		string line;
		while (getline(infile, line)) { //to check all the lines of file
			lines.push_back(line);
		}
		infile.close();

		//finding the account number using for loop
		

		for (size_t i = 0; i < lines.size(); i++) {
			if (lines[i].find("Account Number:" + n) != string::npos) {
				
	

					//getting amount from user to deposit
					
					float amountDeposit;
					cout << "\nEnter amount to deposit:";
					cin >> amountDeposit;

					*this += amountDeposit;

					//rewriting the balance line
					for (size_t j = i; j < lines.size(); j++) {
						if (lines[j].find("User:") != string::npos && j != i) break;

						if (lines[j].find("Balance:") != string::npos) {
							lines[j] = "Balance:" + to_string(getBalance()) + " Rs";
							break;
						}
					}
					break;
			}        
		}

		
			//writing all the lines in the file
			ofstream outfil("user_acc_details.txt");
			for (size_t k = 0; k < lines.size(); k++) {
				outfil << lines[k] << "\n";
			}
			outfil.close();
			cout << "\nDeposit successfully.. your new balance:" << getBalance() << " Rs";
		
		
	}
	void withdraw() {
		string n;
		cout << "Account Number:";
		cin >> n;

		//getting all the lines of file and storing it in a vector
		ifstream infile("user_acc_details.txt");
		vector<string> lines;
		string line;
		while (getline(infile, line)) { //to check all the lines of file
			lines.push_back(line);
		}
		infile.close();

		//finding the account number using for loop
		bool found = false;
		float bal_line_index = -1;
		float oldBalance = 0.0;
		for (size_t i = 0; i < lines.size(); i++) {
			if (lines[i].find("Account Number:") != string::npos) {
				string acc_f = lines[i].substr(15);
				if (acc_f == n) {
					cout << "Account Number found...";
					found = true;

					for (size_t j = i; j < lines.size(); j++) {
						if (lines[j].find("Balance:") != string::npos) {
							bal_line_index = (int)j;
							string balStr = lines[j].substr(8);
							if (!balStr.empty()) {
								oldBalance = stof(balStr);
							}
							setBalance(oldBalance);
							break;
						}
					}



					//getting amount from user to withdraw

					float amountwithdraw;
					cout << "\nEnter amount to withdraw:";
					cin >> amountwithdraw;

					*this -= amountwithdraw;

					//rewriting the balance line

					if (bal_line_index != -1) { // if the balance line exists update balance
						lines[bal_line_index] = "Balance:" + to_string(getBalance()) + " Rs";
					}
					else {
						lines.insert(lines.begin() + i + 1, "Balance:" + to_string(getBalance()) + " Rs");
					}
					break;
				}
			}
		}


		if (found) {
			//writing all the lines in the file
			ofstream outfil("user_acc_details.txt");
			for (size_t k = 0; k < lines.size(); k++) {
				outfil << lines[k] << "\n";
			}
			outfil.close();
			
		}
		else {
			cout << "\nAccount not found...";
		}
			


	}


	
};
class savingsAccount : public Account {
public:
	
	float calculateInterest(float amount) const override{
		return amount * 0.10f;
	}

};

class currentAccount : public Account {
public:
	float calculateInterest(float amount) const override{
		return 0;
	}

};





int main() {
	savingsAccount acc;
	acc.setAccountType("Savings");

	currentAccount acc2;
	acc2.setAccountType("Current");

	while (true) {
		int choice;
		cout << "---------------Bank Mangement System-----------------";
		cout << "\n1. Create Account";
		cout << "\n2. Deposit";
		cout << "\n3. Withdraw";
		cout << "\n4. Show Account Details";
		cout << "\n5. Exit\n";
		cout << "\nEnter your choice:";
		cin >> choice;

		switch (choice) {
		case 1:
			int acc_choice;
			cout << "\nChoose your account type:";
			cout << "\n1." << acc.getAccountTypeAt(0);
			cout << "\n2." << acc2.getAccountTypeAt(0) << "\n";
			cout << "\nEnter your choice(1 or 2):";
			cin >> acc_choice;
			if (acc_choice == 1) {

				savingsAccount obj;
				obj.setAccountType("Savings");
				obj.createAccount();

			}
			else if (acc_choice == 2) {
				currentAccount obj;
				obj.setAccountType("Current");
				obj.createAccount();

			}
			else {
				cout << "Enter Valid Input!(1 for savings and 2 for current account)";
			}
			break;
		case 2:{ 
			string accNum;
			cout << "\nEnter your account number:";
			cin >> accNum;
			ifstream file("user_acc_details.txt");
			string line, type = "Unknown";
			while (getline(file, line)) {
				if (line.find("Account Type:") != string::npos) {
					type = line.substr(13);
				}
				if (line.find("Account Number:" + accNum) != string::npos) {
					break;
				}
			}
			file.close();

			if (type == "Savings") {
				savingsAccount dep_obj_s;
				dep_obj_s.setAccountNumber(accNum);
				dep_obj_s.deposit();
			}
			else if (type == "Current") {
				currentAccount dep_obj_c;
				dep_obj_c.setAccountNumber(accNum);
				dep_obj_c.deposit();
			}
			else {
				cout << "\nAccount not found ";
			}
			break;
			}
		case 3:
			acc.withdraw();
			break;
		case 4:{ 
			string accNo;
			cout << "Enter your account number:";
			cin >> accNo;

			savingsAccount sho_det;
			sho_det.loadAccount(accNo);
			sho_det.displayInfo();
			break;
		}
		case 5:

			exit(0);
			break;
		default:
			cout << "Invalid Input!";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;

		}


		cout << "\n\n";
	}
	return 0;
}
