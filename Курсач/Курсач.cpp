// Курсач.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <limits> //для очистки буфера и потока
#include <vector>
#include <algorithm> //// для функции sort
#include <windows.h>

using namespace std;


const string ADMINS_AND_USERS_PATH = ("admins_and_users.txt"), ADMINS_AND_USERS_TO_VERIFICATION_PATH = ("admins_and_users_to_verification.txt"), DATA_PATH=("data.txt");
int end_menu_number=0;
string active_login = "";



struct worker; //Струтура для сотрудника. Хранит: ФИО, дату рождения, название отдела, должность, дату начала работы
struct Register; //Струтура для регистрации. Хранит: логин и пароль
struct FIO; //Струтура для ФИО. Хранит: фамилию, имя, отчество.
struct Date; //Струтура для даты. Хранит: день, месяц, год.


///////////////////////Прототипы функций////////////////////////////////////////////////////////////////

void Main_Menu(); //Стартовое меню

int Entry(string path, int &); //Сравнение введеных логина и пароля с теми, которые находятся в файлах
void Registration_Menu(string); //Реализация меню регистрации
void Check_Choose(int &choose, int end_menu_number); //Проверка ввода  цифр в меню 
void Check_Choose(int &choose, int,int);
void Register_Write(string path, int); //Запись логина и пароля
void Clear(); //Функция восстановик буфера и потока



void Admin_Menu(); //Меню Администратора

/////////////////////////////////Подпункты меню администратора начало////////////////////////////////////////

void User_Account_Management_Menu(); //Меню управление учетными записями пользователя

//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

//////////////////////Подпункты меню: Управление учетными записями пользователя//////////////////////
void View_all_accounts(string, bool); //Меню просмотра всех аккаунтов или данных;
int Account_editing(string, bool); //Изменение аккаунтов или данных;
int Account_deleting(string, bool);//Удаление аккаунтов или данных;
int Account_Verification(string, bool); //Подтверждение аккаунтов;
int Account_lock(string, bool); //Блокировка аккаунтов;

//////////////////////Дополнительные функции для меню//////////////////////
void Show_Account(fstream &File, int &count); //Функция показа аккаунтов;
void Write_Account_Information_To_Vector(vector<Register> &Person, string); //Запись аккантов в вектор;
void Write_Accounts_To_File(vector<Register> &Person, Register &change_account, string path); //Запись аккантов в файл;
void Editing_Account_In_Vector(vector<Register> &Person, Register &Change, int choose); //Изменение аккаунтов в векторе;
void Deleting_Account_In_Vector(vector<Register> &Person, int choose); //Удаление аккаунта из вектора

//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

void Work_With_Data(); //Работа с данными

//22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

////////////////////////////////////////////////
void Data_Processing_Mode();


void Individual_Task(); //Меню индивидуального задания

void Showing_Employees_Of_Retirement_Age(string path); //Показать сотрудников пенсионного возраста
void Showing_Employees_In_Decreasing_Order_Of_Experience(string path); //Сортировка в порядке убывания стажа

void Search_Data(); //Меню поиска данных

void Search_By_Start_Date(); //Поиск по дате начала
void Search_By_Last_Name(); //По фамилии
void Search_By_Position(); //По должности

void Sorting(); //Меню сортировки

void Sort_By_Alphabet(); //Сортировка по алфовиту
void Sort_By_Position(); //Сортировка по должности

////////////////////////////////////////////////

void Edit_Mode(); //Меню управления учетными записями


void Add_New_Record(string path); //Добавить новую запись
void Show_Data(fstream &File, int &count);  //Показать данные
void Write_Data_Information_To_Vector(vector<worker> &Person, string path); //Записать данные в вектор
void Write_Data_To_File(vector<worker> &Person, worker &change_account, string path); //Записать данные в файл
void Editing_Data_In_Vector(vector<worker> &Person, worker &Change, int choose); //редактирование данных в векторе
void Deleting_Data_In_Vector(vector<worker> &Person, int choose); //Удаление данных в векторе
void Check_Login(string &); //Проверка логина на уникальность

////////////////////////////////////////////////

/////////////////////////////////Подпункты меню администратора конец////////////////////////////////////////


