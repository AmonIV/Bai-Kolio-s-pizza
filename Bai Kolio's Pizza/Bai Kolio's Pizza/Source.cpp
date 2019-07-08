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
	int id = 0;
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
		outfile << id << " " << perprice << " " << sellprice << " " << "0" << endl << name << endl << description << endl;
}

void displayall(ifstream& infile)
{
	string line,name,description;
	while (getline(infile, line))
	{
		getline(infile,name);
		getline(infile, description);
		cout << line << " " << name << " " << description <<endl;
	}
}

void editproduct(ifstream& readfile,ofstream& writefile)
{
	int searchid;
	cout << "Enter the ID of the product you want to edit:";
	cin >> searchid;
	cout << endl;
	cin.get();
	int id,quantity;
	double perprice, sellprice;
	string name, description,dummy;
	if (readfile.is_open())
	{
		if (writefile.is_open())
		{
			while (readfile >> id >> perprice >> sellprice >> quantity)
			{
				getline(readfile, dummy);
				getline(readfile, name);
				getline(readfile, description);
				cout << id;
				if (id == searchid)
				{
					cout << id << " " << perprice << " " << sellprice << " " << name << " " << description << endl;
					cout << "New purchase price:";
					cin >> perprice;
					cout << endl << "New sale price:";
					cin >> sellprice;
					cout << endl << "New name:";
					cin.get();
					getline(cin,name);
					cout << endl << "New description(up to 300 characters):";
					getline(cin,description);
				}
				writefile << id << " " << perprice << " " << sellprice << " " << quantity << endl << name << endl << description << endl;
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
	int id, quantity, wh = 0,newquantity,dif=0,fails;
	double perprice, sellprice,investment,profit,gross;
	string name, description,dummy;
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
			while (readfile >> id >> perprice >> sellprice >> quantity)
			{
				getline(readfile, dummy);
				getline(readfile, name);
				getline(readfile, description);
				if (id == searchid)
				{
					cout << id << " " << perprice << " " << sellprice << " " << quantity << " " << name << " " << description << endl;
					cout << "Enter quantity:";
					cin >> newquantity;
					if (wh == 1)
					{
						dif = newquantity;
						quantity = quantity + newquantity;
					}
					else if (wh == 2)
					{
						dif = newquantity - quantity;
						quantity = newquantity;
					}
				}
				ifstream eread("earnings.txt");
				if (eread.is_open())
				{
					eread >> investment >> gross >> profit >> fails;
				}
				eread.close();
				if (dif > 0)
				{
					investment = investment + (dif * perprice);
				}
				ofstream ewrite("earnings.txt");
				if (ewrite.is_open())
				{
					ewrite << investment << " " << gross << " " << profit << " " << fails;
				}
				ewrite.close();
				writefile << id << " " << perprice << " " << sellprice << " " << quantity << endl << name << endl << description << endl;
			}
		}
	}
}

void runningout(ifstream& qread)
{
	int id, quantity;
	double perprice, sellprice;
	string name, description,dummy;
	if (qread.is_open())
	{
			cout << "Products that are running out:" << endl;
			while (qread >> id >> perprice >> sellprice >> quantity)
			{
				getline(qread, dummy);
				getline(qread, name);
				getline(qread, description);
				if (quantity <= 5)
				{
					cout << id << " " << perprice << " " << sellprice << " " << quantity << " " << name << " " << description << endl;
				}
			}
	}
}

void recordsale(ifstream& readorder,ofstream& writeorder)
{
	int id,quantity,searchid;
	double perprice, sellprice,res=1;
	string name, description,dummy;
	if (readorder.is_open())
	{
		if (writeorder.is_open())
		{
			cout << "Select a product id:";
			cin >> searchid;
			cout << endl;
			while (readorder >> id >> perprice >> sellprice >> quantity)
			{
				getline(readorder, dummy);
				getline(readorder, name);
				getline(readorder, description);
				if (id == searchid)
				{
					ifstream re("earnings.txt");
					int fails;
					double investment, gross, profit;
					if (re.is_open())
					{
						re >> investment >> gross >> profit >> fails;
					}
					re.close();
					gross = gross + sellprice;
					profit = profit + (sellprice - perprice);
					ofstream we("earnings.txt");
					if (we.is_open())
					{
						we << investment << " " << gross << " " << profit << " " << fails;
					}
					we.close();
					quantity--;
					if (quantity < 5)
					{
						cout << "Product is running out!" << endl;
					}
					res = sellprice - perprice;
				}
				writeorder << id << " " << perprice << " " << sellprice << " " << quantity << endl << name << endl << description << endl;
			}
			ofstream order("orders.txt",ios::app);
			if (order.is_open())
			{
				order << searchid << " " << name << " " << sellprice << " " << res << endl;
			}
			order.close();
		}
	}
}

void recordfail(ifstream& readorder, ofstream& writeorder)
{
	int id, quantity, searchid;
	double perprice, sellprice;
	string name, description,dummy;
	if (readorder.is_open())
	{
		if (writeorder.is_open())
		{
			cout << "Select a product id:";
			cin >> searchid;
			cout << endl;
			while (readorder >> id >> perprice >> sellprice >> quantity)
			{
				getline(readorder, dummy);
				getline(readorder, name);
				getline(readorder, description);
				if (id == searchid)
				{
					ifstream re("earnings.txt");
					int fails;
					double investment, gross, profit;
					if (re.is_open())
					{
						re >> investment >> gross >> profit >> fails;
					}
					re.close();
					fails++;
					ofstream we("earnings.txt");
					if (we.is_open())
					{
						we << investment << " " << gross << " " << profit << " " << fails;
					}
					we.close();
					quantity--;
					if (quantity < 5)
					{
						cout << "Product is running out!" << endl;
					}
				}
				writeorder << id << " " << perprice << " " << sellprice << " " << quantity << endl << name << endl << description << endl;
			}
			ofstream order("orders.txt", ios::app);
			if (order.is_open())
			{
				order << searchid << " " << name << " " << perprice << " " << "Order failed" << endl;
			}
			order.close();
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
			ofstream outfile("pizza.txt",ios::app);
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}
		case 2:
		{
			ofstream outfile("drinks.txt",ios::app);
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}
		case 3:
		{
			ofstream outfile("desserts.txt",ios::app);
			if (outfile.is_open())
			{
				addproduct(outfile);
			}
			outfile.close();
			break;
		}
		}
		break;
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
			if (readfile.is_open())
			{
				if (writefile.is_open())
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
			int succ;
			ifstream readfile("drinks.txt");
			ofstream writefile("tempdrinks.txt");
			if (readfile.is_open())
			{
				if (writefile.is_open())
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
			int succ;
			ifstream readfile("desserts.txt");
			ofstream writefile("tempdesserts.txt");
			if (readfile.is_open())
			{
				if (writefile.is_open())
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
			break;
		}
		}
		break;
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
		break;
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
			ifstream infile("pizza.txt");
			if (infile.is_open())
			{
				displayall(infile);
			}
			infile.close();
			int succ;
			ifstream instock("pizza.txt");
			ofstream outstock("temppizza.txt");
			if (instock.is_open())
			{
				if (outstock.is_open())
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
			int succ;
			ifstream instock("drinks.txt");
			ofstream outstock("tempdrinks.txt");
			if (instock.is_open())
			{
				if (outstock.is_open())
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
			int succ;
			ifstream instock("desserts.txt");
			ofstream outstock("tempdesserts.txt");
			if (instock.is_open())
			{
				if (outstock.is_open())
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
			break;
		}
		}
		break;
	}
	case 5 :
	{                                                                           //Showing earnings
		ifstream earnings("earnings.txt");
		double investment, profit,gross;
		int fails;
		if (earnings.is_open())
		{
			earnings >> investment >> gross >> profit >> fails;
			cout << "Money invested:" << investment << "Gross profit:" << gross << " Profit:" << profit << " Fails:" << fails << endl;
		}
		earnings.close();
		break;
	}
	case 6 :                                                                    //Showing products that are running out
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
			ifstream qread("pizza.txt");
			if (qread.is_open())
			{
				runningout(qread);
			}
			qread.close();
			break;
		}
		case 2:
		{
			ifstream qread("drinks.txt");
			if (qread.is_open())
			{
				runningout(qread);
			}
			qread.close();
			break;
		}
		case 3:
		{
			ifstream qread("dessert.txt");
			if (qread.is_open())
			{
				runningout(qread);
			}
			qread.close();
			break;
		}
		}
		break;
	}

	}
}

