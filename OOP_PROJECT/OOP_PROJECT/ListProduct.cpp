#include "ListProduct.h"
#include "Libary.h"
ListProduct::~ListProduct()
{
	for (auto &x : listProduct)
		if (x)
			delete x;
}
ListProduct::ListProduct(const ListProduct &list)
{
	for (Product *product : list.listProduct)
		addProduct(*product);
}
ListProduct &ListProduct::operator=(ListProduct list)
{
	swap(listProduct, list.listProduct);
	return *this;
}
int ListProduct::addProduct(Product &product)
{
	if (!searchProduct(product.getID()))
	{
		listProduct.push_back(new Product(product));
		return (int)ErrorCode::OK;
	}
	return (int)ErrorCode::Unable_to_find;
}

int ListProduct::deleteProduct(int ID)
{
	ErrorCode err;
	Product *p = searchProduct(ID);
	if (!p)
	{
		err = ErrorCode::Unable_to_find;
	}
	else
	{
		delete p;
		p = nullptr;
		for (vector<Product *>::iterator x = listProduct.begin(); x != listProduct.end(); ++x)
		{
			if (*x == nullptr)
				listProduct.erase(x);
		}
		err = ErrorCode::OK;
	}
	return (int)err;
}

int ListProduct::importProduct(int ID, int stock)
{
	if (stock < 0 || ID < 0)
		return (int)ErrorCode::Invalid_parameter;
	Product *p = searchProduct(ID);
	if (p)
	{
		*p += stock;
		return (int)ErrorCode::OK;
	}
	return (int)ErrorCode::Unable_to_find;
}

int ListProduct::exportProduct(int ID, int stock)
{
	if (stock < 0 || ID < 0)
		return (int)ErrorCode::Invalid_parameter;
	Product *p = searchProduct(ID);
	if (p)
	{
		if (p->getStock() < stock)
			return (int)ErrorCode::Not_enough_stock;
		*p -= stock;
		return (int)ErrorCode::OK;
	}
	return (int)ErrorCode::Unable_to_find;
}

Product *ListProduct::searchProduct(int ID)
{
	if (ID < 0)
		return nullptr;
	for (Product *&product : listProduct)
		if (product->getID() == ID)
			return product;
	return nullptr;
}
Product *ListProduct::searchProduct(string name)
{
	for (Product *&product : listProduct)
		if (product->getName() == name)
			return product;
	return nullptr;
}
int ListProduct::size()
{
	return listProduct.size();
}
int ListProduct::totalProducts()
{
	int n = 0;
	for (auto &product : listProduct)
		n += product->getStock();
	return n;
}
int ListProduct::countProduct(int ID)
{
	return searchProduct(ID)->getStock();
}
ListProduct &ListProduct::getListOfExpiredProduct()
{
	ListProduct *list = new ListProduct;
	for (auto &product : listProduct)
		if (product->isExpired())
			list->addProduct(*product);
	return *list;
}
ListProduct &ListProduct::getListOfZeroStock()
{
	ListProduct *list = new ListProduct;
	for (auto &product : listProduct)
		if (product->getStock() == 0)
			list->addProduct(*product);
	return *list;
}
double ListProduct::getPrice(int ID)
{
	Product *p = searchProduct(ID);
	return (p) ? p->getPrice() : -1;
}
double ListProduct::totalPrice()
{
	double total = 0.0;
	for (auto &product : listProduct)
		total += product->getStock() * product->getPrice();
	return total;
}
void ListProduct::outputList()
{
	int n = listProduct.size();
	cout << "Number of type of products: " << n << endl;
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << "Product " << i + 1 << " :" << endl;
		listProduct[i]->output();
	}
}
void ListProduct::loadList(const string &sourceProducts)
{
	ifstream fin(sourceProducts);
	int n;
	fin >> n;
	Product p;
	for (int i = 0; i < n; ++i)
	{
		p.load(fin);
		addProduct(p);
	}
	fin.close();
}
void ListProduct::inputList()
{
	int n;
	Product p;
	cout << "Number of type of products: ";
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "Product " << i + 1 << " :" << endl;
		p.input();
		addProduct(p);
	}
}
void ListProduct::saveList(const string &sourceProducts)
{
	ofstream fout(sourceProducts);
	fout << listProduct.size()<<endl;
	for (Product *&product : listProduct)
		product->save(fout);
	fout.close();
}

Product *ListProduct::searchProductByID(int _id)
{
	// if (_id < 0)
	// 	return nullptr;
	// sort(listProduct.begin(), listProduct.end(), [](Product *&left, Product *&right) {
	// 	return (left->getID() < right->getID());
	// });

	// vector<Product*>::iterator it = lower_bound(listProduct.begin(), listProduct.end(),_id, [](Product *&left, Product *&right) {
	// 	return (left->getID() > right->getID());
	// });
	// if (it == listProduct.end() || (*it)->getID() != _id)
	// {
	// 	return nullptr;
	// }
	// else
	// {
	// 	std::size_t idx = std::distance(listProduct.begin(), it);
	// 	return listProduct[idx];
		
	// }
	if (_id < 0)
		return nullptr;
	for (int i = 0; i < listProduct.size(); i++)
	{
		if (listProduct[i]->getID() == _id)
			return listProduct[i];
	}
	return nullptr;
}
	Product *ListProduct::searchProductByName(string _name)
	{
	// 
	for (int i = 0; i < listProduct.size(); i++)
		{
			if (listProduct[i]->getName() == _name)
				return listProduct[i];
		}
		return nullptr;
	}