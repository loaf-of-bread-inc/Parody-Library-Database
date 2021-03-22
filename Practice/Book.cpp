//
//  Book.cpp
//  Practice
//
//  Created by Jaden  Andrews  on 3/18/21.
//

#include <iostream>

using namespace std;

class Book
{
private:
    string title, author, publisher, genre;
    int pubDate;
    bool available;
public:
    Book(string title = "", string author = "", string publisher = "", int pubDate = 0)
    {
        this->title = title;
        this->author = author;
        this->publisher = publisher;
        this->pubDate = pubDate;
        this->available = true;
    }
    string read_title ( )
    {
        return this->title;
    }
    string read_author ( )
    {
        return this->author;
    }
    string read_publisher ( )
    {
        return this->publisher;
    }
    string read_genre ( )
    {
        return this->genre;
    }
    int read_pubDate ( )
    {
        return this->pubDate;
    }
    bool read_available ( )
    {
        return this->available;
    }
    void write_title(string title)
    {
        this->title = title;
    }
    void write_author (string author)
    {
        this->author = author;
    }
    void write_publisher(string publisher)
    {
        this->publisher = publisher;
    }
    void write_genre(string genre)
    {
        this->genre = genre;
    }
    void write_pubDate(int pubDate)
    {
        this->pubDate = pubDate;
    }
    void write_available ( bool available )
    {
        this->available = available;
    }
    
    void barf()
    {
        cout << "Title: " << this->title << endl;
        cout << "Author: " << this->author << endl;
        cout << "Publisher: " << this->publisher << endl;
        cout << "Date of Publication: " << this->pubDate << endl;
    }
    
    bool operator==(const Book& ph) const
    {
        return (this->title == ph.title) && (author == ph.author);
    }
    bool operator<(const Book& ph) const
    {
        return (this->pubDate < ph.pubDate);
    }
};
