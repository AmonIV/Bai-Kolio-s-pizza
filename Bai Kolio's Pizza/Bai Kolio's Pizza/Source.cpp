#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//void createfi()
//{
	//ofstream cr("idtr.txt");
	//if (cr.is_open())
	//{
		//cr << "0";
		//cout << "done";
	//}
	//cr.close();
//}

int getid()
{
	int id=0;
	ifstream idfile("idtr.txt");
	if (idfile.is_open())
	{
		idfile >> id;
	}
	idfile.close();
	return id;
}

int getidup()
{
	int id = 0;
	ifstream idfile("idtr.txt");
	if (idfile.is_open())
	{
		idfile >> id;
	}
	idfile.close();
	id++;
	ofstream upfile("idtr.txt");
	if (upfile.is_open())
	{
		upfile << id;
	}
	upfile.close();
	return id;
}

void addproduct(ofstream& outfile)
{
		int id = getidup();
		double perprice, sellprice;
		char name[30], description[300];
		cout << "Enter product purchase price:";
		cin >> perprice;
		cout << endl;
		cout << "Enter product sale price:";
		cin >> sellprice;
		cout << endl;
		cout << "Enter product name:";
		cin.get();
		cin.getline(name, 30);
		cout << endl;
		cout << "Enter product description(up to 300 characters):";
		cin.getline(description, 300);
		cout << endl;
		outfile << id << " " << perprice << " " << sellprice << " " << name << " " <<"0 "<< description << endl;
}

void displayall(ifstream& infile)
{
	string line;
	while (getline(infile, line))
	{
		cout << line << endl;
	}
}

void editproduct(ifstream& readfile,ofstream& writefile)
{
	int searchid;
	cout << "Enter the ID of the product you want to edit:";
	cin >> searchid;
	cout << endl;
	int id,quantity;
	double perprice, sellprice;
	char name[30], description[300];
	if (readfile.is_open())
	{
		if (writefile.is_open())
		{
			while (readfile >> id >> perprice >> sellprice >> name >> quantity >> description)
			{
				if (id == searchid)
				{
					cout << id << " " << perprice << " " << sellprice << " " << name << " " << description << endl;
					cout << "New purchase price:";
					cin >> perprice;
					cout << endl << "New sale price:";
					cin >> sellprice;
					cout << endl << "New name:";
					cin.get();
					cin.getline(name, 30);
					cout << endl << "New description(up to 300 characters):";
					cin.getline(description, 300);
				}
				writefile << id << " " << perprice << " " << sellprice << " " << name << " " << quantity << " " << description << endl;
			}
		}
	}
}

void restockproduct(ifstream& readfile, ofstream& writefile)
{
	int searchid;
	cout << "Enter the ID of the product you want to edit:";
	cin >> searchid;
	cout << endl;
	int id, quantity, wh = 0,newquantity;
	double perprice, sellprice;
	char name[30], description[300];
	cout << "Do you want to add to or set the quantity of the product?" << endl;
	cout << "1. Add" << endl;
	cout << "2. Set" << endl;
	while (wh > 2 || wh < 1)
	{
		cin >> wh;
	}
	if (readfile.is_open())
	{
		if (writefile.is_open())
		{
			while (readfile >> id >> perprice >> sellprice >> name >> quantity >> description)
			{
				if (id == searchid)
				{
					cout << id << " " << perprice << " " << sellprice << " " << name << " " << quantity << " " << description << endl;
					cout << "Enter quantity:";
					cin >> newquantity;
					if (wh == 1)
					{
						quantity = quantity + newquantity;
					}
					else if (wh == 2)
					{
						quantity = newquantity;
					}
				}
				writefile << id << " " << perprice << " " << sellprice << " " << name << " " << quantity << " " << description << endl;
			}
		}
	}
}

