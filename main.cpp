#include <stdio.h>
#include "Binary_tree.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include "time.h"
#include <fstream>
#include <random>
using namespace std;

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224))key = _getch();
	return key;
}
int check_int()
{
	int num = 0;
	while (!(cin >> num) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "������� ���������� ��������...\n";
	}
	return num;
}

void intersection(b_tree* A, binary_tree* B, int** answer, int* i)
{
	if (B)
	{
		if (A->contains(B->data) == true)
		{
			(*answer)[*i] = B->data;
			(*i) += 1;
		}
		intersection(A, B->left, answer, i);
		intersection(A, B->right, answer, i);
	}
}
void difference(b_tree* A, binary_tree* B, int** answer, int* i)
{
	if (B)
	{
		if (A->contains(B->data) == true)
		{
			(*answer)[*i] = B->data;
			(*i) += 1;
		}
		intersection(A, B->left, answer, i);
		intersection(A, B->right, answer, i);
	}
}
int check_available(int num_tree, int size)
{
	num_tree = check_int();
	while (num_tree > size || num_tree < 0)
	{
		cout << "\n ������ ������ ���, ������� ���������� �����: ";
		num_tree = check_int();
	}
	return num_tree;
}

b_tree task1(bool check, int current, int* size, b_tree* array)
{
	int* answer = new int[100];
	int num_tree = -3, i = 0;
	if (check == 1)
	{
		cout << "������� ����� ������, � ������� �� ������ ��������� ����������� (�� 1 �� " << *size << " ) : ";
		num_tree = check_available(num_tree, *size);
		intersection(&array[current], array[num_tree - 1].get_root(), &answer, &i);

		system("cls");
		cout << "������ 1:\n";
		array[current].print_tree(array[current].get_root());
		cout << "\n U \n";
		cout << "������ 2:\n";
		array[num_tree - 1].print_tree(array[num_tree - 1].get_root());
		cout << "\n = \n";
		cout << "������ 3:\n";
		if (i == 0)
		{
			cout << " ������� ��������� " << endl;
			throw exception();
		}
		b_tree new_tree(answer[0]);
		for (int j = 0; j < i; j++)
		{
			new_tree.insert(answer[j]);
		}
		new_tree.print_tree(new_tree.get_root());
		system("pause");
		return new_tree;
	}
	else
	{
		cout << "������� ����� ������, � ������� �� ������ ��������� (�� 1 �� " << *size << " ) : ";
		num_tree = check_available(num_tree, *size);
		difference(&array[num_tree - 1], array[current].get_root(), &answer, &i);

		system("cls");
		cout << "������ 1:\n";
		array[current].print_tree(array[current].get_root());
		cout << "\n - \n";
		cout << "������ 2:\n";
		array[num_tree - 1].print_tree(array[num_tree - 1].get_root());
		cout << "\n = \n";
		cout << "������ 3:\n";

		if (i == 0)
		{
			cout << " ������� ��������� " << endl;
			throw exception();
		}

		b_tree new_tree(answer[0]);
		cout << answer[0];

		for (int j = 1; j < i; j++)
		{
			new_tree.insert(answer[j]);
		}
		new_tree.print_tree(new_tree.get_root());
		system("pause");

		return new_tree;
	}
}
void print_array(b_tree* array, int current, int size)
{

	if (size == 0) cout << "��� �������� \n\n";
	else
	{
		cout << "������ �" << (current + 1) << "\n";
		array[current].print_tree(array[current].get_root());
	}
}

