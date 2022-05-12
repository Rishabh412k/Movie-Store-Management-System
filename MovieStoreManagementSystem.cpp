#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


/*
------------------------- ADMIN PASSWORD: admin@123 -------------------------------------------
------------------------- In this program there are two login modules: 1.Admin 2.User ---------

------------------------- Admin can perform following actions: --------------------------------
------------------------- 1.View through entire movie list-------------------------------------
------------------------- 2.Add a movie in file------------------------------------------------
------------------------- 3.Delete a movie from file-------------------------------------------
------------------------- 4.Calculate bill of user if he/she has opted for services------------
------------------------- 5.Revoke access or ban user from performing further operations-------

------------------------- User can perform following operations:-------------------------------
------------------------- 1.View movie list from file -----------------------------------------
------------------------- 2.Search movie from list by name, genre and artist/actor-------------
------------------------- 3.Choose options from subscription package and get bill--------------

*/


class Admin {
    public:

    // It prints movie list with all data present in Film-list.txt file
    void viewMovieList() {
        fstream fs;
        fs.open("Film-list.txt");

        string str;
        while(getline(fs, str)) {
            cout << str << "\n";
        }

        fs.close();
    }


    // It adds movie with other data like genre, actor, director and year in Film-list.txt file
    void addMovie() {
        fstream fs;
        fs.open("Film-list.txt", ios::app | ios::in | ios::out);
        
        string filmData;
        cout << "Enter name of film, genre, actor, director and year: ";
        cin.ignore();
        getline(cin, filmData);
        fs << "\n" << filmData;

        fs.close();
    }


    // It deletes movie from Film-list.txt file
    void deleteMovie() {
        // Open file, search movie and store position of movie in a variable
      fstream readFile;
      readFile.open("Film-list.txt", ios::in | ios::out);
      
      string movieName, temp;
      cout << "Enter movie name to delete: ";
      cin.ignore();
      getline(cin, movieName);

      int pos = 0;
      int matchSize = 0;
      bool flag;
      while(getline(readFile, temp)) {
             pos++;
             for(int i = 0; i < movieName.size(); i++) {
                    if(temp[i] == movieName[i]) {
                           matchSize++;
                    }
                    else if(temp[i] != movieName[i]) {
                           matchSize = 0;
                           break;
                    }
             }         

             if(matchSize == movieName.size()) {
                    flag = true;
                    break;
             }
             else {
                    flag = false;
             }
      }
      readFile.close();

    
      // Create a new file and copy all data from old file to new file except movie you want to delete
      fstream writeFile;
      writeFile.open("Film-list1.txt", ios::out);
      readFile.open("Film-list.txt", ios::in);

      string input;
      int cnt = 0;
      while(getline(readFile, input)) {
             cnt++;
             if(pos != cnt) {
                    writeFile << input << "\n";
             }
      } 

      writeFile.close();
      readFile.close();

      
      // copy all data back to older file
      writeFile.open("Film-list1.txt", ios::in);
      readFile.open("Film-list.txt", ios::out | ios::trunc);

      while(getline(writeFile, input)) {
             readFile << input << "\n";
      }

      writeFile.close();
      readFile.close();


      // delte new file
      remove("Film-list1.txt");
    }


    // It calculates bill of a total bill based on input given by user
    void calculateBill(int response) {
        fstream fs;
        int perDay, weekly, monthly, yearly;
        int res = 0;
        
        if(response == 1) {
            fs.open("Bill.txt", ios::in);
            if(fs.tellp() < 0) {
                cout << "User hasn't chosen any plan yet.\n";
            }
            else {
                string input;
                cin.ignore();
                while(getline(fs, input)) {
                        cout << input << "\n";
                }
            }
            fs.close();
        }

        else if(response == 2) {
        fs.open("Bill.txt", ios::out);
        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: perDay = 5;
                int noOfDays;
                cout << "Enter number of days you want to take subscription for: ";
                cin >> noOfDays;
                cout << "Your bill for " << noOfDays << " days is: Rs." << noOfDays * perDay << "\n";
                res = noOfDays*perDay;
            break;

            case 2: weekly = 20;
                cout << "Your bill for a week: Rs." << weekly << "\n";
                res = weekly;
            break;

            case 3: monthly = 200;
                cout << "Your bill for a month: Rs." << monthly << "\n";
                res = monthly;
            break;

            case 4: yearly = 1200;
                cout << "Your bill for a year: Rs." << yearly << "\n";
                res = yearly;
            break;
        }

            fs << "User's movie bill is " << res;
            fs.close();
        }
    }

    // It can revoke/take away access of a user from performing any operations in this entire program
    void revokeAccessOfUser(bool userStatus) {
        fstream fs;
        fs.open("User-Status.txt", ios::out | ios::trunc);
        
        if(!userStatus) {
            cout << "You have successfully banned user." << "\n";
            fs << "false";
        }
        else {
            cout << "You have successfully unbanned user.\n";
            fs << "true";
        }

        fs.close();
    }
};