void BaiKolio()																	//Bai Kolio menu
{
	int ch = 0;

	cout << "Choose an action:" << endl;
	cout << "1. Add a product" << endl;
	cout << "2. Edit a product" << endl;
	cout << "3. Show all products" << endl;
	cout << "4. Restock product" << endl;
	cout << "5. Show earnings" << endl;
	cout << "6. Show products that are running out" << endl;
	while (ch < 1 || ch>6)
	{
		cin >> ch;
	}
	cin >> ch;
	switch (ch)
	{
	case 1:                                                                     //Adding a product
	{
		int op = 0;
		cout << "Choose category:" << endl;
		cout << "1. Pizza" << endl;
		cout << "2. Drinks" << endl;
		cout << "3. Desserts" << endl;
		while (op < 1 || op>3)
		{
			cin >> op;
		}
		switch (op)
		{
		case 1:
		{
			ofstream outfile("pizza.txt");
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}
		case 2:
		{
			ofstream outfile("drinks.txt");
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}
		case 3:
		{
			ofstream outfile("desserts.txt");
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}

		}
	}
	case 2 :                                                                     //Editing product
	{
		int op = 0;
		cout << "Choose category:" << endl;
		cout << "1. Pizza" << endl;
		cout << "2. Drinks" << endl;
		cout << "3. Desserts" << endl;
		while (op < 1 || op>3)
		{
			cin >> op;
		}
		switch (op)
		{
		case 1:
		{
			ifstream infile("pizza.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			int succ;
			ifstream readfile("pizza.txt");
			ofstream writefile("temppizza.txt");
			if (readfile.is_open)
			{
				if (writefile.is_open)
				{
					editproduct(readfile, writefile);
				}
			}
			readfile.close();
			writefile.close();
			remove("pizza.txt");
			succ=rename("temppizza.txt", "pizza.txt");
			if (succ == 0)
			{
				cout << "product successfully edited!" << endl;
			}
			else
			{
				cout << "error editing product" << endl;
			}
		}
		case 2:
		{
			ifstream infile("drinks.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			int succ;
			ifstream readfile("drinks.txt");
			ofstream writefile("tempdrinks.txt");
			if (readfile.is_open)
			{
				if (writefile.is_open)
				{
					editproduct(readfile, writefile);
				}
			}
			readfile.close();
			writefile.close();
			remove("drinks.txt");
			succ=rename("tempdrinks.txt", "drinks.txt");
			if (succ == 0)
			{
				cout << "product successfully edited!" << endl;
			}
			else
			{
				cout << "error editing product" << endl;
			}
		}
		case 3:
		{
			ifstream infile("desserts.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			int succ;
			ifstream readfile("desserts.txt");
			ofstream writefile("tempdesserts.txt");
			if (readfile.is_open)
			{
				if (writefile.is_open)
				{
					editproduct(readfile, writefile);
				}
			}
			readfile.close();
			writefile.close();
			remove("desserts.txt");
			succ=rename("tempdesserts.txt", "desserts.txt");
			if (succ == 0)
			{
				cout << "product successfully edited!" << endl;
			}
			else
			{
				cout << "error editing product" << endl;
			}
		}
		}
	}
	case 3 :                                                                    //Displaying table
	{
		int op = 0;
		cout << "Choose category:" << endl;
		cout << "1. Pizza" << endl;
		cout << "2. Drinks" << endl;
		cout << "3. Desserts" << endl;
		while (op < 1 || op>3)
		{
			cin >> op;
		}
		switch (op)
		{
		case 1:
		{
			ifstream infile("pizza.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			break;
		}
		case 2:
		{
			ifstream infile("drinks.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			break;
		}
		case 3:
		{
			ifstream infile("desserts.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			break;
		}
		}
	}
	case 4 :                                                                    //Restocking product
	{
		int op = 0;
		cout << "Choose category:" << endl;
		cout << "1. Pizza" << endl;
		cout << "2. Drinks" << endl;
		cout << "3. Desserts" << endl;
		while (op < 1 || op>3)
		{
			cin >> op;
		}
		switch (op)
		{
		case 1:
		{
			int succ;
			ifstream instock("pizza.txt");
			ofstream outstock("temppizza.txt");
			if (instock.is_open)
			{
				if (outstock.is_open)
				{
					restockproduct(instock, outstock);
				}
			}
			instock.close();
			outstock.close();
			remove("pizza.txt");
			succ = rename("temppizza.txt", "pizza.txt");
			if (succ == 0)
			{
				cout << "quantity successfully edited!" << endl;
			}
			else
			{
				cout << "error editing quantity" << endl;
			}
		}
		case 2:
		{
			int succ;
			ifstream instock("drinks.txt");
			ofstream outstock("tempdrinks.txt");
			if (instock.is_open)
			{
				if (outstock.is_open)
				{
					restockproduct(instock, outstock);
				}
			}
			instock.close();
			outstock.close();
			remove("drinks.txt");
			succ = rename("tempdrinks.txt", "drinks.txt");
			if (succ == 0)
			{
				cout << "quantity successfully edited!" << endl;
			}
			else
			{
				cout << "error editing quantity" << endl;
			}
		}
		case 3:
		{
			int succ;
			ifstream instock("desserts.txt");
			ofstream outstock("tempdesserts.txt");
			if (instock.is_open)
			{
				if (outstock.is_open)
				{
					restockproduct(instock, outstock);
				}
			}
			instock.close();
			outstock.close();
			remove("desserts.txt");
			succ = rename("tempdesserts.txt", "desserts.txt");
			if (succ == 0)
			{
				cout << "quantity successfully edited!" << endl;
			}
			else
			{
				cout << "error editing quantity" << endl;
			}
		}
		}
	}
	//case 5 :
	//case 6 :

	}
}

void Employee()																	//Employee menu
{
	int ch = 0;
	cout << "Choose an action:" << endl;
	cout << "1. Record a sale" << endl;
	cout << "2. Record a failed order" << endl;
	cin >> ch;
	//switch (ch)
	//{
	//case 1:
	//case 2:
	//}
}

int main()
{
	int access = 0;
	cout << "What is your access level?" << endl;
	cout << "1. Bai Kolio" << endl;
	cout << "2. Employee" << endl;
	while (access > 2 || access < 1)
	{
		cin >> access;
	}
	system("cls");
	if (access == 1)
	{
		BaiKolio();
	}
	else if (access == 2)
	{
		Employee();
	}
	//else if (access == 3)
	//{
		//createfi();
	//}
	system("pause");
	return 0;
}