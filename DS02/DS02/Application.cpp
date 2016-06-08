#include <iostream>
#include <fstream>
#include <string>
#include "Application.h"

using namespace std;

Application::Application()
{

	User* loginedUser = NULL; //�α��� �� �����
	Seller* loginedAdmin = NULL;

	int categorySize = countCategory();

	categoryArray = new Category[categorySize];
	categoryTitleArray = new title[categorySize];

	cout << "Loading..." << endl;
	load_user_file();
	load_product_file();
	load_category_file();
	
}

Application ::~Application()
{
	delete categoryArray;
	delete categoryTitleArray;
}

void Application::run()
{
	int m_Command;
	int menu = 0; //�ʱ� �α��� ����
	int isAdmin = 0;

	bool isLogined; 
	int uid;
	string passwd;

	while (1)
	{
		
		if (menu == 0)
		{
			printMenu(menu);
			cin >> m_Command;
			cin.clear(); //���ڿ� �Է� ����
			cin.ignore();
			while (m_Command < -1 || m_Command >2)
			{
				cout << "�߸��� ���� �Է��Ͽ����ϴ�.\n";
				printMenu(menu);
				cin >> m_Command;
				cin.clear(); //���ڿ� �Է� ����
				cin.ignore();
			}
		}
			
		if (menu == 1)
		{
			while (1)
			{
				cout << "---------------------------------------------------" << endl;
				loginedUser->printUserInfo();
				cout << "---------------------------------------------------" << endl;
				printMenu(menu);
				m_Command = 0;
				cin >> m_Command; //1,2,3,4,5,6
				cin.clear(); //���ڿ� �Է� ����
				cin.ignore();
				if (m_Command == 1 || m_Command == 2 || m_Command == 3 || m_Command == 4 || m_Command == 5 || m_Command == 6)
				{
					m_Command += 2;
					break;
				}

				else
				{
					cout << "�߸��� ���� �Է��ϼ̽��ϴ�." << endl;
				}
			}


		}
			
		if (menu == 2)
		{
			while (1)
			{
				cout << "---------------------------------------------------" << endl;
				loginedSeller->printSellerInfo();
				cout << "---------------------------------------------------" << endl;
				printMenu(menu);
				m_Command = 0;
				cin >> m_Command; //1,2,3,4
				cin.clear(); //���ڿ� �Է� ����
				cin.ignore();
				if (m_Command == 1 || m_Command == 2 || m_Command == 3 || m_Command == 4)
				{
					m_Command += 8;
					break;
				}

				else
				{
					cout << "�߸��� ���� �Է��ϼ̽��ϴ�." << endl;
				}
			}


		}

		switch (m_Command)
		{
		case 1:		// �α���
			cout << "�������Դϱ�? : ";
			cin >> isAdmin;
			cout << "ID : ";
			cin >> uid;
			cin.clear(); //���ڿ� �Է� ����
			cin.ignore();
			cout << "PW : ";
			cin >> passwd;

			if (isAdmin == 0)
			{
				if (uid == 0)
				{
					cout << "�ùٸ� id�� �Էµ��� �ʾҽ��ϴ�." << endl;
				}
				if (isLogined = login(uid, passwd)) //�α����� �Ǹ�
				{
					menu = 1; //�ι�° �Ŵ��� ��µǰ�
				}
				else
				{
					cout << "�α��ο� �����Ͽ����ϴ�." << endl;
				}
			}
			if (isAdmin == 1)
			{
				if (uid == 0)
				{
					cout << "�ùٸ� id�� �Էµ��� �ʾҽ��ϴ�." << endl;
				}
				if (isLogined = loginAdmin(uid, passwd)) //�α����� �Ǹ�
				{
					menu = 2; //�ι�° �Ŵ��� ��µǰ�
				}
				else
				{
					cout << "�α��ο� �����Ͽ����ϴ�." << endl;
				}
			}
			
			break;
		case 2:		//�α׾ƿ�
			isLogined = false;
			loginedUser = NULL;
			logout();
			break;
		case 3:		//��, ���
			searchByCategory();
			break;
		case 4:		//�۱�
			searchById();
			break;
		case 5:		//����
			shoppingManagement();
			break;
		case 6:		//����� ��ȯ
			printItemList();
			break;
		case 7:		//�ŷ����� ��ȸ
			test();
			break;
		case 8:		//���� �޴���
			menu = 0;
			break;
		case 9:
			addItem();
			break;
		case 10:
			replaceItem();
			break;
		case 11:
			deleteItem();
			break;
		case 12:
			menu = 0;
			break;
		case 0:  //����
			return;
		default:
			cout << "�߸��� ���� �Է��Ͽ����ϴ�.\n";
			break;
		}
	}
}
//�޴� ���
void Application::printMenu(int menu)
{
	if (menu == 0)
	{
		cout << "1.�α���" << endl;
		cout << "2.�α׾ƿ�" << endl;
		cout << "0.����" << endl;
		cout << "->";
		return;
	}
	if (menu == 1)
	{
		cout << "1.ī�װ����� �˻��ϱ�" << endl;
		cout << "2.ID�� �˻��ϱ�" << endl;
		cout << "3.���ΰ���" << endl;
		cout << "4.��ü ��ǰ ����Ʈ" << endl;
		cout << "5.��ٱ��� �׽�Ʈ" << endl;
		cout << "6.���� �޴���" << endl;
		cout << "->";
		return;
	}
	if (menu == 2)
	{
		cout << "1. ��ǰ���" << endl;
		cout << "2. ��ǰ����" << endl;
		cout << "3. ��ǰ����" << endl;
		cout << "4. �ڷ�" << endl;
	}
}
//���Ž� �����Լ�
void Application::resetProductList()
{
	Product dummy;

	productList.ResetList();
	for (int i = 0; i < productList.GetLength(); i++)
	{
		productList.GetNextItem(dummy);
		if (dummy.getAmount() == 0)
		{
			productList.Delete(dummy);
		}
	}
}
//��ٱ��� �Է�
void Application::addItemToCart(int pid)
{
	char YN;

	//��ǰ���� ���
	Product temp;

	temp.setProduct(pid, 0, 0, 0, 0, 0, 0, "", "");
	productList.Get(temp);
	temp.printProductInfo(categoryTitleArray);

	cout << "��ǰ�� īƮ�� �����ðڽ��ϱ�?" << endl;
	cout << "Y/N->";
	cin >> YN;

	loginedUser->addItemToShoppingList(pid);
	if (YN == 'Y')
	{
		loginedUser->addItemToCart(pid);
		return;
	}
	else
	{
		return;
	}
}

