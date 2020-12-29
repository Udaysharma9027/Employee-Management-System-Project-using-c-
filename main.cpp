/*Project of Employee Management System to save to data file , delete , Add  and Print to data file using c++*/
#include<iostream>
#include<string>
#include<fstream>                   //(Header file Includes )
#include<sstream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<math.h>

using namespace std;
const int EMP_ID_WIDTH = 8;
const int EMP_NAME_WIDTH = 20;
const int EMP_EMAIL_WIDTH = 25;
const int EMP_NUMERIC_WIDTH = 10;
const int EMP_TOTAL_WIDTH = 100;

struct employee {

         int EmpId;
         string Name;
         double  BasicSalary;
         double Pf;
         double HealthInsAmt;
         string Email;

};

//Function Prototypes.....................

void readfile (vector <employee> &v_emp);
void printMenu();
void doTask (vector <employee> &v_emp , int option);
void addemployee(vector <employee> &v_emp);
int  SearchEmployee (vector <employee> v_emp , int targetEmpId);
void PrintEmployee(vector <employee> v_emp);
void PrintEmployee(employee e);
double getNetSalary(employee e);
void SaveToFill (vector <employee> v_emp);
bool DeleteEmployee ( vector <employee> &v_emp , int targetEmpId);

int main()
{
    vector <employee> v_emp;
    readfile(v_emp);
    cout << "Total " << v_emp.size() << "records reads from the data file " << endl;


    printMenu();

    bool quit=false;
    while(!quit)
    {
        cout << "Input your Option :";
        int option ;
        cin >> option ;
        if(option ==6)
        {
            quit = true;
        }
        else
        {
            doTask(v_emp , option );
        }
    }
    return 0;
}

void PrintEmployee(vector <employee> v_emp)
{
    cout << endl;
    //First we need to print the heading
    cout << setw(EMP_ID_WIDTH) <<left << "EmpId"
         << setw(EMP_NAME_WIDTH) << left << "Name"
          << setw(EMP_EMAIL_WIDTH) << left << "Email"
          << setw(EMP_NUMERIC_WIDTH) << right <<"Basic ($)"
          << setw(EMP_NUMERIC_WIDTH) << right << "Pf ($)"
          << setw(EMP_NUMERIC_WIDTH) << right << "HealthIns ($)"
          << setw(EMP_NUMERIC_WIDTH) << right << "Net ($)"
           <<endl;
  cout << setw(EMP_TOTAL_WIDTH) << setfill('-') << " " << endl;
  cout << setfill(' ');

  double TotalBasic = 0.0;
  double TotalPfDesucation = 0.0;
  double TotalHealthIns = 0.0;
  double TotalNetSalary = 0.0;
  for(vector <employee> :: iterator it=v_emp.begin(); it!=v_emp.end(); it++)
  {
      PrintEmployee(*it);
      TotalBasic += it->BasicSalary;
      TotalPfDesucation += it->Pf;
      TotalNetSalary += getNetSalary(*it);
  }
  cout << setw(EMP_EMAIL_WIDTH) << setfill('-') << endl;
  cout << setfill(' ');
  cout << setw(EMP_ID_WIDTH) << left << "Total"
       << setw(EMP_NAME_WIDTH) <<left << "In ($)"
       << setw (EMP_EMAIL_WIDTH) << " "
       << setw (EMP_NUMERIC_WIDTH) << setprecision(2) <<right << fixed <<TotalBasic
       << setw (EMP_NUMERIC_WIDTH) << setprecision (2) <<right <<fixed << TotalPfDesucation
       << setw(EMP_NUMERIC_WIDTH) << setprecision (2) << right << fixed << TotalHealthIns
       << setw (EMP_NUMERIC_WIDTH) << setprecision(2) << right << fixed << TotalNetSalary
       << endl;

}

void PrintEmployee(employee e)
{
      cout << setw (EMP_ID_WIDTH) << left << e.EmpId
           << setw   (EMP_NAME_WIDTH) << left << e.Name
           << setw (EMP_EMAIL_WIDTH) << left << e.Email
           << setw(EMP_NUMERIC_WIDTH) << setprecision(2) << fixed << right  << e.BasicSalary
           << setw (EMP_NUMERIC_WIDTH) << setprecision(2) <<fixed << right << e.Pf
           << setw (EMP_NUMERIC_WIDTH)  << setprecision(2) <<fixed << right << e.HealthInsAmt
           << setw (EMP_NUMERIC_WIDTH)    << setprecision(2) <<fixed << right << getNetSalary(e)
           <<endl;
}

double getNetSalary(employee e){
       return e.BasicSalary - (e.Pf + e.HealthInsAmt);
}

