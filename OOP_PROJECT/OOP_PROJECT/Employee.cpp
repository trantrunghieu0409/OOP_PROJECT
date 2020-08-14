#include "Employee.h"
Employee::Employee() :Staff()
{
	stock.loadList("Stock.txt");
}
Employee::Employee(int _ID, string _name, bool _gender, string _phone, string _email, Date _yob, int _nDays):Staff( _ID,  _name,  _gender,  _phone,  _email,  _yob,  _nDays)
{
	stock.loadList("Stock.txt");
}
double Employee::viewSalary()
{
	cout << "Name:" << Staff::getName() << endl;
	cout << "ID:" << Staff::getID() << endl;
	
	double s = 5000000 - Staff::getAbsentDays() * 1000000;
	cout << std::setprecision(3) << std::showpoint << std::fixed;
	cout << "Salary:" << (s < 0 ? 0 : s) << endl;
	return (s<0?0:s);
	
}

void Employee::viewAllProducts()
{
	stock.outputList();
}

void Employee::EnterProductInfo()
{
	cout << "Enter product info :\n";
	Product tmp;
	tmp.input();
	stock.addProduct(tmp);
	stock.saveList("Stock.txt");
	
}

void Employee::exportInvoice()
{
	
}

Product Employee::searchProductById(int _id)
{
	Product* result = stock.searchProductByID(_id);
	if (result == nullptr)
		cout << "Not Found!\n";
	return *result;
}

Product Employee::searchProductByName(string _name)
{
	Product* result = stock.searchProductByName( _name);
	if (result == nullptr)
		cout << "Not Found!\n";
	return *result;
}

void Employee::viewTradeHistory()
{
	listSale.s;
}

void Employee::sellProduct()
{
	cout << "**********SELL PRODUCT**********\n";
	cout << "Enter product:\n";
	cout << "ID:";
	string tmpID;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, tmpID);
	if (!is_number(tmpID))
	{
		do
		{
			cout << "ID must be a number!\n";
			getline(cin, tmpID);
		} while (is_number(tmpID));
	}

	cout << "Quantity:";
	string tmpQuantity;
	getline(cin, tmpQuantity);
	if (!is_number(tmpQuantity))
	{
		do
		{
			cout << "Quantity must be a number!\n";
			getline(cin, tmpQuantity);
		} while (is_number(tmpQuantity));
	}
	Product* soldProducts = stock.searchProductByID(stoi(tmpID));
	if (stock.searchProductByID(stoi(tmpID)) == nullptr)
	{
		cout << "Product:ID " << tmpID << " are out of Stock";
		system("pause");
		return;
	}

	soldProducts -= stoi(tmpQuantity);

	

	listSale.LoadDateSaleList("ID_1.txt");
	listSale.LoadDataSaleList();
	Date* today=new Date;
	Sale* todaySale = nullptr;
	
	todaySale = listSale.FindSale(today->now());

	//if not exit create a new one
	if (todaySale == nullptr)
	{
		listSale.AddSaleDate(today);
		todaySale = new Sale;
	}
	todaySale->AddAtttributeSale(soldProducts, stoi(tmpQuantity));
	listSale.AddSaleData(todaySale);
	listSale.SaveDataSaleList();


}


bool Employee::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
	++it;
	return !s.empty() && it == s.end();
}