//������ �߰�
void Application::addItem()
{
	int command = 0;
	int dep = 0;
	bool found = false;

	Product temp;
	int id=0;
	int price=0;
	string name="";
	string picPath="";
	int amount=0;
	int sellerId = loginedSeller->getId();
	int cat[3] = {0};

	cout << "ID : ";
	cin >> id;
	cout << "NAME : ";
	cin >> name;
	cout << "���� : ";
	cin >> picPath;
	cout << "PRICE : ";
	cin >> price;
	cout << "AMOUNT : ";
	cin >> amount;

	while (dep < 3)
	{
		int i = 0;
		for (i = 0; i < categoryArray[0].getSize(); i++)
		{
			if (categoryArray[i].getPrev() == command)
			{
				categoryArray[i].print();
			}
		}
		dep++;
		cout << endl;
		cin >> command;
		cat[dep-1] = command;
	}
	
	temp.setProduct(id, price, amount, sellerId, cat[0], cat[1], cat[2], name, picPath);
	productList.Add(temp);
	cout << "�Է��� �Ϸ�Ǿ����ϴ�." << endl;
	return;
}
//������ ����
void Application::replaceItem()
{
	int command = 0;
	int dep = 0;
	bool found = false;

	Product temp;
	int id = 0;
	int price = 0;
	string name = "";
	string picPath = "";
	int amount = 0;
	int sellerId = loginedSeller->getId();
	int cat[3] = { 0 };

	Product dummy;

	productList.ResetList();
	cout << "ID\t�̸�\t����\t����\t����" << endl;
	for (int i = 0; i < productList.GetLength(); i++)
	{
		productList.GetNextItem(dummy);
		if (dummy.getSellerId() == loginedSeller->getId())
		{
			dummy.printProductList();
			found = true;
		}
	}
	if (found = false)
	{
		cout << "��ǰ�� �����ϴ�." << endl;
	}
	cout << "������ ��ǰID�� �Է��� �ֽʽÿ�. : ";
	cin >> id;
	cout << "NAME : ";
	cin >> name;
	cout << "���� : ";
	cin >> picPath;
	cout << "PRICE : ";
	cin >> price;
	cout << "AMOUNT : ";
	cin >> amount;

	while (dep < 3)
	{
		int i = 0;
		for (i = 0; i < categoryArray[0].getSize(); i++)
		{
			if (categoryArray[i].getPrev() == command)
			{
				categoryArray[i].print();
			}
		}
		dep++;
		cout << endl;
		cin >> command;
		cat[dep - 1] = command;
	}

	temp.setProduct(id, price, amount, sellerId, cat[0], cat[1], cat[2], name, picPath);
	productList.Replace(temp);
	cout << "�Է��� �Ϸ�Ǿ����ϴ�." << endl;
	return;
}
//������ ����
void Application::deleteItem()
{
	int command = 0;
	int dep = 0;
	bool found = false;

	Product temp;
	int id = 0;
	int price = 0;
	string name = "";
	string picPath = "";
	int amount = 0;
	int sellerId = loginedSeller->getId();
	int cat[3] = { 0 };

	Product dummy;

	productList.ResetList();
	cout << "ID\t�̸�\t����\t����\t����" << endl;
	for (int i = 0; i < productList.GetLength(); i++)
	{
		productList.GetNextItem(dummy);
		if (dummy.getSellerId() == loginedSeller->getId())
		{
			dummy.printProductList();
			found = true;
		}
	}
	if (found = false)
	{
		cout << "��ǰ�� �����ϴ�." << endl;
	}
	cout << "������ ��ǰID�� �Է��� �ֽʽÿ�. : ";
	cin >> id;

	temp.setProduct(id, 0, 0, 0, 0, 0, 0, "", "");
	productList.Delete(temp);
	cout << "�Է��� �Ϸ�Ǿ����ϴ�." << endl;
	return;
}
//���ΰ���
void Application::shoppingManagement()
{
	int command;
	LinkedList<int>* userCart;
	Product dummy;
	int i_dummy;

	cout << "1. ��ٱ��� ����" << endl;
	cout << "2. ���γ��� ����" << endl;
	cout << "3. �����ϱ�" << endl;
	cout << "->";
	cin >> command;
	
	if (command == 1)
	{
		userCart = loginedUser->getCartList();
		userCart->ResetList();
		
		cout << "��ٱ��� ���" << endl;
		for (int i = 0; i < userCart->GetLength(); i++)
		{
			userCart->GetNextItem(i_dummy);
			dummy.setId(i_dummy);
			productList.Get(dummy);
			dummy.printProductList();
		}
	}
	if (command == 2)
	{
		userCart = loginedUser->getShoppingList();
		userCart->ResetList();

		cout << "���� ���" << endl;
		for (int i = 0; i < userCart->GetLength(); i++)
		{
			userCart->GetNextItem(i_dummy);
			dummy.setId(i_dummy);
			productList.Get(dummy);
			dummy.printProductList();
		}
	}
	if (command == 3)
	{
		userCart = loginedUser->getCartList();
		userCart->ResetList();

		cout << "���� ���" << endl;
		for (int i = 0; i < userCart->GetLength(); i++)
		{
			userCart->GetNextItem(i_dummy);
			dummy.setId(i_dummy);
			productList.Get(dummy);
			dummy.setAmount(dummy.getAmount() - 1);
			productList.Replace(dummy);
		}
		printItemList();
		resetProductList();
	}
}

