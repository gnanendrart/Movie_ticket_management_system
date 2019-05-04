//Header Files
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <time.h>
#include<windows.h>
using namespace std;

//GLOBAL VARIABLES
string original,userid,fname,lname,email,card,expiry,cvv,pass;
string moviename[6];
int choice,adult,child,price,selected=0;
int show[6][6];
int monitor=0;
//FUNCTION HEADER DECLARATIONS
void admin();//ADMIN PAGE
void registeruser();//REGISTERS A NEW USER
void purchase();//LETS YOU PURCHASE THE TICKET
void login();//LOGIN PAGE
void confirmation();//TICKET CONFIRMATION AND PRINTING PAGE
void userdetails();//USER DETAILS ARE STORED IN THE GLOBAL VARIABLE USING THE FUNCTION
string password();//GETS THE PASSWORD IN '*' FORMAT
void adminlogin(int choice);//LOGS IN THE ADMIN
void registeradmin();//ALLOWS YOU TO REGISTER A NEW ADMIN
void mainpage();//MAIN PAGE WILL BE DISPLAYED
void currentlyshowing();//SHOWS THAT ARE RUNNING CURRENTLY IN THE THEATER
void shows();//ASSIGNS THE SHOWS AND THEIR TIMINGS TO THE GLOBAL VARIABLES
void purchasetickets();//GETS INFO ON HOW MANY TICKETS ARE NEEDED AND TYPE OF TICKETS
void editmovie();//ALLOWS ADMIN TO EDIT THE SHOWS WHICH ARE RUNNING CURRENTLY
int main()
{
    shows();
    mainpage();
    return 0;
}