void User_Menu(); //Меню Пользователя

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FIO //Структура фамилии
{
	FIO()
	{
		this->surname = ("");
		this->name = ("");
		this->middle_name = ("");
	} //Конструктор присвоения нулевых значений
	string surname, name, middle_name; //Имя, фамилия, отчество
	void Write()
	{
		cout << "Введите фамилию сотрудника: ";
		cin >> surname;
		Clear();
		cout << "Введите имя сотрудника: ";
		cin >> name;
		Clear();
		cout << "Введите отчество сотрудника: ";
		cin >> middle_name;
		Clear();
	} //Метод записи данных в структуру fio

	
};
struct Date //Структура для записи даты
{
	Date() //Конструктор присвоения нулевых значений
	{
		this->day = 0;
		this->month = 0;
		this->year = 1896;
	} 
	int day, month, year; //День, месяц, год
	void Write_Date()
	{
		cout << "Введите день: ";
		Check_Choose(day, 1, 31); //Функция проверки ввода данных
		cout << "Введите месяц: ";
		Check_Choose(month, 1, 12);
		cout << "Введите год: ";
		Check_Choose(year, 1896, 2019);
	} //Метод записи данных в структуру Data
	bool operator == (const Date& other)
	{
		if (this->year == other.year && this->month==other.month && this->day == other.day) return true;
		else return false;
	}
	//Перегрузка оператора "=="  для сравнения объектов структуры
};
struct worker //структура данных о сотруднике
{


	FIO fio; //структура ФИО
	Date date_of_birth, date_of_commencement_of_work; //Дата рождения и дата начала работы
    string department_name, position; //Название отдела и лолжности

	void Set_Date_Of_Birth() //метод для установки даты рождения
	{
		date_of_birth.Write_Date();
	} 
	void Set_Date_Of_Commencement_Of_Work() //метод для установки даты начала работы
	{
		date_of_commencement_of_work.Write_Date();

	} 
	void Write_Worker() //метод для записи информации о сотруднике
	{
		cout << "|Основная информация о сотруднике|\n\n";
		fio.Write();
		cout << "\n|Дата рождения сотрудника| \n";
		date_of_birth.Write_Date();
		cout << "\n\n|Информация связанная с работой| \n";
		cout << "Название отдела: ";
		cin >> department_name;
		Clear();
		cout << "Должность: ";
		cin >> position;
		Clear();
		cout << "\n|Дата начала работы| \n";
		date_of_commencement_of_work.Write_Date();
		cout << "\nДанные успешно записаны!\n\n";
		
	}

};
struct Register //Струтура для регистрации. Хранит: логин, пароль и роль.
{
public:
	Register(string other_login, string other_password) //коструктор присвоения логина и пароля
	{
		this->login = other_login;
		this -> password = other_password;
    }
	Register()  //Конструктор присвоения нулевых значений
	{
		this->login = ""; 
		this->password = "";
		this->role = 0;
	}
	void Write () //Метод записи логина и пароля
	{
		cout<<"\t\t\t\t\t|____Курсовая работа____|\n\n\n";
		cout << "Введите login: ";
		cin >> login;
		cout << "Введите password: ";
		cin >> password;
	}
	void Set_Main_Admin() //Метод установки главного администратора
	{
		Main_Admin();
	}

	bool operator == (const Register& other) //Перегрузка оператора "=="  для сравнения объектов структуры
	{
		if (this->login == other.login && this->password == other.password) return true;
		else return false;
	}

	string login, password ; //логин и пароль
	int role; //Роль 

private: //Секция, которая недоступна в коде.
	void Main_Admin()//Метод установки главного админа
{
	this->login = "Sleepy";
	this->password = "Sleepy";
	this->role = 1;
}

};