class User: public Admin {
    public:


    // It searches movie from file Film-list.txt file and print according to input
    void searchMovieByCategory() {

        cout << "\nSelect from following: \n";
        cout << "1.Search movie by name.\n";
        cout << "2.Search movie by genre.\n";
        cout << "3.Search movie by artist/actor\n.";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                fstream readFile;
                readFile.open("Film-list.txt", ios::in);
                
                string movieName, temp;
                cout << "Search movie by name: ";
                cin.ignore();
                getline(cin, movieName);

                int pos = 0;
                int matchSize = 0;
                bool flag;
                while(getline(readFile, temp)) {
                        pos++;
                        for(int i = 0; i < movieName.size(); i++) {
                                if(temp[i] == movieName[i]) {
                                    matchSize++;
                                }
                                else if(temp[i] != movieName[i]) {
                                    matchSize = 0;
                                    break;
                                }
                        }         

                        if(matchSize == movieName.size()) {
                                flag = true;
                                break;
                        }
                        else {
                                flag = false;
                        }
                }
                readFile.close();


                readFile.open("Film-list.txt", ios::in); 
                if(flag) {
                        string detailOfMovie;
                        int cnt = 0;
                        while(getline(readFile, detailOfMovie)) {
                                cnt++;
                                if(cnt == pos) {
                                        cout << detailOfMovie << "";
                                }
                        }
                }
                else {
                        cout << "Movie not found.\n";
                }
                readFile.close();
            }
            break;


            case 2: {
                fstream readFile;
                readFile.open("Film-list.txt", ios::in);
                
                string genre, temp;
                cout << "\nSearch movie by genre: ";
                cin.ignore();
                getline(cin, genre);

                vector <int> arr;
                int pos = 0;
                int matchSize = 0;
                bool flag;
                while(getline(readFile, temp)) {
                        pos++;
                        int j = 0;
                        for(int i = 0; i < temp.size(); i++) {
                                if(temp[i] == genre[j]) {
                                    matchSize++;
                                    j++;

                                    if(matchSize == genre.size()) {
                                            arr.push_back(pos);
                                    }
                                }
                                else if(temp[i] != genre[j]) {
                                    matchSize = 0;
                                    j = 0;
                                }
                        }         
                }

                arr.size() ? flag = true : flag = false;
                readFile.close();


                readFile.open("Film-list.txt", ios::in); 
                if(flag) {
                        string detailOfMovie;
                        int cnt = 0;
                        while(getline(readFile, detailOfMovie)) {
                                cnt++;
                                for(int i = 0; i < arr.size(); i++) {
                                    if(cnt == arr[i]) {
                                            cout << detailOfMovie << "\n";
                                    }
                                }
                        }
                }
                else {
                        cout << "Movie with genre you entered not found.\n";
                }
                readFile.close();
            }
            break;


            case 3:
                fstream readFile;
                readFile.open("Film-list.txt", ios::in);
                
                string actorName, temp;
                cout << "\nSearch movie by actor name: ";
                cin.ignore();
                getline(cin, actorName);

                vector <int> arr;
                int pos = 0;
                int matchSize = 0;
                bool flag;
                while(getline(readFile, temp)) {
                        pos++;
                        int j = 0;
                        for(int i = 0; i < temp.size(); i++) {
                                if(temp[i] == actorName[j]) {
                                    matchSize++;
                                    j++;

                                    if(matchSize == actorName.size()) {
                                            arr.push_back(pos);
                                    }
                                }
                                else if(temp[i] != actorName[j]) {
                                    matchSize = 0;
                                    j = 0;
                                }
                        }         
                }