void mainpage()
{
    //Displaying the current date and time
    system("CLS");
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	cout<< "Date : "<<timePtr->tm_mday<<"-"<<timePtr->tm_mon+1<<"-"<<timePtr->tm_year + 1900<<"\nTime : "<< timePtr->tm_hour <<":"<<timePtr->tm_min;
    int choice=0;
		//MAIN PAGE WILL BE DISPLAYED EVERYTIME
		cout<<"\n\t\t\t ----------------------------------";
		cout<<"\n\t\t\t Simple Movie Ticket Booking System";
		cout<<"\n\t\t\t ----------------------------------";
		cout<<"\n\t\t\t\t USER INFO";	//Menu for the user
		cout<<"\n\n\t\t\t\t <1> ADMIN";
        cout<<"\n\t\t\t\t <2> CURRENTLY SHOWING";
		cout<<"\n\t\t\t\t <3> LOGIN";
		cout<<"\n\t\t\t\t <4> Exit \n\n";
		cout<<"\t\t\t\tEnter Your Choice :";
		cin>>choice;

		switch(choice)//BASED ON THE USER CHOICE SWITCHES TO THE CORRESPONDING CASE
		{
        case 1:
            admin();
            break;
        case 2:
            currentlyshowing();
            break;
        case 3:
            login();
            break;
        case 4:
            break;
        default:
            cout<<"\n WRONG OPTION";
            cout<<"\n REFRESHING SCREEN";
            Sleep(2000);
            mainpage();//Refreshes the screen to ask for a new input again
		}
}
void shows()
{
    fstream file;
    file.open("currentlyshowing.txt");//opens the file containing the current show info
    for(int i=0; i<=5; i++)
    {
        getline(file,moviename[i]); //Gets each row in the file as an input
    }
    for(int i=0; i<=5; i++)
    {
        for(int j=0; j<=5; j++)
        {
            file>>show[i][j];//Gets the shows for each movie
        }
    }
}
void admin() //Checks if admin is existing or new
{
    system("CLS");
    cout<<"ADMIN PAGE";
    //Display the options for existing or new admin
    cout<<"\n\n\n\n\t\t\t\t <1> Existing Admin";
    cout<<"\n\t\t\t\t <2> Register New Admin";
    int choice;
    cout<<"\n\t\t\t\tEnter Your Choice : ";
    cin>>choice; //User inputs if existing or new admin
    if(choice == 1) //If user is existing, redirect him to existing admin login page
    {
        adminlogin(1);
    }
    else
    {
        adminlogin(2); //If user is new, redirect him to new admin login page
    }
}
void adminlogin(int choice)
{
    ADMIN:
    string username;
    string pass;
    system("CLS");
    cout<<"ADMIN LOGIN PORTAL";
    cout<<"\n\t\t\t\t User Name : ";
    cin>>username; //inputs admin user name
    pass = password(); //gets the password from user and assigns it to a string variable
    string user;
    string pasword;
    ifstream file;
    file.open("Admin.txt");
    int x=0;
    while(!file.eof())//checks the username and password until it reaches end of file or until it finds a match
    {
        file>>user;
        file>>pasword;
    if(!(username.compare(user)) && !(pass.compare(pasword)))//checks if both username and password is correct
    {
        cout<<"\n\t\t\t\t LOGGING IN";
        Sleep(2000);//Waits for 2 seconds and takes to the next screen
        file.close();
        x=1;
        break;
    }
    }
    if(x==0)//if username or password is incorrect
    {
        cout<<"\n\t\t\t\t INCORRECT USERNAME OR PASSWORD";
        cout<<"\n\t\t\t\t Redirecting";
        Sleep(2000);
        file.close();
        goto ADMIN;//Takes you to the same screen again
    }
    if(choice==2)
    {
        registeradmin();//Takes us to the register admin page
    }
    else
    {
        editmovie(); // if login is correct it take it to the edit movie page
    }
}
void registeradmin()
{
    REGISTERADMIN:
    system("CLS");
    cout<<"Register ADMIN page";
    string username, pass1,pass2;
    cout<<"\n\t\t\t\t User Name : ";
    cin>>username;//gets new admin username
    pass1 = password();//gets new password
    cout<<"\n\t\t\t\t Confirm Password : ";
    pass2 = password();//asks to reenter the password
    if(pass1.compare(pass2) != 0)//checks if password and reentered password are matching)
    {
        cout<<"\n\t\t\t\t PASSWORDS DO NOT MATCH ";
        cout<<"\n\t\t\t\t REDIRECTING";
        Sleep(2000);
        goto REGISTERADMIN;
    }
    else //executes when the passwords match
    {
        cout<<"\n\t\t\t\t PASSWORDS MATCH ";
        cout<<"\n\t\t\t\t REGISTERING";
        Sleep(2000);
        system("CLS");
        fstream file;
        file.open("Admin.txt",ios::app);
        file<<username<<endl; //enters the username in the text file
        file<<pass1<<endl; // enters the password in the text file
        file.close();
        mainpage(); // takes to the main page
    }
}
void currentlyshowing() //Print all the current movies
{
    CURRENTLYSHOWING:
    system("CLS");
    cout<<"Currently Showing";
    for(int i=0; i<=5; i++)
    {
        cout<<"\n\n\t\t\t\t <"<<i+1<<"> "<<moviename[i]; //Print all the movies
        cout<<"\n\t\t\t\t Show Timings : ";
        for(int j=0; j<=5; j++)
        {
            cout<<show[i][j]<<"\t"; //Print all the show timings for currently showing
        }
    }
    cout<<"\n\n\t\t\t\t <7> Previous menu"<<endl;
    cout<<"\n\t\t\t\t Enter your choice : ";
    cin>>choice; //Ask choice input from user
    if(choice==7) //If user wants to go back to the main menu
    {
        system("CLS");
        mainpage(); //Display main page
    }
    else
    {
        system("CLS");
        cout<<"\n\n\t\t\t\t YOUR MOVIE CHOICE : ";
        cout<<"\n\n\t\t\t\t <"<<choice<<"> "<<moviename[choice-1]; //Display the movie name and show timings according to the choice
        cout<<"\n\t\t\t\t Show Timings : ";
        for(int j=0; j<=5; j++)
        {
            cout<<"\n\t\t\t\t <"<<j+1<<"> "<<show[choice-1][j];
        }
        cout<<"\n\n\t\t\t\t <7> Previous menu";
        cout<<"\n\t\t\t\t Your Choice : ";
        cin>>selected;
        Sleep(2000);
        if(selected!=7) //If user does not want to go back to previous menu
        {
            if(monitor==1) //If user is logged in, go to purchase tickets page
            {
                purchasetickets();
            }
            else //if user is not logged in, direct him to login page
            {
                login();
            }
        }
        else //if user wants to go back to previous page, redirect him to currently showing page
        {
            goto CURRENTLYSHOWING;
        }
    }
}
void login()
{
    system("CLS");
    cout<<"LOGIN PAGE";
    //monitor =1;
    cout<<"\n\t\t\t\t <1> EXISTING USER";
    cout<<"\n\t\t\t\t <2> NEW USER";
    cout<<"\n\t\t\t\t Enter your Choice : ";
    int choice;
    cin>>choice;
    if(choice == 1)//if the user is an existing user
    {
        LOG:
        system("CLS");
        cout<<"USER LOGIN PAGE";
        cout<<"\n\n\n\n\t\t\t\t UserID : ";
        cin>>userid; //gets user id
        string pass;
        pass=password(); //gets password from user and assigns it to pass
        fstream file;
        file.open("userid.txt"); //opens file containing all user ids and passwords
        int x=0;
        while(!file.eof())
        {
            string user,pasword;
            file>>user;
            file>>pasword;
            if(!(userid.compare(user)) && !(pass.compare(pasword)))//checks if both user id and password is correct
            {
                original=user;
                cout<<"\n\t\t\t\t LOGGING IN";
                Sleep(2000);//Waits for 2 seconds and takes to the next screen
                file.close();
                x=1;
                monitor = 1;
                userdetails();
                break;
            }
        }
        if(x==0)//if either password or username is incorrect
        {
            cout<<"\n\t\t\t\t INCORRECT USERNAME OR PASSWORD";
            cout<<"\n\t\t\t\t Redirecting";
            Sleep(2000);
            file.close();
            goto LOG;//Takes you to the same screen again
        }
    }
    else
    {
        registeruser();//registers new user
    }
    if(selected==0)
        {
            mainpage();//takes to main page
        }
        else
        {
            purchasetickets(); // takes to purchase page when both user id and password is correct
        }
}
void userdetails() //Matches the current user with the existing users stored in the user.txt file
{
    fstream file;
    file.open("user.txt"); //Opens file with user data
    while(!file.eof()) // Repeats loop till end of the file
    {
        file>>userid;
        file>>pass;
        file>>lname;
        file>>fname;
        file>>email;
        file>>card;
        file>>expiry;
        file>>cvv;
        if(original.compare(userid)==0)//Compare current user to users in database
        {
            break;
        }
        else //If current user does not match the user in the loop, set all details to null
        {
            userid=" ";
            pass=" ";
            lname=" ";
            fname=" ";
            email=" ";
            card=" ";
            expiry=" ";
            cvv=" ";
        }
    }
}
void registeruser() //Register New user details
{
    REGISTERUSER:
    system("CLS");
    cout<<"Register NEW USER page";
    string pass1,pass2;
    cout<<"\n\t\t\t\t User ID : ";
    cin>>userid; //Input the new userid
    pass1 = password(); //Enter new password
    cout<<"\n\t\t\t\t Confirm Password : ";
    pass2 = password(); //Confirm new password
    if(pass1.compare(pass2) != 0) //Checks if both the passwords match
    {
        //If passwords do not match, redirect the user to re-register page
        cout<<"\n\t\t\t\t PASSWORDS DO NOT MATCH ";
        cout<<"\n\t\t\t\t REDIRECTING";
        Sleep(2000);
        goto REGISTERUSER;
    }
    else
    {
        //If passwords match, prompt the user to enter the rest of his details like name, email id, card number.
        cout<<"\n\t\t\t\t PASSWORDS MATCH ";
        cout<<"\n\t\t\t\t First Name : ";
        cin>>fname;
        cout<<"\n\t\t\t\t Last name : ";
        cin>>lname;
        cout<<"\n\t\t\t\t Email-id : ";
        cin>>email;
        cout<<"\n\t\t\t\t Card Number : ";
        cin>>card;
        cout<<"\n\t\t\t\t EXPIRY(MMDD) : ";
        cin>>expiry;
        cout<<"\n\t\t\t\t CVV : ";
        cin>>cvv;
        cout<<"\n\t\t\t\t REGISTERING";
        Sleep(2000);
        system("CLS");
        //Store the userid of the new user in the userid.txt file
        fstream file1;
        original = userid;
        file1.open("userid.txt",ios::app);
        file1<<userid<<endl;
        file1<<pass1<<endl;
        //Store the user details of the new user in the user.txt file
        fstream file;
        file.open("user.txt",ios::app); //Open the user.txt file
        //Store all the details
        file<<userid<<endl;
        file<<pass1<<endl;
        file<<lname<<endl;
        file<<fname<<endl;
        file<<email<<endl;
        file<<card<<endl;
        file<<expiry<<endl;
        file<<cvv<<endl;
        file.close(); //Close the file
        monitor = 1; //The person is logged in
        userdetails();
        //Check if person selected the show or not
        if(selected==0) //IF not selected, prompt user to select
        {
            mainpage();
        }
        else
        {
            purchasetickets(); //Else purchase tickets
        }
    }
}
void purchase()