class FnameComparator //Сортировка по дате
{
public:
	bool operator () (worker& a, worker& b) 
	{ 
		return (a.date_of_commencement_of_work.year + a.date_of_commencement_of_work.month + a.date_of_commencement_of_work.day) < (b.date_of_commencement_of_work.year + b.date_of_commencement_of_work.month + b.date_of_commencement_of_work.day);
	}
};
class FnameComparator2 //сортировка по алфовиту
{
public:
	bool operator () (worker& a, worker& b) { return (a.fio.surname + a.fio.name + a.fio.middle_name) < (b.fio.surname + b.fio.name + b.fio.middle_name); }
};
class FnameComparator3 //Сортировка по должности
{
public:
	bool operator () (worker& a, worker& b)
	{ 
		return (a.position) < (b.position);
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////

//Перегрузка оператора ">>"  для записи из объекста структуры в файл
ostream& operator<< (ostream& os, const Register& file)
{
	os << file.login << " " << file.password<< " " << file.role << "\n";
	return os;
}

//Перегрузка оператора "<<" для записи из файла в объекст структуры
istream& operator>> (istream& is, Register& file)
{
	is >> file.login >> file.password >> file.role;
	return is;
}


ostream& operator<< (ostream& os, const FIO & file)
{
	os << file.surname << " " << file.name << " " << file.middle_name;
	return os;
}
istream& operator>> (istream& is, FIO& file)
{
	is >> file.surname >> file.name >> file.middle_name;
	return is;
}

ostream& operator<< (ostream& os, const Date & file)
{
	os << file.day << " " << file.month << " " << file.year;
	return os;
}
istream& operator>> (istream& is, Date& file)
{
	is >> file.day >> file.month >> file.year;
	return is;
}

ostream& operator<< (ostream& os, const worker& file)
{
	os << file.fio<<" "<< file.date_of_birth<<" "<< file.department_name<<" "<< file.position<<" "<<file.date_of_commencement_of_work<<"\n";
	return os;
}
istream& operator>> (istream& is, worker& file)
{
	is >> file.fio >> file.date_of_birth >> file.department_name >> file.position >> file.date_of_commencement_of_work;
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////




int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	setlocale (0, "rus");

	Main_Menu(); //Запуск всей программы

	return 0;
}






///////////////////////////////////////////////////////////////////////////////////////


//Стартовое меню
void Main_Menu()
{
	int Choose_Entry = 0, flag = 0;

	while (true)
	{

		cout << "\t\t\t\t\t|____Курсовая работа____|\n\n\n";
		cout << "1)Вход  \n2)Регистрация \n0)Завершить работу\n\nВаш выбор: ";
		end_menu_number = 2;
		Check_Choose(Choose_Entry, end_menu_number); //Проверка ввода

		switch (Choose_Entry)
		{
			///////////////////////Меню админа////////////////////////////////////////////////////////////////
		case 1:
			Entry(ADMINS_AND_USERS_PATH, flag); //Запуск меню входа

			if (flag == 1) //Если меню входа возвршает 1 - запуск админ меню
			{
				system("cls");
				Admin_Menu();
				break;
			}

			if (flag == 0) //Если меню входа возвршает 0 - запуск пользовательского меню
			{
				system("cls");
				User_Menu();
				break;
			}

			if (flag == 7) //Если меню входа возвршает 7 - выбивает ошибку
			{
				cout << "\nПользователь не найден. Повторите вход или зарегистрируйтесь.\n\n";
				system("pause");
				system("cls");
				break;
			}

			if (flag == 2) //Если меню входа возвршает 2 - значит пользователь заблокирован
			{
				cout << "\nВы были заблокированы. Обратитесь к администратору.\n\n";
				system("pause");
				system("cls");
				break;
			}
			///////////////////////Меню пользователя////////////////////////////////////////////////////////////////

			///////////////////////Регистрация////////////////////////////////////////////////////////////////
		case 2:
			Registration_Menu(ADMINS_AND_USERS_TO_VERIFICATION_PATH);
			break;
			///////////////////////Выход////////////////////////////////////////////////////////////////
		case 0: exit(0);
		}
	}



}



//Меню Администратора
void Admin_Menu()
{
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Меню администратора____|\n\n\n";
		cout << "1)Управление учетными записями пользователей \n2)Работа с данными \n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 2;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)

		{
		case 1: User_Account_Management_Menu(); //Меню работы с аккаунтами
			    break;

		case 2: Work_With_Data(); //Меню работы с данными
			    break;

		case 0: break;
		}


		if (Choose_Entry == 0) break;
	}
} 

/////////////////////////////////Подпункты меню администратора////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

void User_Account_Management_Menu() //Меню управление учетными записями пользователя
{
	int Choose_Entry = 0;
	bool flag = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Управление учетными записями пользователей____|\n\n\n";
		cout << "1)Просмотр всех учетных записей \n2)Добавление новой учетной записи \n3)Редактирование учетной записи \n4)Удаление учетной записи\n";
		cout << "5)Подтверждение учетной записи\n6)Изменение прав доступа\n\n0)Вернуться в меню администратора\n\nВаш выбор: ";

		end_menu_number = 6;
		Check_Choose(Choose_Entry, end_menu_number);

		switch (Choose_Entry)

		{
		case 1: View_all_accounts(ADMINS_AND_USERS_PATH, flag); //Показать все аккаунты
			system("pause");
			system("cls");
			break;

		case 2: Registration_Menu(ADMINS_AND_USERS_PATH); //Зарегистрировать аккаунты
			break;

		case 3: Account_editing(ADMINS_AND_USERS_PATH, flag); // Редактировать аккаунт
			break;
		case 4: Account_deleting(ADMINS_AND_USERS_PATH, flag); //Удалить аккаунт
			break;
		case 5: Account_Verification(ADMINS_AND_USERS_TO_VERIFICATION_PATH, flag); //Подтвердить аккаунт
			break;
		case 6:  Account_lock(ADMINS_AND_USERS_PATH, flag); //Изменить права доступа аккаунта
			break;


		case 0: system("cls");
			break;
		}


		if (Choose_Entry == 0) break;
	}
}