                arr.size() ? flag = true : flag = false;
                readFile.close();


                readFile.open("Film-list.txt", ios::in); 
                if(flag) {
                        string detailOfMovie;
                        int cnt = 0;
                        while(getline(readFile, detailOfMovie)) {
                                cnt++;
                                for(int i = 0; i < arr.size(); i++) {
                                    if(cnt == arr[i]) {
                                            cout << detailOfMovie << "\n";
                                    }
                                }
                        }
                }
                else {
                        cout << "Movie with genre you entered not found.\n";
                }
                readFile.close();
            break;
        }
    }


    // It gives input to calculateBill() function if bill hasn't been calculated before. Otherwise, it fetches data from Bill.txt file
    void checkYourBill(int response) {
        fstream fs;
        fs.open("Bill.txt", ios::in);
        if(fs.tellp() < 0) {
                cout << "Select from following: \n";
                cout << "1.Days wise subscription.\n";
                cout << "2.Weekly subscription.\n";
                cout << "3.Monthly subscription.\n";
                cout << "4.Yearly subscription.\n";

                calculateBill(response);
        }
        else {
                string input;
                while(getline(fs, input)) {
                    cout << input << "\n";
                }
        }

        fs.close();
    }
};


int main() {

    cout << "-----------------------------" << "\n";
    cout << "MOVIE STORE MANAGEMENT SYSTEM" << "\n";
    cout << "-----------------------------" << "\n\n";

    cout << "If you are admin press 1, for user press 2." << "\n";
    cout << "1.Admin" << "\n";
    cout << "2.User" << "\n";
    cout << "3.Exit" << "\n";
    
    int response;
    cout << "Enter your response: ";
    cin >> response;


    //------------ ADMIN------------- 
    if(response == 1) {
        string password;
        cout << "Enter your password: ";
        cin >> password;
        cout << "\n\n";

        if(password == "admin@123") {
            system("cls");
            cout << "-----------------------------" << "\n";
            cout << "MOVIE STORE MANAGEMENT SYSTEM" << "\n";
            cout << "-----------------------------" << "\n\n";
            cout << "Welcome Admin!\n\n";

            cout << "Select from following: " << "\n";
            cout << "1.View movie list.\n";
            cout << "2.Add a movie.\n";
            cout << "3.Delete a movie.\n";
            cout << "4.Calculate bill.\n";
            cout << "5.Revoke access of user.\n";
            cout << "6.Exit\n\n";

            int choice;
            cout << "Enter your response: ";
            cin >> choice;

            Admin admin;
            switch(choice) {
                case 1: admin.viewMovieList();
                break;

                case 2: admin.addMovie();
                break;

                case 3: admin.deleteMovie();
                break;

                case 4: admin.calculateBill(response);
                break;

                case 5:
                    int choice;
                    cout << "Do you want to ban user ?\n";
                    cout << "Select from following: \n";
                    cout << "0.Yes\n";
                    cout << "1.No\n";
                    cout << "Enter: ";
                    cin >> choice;

                    admin.revokeAccessOfUser(choice);
                break;

                case 6: exit(0);
                break;
            }
        }
 
        //------------ WRONG PASSWORD------------
        else {
            cout << "OOPS! You've entered wrong password try again.";
        }
    }


    //--------USER-----------
    else if(response == 2) {
        fstream fs;
        fs.open("User-Status.txt", ios::in);

        string input; 
        getline(fs, input);

        if(input == "true" || fs.tellp() < 0) {
            system("cls");
            cout << "-----------------------------" << "\n";
            cout << "MOVIE STORE MANAGEMENT SYSTEM" << "\n";
            cout << "-----------------------------" << "\n\n";
            cout << "\n\n" << "Welcome User!\n\n";

            cout << "Select from following: " << "\n";
            cout << "1.View movie list.\n";
            cout << "2.Search a movie by category.\n";
            cout << "3.Check usage bill.\n";
            cout << "4.Exit\n";

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            User user;
            switch(choice) {
                case 1: user.viewMovieList();
                break;

                case 2: user.searchMovieByCategory();
                break;

                case 3: user.checkYourBill(response);
                break;

                case 4: exit(0);
                break;
            }
        }
        else if(input == "false"){
            cout << "You have been banned by Admin.\n";
        }
        fs.close();
    }

    else if(response == 3) {
        exit(0);
    }
}