//ī�װ��� �˻����
void Application::searchByCategory()
{
	int command = 0;
	int dep = 0;
	bool found = false;

	LinkedList<int>* tempList;

	while (dep < 3)
	{
		for (int i = 0; i < categoryArray[0].getSize(); i++)
		{
			if (categoryArray[i].getPrev() == command)
			{
				categoryArray[i].print();
			}
		}
		dep++;
		cout << endl;
		cin >> command;
	}
	categoryArray[command - 1].setList(productList);
	tempList = categoryArray[command - 1].getList();
	
	int p=-1;
	Product dummy;
	tempList->ResetList();	// ����Ʈ �ʱ�ȭ
	
	// list�� ��� �����͸� ȭ�鿡 ���
	cout << "ID\t�̸�\t����\t����\t����" << endl;
	for (int i = 0; i < tempList->GetLength(); i++)
	{
		tempList->GetNextItem(p);
		dummy.setId(p);
		productList.Get(dummy);
		dummy.printProductList();
	}
	if (found = false)
	{
		cout << "�ش� ī�װ����� ��ǰ�� �����ϴ�." << endl;
	}
	else
	{
		cout << "��ǰ�� �����Ͽ� �ֽʽÿ�" << endl;
		cout << "->";
		cin >> command;
		if (command == 0)
			return;
		else
			addItemToCart(command);
	}
}
//ID�˻����
void Application::searchById()
{
	int command = 0;
	
	cout << "ã���� �ϴ� ID�� �Է��Ͽ� �ֽʽÿ�.";
	cout << "->";
	cin >> command;

	Product temp;
	int found;

	temp.setProduct(command, 0, 0, 0, 0, 0, 0, "", "");
	found = productList.Get(temp);
	if (found)
		addItemToCart(temp.getId());
	else
	{
		cout << "�ش� ID�� ��ǰ�� �����ϴ�." << endl;
		return;
	}
}