//////////////////////Подпункты меню: Управление учетными записями пользователя//////////////////////
void View_all_accounts(string path, bool flag)
{
	system("cls");
	int count=1;
	fstream File_Persons;

	cout << "\t\t\t\t\t|____Просмотр всех записей____|\n\n\n";
	
	File_Persons.open(path, fstream::in | fstream::out | fstream::app);
	if (flag == 0)
	{
		cout << "| № | login | password | role |\n\n";
		Show_Account(File_Persons, count);
		cout << endl;
	}
	else 
	{
		cout << "|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";
		Show_Data(File_Persons, count);
		cout << endl;
	}
	File_Persons.close();

}
int Account_editing(string path, bool flag)
{
	system("cls");
	int choose=0;
	vector<Register> Person;
	vector<worker> employee;
	fstream File_Persons;
	Register change_account;
	worker change_employee;

	View_all_accounts(path, flag);
	
	if (flag == 0)
	{
		Write_Account_Information_To_Vector(Person, path);
		end_menu_number = Person.size();
	}
	else
	{
		Write_Data_Information_To_Vector(employee, path);
		end_menu_number = employee.size();
	}

	cout << "0)Вернуться в меню управление учетными записями пользователя \n\nВведите номер записи, которую вы хотите отредактировать: ";
    Check_Choose(choose,end_menu_number);
	if (choose == 0) return 0;

	system("cls");

	if (flag == 0)
	{
		Editing_Account_In_Vector(Person, change_account, choose);
		active_login = change_account.login;
		File_Persons.open(path, fstream::out);
		for (size_t i = 0; i < Person.size(); i++)
		{
			change_account = Person[i];
			File_Persons << change_account;
		}
		File_Persons.close();
	}
	else 
	{
		Editing_Data_In_Vector(employee, change_employee, choose);

		File_Persons.open(path, fstream::out);

		for (size_t i = 0; i < Person.size(); i++)
		{
			change_employee = employee[i];
			File_Persons << change_employee;
		}

		File_Persons.close();

	}
	system("pause");
	system("cls");
}
int Account_deleting(string path, bool flag)
{
	system("cls");
	int choose = 0;
	vector<Register> Person;
	vector<worker> employee;
	fstream File_Persons;
	Register change_account;
	worker change_employee;

	if (flag == 0)
	{
		Write_Account_Information_To_Vector(Person, path);
		end_menu_number = Person.size();
		if (Person.size() == 0)
		{
			cout << "Записей не обнаруженно, сначала добавьте запись для удаления\n\n";
			system("pause");
			system("cls");
			return 0;
		}
	}
	else
	{
		Write_Data_Information_To_Vector(employee, path);
		end_menu_number = employee.size();
		if (employee.size() == 0)
		{
			cout << "Записей не обнаруженно, сначала добавьте запись для удаления\n\n";
			system("pause");
			system("cls");
			return 0;
		}
	}



	View_all_accounts(path, flag);


	cout << "0)Шаг назад \n\nВведите номер записи, которую вы хотите удалить: ";


	Check_Choose(choose, end_menu_number);
	if (choose == 0) return 0;

	if (flag == 0)
	{
		if (Person[choose - 1].login == active_login) return Account_deleting(path,flag);
		Deleting_Account_In_Vector(Person, choose);
		Write_Accounts_To_File(Person, change_account, path);
		
	}
	else
	{
		Deleting_Data_In_Vector(employee, choose);
		Write_Data_To_File(employee, change_employee, path);
	}

	cout << "Аккаунт удален!\n\n";
	system("pause");
	system("cls");
}
int Account_Verification(string path, bool flag)
{
	system("cls");
    int number=0;
	vector<Register> Person;
	fstream File_Persons;
	Register Change;


	View_all_accounts(path, flag);
	Write_Account_Information_To_Vector(Person, path);

	cout << "0)Шаг назад \n\nВведите номер записи, которую вы хотите подтвердить: ";
	Check_Choose(number, Person.size());
	if (number == 0) return 0;

	Change = Person[number-1];

	File_Persons.open(ADMINS_AND_USERS_PATH, fstream::app);
	File_Persons << Change;
	File_Persons.close();

	Deleting_Account_In_Vector(Person, number - 1);
	Write_Accounts_To_File(Person, Change, ADMINS_AND_USERS_TO_VERIFICATION_PATH);
	
	cout << "\nПользователь успешно подтвержден!\n\n";
	system("pause");
	system("cls");
}
int Account_lock(string path, bool flag)
{
	system("cls");
	int role = 0, number=0;
	vector<Register> Person;
	fstream File_Persons;
	Register Change;


	View_all_accounts(path, flag);
	Write_Account_Information_To_Vector(Person, ADMINS_AND_USERS_PATH);

	cout << "0)Шаг назад \n\nВведите номер учетной записи, у которой вы хотите изменить доступ: ";
	Check_Choose(number, Person.size() + 1);

	if (number == 0) return 0;
	if (Person[number - 1].login == active_login) return Account_lock( path, flag);

	cout << "\t\t\t\t\t|____Изменение доступа аккаунта____|\n\n\n";
	cout << "0-сделать пользователем; 1-сделать администратором; 2-заблокировать\n\nВаш выбор: ";
	Check_Choose(role, 2);
	Person[number - 1].role = role;
	File_Persons.open(path, fstream::out);
	for (size_t i = 0; i < Person.size(); i++)
	{
		Change = Person[i];
		File_Persons << Change;
	}
	File_Persons.close();
	cout << "Роль успешно изменина!\n\n";
	system("pause");
	system("cls");
}