b_tree* add_node(b_tree* array, int current)
{
	cout << "������� �������� ������ ����  " << ":" << endl;
	int data = check_int();
	while (array[current].contains(data) == true)
	{
		cout << "����� �������� ��� ����, ����� ������ �������� �� ����������!" << endl;
		data = check_int();
	}
	bool check = array[current].insert(data);
	if (check)
	{
		cout << "���������� ���� ������ �������!\n";
		system("pause");
	}
	return array;
}
b_tree* delete_all_tree(b_tree* array, int* current, int* size)
{
	delete[] array;
	array = NULL;
	*current = 0;
	*size = 0;
	cout << "������� ������ ���..\n";
	system("pause");
	return NULL;
}
b_tree* delete_one_tree(b_tree* array, int* current, int* size)
{
	if (*size == 1)
		return delete_all_tree(array, current, size);
	int tmp_current = *current;
	b_tree* new_array = new b_tree[*size - 1];
	for (int i = 0; i < *size; i++)
	{
		if (i < tmp_current)
			new_array[i] = array[i];
		else if (i == tmp_current)
		{
			array[i].delete_tree(array[i].get_root());
		}
		else  if (i >= tmp_current)
			new_array[i - 1] = array[i];
	}
	*size -= 1;
	cout << "�������� ������ ������ �������!\n";
	system("pause");
	return new_array;
}

b_tree* del_node(b_tree* array, int* current, int* size)
{
	cout << "������� �������� ���������� ����  " << ":" << endl;
	int data = check_int();
	while (array[*current].contains(data) == false)
	{
		cout << "������ �������� ���, ����� ������ ��, ������� ����!" << endl;
		data = check_int();
	}
	bool check = array[*current].erase(data);
	if (check)
	{
		cout << "�������� ���� ������ �������!\n";
		system("pause");
	}
	if (array[*current].get_root() == NULL)
	{
		delete_one_tree(array, current, size);
	}
	return array;

}
b_tree create_random_tree()
{
	srand(time(0));
	cout << "������� ���-�� ��������� � ������: ";
	int n = 0;
	n = check_int();
	while (n <= 0 || n > 10)
	{
		cout << "������� �������� ������ ����... �� ������ 10\n";
		n = check_int();
	}
	int a = -100 + rand() % 200;
	b_tree new_tree(a);

	for (int i = 0; i < n - 1; i++)
	{
		a = -100 + rand() % 200;
		while (new_tree.insert(a) == false)
		{
			a = -100 + rand() % 200;
		}
	}
	return new_tree;
}
b_tree create_new_tree()
{
	cout << "������� ���-�� ��������� � ������: ";
	int n = 0;
	n = check_int();
	while (n <= 0 || n > 10)
	{
		cout << "������� �������� ������ ����... �� ������ 10\n";
		n = check_int();
	}


	cout << "������� �������� �����: ";
	int a = check_int();
	b_tree new_tree(a);

	for (int i = 0; i < n - 1; i++)
	{
		cout << "������� �������� ���� � " << i + 1 << ":" << endl;
		a = check_int();
		while (new_tree.insert(a) == false)
		{
			cout << "����� �������� ��� ����, ����� ������ �������� �� ����������!" << endl;
			a = check_int();
		}
	}
	return new_tree;
}
b_tree* add_tree(b_tree* array, int current, int* size, b_tree new_tree)
{

	b_tree* new_array = new b_tree[*size + 1];

	for (int i = 0; i < *size + 1; i++)
	{
		if (i < current)
			new_array[i] = array[i];
		else if (i == current)
			new_array[i] = new_tree;
		else if (i > current)
			new_array[i] = array[i - 1];
	}
	*size += 1;

	return new_array;
}

void info()
{
	cout << "1 - ������� ������" << endl;
	cout << "Q - ������� ��������� ������" << endl;
	cout << "2 - ������� ������� ������ " << endl;
	cout << "3 - ������� ��� �������" << endl;
	cout << "4 - �������� ���� � ������� ������" << endl;
	cout << "5 - ������� ���� � ������� ������" << endl;
	cout << "6 - ����� ����������� ���� ��������" << endl;
	cout << "7 - ����� �������� ���� ��������" << endl;
	cout << "8 - ������� � ���� ������ �� ��������" << endl;
	cout << "0 - ��������� ������" << endl;
	cout << "-> ������\n-< �����\n" << endl;
}
void info_2()
{
	cout << "\t ������:" << endl;
	cout << "1 - ����� ���������� ������ N ������" << endl;
	cout << "2 - ����� ������ �������� � ������ � N ������" << endl;
	cout << "3 - ����� ���������� � ������ � N ������" << endl;
	cout << "4 - ����� �������� �� ������ � N ������" << endl;
	cout << "\t ������:" << endl;
	cout << "5 - ����� ���������� ������� N ������" << endl;
	cout << "6 - ����� ������ �������� � ������� � N ������" << endl;
	cout << "7 - ����� ���������� � ������ � N ������" << endl;
	cout << "8 - ����� �������� �� ������� � N ������" << endl;
	cout << "0 - ����� � ������� ����" << endl;
}

