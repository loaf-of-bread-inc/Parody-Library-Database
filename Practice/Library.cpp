//
//  Library.cpp
//  Practice
//
//  Created by Jaden  Andrews  on 3/18/21.
//

#include <stdio.h>
#include <vector>
#include <map>
#include "Book.cpp"
#include "Address.cpp"

using namespace std;

class Library
{
private:
    string name;
    Address address;
    vector<Book> books;
    vector<Book> a_books;
    vector<Book> u_books;
public:
    Library( string name = "", Address address = Address() )
    {
        this->name = name;
        this->address = address;
        this->books = { };
    }
    string read_name( )
    {
        return this->name;
    }
    vector<Book> books_inventory( )
    {
        return this->books;
    }
    vector<Book> books_available ( )
    {
        return this->a_books;
    }
    vector<Book> books_unavailable ( )
    {
        return this->u_books;
    }
    string aBooks( )
    {
        string ph;
        int i = 0;
        for( Book x:this->a_books )
        {
            if( i % 3 == 0 )
            {
                cout << endl;
            }
            ph+= x.read_title( ) + " by " + x.read_author( ) + "/t";
        }
        return ph;
    }
    string uBooks( )
    {
        string ph;
        int i = 0;
        for( Book x:this->u_books )
        {
            if( i % 3 == 0)
            {
                cout << endl;
            }
            ph+= x.read_title( ) + " by " + x.read_author( ) + "\t";
        }
        return ph;
    }
    void write_name( string name )
    {
        this->name = name;
    }
    void add_book ( Book book )
    {
        this->books.push_back( book );
        if( book.read_available( ) )
        {
            a_books.push_back( book );
        } else
        if( !book.read_available( ) )
        {
            u_books.push_back( book );
        }
    }
    void remove_book( Book book )
    {
        vector<Book> ph;
        for( Book x:books )
        {
            if( x == book )
            {
                continue;
            }
            ph.push_back( book );
        }
        this->books = ph;
        if( book.read_available( ) )
        {
            ph = {};
            for( Book x:a_books )
            {
                if( x == book )
                {
                    continue;
                }
                ph.push_back(x);
            }
            this->a_books = ph;
        }
    }
    void write_aBooks ( vector<Book> book )
    {
        this->a_books = book;
    }
    
    
};
