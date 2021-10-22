// Car Rental System.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<time.h>
#include<sstream>
#pragma warning(disable:4996)
using namespace std;
string login()
{
    string username, pass, example;
    string* data;
    int size = 0;
    fstream fin;
    cout << "Login: ";
    cin >> username;
    cout << "Password: ";
    cin >> pass;
    fin.open("Users.txt");
    while (fin >> example)
    {
        size++;
    }
    data = new string[size];
    fin.close();
    fin.open("Users.txt");
    size = 0;
    while (fin >> example)
    {
        data[size] = example;
        size++;
    }
    for (int i = 0; i < size; i += 2)
    {
        if (data[i] == username && data[i + 1] == pass)
        {
            system("cls");
            cout << "Succesfully logged in" << endl << "Hello, " << username << "!";
            return username;
        }
        if (i == size - 2)
        {
            system("cls");
            cout << "Wrong username or password. Please try again or register!";
            return "Wrong username or password. Please try again or register!";
        }
    }

    fin.close();
    delete[] data;
}

void reg()
{
    ofstream fout;
    string username, pass;
    cout << "Login: ";
    cin >> username;
    cout << "Password: ";
    cin >> pass;
    fout.open("Users.txt", ios::app);
    fout << username << endl << pass << endl;
    fout.close();
    system("cls");
    cout << "Succesfully registered" << endl << endl;
}

void regSys(string &username, int &status)
{
    int option;
    bool s = false;
    cout << "Hello!" << endl;
    cout << "Choose your option:" << endl;
    while (s != true)
    {
        cout << "1.Login" << endl << "2.Register" << endl << "3.Close app" << endl << "Option: ";
        cin >> option;
        system("cls");
        if (option == 1)
        {
            username = login();
            cout << endl << endl;
            if(username!= "Wrong username or password. Please try again or register!") break;

        }
        else if (option == 2)
        {
            reg();
        }
        else if (option == 3)
        {
            s = true;
            status = 3;
        }
        else
        {
            cout << "Wrong option number! Please try again." << endl << endl;
        }
    }
}

string IntToString(int a)
{
    string str;
    stringstream ss;
    ss << a;
    ss >> str;
    if (a < 10)
    {
        str = "0" + str;
    }
    return str;
}

string StringSubstraction(string a, string b)
{
    int result = stoi(a) - stoi(b);
    return IntToString(result);
}

class Car
{
public:
    Car(){}
    Car(int carNumber)
    {
        this->carNumber = carNumber;
    }
    void Properties()
    {
        cout << "Mark: \t\t\t" << mark[carNumber] << "\n";
        cout << "Model: \t\t\t" << model[carNumber] << endl;
        cout << "Color: \t\t\t" << color[carNumber] << endl;
        cout << "Max speed: \t\t" <<maxs_peed[carNumber] <<endl;
        cout << "Price: \t\t\t" << price[carNumber] << endl;
        cout << "Date of manufacture: \t" << date[carNumber] << endl;
    }
    string GetMark(int num)
    {
        return mark[num];
    }
    string GetModel(int num)
    {
        return model[num];
    }
    void SetCar(int a)
    {
        this->carNumber = a;
    }
    int GetPrice(int num)
    {
        return price[num];
    }

private:
    int carNumber;
    string mark[9] = { "Hyundai","BMW","Mercedes","Audi","Tesla","Skoda","Volkswagen","Toyota","Ford" };

    string model[9] = { "Tucson","X5","S-Class","A8","Model-S","Superb","Passat","Raw4","Mondeo" };

    string color[9] = { "Red","black","yellow","Blue","Red","Brown","Silver","Black","grey" };

    string maxs_peed[9] = { "100 Km/h ","150 Km/h","150 Km/h","170 Km/h","130 Km/h","140 Km/h","130 Km/h","120 Km/h","150 Km/h" };

    int price[9] = { 100,200,300,500,200,250,400,600,900 };

    int date[9] = { 2010,2012,2013,2017,2018,2005,2008,2010,2014 };
};

class Time
{
private:
    int year, mon, day, hour, minute, sec;
public:
    Time()
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        year = 1900 + ltm->tm_year;
        mon = 1 + ltm->tm_mon;
        day = ltm->tm_mday;
        hour = ltm->tm_hour;
        minute = ltm->tm_min;
        sec = ltm->tm_sec;
    }
    string GetYear()
    {
       return IntToString(year);
    }
    string GetMonth()
    {
        return IntToString(mon);
    }
    string GetDay()
    {
        return IntToString(day);
    }
    string GetHour()
    {
        return IntToString(hour);
    }
    string GetMinute()
    {
        return IntToString(minute);
    }
    string GetSecond()
    {
        return IntToString(sec);
    }
    void Print()
    {
        cout << day << "." << mon << "." << year << "\t" << hour << ":" << minute << ":" << sec << endl;
    }
};

