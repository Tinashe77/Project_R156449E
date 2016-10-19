#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<iostream>
#include<string.h>
#include<windows.h>
#include<iomanip>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
using namespace std;

class file {
    char file_no[6];
    char file_name[50];
    char author_name[20];
public:

    void create_file();
    void show_file();
    char* retfno();
    void report();
}; //class ends here

void file::create_file() {
    cout << "\nNEW FILE ENTRY...\n";
    cout << "\nEnter The file no.";
    cin>>file_no;
    cout << "\n\nEnter The Name of The File ";
    cin>>file_name;
    cout << "\n\nEnter The Author's Name ";
    cin>>author_name;
    cout << "\n\n\nFile Created..";
}

void file::show_file() {
    cout << "\nBook/Article no. : " << file_no;
    cout << "\nBook/article Name : " << file_name;
    cout << "Author Name : " << author_name;
}

char* file::retfno() {
    return file_no;
}

void file::report() {
    cout << file_no << setw(30) << file_name << setw(30) << author_name << setw(30);
}

class article : public file {
    string validity;
public:
    void validation();
    void article_report();

    void show_art() {
        cout << "\nValidation Period : " << validity;
    }
};

void article::validation() {
    cout << "Enter the validity period in format DD-MM-YYYY" << endl;
    cin>>validity;
}

void article::article_report() {
    cout << validity << endl;
}

class book : public file {
    char subject[20];
public:
    void addsubject();
    void book_report();

    void show_book() {
        cout << "\nBook subject : " << subject;
    }
};

void book::addsubject() {
    cout << "Enter book subject" << endl;
    cin>>subject;
}

void book::book_report() {
    cout << subject << endl;
}
//***************************************************************
//                   CLASSES FOR MEMBERS USED IN PROJECT
//****************************************************************
class staff ;
class student ;
class Member {
    char admission_no[6];
    char member_name[20];
    char stbno[6], post[6], lev[6], dep[10];
    int token;
public:

    void create_member(char m[]);
    void create_member(char n[], char b[]);
    void show_member();
    char* retadmno();
    char* retstbno();
    int rettoken();
    void addtoken();
    void resettoken();
    void getstbno(char t[]);
    void report(staff fc);
    void report(student st);
}; //class ends here

class staff : public Member {
    char post[20];
public:
    void addpost();
    void staff_report();

    void show_staff() {
        cout << "\nPost. : " << post;

    }

}; //class ends here

void staff::addpost() {
    cout << "whats your post" << endl;
    cin>>post;
}

class student : public Member {
    char level[20];
public:
    void addlevel();
    void student_report();

    void show_student() {
        cout << "\nLevel. : " << level;

    }
};

/*void student::addlevel() {
    cout << "What year are you in?...(FIRST,SECOND,THIRD OR FINAL?)" << endl;
    cin>>level;
}*/

/*void student::student_report() {
    cout << lev << endl;
}*

void staff::staff_report() {
    cout << post << endl;
}*/

void Member::create_member(char m[6]) {
    cout << "\nNEW MEMBER ENTRY...\n";
    cout<<m;
    cout << "\nEnter The admission no. ";
    cin>>admission_no;
    cout << "\n\nEnter The Name of The Member ";
    cin>>member_name;
    lev [6]= m[6];//failed to intialize using this method
    cout<<lev;
    token = 0;
    stbno[0] = '/0';
    cout << "\nMember Record Created..";
}

void Member::create_member(char n[], char b[]) {
    cout << "\nNEW MEMBER ENTRY...\n";
    cout << "\nEnter The admission no. ";
    cin>>admission_no;
    cout << "\n\nEnter The Name of The Member ";
    cin>>member_name;
    post[6] = n[6];
    dep[10]= b[10];
    token = 0;
    stbno[0] = '/0';
    cout << "\nMember Record Created..";
}

void Member::show_member() {
    cout << "\nAdmission no. : " << admission_no;
    cout << "\nMember Name : " << member_name;
    cout << "\nNo of Book issued : " << token;
    if (token == 1)
        cout << "\nBook No " << stbno;
}

char* Member::retadmno() {
    return admission_no;
}

char* Member::retstbno() {
    return stbno;
}

int Member::rettoken() {
    return token;
}

