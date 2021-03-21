//
//  main.cpp
//  Practice
//
//  Created by Jaden  Andrews  on 3/16/21.
//
/**
 *  At this time, the program is limited to one word responses.
 *  Also, the password is not secure.
 *  Also, not all the pathways are finished.
 *  Please don't judge... this is a work in progress.
 *  If you notice any other bugs/iimitations, please feel free to let me know.
 *  And yes, I used documentation comments. I don't even know how these work.
 *  But they're visually appealing.
 */
#include <iostream>
#include <map>
#include <regex>
#include "Library.cpp"

using namespace std;


void ops( Library &lib );
void admin_access( Library &lib );

void set_book ( Book &book, int x, string &request_admin )
{
    vector<string> ph {
        "Ok, what is the title of the book: ",
        "Ok, who is the author: ",
        "Ok, who is the publisher: ",
        "Ok, what year was it published: ",
        "Ok, is it available: "
    };
    cout << ph[x];
    cin >> request_admin;
}
void logic_in_esb ( Book book, regex yes, regex no, string &request_admin)
{
    if( regex_search( request_admin, yes) )
    {
        book.write_available(true);
    } else if ( regex_search( request_admin, no ))
    {
        book.write_available(false);
    }else{
        cout << "Please say yes or no..." << endl;
        cin >> request_admin;
        logic_in_esb( book, yes, no, request_admin);
    }
}
void execute_set_book ( Book &book , string &request_admin, regex yes, regex no )
{
    set_book( book, 0, request_admin );
    book.write_title( request_admin );
    set_book( book, 1, request_admin );
    book.write_author( request_admin );
    set_book( book, 2, request_admin );
    book.write_publisher( request_admin );
    set_book( book, 3, request_admin );
    book.write_pubDate( stoi( request_admin ) );
    set_book( book, 4, request_admin );
    logic_in_esb( book, yes, no, request_admin );
    
}
void esb_logic( Library lib, Book &book, regex yes, regex no, string &request_admin)
{
    if( regex_search( request_admin, yes ) )
    {
        cout << "Ok...";
        admin_access( lib );
    } else if ( regex_search ( request_admin, no ) )
    {
        execute_set_book( book, request_admin, yes, no );
    }
    else
    {
        cout << "Use words...";
        cin >> request_admin;
        esb_logic( lib, book, yes, no, request_admin );
    }
}

void admin_access( Library &lib )
{
    auto const yes = regex("^[yY]([eE][sS])?$");
    auto const no = regex("^[nN]([oO][pP][eE])?$");
    cout << "Here are your admin options: " << endl;
    cout << "1: Change Library Name \t 2: Change Library Location" << endl;
    cout << "3: Add a book          \t 4: Get Book Info" << endl;
    cout << "5: Random bc $*^# it...\t 6: Go Back to Main Menu" << endl;
    
    int choice;
    cin >> choice;
    if( choice == 1 )
    {
        string libName;
        string request_admin;
        cout << "Ok. What would you like to rename " + lib.read_name() + " library?" << endl <<
        "New Name: ";
        
        cin >> libName;
        lib.write_name( libName );
        cout << "Ok. The library is now called " << lib.read_name() << ". Anthing else?" << endl;
        cin >> request_admin;
        if( regex_search( request_admin, yes ) )
        {
            admin_access( lib );
        }
        
    } else if( choice == 2 )
    {
        string request_admin;
        cout << "Ok, where is the library located? " << endl
        << "Location: ";
    }
    else if ( choice == 3 )
    {
        Book book;
        string request_admin;
        execute_set_book( book, request_admin, yes, no );
        cout << "Ok. is this correct: " << endl;
        book.barf();
        cin >> request_admin;
        esb_logic( lib, book, yes, no, request_admin );
        lib.add_book( book );
        
    }else if ( choice == 6 )
    {
        ops( lib );
    }
}

void password( string &psswd, map<string, string> &login, string &usrnm, Library &lib )
{
    if( login[usrnm] == psswd )
    {
        admin_access( lib );
    } else
    {
        cout << "That password was incorrect. Please try again: ";
        cin >> psswd;
        password( psswd, login, usrnm, lib );
    }
}

void log_in( string &request_admin, map<string, string> &login, string &usrnm, Library &lib )
{
    int x = rand() % 3;
    vector<string> responses {
        "Use english please...",
        "I do not understand...",
        "That doesn't make sense to me..."
    };
    regex const yes = regex("^[yY]([eE][sS])?$");
    regex const no = regex("^[nN]([oO][pP][eE])?$");
    cout << "Are you requesting Admin Access? ";
    cin >> request_admin;
    cout << endl;
    if(regex_search( request_admin, yes ))
    {
        string psswd;
        cout << "Ok, what is your password? " << endl << "Password: ";
        cin >> psswd;
        password( psswd, login, usrnm, lib );
    } else if ( regex_search( request_admin, no ) )
    {
        cout << "Ok fine then..." << endl;
    }
    else
    {
        cout << responses[x] << endl;
        log_in( request_admin, login, usrnm, lib );
    }
}


string welcome_speech( Library &lib, Address &a )
{
    string welcome = "Welcome to the " + lib.read_name() + " library located at " + a.read_address() +
                        ". By using this database, you agree to the Terms of Use Agreement located at https://www.emochurro.com/dadatabasa/urscrude. What is your name?";
    return welcome;
}


void ops( Library &lib )
{
    int i;
    vector<string> responses {
        "That's not a valid response...",
        "T-T",
        "Choose from your available options..."
    };
    cout << "What would you like to do today?" << endl;
    cout << "1: Check Book Availability \t 2: Join the Waitlist for a Book" << endl;
    cout << "3: Random Shit             \t 4: Create an Account"<< endl;
    cin >> i;
    if( i == 1 )
    {
        cout << lib.aBooks() << endl;
        if(lib.aBooks().size() == 0)
        {
            cout << "Sorry, there are no books available..."
            << endl << endl;
            ops( lib );
        }
    }
    else
    {
        cout << responses[rand() % 3] << endl;
        ops( lib );
    }
}



int main() {
    
    map<string, string> login;
        login["Jaden"] = "luv2read";
    
    string libName = "Destitute", request_admin, usrnm;
    Address libAddress ( 121, "Despair", 1 );
    Library lib (libName);
    
    cout << welcome_speech( lib, libAddress ) << endl;
    cin >> usrnm;
    cout << "Welcome " << usrnm << endl;
    if( login.count( usrnm ) )
    {
        log_in( request_admin, login, usrnm, lib );
    } else{
        ops( lib );
    }
}