void Show_Account(fstream &File, int &count)
{
	while (true)
	{
		Register Person;
		File >> Person;
		if (File.eof()) break;
		if (Person.role == 0) cout << count << ") " << "(Пользователь): ";
		if (Person.role == 1) cout << count << ") " << "(Администратор): ";
		if (Person.role == 2) cout << count << ") " << "(Заблокирован): ";
		cout  << Person;
		count++;

	}
}
void Write_Account_Information_To_Vector(vector<Register> &Person, string path)
{
	fstream file;
	file.open(path, fstream::in);
	while (true)
	{
		Register Buffer;
		file >> Buffer;
		if (file.eof()) break;
		Person.push_back(Buffer);
	}
	file.close();
}
void Editing_Account_In_Vector(vector<Register> &Person, Register &Change, int choose)
{
	cout << "\t\t\t\t\t|____Редактирование учетной записи____|\n\n\n";
	cout << "Старый логин: " << Person[choose - 1].login << " | Старый password: " << Person[choose - 1].password << endl<<endl;
	Change.Write();
	Check_Login(Change.login);
	Person[choose - 1].login = Change.login;
	Person[choose - 1].password = Change.password;
	cout << "\n\nНовый логин: " << Person[choose - 1].login << " | Новый password: " << Person[choose - 1].password << endl<<endl;
}
void Write_Accounts_To_File(vector<Register> &Person, Register &change_account, string path )
{
	fstream File_Persons;
	File_Persons.open(path, fstream::out);
	for (size_t i = 0; i < Person.size(); i++)
	{
		change_account = Person[i];
		File_Persons << change_account;
	}
	File_Persons.close();
}
void Deleting_Account_In_Vector(vector<Register> &Person, int choose)
{
	vector<Register>::iterator it = Person.begin();
	advance(it, choose - 1);
	Person.erase(it);
}

//////////____________________________///////
void Work_With_Data()
{

	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Работа с данными____|\n\n\n";
		cout << "1)Режим обработки данных \n2)Режим редактирования\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 2;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)

		{
		case 1: Data_Processing_Mode();
			    break;
		case 2: Edit_Mode();
			    break;

		case 0: system("cls");
			break;
		}


		if (Choose_Entry == 0) break;
	}
}

