#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

#include "dec.cpp"
#include "en.cpp"
#include "md5.cpp"

void init();
void SignUp();// function to create new account. password is hased using MD5.
void LogIn();// function to login using username and password.
void create(const char* uname);
string isExisting(const char* uname);
void error(bool q);
void notes(const char* uname);
void LogOut();
void cal_key(string pass);
int key;
// opening the file users.txt which holds users info. if file not present then creating new file.
void init(){
	ofstream f1;
   	f1.open("users.txt",ios::app);
	f1.close();
}

// creating key which would be used for ceasaer's cipher encryption
void cal_key(string p)
{
    int sum = 0 ;
    for(int i=0 ; i < p.size() ; i++)
        sum += p[i];
    key = sum/p.size();
    return;
}

//providing choices to users 
void start()
{
  cout<<"1. Sign Up\n2. Log In\n";// sign up for new user and log in for already existing user
  int choice;
  cin>>choice;
  if( choice == 1 )
    SignUp();
    else if(choice == 2 )
    LogIn();
  else
  {
    cout<<" Invalid Choice\n";
    start();
  }
}

// opening screen after succesfully loging in
void notes(const char* uname)
{
    cout<<"\n You have Logged-In Successfuly \n";
    while(true){
    cout<<"1. Read Notes\n2. Write Notes\n3. Log Out\n";
    int ch;
    cin>>ch;
    if(ch == 1) //Decrypting notes and displaying saved notes
    {
        string filename , u;
        stringstream str;
        str << uname;
        filename = "";
        filename += str.str();
      //  filename += ".txt";
     //   cout<<filename<<endl;
        ifstream readf;
        readf.open(filename,ios::in);
       while(!readf.eof())
       {
            getline(readf , u);
            cout<<dec(u , key)<<endl;
       }
       readf.close();
    }

    else if(ch == 2) // Writing notes and saving it in encrypted form
    {
        string filename;
        stringstream str;
        str << uname;
        filename = "";
        filename += str.str();
      //  filename += ".txt";
        ofstream writef;
        writef.open(filename,ios::app);
            string temp;
            cout<<"/* Enter END to Save your file and Exit */\n";
	
            getline(cin , temp);
            while( temp != "END")
            {
                writef << enc(temp , key) << endl;
                getline(cin , temp);
            }
       writef.close();
    }
    else if(ch == 3) // logging out from current account
        LogOut();
     else
         cout<<"Invalid Choice";
    }
}

void LogOut()
{
    cout<<"You have Successfully logged out";
    exit(0);

}

void LogIn()
{
    char ch;
    string uname , pass , p;
    cout<<"Enter a Username : ";
    cin>>uname;
    pass = isExisting(uname.c_str());

    if(pass =="$")
        error(false);
    cout<<"Enter your Password \n show password(y/n)? ";
    cin>>ch;
    if(ch == 'Y' || ch == 'y' )
   {
    cout<<"Your password will be visible\nPassword: ";
    cin>>p;
    p = md5(p);
    if( p != pass )
        error(false);
    else
       {
       cal_key(pass);
       notes(uname.c_str());

       }
   }
   else
   {
	cout<<"Password will be hidden\n";
	char *password = getpass("Password: ");
	p = md5(password);
    if( p != pass )
        error(false);
    else
       {
       cal_key(pass);
       notes(uname.c_str());

       } 
   }
}

void SignUp()
{

    string uname , pass;
    cout<<"Enter a Username : ";
    cin>>uname;
    pass = isExisting(uname.c_str());
   // cout<<pass;
    if(pass == "$"){
        create(uname.c_str());
        }
    else
        error(true);
        start();
}

string isExisting(const char* uname)
{
    string u,p;
   ifstream readf;
   readf.open("users.txt",ios::in);
   while(!readf.eof())
   {
      getline(readf , u);
      getline(readf , p);
      if(u == uname)
        return p;
   }
   return "$";
}

void create(const char* uname)
{
   string pass;
    char ch;
    char *password;
    cout<<"Enter your Password \n show password(y/n)? ";
    cin>>ch;
    if(ch == 'Y' || ch == 'y' )
   {
	cout<<"Your password will be visible : ";
	cin>>password;
   }
   else
   {
      password = getpass("Your password will be hidden : ");
   }
    ofstream f1;
   f1.open("users.txt",ios::app);
   f1<<uname<<endl;
   pass = md5(password);
   f1<<pass<<endl;
   f1.close();
// create user's file
        string filename;
        stringstream str;
        str << uname;
        filename = "";
        filename += str.str();
    //    filename += ".txt";
        ofstream out(filename.c_str());
	cout<<"\n You have signed Up Successfully \n";
}

void error(bool q)
{
   if(q)
    cout<<" Username already Exists \n";
   else
    cout<<" Wrong Username or Password \n";

   start();
}

// 
int main()
{
  int choice_user,f = 0;
  cout<<"<-----------------------------Welcome To NotesFlow----------------------------------->\n";
  init();
  start();

//	while(!f1.eof()){};


 return 0;
}