void Member::addtoken() {
    token = 1;
}

void Member::resettoken() {
    token = 0;
}

void Member::getstbno(char t[]) {
    strcpy(stbno, t);
}

void Member::report(student st) {
    cout << "\t" << admission_no << setw(20) << member_name << setw(20) << token << setw(10) << lev<<endl;
}
void Member::report(staff fc) {
    cout << "\t" << admission_no << setw(20) << member_name << setw(20) << token << setw(10) << post << setw(10)<<endl;
}

//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp, fp1;
book bk;
article art;
student stud;
staff stff;
//***************************************************************
//    	function to write in file
//****************************************************************

void write_staff() {
    char ch,pos[6],dpt[10];
    fp.open("staff.dat", ios::out | ios::app);
    do {
        cout << "Whats your post and department?" << endl;
        cin>>pos;
        cin>>dpt;
        stff.create_member(pos,dpt);
        //stff.addpost();
        fp.write((char*) &stff, sizeof (staff));
        cout << "\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_student() {
    char ch, level[6];
    fp.open("student.dat", ios::out | ios::app);
    do {
        cout << "Whats your level?" << endl;
        cin>>level;
        stud.create_member(level);
        //stud.addlevel();
        fp.write((char*) &stud, sizeof (student));
        cout << "\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_article() {
    char ch;
    fp.open("article.dat", ios::out | ios::app);
    do {
        art.create_file();
        art.validation();
        fp.write((char*) &art, sizeof (article));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_book() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        bk.create_file();
        bk.addsubject();
        fp.write((char*) &bk, sizeof (book));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}
//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_spbook(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*) &bk, sizeof (book))) {
        if (strcmpi(bk.retfno(), n) == 0) {
            bk.show_file();
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nBook does not exist";
    getch();
}

void display_sparticle(char n[]) {
    cout << "\nARTICLE DETAILS\n";
    int flag = 0;
    fp.open("article.dat", ios::in);
    while (fp.read((char*) &art, sizeof (article))) {
        if (strcmpi(art.retfno(), n) == 0) {
            art.show_file();
            art.show_art();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nArticle does not exist";
    getch();
}

void display_student(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*) &stud, sizeof (student))) {
        if ((strcmpi(stud.retadmno(), n) == 0)) {
            stud.show_member();
            stud.show_student();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStudent does not exist";
    getch();
}

void display_staff(char n[]) {
    cout << "\nSTAFF DETAILS\n";
    int flag = 0;
    fp.open("staff.dat", ios::in);
    while (fp.read((char*) &stff, sizeof (staff))) {
        if ((strcmpi(stff.retadmno(), n) == 0)) {
            stff.show_member();
            stff.show_staff();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStaff does not exist";
    getch();
}
//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student() {
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin>>n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*) &stud, sizeof (student))) {
        if (strcmpi(stud.retadmno(), n) != 0)
            fp2.write((char*) &stud, sizeof (student));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    getch();
}

void delete_staff() {
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE STAFF...";
    cout << "\n\nEnter The admission no. of the Staff You Want To Delete : ";
    cin>>n;
    fp.open("staff.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*) &stff, sizeof (staff))) {
        if (strcmpi(stff.retadmno(), n) != 0)
            fp2.write((char*) &stff, sizeof (staff));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("staff.dat");
    rename("Temp.dat", "staff.dat");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    getch();
}
//***************************************************
//                 DELETING FILES
//***************************************************

void delete_book() {
    char n[6];
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*) &bk, sizeof (book))) {
        if (strcmpi(bk.retfno(), n) != 0) {
            fp2.write((char*) &bk, sizeof (book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}

void delete_article() {
    char n[6];
    cout << "\n\n\n\tDELETE ARTICLE ...";
    cout << "\n\nEnter The Article no. of the Article You Want To Delete : ";
    cin>>n;
    fp.open("article.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*) &art, sizeof (article))) {
        if (strcmpi(art.retfno(), n) != 0) {
            fp2.write((char*) &art, sizeof (article));
        }
    }

    fp2.close();
    fp.close();
    remove("article.dat");
    rename("Temp.dat", "article.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}
//***************************************************************
//    	function to display all students list
//****************************************************************

void display_allstudents() {
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "========================================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued" << setw(10) << "Level\n";
    cout << "=========================================================================================\n";

    while (fp.read((char*) &stud, sizeof (student))) {
        stud.report(stud);
    }

    fp.close();
    getch();
}

void display_allstaff() {
    fp.open("staff.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tSTAFF LIST\n\n";
    cout << "=====================================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued" << setw(10) << "Post\n";
    cout << "=====================================================================================\n";

    while (fp.read((char*) &stff, sizeof (staff))) {
        stff.report(stff);
    }

    fp.close();
    getch();
}

//***************************************************************
//    	function to display Books list
//****************************************************************

void display_allbooks() {
    fp.open("book.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << "======================================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author" << setw(20) << "Subject\n";
    cout << "======================================================================================\n";

    while (fp.read((char*) &bk, sizeof (book))) {
        bk.report();
        bk.book_report();
    }
    fp.close();
    getch();
}

void display_allarticle() {
    fp.open("article.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tArticle LIST\n\n";
    cout << "================================================================================================\n";
    cout << "Article Number" << setw(20) << "Article Name" << setw(25) << "Author" << setw(20) << "ValidityPeriod\n";
    cout << "================================================================================================\n";

    while (fp.read((char*) &art, sizeof (article))) {
        art.report();
        art.article_report();
    }
    fp.close();
    getch();
}
//***************************************************************
//    	function to issue book
//****************************************************************

void book_student_issue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*) &stud, sizeof (student)) && found == 0) {
        if (strcmpi(stud.retadmno(), sn) == 0) {
            found = 1;
            if (stud.rettoken() == 0) {
                cout << "\n\n\tEnter the book no. ";
                cin>>bn;
                while (fp1.read((char*) &bk, sizeof (book)) && flag == 0) {
                    if (strcmpi(bk.retfno(), bn) == 0) {
                        bk.show_file();
                        bk.show_book();
                        flag = 1;
                        stud.addtoken();
                        stud.getstbno(bk.retfno());
                        int pos = -1 * sizeof (stud);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stud, sizeof (student));
                        cout << "\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "You have not returned the last book ";

        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

void book_staff_issue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The staff's admission no.";
    cin>>sn;
    fp.open("staff.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*) &stff, sizeof (staff)) && found == 0) {
        if (strcmpi(stff.retadmno(), sn) == 0) {
            found = 1;
            if (stff.rettoken() == 0) {
                cout << "\n\n\tEnter the book no. ";
                cin>>bn;
                while (fp1.read((char*) &bk, sizeof (book)) && flag == 0) {
                    if (strcmpi(bk.retfno(), bn) == 0) {
                        bk.show_file();
                        bk.show_book();
                        flag = 1;
                        stff.addtoken();
                        stff.getstbno(bk.retfno());
                        int pos = -1 * sizeof (stff);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stff, sizeof (staff));
                        cout << "\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "You have not returned the last book ";

        }
    }
    if (found == 0)
        cout << "Staff record not exist...";
    getch();
    fp.close();
    fp1.close();
}
//***************************************************************
//    	function to issue article
//****************************************************************

void article_student_issue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nArticle ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("article.dat", ios::in | ios::out);
    while (fp.read((char*) &stud, sizeof (student)) && found == 0) {
        if (strcmpi(stud.retadmno(), sn) == 0) {
            found = 1;
            if (stud.rettoken() == 0) {
                cout << "\n\n\tEnter the article no. ";
                cin>>bn;
                while (fp1.read((char*) &art, sizeof (article)) && flag == 0) {
                    if (strcmpi(art.retfno(), bn) == 0) {
                        art.show_file();
                        art.show_art();
                        flag = 1;
                        stud.addtoken();
                        stud.getstbno(art.retfno());
                        int pos = -1 * sizeof (stud);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stud, sizeof (student));
                        cout << "\n\n\t Article issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "You have not returned the last book ";

        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

void article_staff_issue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nArticle ISSUE ...";
    cout << "\n\n\tEnter The staff's admission no.";
    cin>>sn;
    fp.open("staff.dat", ios::in | ios::out);
    fp1.open("article.dat", ios::in | ios::out);
    while (fp.read((char*) &stff, sizeof (staff)) && found == 0) {
        if (strcmpi(stff.retadmno(), sn) == 0) {
            found = 1;
            if (stff.rettoken() == 0) {
                cout << "\n\n\tEnter the article no. ";
                cin>>bn;
                while (fp1.read((char*) &art, sizeof (article)) && flag == 0) {
                    if (strcmpi(art.retfno(), bn) == 0) {
                        art.show_file();
                        art.show_art();
                        flag = 1;
                        stff.addtoken();
                        stff.getstbno(art.retfno());
                        int pos = -1 * sizeof (stff);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stff, sizeof (staff));
                        cout << "\n\n\t Article issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                    cout << "Article no does not exist";
            } else
                cout << "You have not returned the last book ";

        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

//***************************************************************
//    	function to student deposit 
//****************************************************************

void book_student_deposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;

    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The studentâ€™s admission no.";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*) &stud, sizeof (student)) && found == 0) {
        if (strcmpi(stud.retadmno(), sn) == 0) {
            found = 1;
            if (stud.rettoken() == 1) {
                while (fp1.read((char*) &bk, sizeof (book)) && flag == 0) {
                    if (strcmpi(bk.retfno(), stud.retstbno()) == 0) {
                        bk.show_file();
                        bk.show_book();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days";
                        cin>>day;
                        if (day > 15) {
                            fine = (day - 15)*1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        stud.resettoken();
                        int pos = -1 * sizeof (stud);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stud, sizeof (student));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

void article_student_deposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;

    cout << "\n\nArticle DEPOSIT ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("article.dat", ios::in | ios::out);
    while (fp.read((char*) &stud, sizeof (student)) && found == 0) {
        if (strcmpi(stud.retadmno(), sn) == 0) {
            found = 1;
            if (stud.rettoken() == 1) {
                while (fp1.read((char*) &art, sizeof (article)) && flag == 0) {
                    if (strcmpi(art.retfno(), stud.retstbno()) == 0) {
                        art.show_file();
                        art.show_art();
                        flag = 1;
                        cout << "\n\narticle deposited in no. of days";
                        cin>>day;
                        if (day > 15) {
                            fine = (day - 15)*1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        stud.resettoken();
                        int pos = -1 * sizeof (stud);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stud, sizeof (student));
                        cout << "\n\n\t Article deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Article no does not exist";
            } else
                cout << "No Articl is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}
//***************************************************************
//    	function to staff deposit
//****************************************************************

void book_staff_deposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;

    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The staff's admission no.";
    cin>>sn;
    fp.open("staff.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*) &stff, sizeof (staff)) && found == 0) {
        if (strcmpi(stff.retadmno(), sn) == 0) {
            found = 1;
            if (stff.rettoken() == 1) {
                while (fp1.read((char*) &bk, sizeof (book)) && flag == 0) {
                    if (strcmpi(bk.retfno(), stff.retstbno()) == 0) {
                        bk.show_file();
                        bk.show_book();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days";
                        cin>>day;
                        if (day > 15) {
                            fine = (day - 15)*1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        stff.resettoken();
                        int pos = -1 * sizeof (stff);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stff, sizeof (staff));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Staff record not exist...";
    getch();
    fp.close();
    fp1.close();
}

void art_staff_deposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;

    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The staffâ€™s admission no.";
    cin>>sn;
    fp.open("staff.dat", ios::in | ios::out);
    fp1.open("article.dat", ios::in | ios::out);
    while (fp.read((char*) &stff, sizeof (staff)) && found == 0) {
        if (strcmpi(stff.retadmno(), sn) == 0) {
            found = 1;
            if (stff.rettoken() == 1) {
                while (fp1.read((char*) &art, sizeof (article)) && flag == 0) {
                    if (strcmpi(art.retfno(), stff.retstbno()) == 0) {
                        art.show_file();
                        art.show_art();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days";
                        cin>>day;
                        if (day > 15) {
                            fine = (day - 15)*1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        stff.resettoken();
                        int pos = -1 * sizeof (stff);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*) &stff, sizeof (staff));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Staff record not exist...";
    getch();
    fp.close();
    fp1.close();
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro() {

    cout << "LIBRARY";
    cout << "MANAGEMENT";
    cout << "SYSTEM";
    cout << "\n\nMADE BY : Tinashe";
    cout << "\n\nSCHOOL : Karodza";
    getch();
}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu() {
    system("CLEAR");
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.CREATE STAFF RECORD";
    cout << "\n\n\t3.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t4.DISPLAY ALL STAFF RECORD";
    cout << "\n\n\t5.DISPLAY aSPECIFIC STUDENT RECORD ";
    cout << "\n\n\t6.DISPLAY aSPECIFIC STAFF RECORD ";
    cout << "\n\n\t7.DELETE STUDENT RECORD";
    cout << "\n\n\t8.DELETE STAFF RECORD";
    cout << "\n\n\t9.CREATE BOOK ";
    cout << "\n\n\t10.CREATE ARTICLE ";
    cout << "\n\n\t11.DISPLAY ALL BOOKS ";
    cout << "\n\n\t12.DISPLAY ALL ARTICLES ";
    cout << "\n\n\t13.DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t14.DISPLAY SPECIFIC ARTICLE ";
    cout << "\n\n\t15.DELETE BOOK ";
    cout << "\n\n\t16.DELETE ARTICLE ";
    cout << "\n\n\t17.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch (ch2) {
        case 1:
            write_student();
            break;
        case 2:
            write_staff();
            break;
        case 3:
            display_allstudents();
            break;
        case 4:
            display_allstaff();
            break;
        case 5:
        {
            char num[6];
            cout << "\n\n\tPlease Enter The Admission No. ";
            cin>>num;
            display_student(num);
            break;
        }
        case 6:
        {
            char num[6];
            cout << "\n\n\tPlease Enter The Admission No. ";
            cin>>num;
            display_staff(num);
            break;
        }
        case 7:
            delete_student();
            break;
        case 8:
            delete_staff();
            break;
        case 9:
            write_book();
            break;
        case 10:
            write_article();
            break;
        case 11:
            display_allbooks();
            return;
        case 12:
            display_allarticle();
            break;
        case 13:
        {
            char num[6];
            cout << "\n\n\tPlease Enter The book No. ";
            cin>>num;
            display_spbook(num);
            break;
        }
        case 14:
        {
            char num[6];
            cout << "\n\n\tPlease Enter The article No. ";
            cin>>num;
            display_sparticle(num);
            break;
        }
        case 15:
            delete_book();
            break;
        case 16:
            delete_book();
            break;
        case 17:
            intro();
            break;
        default:cout << "\a";
    }
    admin_menu();
}

int main(int argc, char** argv) {
    char ch;
    int cho;
    intro();
    cout << "\n\n\n\tMAIN MENU";
    cout << "\n\nAre your a staff member our student....1=>STAFF AND 2=>STUDENT\n";
    cin>>cho;
    if (cho == 1) {
        do {
            cout << "\n\n\t01. BOOK ISSUE";
            cout << "\n\n\t02. ARTICLE ISSUE";
            cout << "\n\n\t03. BOOK DEPOSIT";
            cout << "\n\n\t04. ARTICLE DEPOSIT";
            cout << "\n\n\t05. ADMIN MENU";
            cout << "\n\n\tPlease Select Your Option (1-4) ";
            ch = getche();
            switch (ch) {
                case '1':
                    book_staff_issue();
                    break;
                case '2':
                    article_staff_issue();
                    break;
                case '3':
                    book_staff_deposit();
                    break;
                case '4':
                    art_staff_deposit();
                    break;
                case '5':
                    admin_menu();
                    break;
                case '6':
                default:
                    cout << "\a";
            }
        } while (ch != '6');
        return 0;
    } else if (cho == 2) {
        do {
            cout << "\n\n\t01. BOOK ISSUE";
            cout << "\n\n\t02. ARTICLE ISSUE";
            cout << "\n\n\t03. BOOK DEPOSIT";
            cout << "\n\n\t04. ARTICLE DEPOSIT";
            cout << "\n\n\tPlease Select Your Option (1-4) ";
            ch = getche();
            switch (ch) {
                case '1':
                    book_student_issue();
                    break;
                case '2':
                    article_student_issue();
                    break;
                case '3':
                    book_student_deposit();
                    break;
                case '4':
                    article_student_deposit();
                    break;
                case '5':
                default:
                    cout << "\a";
            }
        } while (ch != '5');

    }

    return 0;
}