void Edit_Mode()
{
	bool flag = 1;
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Управление учетными записями пользователей____|\n\n\n";
		cout << "1)Просмотр всех данных \n2)Добавление новой записи \n3)Удаление записи \n4)Редактирование записи\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 4;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)

		{
		case 1: View_all_accounts(DATA_PATH,flag);
			system("pause");
			system("cls");
			    break;
		case 2: Add_New_Record(DATA_PATH);
			system("cls");
			    break;
		case 3: Account_deleting(DATA_PATH, flag);
			    break;
		case 4: Account_editing(DATA_PATH, flag);
			    break;
	
		case 0: system("cls");
			break;
		}


		if (Choose_Entry == 0) break;
		
	}
}
///////////////////////////////////////////////////////////
void Add_New_Record(string path)
{
	worker employee;
	fstream File_Person;

	employee.Write_Worker();
	system("pause");
	File_Person.open(path, fstream::in | fstream::out | fstream::app);
	File_Person << employee;
	File_Person.close();
}
void Show_Data(fstream &File, int &count)
{
	while (true)
	{
		worker employee;
		File >> employee;
		if (File.eof()) break;
		cout << count << ")" << employee;
		count++;

	}
}
void Write_Data_Information_To_Vector(vector<worker> &Person, string path)
{
	{
		fstream file;
		file.open(path, fstream::in);
		while (true)
		{
			worker Buffer;
			file >> Buffer;
			if (file.eof()) break;
			Person.push_back(Buffer);
		}
		file.close();
	}
}
void Editing_Data_In_Vector(vector<worker> &Person, worker &Change, int choose)
{
	cout << "\t\t\t\t\t|____Редактирование учетной записи____|\n\n\n";
	cout << "Старые данные: " << Person[choose - 1]<<endl;
	Change.Write_Worker();
	Person[choose - 1] = Change;
	cout << "\nНовые данные: " << Change;
}
void Write_Data_To_File(vector<worker> &Person, worker &change_account, string path)
{
	fstream File_Persons;
	File_Persons.open(path, fstream::out);
	for (size_t i = 0; i < Person.size(); i++)
	{
		change_account = Person[i];
		File_Persons << change_account;
	}
	File_Persons.close();
}
void Deleting_Data_In_Vector(vector<worker> &Person, int choose)
{
	vector < worker> ::iterator it = Person.begin();
	advance(it, choose - 1);
	Person.erase(it);
}
///////////////////////////////////////////////////////////
void Data_Processing_Mode()
{
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Режим обработки данных____|\n\n\n";
		cout << "1)Индивидуальное задание \n2)Поиск данных \n3)Сортировка\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 3;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)
		{
		case 1: Individual_Task();
			    break;
		case 2: Search_Data();
			    break;
		case 3: Sorting();
			    break;

		case 0: system("cls");
			break;
		}
		if (Choose_Entry == 0) break;
	}
}

void Individual_Task()
{
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Индивидуальное задание____|\n\n\n";
		cout << "1)Вывести список сотрудников пенсионного возраста \n2)Вывести список сотрудников в порядке убывания стажа.\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 2;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)

		{
		case 1: Showing_Employees_Of_Retirement_Age(DATA_PATH);
			system("cls");
			    break;
		case 2: Showing_Employees_In_Decreasing_Order_Of_Experience(DATA_PATH);
			system("cls");
			    break;

		case 0: system("cls");
			break;
		}


		if (Choose_Entry == 0) break;
	}
}
void Showing_Employees_Of_Retirement_Age(string path)
{
	system("cls");
	vector<worker> employee;
	worker change_employee;
	cout << "\t\t\t\t\t|____Показ сотрудников пенсионного возраста____|\n\n\n";
	cout << "|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";;

	Write_Data_Information_To_Vector(employee, path);
	for (int i=0; i!=employee.size(); i++)
	{
		if (employee[i].date_of_birth.year < 1956) cout <<i+1<<")"<< employee[i];
	}
	cout << endl;
	system("pause");
	
}
void Showing_Employees_In_Decreasing_Order_Of_Experience(string path)
{
	system("cls");
	vector<worker> employee;

	Write_Data_Information_To_Vector(employee, path);
	sort(employee.begin(),employee.end(),FnameComparator());
	cout << "\t\t\t\t\t|____Сортировка в порядке убывания стажа____|\n\n\n";
	cout << "|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";

	for (size_t i = 0; i != employee.size(); i++)
	{
		cout << employee[i];
	}
	cout << endl;
	system("pause");

}

