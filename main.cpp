#include<iostream>
#include<mysql.h>  //mysql library for c api functions
//these all libraries were added by including folders to project options
#include<mysqld_error.h> // and this particularly , when posting the .dll to the project folder
//mysql error codes

using namespace std;

//defining the connection parameters
char HOST[] = "localhost";//database server address
char USER[] = "    ";//username for database login//your database username
char PASS[] = "    ";//password for database login//your database password
int main() 
{
	MYSQL* obj; 			// pointer to mysql object to manage MYSQL session
	//variables and arrays to store info of the database tables
	int  College_ID;
	char name[20];
	char BirthDate[11]; 		//this is always 11 : YYYY-MM-DD + 0 from every chsr array
	float Grade;
	
	bool ProgramIsOpened = true;//flag to control the loop for adding records later on
	int answer; 		//to keep the program opened
	
	char* consult;// pointer to hold the sql query string later on....
	char* sentence;// "    "      "   "  formatted sql query
	string sentence_aux;  //to add data to table
	
	
	//.................................................//  
//	connection

	if(!(obj = mysql_init(0)))//initializing the sql object!!!!!
	{
		cout<<"ERROR: Mysql object could not be created."<<endl;//print error if fail
		
	}
	else
	{
		if(!mysql_real_connect(obj,HOST,USER,PASS,"school",3306,NULL,0))//attempt to connect to database
		{
			cout<<"ERROR: some database info is wrong or do not exist. "<<endl;
			cout<<mysql_error(obj)<<endl;
		}
		else
		{
			cout<<"LOGGED IN" <<endl<<endl;
			
			while(ProgramIsOpened)//loop to add records until user exits
			{
				cout<<"College_ID: ";
				cin>>College_ID;
				cin.ignore(100,'\n');  //remember to clean your buffer after using cin for int,float and double
				
				cout<<"name: ";
				cin.getline(name,20,'\n'); //we don't use cin<<name cause it doesn't read spaces.
				cout<<"BirthDate: ";
				cin.getline(BirthDate,11,'\n');
				
				cout<<"grade: ";
				cin>>Grade;
				cin.ignore(100,'\n');
				cout<<endl;
				
				//setting our update
				
				sentence_aux = "INSERT INTO students(College_ID, name,BirthDate, Grade) VALUES('%d' , '%s' , '%s' , '%f')";
				sentence = new char[sentence_aux.length() + 1];
				strcpy(sentence,sentence_aux.c_str());  //we copy string into a *char
				
				consult = new char[strlen(sentence) + sizeof(int) + strlen(BirthDate) + sizeof(float)];
				sprintf(consult,sentence,College_ID,name,BirthDate,Grade);  //substitutes %d... for actual values
				
				
				//make our attempt
				
				if(mysql_ping(obj))
				{
					cout<<"ERROR: Impossible to connect."<<endl;
					cout<<mysql_error(obj)<<endl;
					
				}
				if(mysql_query(obj,consult))
				{
					 cout<<"ERROR: "<<mysql_error(obj)<<endl;
					 rewind(stdin);
					 getchar();
				}
				else
				{
					cout<<"Info added correctly."<<endl;
				}
				mysql_store_result(obj);
				cout <<endl<<"Another? "<<endl;
				cout<<"[1]: yes"<<endl;
				cout<<"[0]: no"<<endl;
				cout<<"Answer: ";
				cin>>answer;
				cin.ignore(100,'\n');
				if(answer==0)
				{
					ProgramIsOpened = false;
				}
				cout<<endl;
				
			}
		}
	}
	cout<<"BYE!"<<endl;
	
	return 0;
}
