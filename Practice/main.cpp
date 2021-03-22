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
 *  Also, when you are adding a book, if you say no, it will ask you for the correct information, then exit the program. (fixed)
 *  Also, when you're adding a book, it doesn't get added to the Library. (fixed)
 *  Please don't judge... this is a work in progress.
 *  If you notice any other bugs/iimitations, please feel free to let me know.
 *  And yes, I used documentation comments. I don't even know how these work.
 *  But they're visually appealing.
 */
// You need to tie the "Check Book Availability" options from the 'regular users' and a'dmin users' pathways to a single function
#include <iostream>
#include <map>
#include <regex>
#include "Library.cpp"

using namespace std;

string libName = "Destitute", request_admin, usrnm;
Library lib ( libName );
map<string, string> login;
Address libAddress ( 121, "Despair", 1 );
void ops( );
void admin_access( );
regex const yes = regex( "^[yY]([eE][sS])?$") ;
regex const no = regex( "^[nN]([oO]([pP][eE])?)?$" );


/**
 * This function 'set_book'  chooses from one of five string options in vector ph, prints it out, then awaits a response to the question.
 * Idea: Change the vector to a map<string, string> . Even though they don't all take the same response type, you could convert them when you needed them.
 *          This means that you would have to refine all potential input values. A year could not be beyond a certain number of digits.
 *          Javascript is just better when it comes to types because they are undeclared until need be, and they are amorphous so they can change whenever.
 * Idea: Change the name to opFive
 */
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
/**
 *This function determines whether 'this->book.available' is true or false. If it is neither, it repeats itself until it is either true or false.
 *Idea: Change the name to excOpFive_logic
 */
void logic_in_esb ( Book book, string &request_admin )
{
    if( regex_search( request_admin, yes ) )
    {
        book.write_available( true );
    } else if ( regex_search( request_admin, no ) )
    {
        book.write_available( false );
    }else{
        cout << "Please say yes or no..." << endl;
        cin >> request_admin;
        logic_in_esb( book, request_admin );
    }
}
/**
 *This function uses the functions 'set_book( )'  and 'logic_in_esb( )' to determine the values of each variable in a given book
 * Idea: Change name to excOpFive
 */
void execute_set_book ( Book &book , string &request_admin )
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
    logic_in_esb( book, request_admin );
    
}
/**
 * This function provides logic for 'admin_access( )' off the back of the
 * Idea: Change name to opFive_logic
 */
void esb_logic( Book &book, string &request_admin )
{
    cout << endl << "Ok. is this correct: " << endl << endl;
    book.barf( );
    cin >> request_admin;
    if( regex_search( request_admin, yes ) )
    {
        cout << endl << "Ok...";
        lib.add_book( book );
        admin_access( );
    } else if ( regex_search ( request_admin, no ) )
    {
        execute_set_book( book, request_admin );
        esb_logic( book, request_admin );
    }
    else
    {
        cout << "Use words...";
        cin >> request_admin;
        esb_logic( book, request_admin );
    }
}
/**
 *
 */
void admin_access( )
{
    int choice;
    cout << "Here are your admin options: " << endl;
    cout << "1: Change Library Name    \t 2: Change Library Location" << endl;
    cout << "3: Add a book             \t 4: Get Book Info" << endl;
    cout << "5: Check Book Availability\t 6: Go Back to Main Menu" << endl;
    
    cin >> choice;
    if( choice == 1 )
    {
        string libName;
        string request_admin;
        cout << "Ok. What would you like to rename " + lib.read_name( ) + " library?" << endl <<
        "New Name: ";
        
        cin >> libName;
        lib.write_name( libName );
        cout << "Ok. The library is now called " << lib.read_name( ) << ". Anthing else?" << endl;
        cin >> request_admin;
        if( regex_search( request_admin, yes ) )
        {
            admin_access( );
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
        execute_set_book( book, request_admin );
        
        esb_logic( book, request_admin );
    }else if ( choice == 5 )
    {
        for( Book book:lib.books_available( ) )
        {
            cout << endl;
            book.barf();
            cout << endl;
        }
        cout << endl << "Those are all the available books..." << endl;
        admin_access();
    }else if ( choice == 6 )
    {
        ops( );
    }
}

void password( string &psswd, map<string, string> &login, string &usrnm )
{
    if( login[ usrnm ] == psswd )
    {
        admin_access( );
    } else
    {
        cout << "That password was incorrect. Please try again: ";
        cin >> psswd;
        password( psswd, login, usrnm );
    }
}

void log_in( string &request_admin, map<string, string> &login, string &usrnm )
{
    int x = rand( ) % 3;
    vector<string> responses {
        "Use english please...",
        "I do not understand...",
        "That doesn't make sense to me..."
    };
    cout << "Are you requesting Admin Access? ";
    cin >> request_admin;
    cout << endl;
    if(regex_search( request_admin, yes ) )
    {
        string psswd;
        cout << "Ok, what is your password? " << endl << "Password: ";
        cin >> psswd;
        password( psswd, login, usrnm );
    } else if ( regex_search( request_admin, no ) )
    {
        cout << "Ok fine then..." << endl;
        ops( );
    }
    else
    {
        cout << responses[x] << endl;
        log_in( request_admin, login, usrnm );
    }
}


string welcome_speech( Address &a )
{
    string welcome = "Welcome to the " + lib.read_name( ) + " library located at " + a.read_address( ) +
                        ". By using this database, you agree to the Terms of Use Agreement located at https://www.emochurro.com/dadatabasa/urscrude. What is your name?";
    return welcome;
}


void ops( )
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
        cout << lib.aBooks( ) << endl;
        if(lib.aBooks( ).size( ) == 0)
        {
            cout << "Sorry, there are no books available..."
            << endl << endl;
            ops( );
        }
    }
    else
    {
        cout << responses[ rand( ) % 3 ] << endl;
        ops( );
    }
}



int main( ) {
    login[ "Jaden" ] = "luv2read";
    lib.write_address( libAddress );
    cout << welcome_speech( libAddress ) << endl;
    cin >> usrnm;
    cout << "Welcome " << usrnm << endl;
    if( login.count( usrnm ) )
    {
        log_in( request_admin, login, usrnm );
    } else{
        ops( );
    }
}