void Search_Data()
{
	int Choose_Entry=0;
	while (true)
	{
		cout << "\t\t\t\t\t|____Поиск данных____|\n\n\n";
		cout << "1)Поиск по дате начала работы\n2)Поиск по фамилии \n3)Поиск по должности\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 3;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)
		{
		case 1: Search_By_Start_Date();
			system("pause");
			system("cls");
			    break;
		case 2: Search_By_Last_Name();
			system("pause");
			system("cls");
			    break;
		case 3: Search_By_Position();
			system("pause");
			system("cls");
			    break;

		case 0: system("cls");
			break;
		}
		if (Choose_Entry == 0) break;
	}

}
void Search_By_Start_Date()
{
	system("cls");
	Date date_start;
	vector<worker> employee;

	Write_Data_Information_To_Vector(employee, DATA_PATH);
	cout << "\t\t\t\t\t|____Поиск по дате начала работы____|\n\n\n";
	date_start.Write_Date();

	
	cout << "\n|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";

	for (size_t i = 0; i < employee.size(); i++)
	{
		if (employee[i].date_of_commencement_of_work == date_start) cout << i + 1 << ") " << employee[i];
	}
	cout << endl;
}
void Search_By_Last_Name()
{
	system("cls");
	worker Person;
	vector<worker> employee;


	Write_Data_Information_To_Vector(employee, DATA_PATH);

	cout << "\t\t\t\t\t|____Cортировка по фамилии____|\n\n\n";
	cout << "Ведите фамилию: ";
	cin >> Person.fio.surname;
	cout << "\n|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";

	for (size_t i = 0; i < employee.size(); i++)
	{
		if (employee[i].fio.surname == Person.fio.surname) cout << i + 1 << ") " << employee[i];
	}
	cout << endl;
}
void Search_By_Position()
{
	system("cls");
	worker person;
	vector<worker> employee;

	cout << "\t\t\t\t\t|____Поиск по должности____|\n\n\n";
	Write_Data_Information_To_Vector(employee, DATA_PATH);
	cout << "Введите должность: ";
	cin >> person.position;

	system("cls");

	cout << "\n|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";

	for (size_t i = 0; i < employee.size(); i++)
	{
		if (employee[i].position == person.position) cout << i + 1 << ") " << employee[i];
	}

	cout << endl;
}