bool ifRented(string username)
{
    fstream fin;
    string filename = username + ".txt";
    string word, car;
    int rent =0, ret=0;
    fin.open(filename);
    while (!fin.eof())
    {
        fin >> word;
        if (word == "Rented:") rent++;
        if (word == "Returned:") ret++;
    }
    fin.close();
    if (rent == ret) return false;
    else return true;
    return false;
}

void CarTab(Car a)
{
    cout << "Car\t\t\tPrice (per day)" << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i == 0 || i == 2 || i == 6)
            cout << i + 1 << "." << a.GetMark(i) << " " << a.GetModel(i) << "\t" << a.GetPrice(i) << endl;

        else
            cout << i + 1 << "." << a.GetMark(i) << " " << a.GetModel(i) << "\t\t" << a.GetPrice(i) << endl;
    }
}

void rent(string username)
{
    ofstream fin;
    Car a;
    int CarOp, Prop;
    string fileName = username + ".txt";
    if (ifRented(username))
    {
        cout << "Sorry, you have already rented a car. You need to return it first"<<endl;
    }
    else
    {
        cout << "Which car do you want to rent?" << endl;
        /*cout << "Car\t\t\tPrice (per day)" << endl;
        for (int i = 0; i < 9; i++)
        {
            if(i==0 || i ==2 || i==6) 
                cout << i + 1 << "." << a.GetMark(i) << " " << a.GetModel(i)<<"\t"<< a.GetPrice(i) << endl;

            else
                cout << i + 1 << "." << a.GetMark(i) << " " << a.GetModel(i) << "\t\t" << a.GetPrice(i) << endl;
        }*/
        CarTab(a);
        cin >> CarOp;
        CarOp--;
        while (CarOp>=9)
        {
            system("cls");
            cout << "Wrong number, please try again\n\n";
            CarTab(a);
            cin >> CarOp;
            CarOp--;
        }
        system("cls");
        cout << "Do you want to see car's properties?" << endl;
        cout << "1.Yes\n2.No\n";
        cin >> Prop;
        if (Prop == 1)
        {
            system("cls");
            a.SetCar(CarOp);
            a.Properties();
        }
        cout << "\nCar successfully rented!";
        fin.open(fileName, ios::app);
        fin << "Rented: " << a.GetMark(CarOp) << " " << a.GetModel(CarOp) << endl;
        time_t now = time(0);
        tm* ltm = localtime(&now);
        fin << "Rent time: " << ltm->tm_mday << "." << 1 + ltm->tm_mon << "." << 1900 + ltm->tm_year << "\t" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
        fin.close();
    }
}

int number_of_strings(string filename)
{
    fstream fin;
    string word;
    int num = 0;
    fin.open(filename);
    while (!fin.eof())
    {
        getline(fin, word);
        num++;
    }
    fin.close();
    num--;
    return num;
}

void Return(string username)
{
    fstream fin;
    ofstream fout;
    string *arr;
    int num, carOp, retOp;
    string filename = username + ".txt";
    if (ifRented(username))
    { 
        system("cls");
        num = number_of_strings(filename);
        arr = new string[num];
        fin.open(filename);
        for (int i = 0; i < num; i++)
        {
            getline(fin, arr[i]);
        }
        cout << "Do you want to return " <<arr[num-2].substr(8)<< "?\n";
        cout << "1. Yes\n" << "2. No\n";
        cin >> retOp;
        while (retOp>2)
        {
            cout << "Wrong number, please try again\nOption: ";
            cin >> retOp;
        }
        if (retOp == 1)
        {
            fout.open(filename, ios::app);
            fout << "Returned: " << arr[num - 2].substr(8) << endl;
            Time a;
            fout << "Returned time: " << a.GetDay() << "." << a.GetMonth() << "." << a.GetYear() << "\t" << a.GetHour() << ":" 
                << a.GetMinute() << ":" << a.GetSecond() << endl;
            fout.close();
            system("cls");
            cout << "Car successfully returned";
        }
        
        fin.close();

        delete[] arr;
    }
    else
    {
        cout << "You have nothing to return";
    }
    
    
    
}

#define n
int main()
{
#ifdef n
    string username;
    int RentOption, status;
    regSys(username, status);
    bool i = true;
    //cout << "\n\n" << username;
    if (status == 3) return 0;
        
        
        while (i == true)
        {
            cout << "1.Rent Car\n" << "2.Return Car\n";
            cout << "Option: ";
            cin >> RentOption;
            if (RentOption == 1)
            {
                system("cls");
                rent(username);
                i = false;
            }

            else if (RentOption == 2)
            {
                Return(username);
                i = false;
            }
            else
            {
                system("cls");
                cout << "Sorry, you've chosen wrong number. Please try again\n\n";
            }
        }
#endif
    return 0;
}