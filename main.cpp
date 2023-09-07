//
//  main.cpp
//  Database-System
//
//  Created by Edward Duque on 8/29/23.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    
    //variables for the Book.
    string isbn;
    int year = 0;
    string author;
    string title;
    
    //variables for the Library.
    string libraryName;
    string city;
    int zipCode;
    
    //boolean variable used to exit program.
    bool exitProgram= false;
    
    //while "exitProgram" is not true, keep asking the user to enter commands and variables.
    while(!exitProgram){
        
        cout<<">>> ";
        char command; //variable used for the switch statements.
        cin>>command;
        
        
        
        switch(command){
                
            case 'a'://case 'a' is used for "add"
                
                cin>>command; //ask the user for a seccond command.
                
                switch(command){
                        
                    case 'b':{ //case 'b' is for the user to add a book.
                        
                        //input all book variables or components.
                        cin>> isbn;
                        cin>> year;
                        cin>> author;
                        getline(cin, title);
                        
                        ifstream inputFile("books.txt");//reads file.
                        
                        bool isbnExists= false; //boolean variable to check if book it's in the database.
                        string storedIsbn; //variable to compare the stored ISBN with the ISBN entered by the user.
                        
                        //while the input file is reading a stored ISBN
                        while(inputFile >> storedIsbn){
                            
                            /*if the stores ISBN equals the ISBN entered by the user,
                             the ISBN already exists.*/
                            if (storedIsbn == isbn) {
                                isbnExists = true;
                                break;
                            }
                        }
                        
                        inputFile.close();
                        //if the ISBN exists, print a message.
                        if(isbnExists){
                            cout << "ISBN already exists in the database." << endl;
                        }
                        else{
                            //if the ISBN doesn't exists, enter book information into the file.
                            ofstream outputFile("books.txt", ios::app);
                            
                            if (!outputFile)
                            {
                                cout<<"Failed to load file"<< endl;
                                return 1;
                            }
                            
                            outputFile<< isbn <<" "<< year<< " "<<author<<" "<< title<< endl;
                            
                            outputFile.close();
                        }
                            
                        break;
                    
                    }
                        
                    case 'l':{ //case 'l' is for the user to add a Library.
                        
                        //variables for the Library.
                        cin>> libraryName;
                        cin>> city;
                        cin>> zipCode;
                        
                        //ofstream object and append any information into the file.
                        ofstream outputFile("libraries.txt", ios::app);
                        
                        if (!outputFile)
                        {
                            cout<<"Failed to load file"<< endl;
                            return 1;
                        }
                        //enter book information into the file.
                        outputFile<< libraryName <<" "<< city<< " "<< zipCode<< endl;
                        
                        outputFile.close();
                        
                        
                        break;
                    }
                        
                    case 'h':{ //case 'h' is for the user to hold an ISBN into a Library.
                        
                        //variables used for the holding.
                        cin>> isbn;
                        cin>> libraryName;
                        int copiesBook;//variable for the existing copies in the library.
                        
                        ofstream of("holdings.txt");
                        ifstream inputFile("holdings.txt");
                        
                        if (!inputFile)
                        {
                            cout<<"Failed to load file"<< endl;
                            return 1;
                        }
                        
                        bool bookFound= false;//boolean variable checks if the book is already in the library.
                        //variables used to compare the stored library name and ISBN with the ones entered by the user.
                        string isbnBook;
                        string libraryNameBook;
                        
                        while(inputFile >> isbnBook >> libraryNameBook >> copiesBook)
                        {   /*if the isbn and library name are the same than the stored ones,
                             add one copy, and enter the information into the file*/
                            if(isbn == isbnBook && libraryName == libraryNameBook)
                            {
                                copiesBook++;
                                bookFound= true;
                                
                                ofstream outputFile("holdings.txt", ios::app);
                                
                                outputFile<<isbn<<" "<<libraryName<<" "<<copiesBook<<endl;
                                
                                
                            }
                        }
                        
                        ofstream outputFile("holdings.txt", ios::app);
                        //if the book is not found, create a new entry for the book.
                        if(!bookFound)
                        {
                            outputFile<< isbn<<" "<< libraryName<<" "<< 1<< endl;
                        }
                        
                        outputFile.close();
                        
                        
                        
                        break;
                        
                    }
                    }
                        
                        break;
                }
                
                switch(command){
                        
                    case 'l'://case 'l' is for listing the objects that are in the files.
                        
                        cin>>command;
                        
                        switch(command){
                                
                            case 'b':{//case 'b' is for listing the books in books.txt
                                
                                ifstream inputFile("books.txt");
                                
                                if(!inputFile){
                                    
                                    cerr<<"Failed to load file"<<endl;
                                    return 1;
                                }
                                //string used to get the whole line in the file.
                                string line;
                                
                                while (getline(inputFile, line)) {//while there are books, print them.
                                    cout << line << endl;
                                }
                                
                                inputFile.close();
                                
                                break;
                            }
                                
                            case 'l':{//case 'l' is for listing all libraries in libraries.txt
                                
                                ifstream inputFile("libraries.txt");
                                
                                if (!inputFile) {
                                    cerr << "Failed to load file" << endl;
                                    return 1;
                                }
                                // same as in the previous case.
                                string line;
                                
                                while(getline(inputFile, line)){//while there are librarie, print them.
                                    
                                    cout<< line<< endl;
                                }
                                
                                inputFile.close();
                                
                                break;
                                
                            }
                                
                        }
                        
                        break;
                        
                }
                
                switch(command){
                        
                    case 'f':// case 'f' used to find the ISBN in the different libraries.
                        
                        cin>> isbn;
                        
                        //reading all files.
                        ifstream holdingsFile("holdings.txt");
                        ifstream booksFile("books.txt");
                        ifstream librariesFile("libraries.txt");
                        
                        if (!holdingsFile || !booksFile || !librariesFile)
                            {
                                cerr << "Failed to load one or more files" << endl;
                                return 1;
                            }
                            
                            bool bookFound = false;
                            //variable used to compare the stored ISBN with the one entered by the user.
                            string isbnBook;
                            //variables used to enable the file to read all the information.
                            string libraryNameBook;
                            int copiesBook;
                        
                        //first go through holdings file.
                        while (holdingsFile >> isbnBook >> libraryNameBook >> copiesBook)
                            {
                                if (isbn == isbnBook)
                                {
                                    bookFound = true;

                                    // look for the book information
                                    string bookTitle, authorName;
                                    int publishYear;
                                    
                                    //then go through books file.
                                    while (booksFile >> isbnBook >> publishYear >> authorName)
                                    {
                                        getline(booksFile, bookTitle);//get the whole line.
                                        // if the isbn it's found in both files, print the book information.
                                        if (isbn == isbnBook)
                                        {
                                            cout << libraryNameBook << ": " << isbnBook << " " << publishYear << " " << authorName << " " << bookTitle << " Copy Number: " << copiesBook << endl;
                                        }
                                    }
                                    booksFile.clear();  // Reset the file stream for the next search
                                    booksFile.seekg(0, ios::beg);//beggining of the stream.
                                }
                            }
                        
                        if (!bookFound)
                           {
                               cout << "No holdings found for ISBN " << isbn << endl;
                           }

                           holdingsFile.close();
                           booksFile.close();
                           librariesFile.close();

                        
                        break;
                }
                
                switch(command){
                        
                    case 'q'://case 'q' used to exit the program.
                        
                        exitProgram= true;
                        break;
                }
                
        }
        
    }
    