void Employee()																	//Employee menu
{
	int ch = 0;
	cout << "Choose an action:" << endl;
	cout << "1. Record a sale" << endl;
	cout << "2. Record a failed order" << endl;
	cin >> ch;
	switch (ch)
	{
	case 1:
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
			ifstream readsale("pizza.txt");
			ofstream writesale("temppizza.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordsale(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("pizza.txt");
			succ = rename("temppizza.txt", "pizza.txt");
			if (succ == 0)
			{
				cout << "Order was successful" << endl;
			}
			else
			{
				cout << "Order failed" << endl;
			}
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
			int succ;
			ifstream readsale("drinks.txt");
			ofstream writesale("tempdrinks.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordsale(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("drinks.txt");
			succ = rename("tempdrinks.txt", "drinks.txt");
			if (succ == 0)
			{
				cout << "Order was successful" << endl;
			}
			else
			{
				cout << "Order failed" << endl;
			}
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
			int succ;
			ifstream readsale("desserts.txt");
			ofstream writesale("tempdesserts.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordsale(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("desserts.txt");
			succ = rename("tempdesserts.txt", "desserts.txt");
			if (succ == 0)
			{
				cout << "Order was successful" << endl;
			}
			else
			{
				cout << "Order failed" << endl;
			}
			break;
		}
		}
		break;
	}
	case 2:
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
			ifstream readsale("pizza.txt");
			ofstream writesale("temppizza.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordfail(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("pizza.txt");
			succ = rename("temppizza.txt", "pizza.txt");
			if (succ == 0)
			{
				cout << "Recorded successfully" << endl;
			}
			else
			{
				cout << "Recording failed" << endl;
			}
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
			int succ;
			ifstream readsale("drinks.txt");
			ofstream writesale("tempdrinks.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordfail(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("drinks.txt");
			succ = rename("tempdrinks.txt", "drinks.txt");
			if (succ == 0)
			{
				cout << "Recorded successfully" << endl;
			}
			else
			{
				cout << "Recording failed" << endl;
			}
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
			int succ;
			ifstream readsale("desserts.txt");
			ofstream writesale("tempdesserts.txt");
			if (readsale.is_open())
			{
				if (writesale.is_open())
				{
					recordfail(readsale, writesale);
				}
			}
			readsale.close();
			writesale.close();
			remove("desserts.txt");
			succ = rename("tempdesserts.txt", "desserts.txt");
			if (succ == 0)
			{
				cout << "Recorded successfully" << endl;
			}
			else
			{
				cout << "Recording failed" << endl;
			}
			break;
		}
		}
		break;
	}
	}
}

int main()
{
	int access = 0;
	while (access != 3)
	{
		cout << "What is your access level?" << endl;
		cout << "1. Bai Kolio" << endl;
		cout << "2. Employee" << endl;
		cout << "3. Exit" << endl;
		while (access > 3 || access < 1)
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
		else if (access == 3)
		{
			system("pause");
			return 0;
		}
		access = 4;
	}
	system("pause");
	return 0;
}