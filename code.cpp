#include<bits/stdc++.h>

using namespace std;

#include "dec.cpp"
#include "en.cpp"
#include "md5.cpp"

void init();
void SignUp();
void  LogIn();
void create(const char* uname);
string isExisting(const char* uname);
void error(bool q);
void notes(const char* uname);
void LogOut();
void LogIn();
void cal_key(string pass);
int key;

void init(){
	ofstream f1;
   	f1.open("users.txt",ios::app);
	f1.close();
}

void cal_key(string p)
{
    int sum = 0 ;
    for(int i=0 ; i < p.size() ; i++)
        sum += p[i];
    key = sum/p.size();
    return;
}

void start()
{
  cout<<"1. Sign Up\n2. Log In\n";
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

void notes(const char* uname)
{
    cout<<"\n You have Logged-In Successfuly \n";
    while(true){
    cout<<"1. Read Notes\n2. Write Notes\n3. Log Out\n";
    int ch;
    cin>>ch;
    if(ch == 1)
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

    else if(ch == 2)
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
    else if(ch == 3)
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

    string uname , pass , p;
    cout<<"Enter a Username : ";
    cin>>uname;
    pass = isExisting(uname.c_str());

    if(pass =="$")
        error(false);
    cout<<"Enter your Password : ";
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
   cout<<"Enter Your password : ";
   cin>>pass;
    ofstream f1;
   f1.open("users.txt",ios::app);
   f1<<uname<<endl;
   pass = md5(pass);
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

}

void error(bool q)
{
   if(q)
    cout<<" Username already Exists \n";
   else
    cout<<" Wrong Username or Password \n";

   start();
}

int main()
{
  int choice_user,f = 0;
  cout<<"<-----------------------------Welcome To NotesFlow----------------------------------->\n";
  init();
  start();

//	while(!f1.eof()){};


 return 0;
}