void readfile (vector <employee> &v_emp)
{
    ifstream fin;
    fin.open("emp.txt");
    if(!fin)
    {
        cout << "Unable to open database file emp.txt" <<endl
               << "Make sure that the file exit " <<endl;
               exit(1);
    }
    string line;
    int recNo=0;
    while(!fin.eof())
    {
        getline(fin,line);
        recNo++;
        //cout << recNo << "-" <<line <<endl;
        //Since we have successfully read a line from the file.
        // So it is time to parse each token for field values .
        istringstream iss(line);
        string strEmpId;
        string strName;
        string strBasicSalary;
        string strPf;
        string  strHealthInsAmt;
        string strEmail;
        getline(iss , strEmpId , ','); // 101,John Alter,5000,75,100,jdoe@gmail.com
        getline(iss , strName , ',');
        getline(iss ,  strBasicSalary , ',');
        getline(iss , strPf , ',');
        getline(iss , strHealthInsAmt , ',');
        getline(iss , strEmail , ',');

        employee temp;
        temp.EmpId= atoi(strEmpId.c_str());
        temp.Name = strName;
        temp.BasicSalary = atof(strPf.c_str());
        temp.Pf = atoi(strPf.c_str());
        temp.HealthInsAmt = atof(strHealthInsAmt.c_str());
        temp.Email = strEmail;
        v_emp.push_back(temp);



    }
    fin.close();
}

void printMenu() {
    cout << "1.Add Employee" << endl; // Command for Adding the Employee.
    cout << "2.Print Employee Report" << endl; // command for print Employee Report .
    cout << "3.Search Employee" << endl; // command for Searching the Employee.
    cout << "4.Delete Employee " << endl ; // command for Deleting the Employee.
    cout << "5.Save " << endl; // command for saving the Employee.
    cout << "6.Exit " << endl ; // command for Exit the Program .

}

void doTask (vector <employee> &v_emp , int option)
{
    int targetEmpId;
    int index;
    switch (option)
    {
        case 1 :  addemployee(v_emp);
                 break;
        case 2 :  PrintEmployee(v_emp);
                 break;
        case 3 :
                   cout << "Enter emp id to search : ";
                   cin >> targetEmpId ;
                   index = SearchEmployee(v_emp , targetEmpId);
                   if(index == -1)
                   {
                       cout << "Employee with Id :" <<  targetEmpId << "does not exit " << endl;
                   }
                   else
                   {
                       cout << "Employee with Id : " << targetEmpId << "found " << endl;
                       PrintEmployee(v_emp[index]);
                   }
                 break;
        case 4 :  cout << "Enter emp id to delete ";
                  cin >> targetEmpId;
                  if(DeleteEmployee(v_emp , targetEmpId))
                  {
                      cout << "Employee With Id : " <<targetEmpId << "Delete Successfully " << endl;
                      cout << "Please use option -5 to save the changes permanently " << endl;
                  }
                  else
                  {
                      cout << "Employee Id : " << targetEmpId << "could not be delete " << endl;
                  }
                 break;
        case 5 : SaveToFill(v_emp);
                 break;
        default: cout << "Invalid Menu Option Chosen Valid Option Are from 1-6" << endl;
    }
}

void addemployee(vector <employee> &v_emp)
{
    employee temp;
    bool isDuplicate = false;
    do
    {
         cout << "Employee Id" ;
         cin >> temp.EmpId;
         isDuplicate = false;
         if(SearchEmployee(v_emp, temp.EmpId) !=-1)
         {
             isDuplicate = true;
             cout << "Employee Id " << temp.EmpId << "already exit, please input unique number" << endl;
         }
    } while(isDuplicate);
    cout << "Name :" ;
    cin.clear();
    cin.ignore(INT_MAX , '\n');
    getline(cin,temp.Name);
    cout << "Basic Salary ($)" ;
    cin >> temp.BasicSalary;
    cout << "Pf ($)";
    cin >> temp.Pf;
    cout << "Health Income ($)";
    cin >> temp.HealthInsAmt;
    cout << "Email ";
    cin.clear();
    cin.ignore(INT_MAX , '\n');
    getline(cin , temp.Email);
    v_emp.push_back(temp);
    cout << "Employee Id " << temp.EmpId << "added successfully " <<endl;
    cout << "Total Employee " << v_emp.size() << endl;
}

int  SearchEmployee (vector <employee> v_emp , int targetEmpId)
{
    for(int i=0 ; i<v_emp.size() ; i++)
    {
        if(v_emp[i].EmpId == targetEmpId)
        {
            return i ;
        }
    }
    return -1;
}

void SaveToFill (vector <employee> v_emp)
{
    ofstream fout ("emp.txt");
    if(!fout)
    {
        cout << "Unable to open the data file emp.txt" << endl;
        return ;
    }
    int recout = 0;
    for(vector <employee> :: iterator it=v_emp.begin(); it!=v_emp.end();it++)
    {
        fout << it->EmpId << "," << it->Name << "," << it->BasicSalary << "," << it->Pf << "," << it->HealthInsAmt << "," <<it->Email;
        recout ++ ;
        if(recout !=v_emp.size())
        {
            fout << endl;
        }
    }
    fout.close();
    cout << "Total of " <<recout << "Records Saved Successfully into the file " << endl;
}

bool DeleteEmployee ( vector <employee> &v_emp , int targetEmpId)
{
    int index = SearchEmployee(v_emp , targetEmpId);
    if(index == -1)
    {
        return false;
    }
    //Record Found At Index
    cout << "Target Employee With Id : " << targetEmpId << "Found " << endl;
    PrintEmployee(v_emp[index]);
    cout << "Are you sure to delete ? Input 1 to delete 0 to exit " << endl;
    int option;
    cin >> option;
    if(option == 1)
    {
        v_emp.erase(v_emp.begin() + index);
        return true;

    }
    return false;
}