//��ȯ �޴� ���
void Application::printItemList()
{
	Product dummy;

	productList.ResetList();
	for (int i = 0; i < productList.GetLength(); i++)
	{
		productList.GetNextItem(dummy);
		dummy.printProductList();
	}
}

void Application::test()
{
	loginedUser->addItemToCart(1);
	loginedUser->addItemToCart(2);
	loginedUser->addItemToCart(3);
	loginedUser->addItemToCart(4);
	loginedUser->addItemToCart(5);
}

//�α��� �Լ�
bool Application::login(int uid, string Password)
{
	User temp;
	string dummy = "";
	int found;

	temp.setUser(uid, Password, dummy);
	found = userList.Get(temp);

	if (!found)
	{
		cout << "���� ����" << endl;
		return false;
	}
	else
	{
		if (temp.getPW() == Password)
		{
			loginedUser = new User(temp);
			return true;
		}
		else
		{
			cout << "��й�ȣ ����" << endl;
			return false;
		}
	}
}

bool Application::loginAdmin(int uid, string Password)
{
	Seller temp;
	string dummy = "";
	int found;

	temp.setSeller(uid, Password, dummy, 0, 0);
	found = sellerList.Get(temp);

	if (!found)
	{
		cout << "���� ����" << endl;
		return false;
	}
	else
	{
		if (temp.getPW() == Password)
		{
			loginedSeller = new Seller(temp);
			return true;
		}
		else
		{
			cout << "��й�ȣ ����" << endl;
			return false;
		}
	}
}