void func(float (*func_point)(int), string name)
{
	fstream file;
	file.open(name, ios::app);
	float res1 = func_point(1000);
	float res2 = func_point(10000);
	float res3 = func_point(100000);
	file << 1000 << " " << res1 << endl;
	file << 10000 << " " << res2 << endl;
	file << 100000 << " " << res3 << endl << endl;
	file.close();

	system("pause");
}

void menu_2()
{
	int key = 0;
	bool menu2 = true;
	while (menu2)
	{
		system("cls");
		info_2();
		key = get_key();
		switch (key)
		{
		case 48:
			menu2 = false;
			break;
		case 49:
			func(create_time, "res_tree.txt");
			break;
		case 50:
			func(find_time, "res_tree.txt");
			break;
		case 51:
			func(insert_time, "res_tree.txt");
			break;
		case 52:
			func(erase_time, "res_tree.txt");
			break;
		case 53:
			func(create_time_vector, "res_vector.txt");
			break;
		case 54:
			func(find_time_vector, "res_vector.txt");
			break;
		case 55:
			func(insert_time, "res_vector.txt");
			break;
		case 56:
			func(erase_time, "res_vector.txt");
			break;
		default:
			break;
		}

	}
}
void menu_1()
{
	int key = 0;
	bool menu1 = true;
	int current = 0, size = 0, height = 0, check = 0;
	b_tree* array = NULL;
	while (menu1)
	{

		system("cls");
		print_array(array, current, size);

		info();
		key = get_key();
		switch (key)
		{
		case 48:
			menu1 = false;
			break;
		case 49:
			array = add_tree(array, current, &size, create_new_tree());
			break;
		case 113:
			array = add_tree(array, current, &size, create_random_tree());
			break;
		case 233:
			array = add_tree(array, current, &size, create_random_tree());
			break;
		case 50:
			if (size == 0)
			{
				cout << "���� �������� ���, �� � ������� ������)\n";
				system("pause");
				break;
			}
			array = delete_one_tree(array, &current, &size);
			break;
		case 51:
			if (size == 0)
			{
				cout << "���� �������� ���, �� � ������� ������)\n";
				system("pause");
				break;
			}
			array = delete_all_tree(array, &current, &size);
			break;
		case 52:
			if (size == 0)
			{
				cout << "���� �������� ���, �� � �������� ������)\n";
				system("pause");
				break;
			}
			array = add_node(array, current);
			break;
		case 53:
			if (size == 0)
			{
				cout << "���� �������� ���, �� � ������� ������)\n";
				system("pause");
				break;
			}
			array = del_node(array, &current, &size);
			break;
		case 54:
			if (size < 2)
			{
				cout << "� ��� ������ ���� ���� �� ��� ������!" << endl;
				system("pause");
				break;
			}
			check = 1;
			try
			{
				array = add_tree(array, current, &size, task1(check, current, &size, array));
			}
			catch (const std::exception&)
			{
				cout << "\n ����������� ���!\n";
				system("pause");
			}

			break;
		case 55:
			if (size < 2)
			{
				cout << "� ��� ������ ���� ���� �� ��� ������!" << endl;
				system("pause");
				break;
			}
			check = 0;
			try
			{
				array = add_tree(array, current, &size, task1(check, current, &size, array));
			}
			catch (const std::exception&)
			{
				cout << "\n �������� ���!\n";
				system("pause");
			}
			break;
		case 56:
			menu_2();
			break;
		case 75:
			if (current > 0) current--;
			break;
		case 77:
			if (current < size - 1) current++;
			break;
		default:
			break;
		}

	}
}


int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("pause");
	menu_1();

	return 0;
}