void Sorting()
{
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Cортировка____|\n\n\n";
		cout << "1)Сортировка в порядке убывания стажа\n2)Сортировка по алфовиту \n3)Сортировка по должности\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 3;
		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)
		{
		case 1: Showing_Employees_In_Decreasing_Order_Of_Experience(DATA_PATH);
			system("cls");
			    break;
		case 2: Sort_By_Alphabet();
			    system("pause");
			    system("cls");
			    break;
		case 3: Sort_By_Position();
			    system("pause");
			    system("cls");
			    break;

		case 0: system("cls");
			break;
		}
		if (Choose_Entry == 0) break;
	}
}
void Sort_By_Alphabet()
{
	system("cls");
	vector<worker> employee;

	Write_Data_Information_To_Vector(employee, DATA_PATH);
	sort(employee.begin(), employee.end(), FnameComparator2()); //сортировка по алфовиту

	Date date_of_birth, date_of_commencement_of_work;
	string department_name, position;

	cout << "\t\t\t\t\t|____Cортировка по алфовиту____|\n\n\n";
	cout << "|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";
	for (size_t i = 0; i != employee.size(); i++)
	{
		cout << employee[i];
	}
	cout << endl;
}
void Sort_By_Position()
{
	system("cls");
	vector<worker> employee;

	Write_Data_Information_To_Vector(employee, DATA_PATH); //Запись данных в вектор
	sort(employee.begin(), employee.end(), FnameComparator3()); //Сортировка по должности

	cout << "\t\t\t\t\t|____Cортировка по должности____|\n\n\n";
	cout << "|Фамилия|Имя|Отчество|День рождения|Месяц|Год|Название отдела|Должность|День начала работы|Месяц|Год|\n\n";

	for (size_t i = 0; i != employee.size(); i++)
	{
		cout << employee[i];
	}
	cout << endl;
}
///////////////////////////////////////////////////////////
void User_Menu() //Меню пользователя
{
	int flag = 1;
	int Choose_Entry = 0;

	while (true)
	{
		cout << "\t\t\t\t\t|____Меню пользователя____|\n\n\n";
		cout << "1)Просмотр всех данных \n2)Индивидуальное задание \n3)Поиск данных \n4)Сортировка\n0)Вернуться в основное меню\n\nВаш выбор: ";
		end_menu_number = 4;

		Check_Choose(Choose_Entry, end_menu_number);


		switch (Choose_Entry)
		{
		case 1: View_all_accounts(DATA_PATH, flag); //Просмотр всех данных
			system("pause");
			system("cls");
			    break;
		case 2: Individual_Task(); //Индивидуальное задание
			    break;
		case 3: Search_Data(); //Поиск данных
			    break;
		case 4: Sorting(); //Сортировка

			    break;

		case 0: system("cls");
			break;
		}
		if (Choose_Entry == 0) break;

	}
}
//////////////////////////////////////////////////////////
//Реализация меню регистрации
void Registration_Menu(string path)
{
int choose=0, role=0;
system("cls");
while (true)
{
cout << "\t\t\t\t\t|____Регистрация____|\n\n\n";
cout << "1)Регистрация Пользователя \n2)Регистрация Администратора \n\n0)Выход\n\n\nВаш выбор: ";
end_menu_number = 2;
Check_Choose(choose, end_menu_number);
	switch (choose)
	{
	case 1: "\t\t\t\t|____Регистрация Пользователя____|\n\n\n";
		Register_Write(path, role);
		cout << "\nРегистрация прошла успешно!\n\n";
		system("pause");
		system("cls");
		break;
	case 2: "\t\t\t\t\t|____Регистрация Администратора____|\n\n\n";
		role = 1;
		Register_Write(path, role);
		cout << "\nРегистрация прошла успешно! \n\n";
		system("pause");
		system("cls");
		break;
	case 0: break;
	}
	if (choose==0) break;
}
}
//Проверка ввода  цифр в меню 
void Check_Choose(int &choose, int a)
{
	while (true)
	{
		cin >> choose;
		if (cin.get() != '\n' || (!cin<<choose)|| choose<0 || choose>a)
		{
			cout << "Некорректный Ввод: ";
			Clear();
		}
		else
		{
			system("cls");
			break;
		}
	}
}
void Check_Choose(int &choose, int a, int b)
{
	while (true)
	{
		cin >> choose;
		if (cin.get() != '\n' || (!cin << choose) || choose>b || choose<a)
		{
			cout << "Некорректный Ввод: ";
			Clear();
		}
		else
		{
			break;
		}
	}
}
//Сравнение введеных логина и пароля с теми, которые находятся в файлах
int Entry(string path,int &flag)
{
	system("cls");
	Register Person, Other_Person, Main_Admin;
	fstream File_Persons;

	Person.Write(); //Вводим логин и пароль
	active_login = Person.login; //Присваиваем активный логин
	Main_Admin.Set_Main_Admin(); //Устанавливаем главного админа

	File_Persons.open(path, fstream::in | fstream::out | fstream::app);
	while(true)
	{
		File_Persons >> Other_Person; 
		if (Person == Other_Person || Person==Main_Admin) //Проверяем на равенство данных
		{
			if (Person == Main_Admin)
			{
				flag=1;
				break;
			}
			if (Other_Person.role == 0) flag = 0;
			if (Other_Person.role == 1) flag = 1;
			if (Other_Person.role == 2) flag = 2;
			break;
		}
		else flag = 7;
		if (File_Persons.eof()) break;
	}
    File_Persons.close();


   return flag;

}
//Запись логина и пароля
void Register_Write(string path, int role)
{
	Register Person; 
	fstream File_Person;

	Person.Write(); //Пишем логин и пароль 
	Check_Login(Person.login); //Проверяем логИн
	File_Person.open(path, fstream::in | fstream::out | fstream::app);
	if (role==0) Person.role = 0; //Присваиваем роль
	if (role==1) Person.role = 1;
	File_Person << Person; //Записываем в файл
	File_Person.close();
}
void Check_Login(string &login) //Функция проверки уникальности логина
{
	vector<Register> verification_admin, not_verification_admin; //Вектора всех аккаунтов
	Write_Account_Information_To_Vector(verification_admin, ADMINS_AND_USERS_PATH); //Запись информации об всех аккаунтах в вектора
	Write_Account_Information_To_Vector(not_verification_admin, ADMINS_AND_USERS_TO_VERIFICATION_PATH);
	Register main_admin;
	main_admin.Set_Main_Admin();

	for (size_t i = 0; i < not_verification_admin.size(); i++) //Проверка на уникальность 
	{
		if (login == not_verification_admin[i].login || login==main_admin.login)
		{
			Clear();
			cout << "\n\nТакой пользователь уже существует, введите новый логин: ";
			cin >> login;
			Check_Login(login);
		    
		}
	}
	for (size_t i = 0; i < verification_admin.size(); i++)
	{
		if (login == verification_admin[i].login || login == main_admin.login)
		{
			Clear();
			cout << "\n\nТакой пользователь уже существует, введите новый логин: ";
			cin >> login;
			Check_Login(login);
		}
	}
}

//Функция очистки буфера и потока
void Clear()
{
	cin.clear(); //Очистка потока
	cin.ignore(1000, '\n'); //Очистка буфера
}
 