bool Application::logout()
{
	//saveFiles(); //DB����
	loginedUser = NULL; //�α��� ���� �ʱ�ȭ
	cout << "LOGOUT!" << endl;
	return true;
}


int Application::countCategory()
{
	fstream ifs;
	ifs.open("category.txt");

	if (!ifs) //���Ͼ��� ��� ����ó��
	{
		cerr << "ī�װ��� DB�� �ҷ����� ���߽��ϴ�." << endl;
		cerr << "���α׷��� �����մϴ�." << endl;
		exit(100);
	}

	int index = 0;

	int id = 0;
	int dep = 0;
	int prev = 0;
	string name = "";

	//������
	while (!ifs.eof()) {
		ifs >> id >> prev >> name >> dep;
		index++;
	}
	ifs.close();

	return index;
}

void Application::load_user_file()
{
	fstream ifs;
	ifs.open("users.txt");

	if (!ifs) //���Ͼ��� ��� ����ó��
	{
		cerr << "����� DB�� �ҷ����� ���߽��ϴ�." << endl;
		cerr << "���α׷��� �����մϴ�." << endl;
		exit(100);
	}

	int index = 0;
	int isAdmin = 0;
	//���� �ʱ�ȭ
	int id=0;
	string password="";
	string name="";
	int accountNumber=0;
	int balance=0;
	int creditRating=0;
	int regitNum = 0;
	int phone = 0;
	User temp;
	Seller temp2;

	//������
    while(!ifs.eof()){
		ifs >> isAdmin;
		if (isAdmin == 0)
		{
			ifs >> id >> password >> name;
			temp.setUser(id, password, name);
			userList.Add(temp);
			index++;
		}
		else
		{
			ifs >> id >> password >> name >> phone >> regitNum;
			temp2.setSeller(id, password, name, phone, regitNum);
			sellerList.Add(temp2);
			index++;
		}
    }
    ifs.close();
    return;
}
void Application::load_product_file()
{
	fstream ifs;
	ifs.open("products.txt");  

	if (!ifs)//���Ͼ��� ��� ����ó��
	{
		cerr << "�ŷ����� DB�� �ҷ����� ���߽��ϴ�." << endl;
		cerr << "���α׷��� �����մϴ�." << endl;
		exit(100);
	}

	int index = 0;
	//���� �ʱ�ȭ
	int id = 0;
	int price = 0;
	int amount = 0;
	int sellerId = 0;
	int cat_1 = 0;
	int cat_2 = 0;
	int cat_3 = 0;
	string name = "";
	string picPath = "";
	Product temp;

	//������
	while (!ifs.eof()) {
		ifs >> id >> name >> price >> amount >> sellerId >> cat_1 >> cat_2 >> cat_3 >> picPath;
		temp.setProduct(id, price, amount, sellerId, cat_1, cat_2, cat_3, name, picPath);
		productList.Add(temp);
		index++;
	}

	productList.ResetList();	// ����Ʈ �ʱ�ȭ
							// list�� ��� �����͸� ȭ�鿡 ���
	for (int i = 0; i < productList.GetLength(); i++)
	{
		productList.GetNextItem(temp);
	}

	ifs.close();



	return;
}
void Application::load_category_file()
{
	fstream ifs;
	ifs.open("category.txt");

	if (!ifs) //���Ͼ��� ��� ����ó��
	{
		cerr << "ī�װ��� DB�� �ҷ����� ���߽��ϴ�." << endl;
		cerr << "���α׷��� �����մϴ�." << endl;
		exit(100);
	}

	int index = 0;
	//���� �ʱ�ȭ
	int id = 0;
	int dep = 0;
	int prev = 0;
	string name = "";

	//������
	while (!ifs.eof()) {
		ifs >> id >> prev >> name >> dep;
		categoryArray[index].setCategory(id, prev, name, dep);
		categoryTitleArray[index].category_id = id;
		categoryTitleArray[index].category_title = name;
		index++;
	}
	ifs.close();
	return;
}