{
    system("CLS");
    cout<<" VERIFICATION PAGE ";
    cout<<"\n\n\n\t\t\t\t USER ID : "<<userid;
    cout<<"\n\t\t\t\t CARD NUMBER : "<<card;//userid and card details are being received from GLOBAL VARIABLE
    string cvv1;//To Check the CVV Confirmation
    cout<<"\n\t\t\t\t ENTER CVV : ";
    cin>>cvv1;
    if(cvv.compare(cvv1)==0)//CHECKS IF THE CVV OF THE CARD IS THE SAME AS THAT OF THE ENTERED CVV
    {
        //confirmation();
        cout<<"\n\t\t\t\t CONFIRMED";
        cout<<"\n\t\t\t\t REDIRECTING TO TICKET CONFIRMATION PAGE";
        Sleep(2000);
        confirmation();
    }
    else//IF NOT REDIRECTS IT TO THE CVV FILE
    {
        cout<<"\n\t\t\t\t  CVV DOES NOT MATCH ";
        cout<<"\n\t\t\t\t Redirecting ";
        Sleep(2000);
        purchase();
    }
}
void editmovie()
{
    system("CLS");
    cout<<"EDIT MOVIE SCREEN ";
    cout<<"\n\t\t\t\t The Movies currently shown are : ";
    for(int i=0;i<6;i++)
    {
        cout<<"\n\t\t\t\t <"<<i+1<<"> "<<moviename[i];
    }
    cout<<"\n\t\t\t\t Which one would you like to replace? : ";
    int x;
    cin>>x;//TAKES INPUT FROM THE ADMIN TO CHOOSE WHICH MOVIE IS TO BE EDITED
    string replacement;
    replacement = moviename[x-1];
    cout<<"\n\t\t\t\t Enter the New movie title : ";
    string newmovie;
    cin>>newmovie;//NAME OF THE NEW MOVIE TITLE WILL BE STORE
    ofstream file("Currentlyshowing.txt");//OPENS THE EXISTING FILE IN WRITE FORMAT
    for(int i=0; i<6; i++)
    {
        if(moviename[i]== replacement)//CHECKS IF THE EXISTING MOVIE NAME AND REPLACEMENT STRINGS ARE SAME
        {
            moviename[i]=newmovie;//IF SAME,REPLACES THE EXISTING MOVIE TITLE WITH THE USER ENTERED FILE
        }
        file<<moviename[i]<<endl;//INPUTS THE MOVIE TITLE ONE BY ONE INTO THE FILE
    }
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            file<<show[i][j]<<" ";//THE SHOWS ARE STORED AGAIN INTO THE FILE
            if(j==5)
                file<<endl;
        }
    }
    cout<<"\n\t\t\t\t Editing complete";
    shows();//SHOWS FUNCTION IS CALLED TO UPDATE THE GLOBAL VARIABLES
    cout<<"\n\t\t\t\t Returning to the main menu";
    Sleep(2000);
    mainpage();//MAIN PAGE GETS DISPLAYED AGAIN FOR THE USER TO INPUT HIS PRIVILAGES

}
void confirmation() //Confirms and displays confirmation page with ticket
{
   system("CLS");
   cout<<"MOVIE PASS";
   //Display Ticket:
   cout<<"\n\t\t\t -----------------------------------------------------------------";
   cout<<"\n\t\t\t |                                                               |";
   cout<<"\n\t\t\t      MOVIE NAME : "<<moviename[choice-1];
   cout<<"\n\t\t\t      SHOW TIME  : "<<show[choice-1][selected-1];
   cout<<"\n\t\t\t      ADULT : "<<adult/20<<"\t CHILD : "<<child/10;
   cout<<"\n\t\t\t      PRICE : "<<price;
   cout<<"\n\t\t\t |                                                               |";
   cout<<"\n\t\t\t -----------------------------------------------------------------";
   Sleep(10000);
   mainpage(); //Go back to main page
}
void purchasetickets()
{
    system("CLS");
    cout<<"Your Selection : ";
    cout<<"\n\n\t\t\t\t YOUR MOVIE CHOICE : ";
    cout<<"\n\n\t\t\t\t <"<<choice<<"> "<<moviename[choice-1];
    cout<<"\n\t\t\t\t Your Show Time : ";
    cout<<show[choice-1][selected-1];//KEEPS TRACK OF YOUR SELECTED MOVIES
    cout<<"\n\n\n\t\t\t\t Ticket Prices:";
    cout<<"\n\t\t\t\t Adult             : $20";
    cout<<"\n\t\t\t\t Child(under age 8): $10";
    cout<<"\n\n\n\t\t\t\t Adult Tickets : ";
    cin>>adult;//ADULT AND CHILD TICKETS ARE STORED IN THE GLOBAL VARIABLES
    adult *=20;
    cout<<"\n\t\t\t\t Child Tickets : ";
    cin>>child;
    child *=10;
    price = child+adult;
    system("CLS");
    cout<<"\n\n\n\t\t\t\t Ticket Information";
    cout<<"\n\t\t\t\t --------------------------------------";
    cout<<"\n\t\t\t\t MOVIE NAME : "<<moviename[choice-1];
    cout<<"\n\t\t\t\t SHOW TIME  : "<<show[choice-1][selected-1];
    cout<<"\n\t\t\t\t ADULT : "<<adult/20<<"\t CHILD : "<<child/10;
    cout<<"\n\t\t\t\t PRICE : "<<price;
    Sleep(2000);
    purchase();//TAKES YOU TO THE TICKET PURCHASE PAGE
}
string password()
{
    START:
    cout<<"\n\t\t\t\t Enter Password  : ";
    char pass[32];//to store password.
    int i = 0;
    char a;//a Temp char
    for(i=0;;)//infinite loop
    {
        a=getch();//stores char typed in a
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
        //check if a is numeric or alphabet
        {
            pass[i]=a;//stores a in pass
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)//if user typed backspace
        //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';//null means end of string.
            break;//break the loop
        }
    }
    //here we can even check for minimum digits needed
    if(i<=5)
    {
        cout<<"\nMinimum 6 digits needed.\nEnter Again";
        getch();//It was not pausing :p
        goto START;
    }
    return pass;
}
