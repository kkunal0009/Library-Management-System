#include <iostream>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include<queue>
#include<stdio.h>
#include<stdlib.h>



using namespace std;
#include<iomanip>
using std::setw;

long getid(string s);
void subj();
/*physics maths cs english other*/
class book{
	public:
	long bid;
	string name;
	string author;
	int issue;
	int nobook;
	int subject;
	book *nxt;
	book *pre;
	book()
	{		
		bid = 0;
		name = "NULL";
		author ="NULL";
		issue = 0;
		nobook=0;
		subject = 0;
	}
	book(string nname,string nauthor,int s)
	{
		bid = getid(nname);
		name = nname;
		author = nauthor;
		issue = 0;
		subject = s;
		pre = nullptr;
	}
	book(book *bk)
	{
		bid = bk->bid;
		name = bk->name;
		author = bk->author;
		nxt = nullptr;
		issue = 0;
		nobook = bk->nobook;
		subject = bk->subject;
		pre = bk->pre;
	}
	void inputbook()
	{
		cout<<"\n\t\tEnter book name\n\t\t";
		fflush(stdin);
		getline(cin,name);
		fflush(stdin);
		cout<<"\t\tenter author name\n\t\t";
		getline(cin,author);
		cout<<"\t\tEnter subject\n\t\t";
		cin>>subject;
		bid = getid(name);
		pre = nullptr;

	}
	
	void outputbook()
	{
		cout << setw(9) << bid << setw(30) << name << setw(30) << author << setw(14) << nobook<<setw(15)<<subject;
	
		if(issue)
		cout<<setw(18)<<"Yes\n";
		else
		cout<<setw(18)<<"No\n";
	}
};
book *bk[5][5] = {nullptr};
void issuebook(long sid,string bookname,string author,int sub);

class student{
	public:
		
	long id;
	string name;
	string batch;
	int n;
	book *biss;
	
		student()
		{
			id=0;
			name = "NULL";
			batch = "NULL";
			n=0;
			biss = nullptr;
		}
		student(long nid,string nname,string nbatch,int bn=0,book *nbk = nullptr)
		{
			id = nid;
			name = nname;
			batch = nbatch;
			biss = nbk;
			n=bn;
		}
		
		void inputstud()
		{
			int bi,sub;
			string bname,autname;
			cout<<"\n\t\tenter student id\n\t\t";
			cin>>id;
			fflush(stdin);
			cout<<"\n\t\tEnter name of student\n\t\t";
			getline(cin,name);
			fflush(stdin);
			cout<<"\n\t\tEnter batch of student\n\t\t";
			getline(cin,batch);
			cout<<"\n\t\tEnter no of books issued\n\t\t";
			cin>>n;
			
		}
		void outputstud()
		{
			cout<<"\t\tStudent id : \n\t\t";
			cout<<id<<endl;
			cout<<"\t\tStudent name :\n\t\t";
			cout<<name<<endl;
			cout<<"\t\tBatch :\n\t\t";
			cout<<batch<<endl;
			cout<<"\t\tNo of books issued :\n\t\t";
			cout<<n<<endl;
			book *temp = biss;
			int z=0;
			cout<<"\n";
			while(temp != nullptr)
			{
				z++;
				cout<<"\t\tBook No."<<z<<endl;
				cout<<"\t\tName : "<<temp->name<<endl;
				cout<<"\t\tAuthor name :"<<temp->author<<endl;
				cout<<"\t\tSubject code : "<<temp->subject<<"\n\n";
				temp = temp->nxt;
			}
		}
		
};

class state {
public:
    long id;
    struct state *left, *right;
    student *next;
    state()
    {
    	
        left = nullptr;
        right = nullptr;
        next = nullptr;
	}
    state(int new_id) {
        id = new_id;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }
};



state *b = nullptr;


// Functions for student :
state* insertnode(long ky)
{
	
	state *nxt = new state(ky);
	state *r = b;
	state *p = r;
	if(r==nullptr)
	{
		b = nxt;
	
		return nxt;
	}
	while(r!=nullptr)
	{
		p=r;
		if(r->id >ky)
		{
			r=r->left;
		}
		else
		{
			r=r->right;
		}
		
	}
	if(p->id > ky)
	{
		p->left = nxt;
	}
	else
	{
		p->right = nxt;
	}
	return nxt;
}
state* searchnode(long ky,state *bs = b)
{
	state *r = bs;
	int f = 0;
	if(r!= nullptr)
	{
		if(r->id > ky)
		{
			return searchnode(ky,r->left);
		}
		else if(r->id < ky)
		{
			return searchnode(ky,r->right);
		}
		else
		{
			return r;	
		}
		
	}	
}

state* insertstud()
{
	system("cls");
	cout<<"\n\n\t\t\t**** Inserting new student ****\n";
	subj();
	student *s = new student;
	s->inputstud();
	state* nw = insertnode(s->id);
	
	nw->next = s;
	int z = s->n;
	if(z>0)
	{
		string bname,autname;
		int sub;
		for(int i=0;i< z;++i)
		{
			cout<<"\n\t\t\tenter book name\n\t\t";
			fflush(stdin);
			getline(cin,bname);
			fflush(stdin);
			cout<<"\t\t\tenter author name\n\t\t";
			getline(cin,autname);
			cout<<"\t\t\tenter subject\n\t\t";
			cin>>sub;
			issuebook(s->id,bname,autname,sub);
		}
	}

	cout<<"\nInserted";
}

state* insertstud(long sid,string name,string batch,int nb)
{
	system("cls");
	cout<<"\n\n\t\t\t**** Inserting new student ****\n";
	subj();
	student *s = new student(sid,name,batch);
	s->n=nb;
	state *nw = insertnode(s->id);
	
	nw->next = s;

	cout<<"\nInserted";
}

void searchstud(long ig)
{
	state* ne = searchnode(ig);
	ne->next->outputstud();
}

void displaystud(state *bs = b)
{
	state *r = bs;
	
	if(r!= nullptr)
	{
		r->next->outputstud();
		displaystud(r->left);
		displaystud(r->right);
	
	}
}

//functions for book :
book* insertbook()
{
	system("cls");
	cout<<"\n\n\t\t\t**** Inserting new Book ****\n";
	subj();
	book *add = new book;
	add->inputbook();
	
	int s ;
	int r = add->subject;
	r = r-1;
	int count = 0;
	
	for(s=0;s<5;++s)
	{
		count = 0;
		book *k = bk[r][s];
		if(k==nullptr)
		{
			count = 0;
		}
		else
		{
			count = k->nobook;
		}
		
		if(count<=5)
		{
			break;
		}
	}
	if(s==5)
	{
		cout<<"no insertion possible";
	}
	
	add->nobook = count+1;
	if(bk[r][s]!= nullptr)
	{
		bk[r][s]->pre = add;
	}
	add->nxt = bk[r][s];
	bk[r][s] = add;	

	cout<<"\n\t\t\tInserted";
}

book* insertbook(string nam,string aut,int sub)
{
	system("cls");
	cout<<"\n\n\t\t\t**** Inserting new Book ****\n";
	subj();
	book *add = new book(nam,aut,sub);
	int s = 0 ;
	int r = add->subject;
	r = r-1;
	
	int count;
	for(s=0;s<=5;++s)
	{
		count = 0;
		book *k = bk[r][s];
		if(k==nullptr)
		{
			count = 0;
		}
		else
		{
			count = k->nobook;
		}
		
		if(count<=5)
		{
			break;
		}
	}
	if(s==5)
	{
		cout<<"no insertion possible";
	}
	add->nobook = count+1;
	
	if(bk[r][s]!= nullptr)
	{
		bk[r][s]->pre = add;
	}
	add->nxt = bk[r][s];
	bk[r][s] = add;		
	
	cout<<add->bid<<endl;
	cout<<"\nInserted";
}

book* searchbook(book *n,string bname,string aname)
{
	long bkd = getid(bname);
	
	book *r = n;
	
	while(r != nullptr)
	{
		if(r->bid == bkd && r->author == aname)
		{
			break;
		}
		r = r->nxt;
	}
	return r;
}

void deletebook()
{
	system("cls");
	cout<<"\n\n\t\t\t**** Deleting book ****\n";
	subj();
	string bname,aname;
	int subno;
	fflush(stdin);
	cout<<"\n\n\t\tenter book name\n\t\t";
	getline(cin,bname);
	fflush(stdin);
	cout<<"\n\t\tenter author name\n\t\t";
	getline(cin,aname);
	cout<<"\n\t\tEnter subject code\n\t\t";
	cin>>subno;
	long bkd = getid(bname);
	
	if(subno>5)
	{
		cout<<"\n\t\tInvalid Subject";
		return;
	}
	int s = 0;
	int r = subno - 1;
	int found = 0;
	
	while(bk[r][s]!=nullptr){
		book *rt = bk[r][s];
		book *p = rt;
	
		while(rt != nullptr)
		{
			if(rt->bid == bkd && rt->author == aname)
			{
				
				if(p==rt)
				{
					bk[r][s] = rt->nxt;
					rt->nxt->pre = nullptr;
					delete rt;
					cout<<"\n\t\tBook Deleted";
					return;
				}
				
				if(rt->nxt != nullptr)
				{
					book *up = rt->nxt;
					up->pre = p;
				}
				p->nxt = rt->nxt;
				delete rt;
				cout<<"\n\t\tBook Deleted";
				return;
			}
			p = rt;
			rt = rt->nxt;	
		}
		++s;
    }
	cout<<"\nBook not found";
}

void showbook()
{
	system("cls");
	cout<< "\t\t\t\t*****  D I S P L A Y  ***** \n";
	subj();
	for(int r=0;r<5;++r)
	{
		cout << "\n\t\t\t\t*****  R A C K  " << r + 1 << " *****\n";
		for(int s=0;s<5;++s)
		{
			cout << "\n\t\t\t\t*****  S H E L F  " << s + 1 << " *****\n";
            cout << "  BOOK ID" << "\t\t\t NAME" << "\t\t\t       AUTHOR" <<"\t\tBOOK NO."<<"\tSUBJECT"<<"\t\tISSSUED\n"<< endl;
			book *rt = bk[r][s];
			
			while(rt!=nullptr)
			{
				rt->outputbook();
				rt = rt->nxt;
				
			}
		
		}
	}
}

//other activity functions:
void issuebook()
{
	long sid;
	int sub;
	system("cls");
	cout<<"\n\n\t\t\t**** Issuing new Book ****\n";
	subj();
	string bookname,author;
	cout<<"\n\t\tStudent id\n\t\t";
	cin>>sid;
	cout<<"\t\tBook name\n\t\t";
	fflush(stdin);
	getline(cin,bookname);
	cout<<"\t\tBook author name\n\t\t";
	fflush(stdin);
	getline(cin,author);
	cout<<"\t\tEnter subject\n\t\t";
	cin>>sub;
	
	int bid = getid(bookname);
	int s;
	int r = sub-1;
	book *fd;
	state *sr;
	
	for(s=0;s<5;++s){
		fd = searchbook(bk[r][s],bookname,author);
		sr = searchnode(sid);
		if(fd!=nullptr)
		{
			break;
		}
	}
	if(fd->issue == 1)
	{
		cout<<"\n\t\tIssued by someone else.";
		return;
	}
	if(fd==nullptr)
	{
		cout<<"\t\tbook not found";
		return;
	}
		fd->issue = 1;
		student *st = sr->next;
		book *nb = new book(fd);
		if(st->biss!=nullptr)
		{
			st->biss->pre = nb;
		}
		nb->nxt = st->biss;
		nb->pre = nullptr;
		st->biss = nb;
		st->n+=1;
		
	cout<<"\n\t\tIssued";
}
void issuebook(long sid,string bookname,string author,int sub)
{
	system("cls");
	cout<<"\n\n\t\t\t**** Issuing new Book ****\n";
	subj();
	int bid = getid(bookname);
	int s;
	int r = sub-1;
	book *fd;
	state *sr;
	for(s=0;s<5;++s){
		fd = searchbook(bk[r][s],bookname,author);
		sr = searchnode(sid);
		if(fd!=nullptr)
		{
			break;
		}
	}
	if(fd==nullptr)
	{
		cout<<"book not found";
		return;
	}
	if(fd->issue == 1)
	{
		cout<<"\n\t\tIssued by someone else.";
		return;
	}
		fd->issue = 1;
		student *st = sr->next;
		book *nb = new book(fd);
		
		if(st->biss!=nullptr)
		{
			st->biss->pre = nb;
		}
		
		nb->nxt = st->biss;
		nb->pre = nullptr;
		st->biss = nb;
	cout<<"\nIssued";
}
void returnbook()
{
	system("cls");
	cout<<"\n\n\t\t\t**** Returning Book ****\n";
	subj();
	long sid;
	int subno;
	string bookname,author;
	cout<<"\n\n\t\tStudent id\n\t\t";
	cin>>sid;
	cout<<"\n\t\tBook name\n\t\t";
	fflush(stdin);
	getline(cin,bookname);
	cout<<"\n\t\tauthor name\n\t\t";
	fflush(stdin);
	getline(cin,author);
	fflush(stdin);
	cout<<"\n\t\tEnter book subject\n\t\t";
	cin>>subno;
	
	if(subno>5)
	{
		cout<<"\n\t\t Invalid subject no";
	}
	
	int bid = getid(bookname);
	int sh = 0;
	int r = subno - 1;
	book *fd;
	while(sh!=5){
		fd = searchbook(bk[r][sh],bookname,author);
		if(fd!=nullptr)
		{
			break;
		}
		++sh;
	}
	if(fd==nullptr)
	{
		cout<<"\n\t\tNo such book";
		return;
	}
	state *s = searchnode(sid);
	
	fd->issue = 0;
	student *st = s->next;
	book *sr = st->biss;
	book *fol = sr;
	
	while(sr!= nullptr)
	{
		if(sr->bid==fd->bid && sr->author==fd->author)
		{
			if(fol==sr)
			{	
				st->biss = sr->nxt;
				if(sr->nxt != nullptr)
				{
					sr->nxt->pre = nullptr;
				}
				delete sr;
				st->n-=1;
				cout<<"\n\t\tReturned\n";
				return;
			}
			fol->nxt = sr->nxt;
			if(sr->nxt != nullptr)
			{
				sr->nxt->pre = fol;
			}
			delete sr;
			st->n-=1;
			cout<<"\n\t\tReturned\n";
			return;
		}
			fol = sr;
			sr = sr->nxt;
	}
	cout<<"\n\t\tNo such book issued\n";
}

void displayissued()
{
	system("cls");
	cout<<"\t\t\t\t***** Issued Books ***** \n\n";
	subj();
	cout << "  BOOK ID" << "\t\t\t NAME" << "\t\t\t       AUTHOR" <<"\t\tBOOK NO."<<"\tSUBJECT"<<"\t\tISSSUED\n"<< endl;
	for(int r=0;r<5;++r)
	{
		for(int s=0;s<5;++s)
		{
			book *rt = bk[r][s];
			while(rt!=nullptr)
			{
				if(rt->issue==1)
				{
					rt->outputbook();
				}
				rt = rt->nxt;
			
			} 
		}
	}
}

//convertion function
int convertc(char ch)
{
	ch=tolower(ch);
	int i=(int)ch;
	return i-96;
}

long getid(string s)
{
	queue<int> idq;
	int n=s.size(),cs=0,id=0;
	for(int i=0;i<n;++i)
	{
		
		if(s[i]==' ')
		{
			idq.push(cs);
			cs=0;
		}
		else
		{
			
			cs+=convertc(s[i]);
			
		}
	}
	idq.push(cs);
    cs=0; 
    stringstream string_stream;
    while (!idq.empty()) {
        // Adding whole que values to string_stream
        string_stream << idq.front();
        idq.pop();
    }
    
    string combining_values = string_stream.str();
    istringstream integer_string_stream(combining_values);
    integer_string_stream >> id;
    return id;
}

//file function
void generateLibdata() {
    ifstream inFile;
    inFile.open("library.txt");
    if (!inFile) {
        cerr << "Unable to open file library.txt";
        exit(1);   // call system to stop
    }

    // Variables that will collect data
    string book_name;
    string author_name;
    string sn;
    int sb;
    while (getline(inFile, book_name)) {
        // converting shelve_str to int
        getline(inFile, author_name);
        getline(inFile, sn);
        sb = stoi(sn);
        insertbook(book_name, author_name,sb);
    }
    inFile.close();
}
void generatestudata()
{
	ifstream inFile;
    inFile.open("student.txt");
    if (!inFile) {
        cerr << "Unable to open file student.txt";
        exit(1);   
    }

    // Variables that will collect data
 	long sid;
 	int n;
	string stsid,stn;
    string sname;
    string sbatch;
    string sbookname;
	string sauthor; 
	string subj;
	int sb;
    while (getline(inFile, stsid)) {
        // converting shelve_str to int
        sid = stoi(stsid);
		getline(inFile, sname);
        getline(inFile, sbatch);
        
        getline(inFile, stn);
        n = stoi(stn);
        
        insertstud(sid,sname,sbatch,n);
        
        for(int i=0;i<n;++i)
        {
        	getline(inFile, sbookname);
            getline(inFile, sauthor);
            getline(inFile, subj);
        	sb = stoi(subj);
            issuebook(sid,sbookname,sauthor,sb);
		}
    }
    inFile.close();
}

//update fns
void updateLibdata() {
    ofstream file;
    file.open("library.txt");
    if (!file) {
        cerr << "Unable to open file library.txt";
        exit(1);   
    }
    int no;
    char ch;
    for(int r=0;r<5;++r)
	{
		for(int s=0;s<5;++s)
		{
			book *rt = bk[r][s];
			
			if(rt==nullptr)
			{
				continue;
			}
			while(rt->nxt != nullptr)
			{
				rt = rt->nxt;
			}
			
			while(rt!=nullptr)
			{
				file<< rt->name<< endl;
				file<< rt->author << endl;
				
				no = rt->subject + 48;
				ch = (char)no;
				file<<ch<<endl;
				
				rt = rt->pre;
			}
		}
	}
	file.close();    
}

//to update student file
void upd(ofstream& fle,state* bs){

	state *r = bs;
	int no;
	char ch;
	string str;
	
	if(r!= nullptr)
	{
		stringstream si,sn;  
		student *st = r->next;
				
  		si << st->id;  
  		si >> str;  
  		
		fle<<str<<endl;
		fle<<st->name<<endl;
		fle<<st->batch<<endl;
		
		sn << st->n;  
  		sn >> str;  
		fle<<str<<endl;
		
		book *rt = st->biss;
		
		if(rt!=nullptr)
		{
			while(rt->nxt != nullptr)
			{
				rt = rt->nxt;
			}
				
			while(rt!=nullptr)
			{
				fle<< rt->name<< endl;
				fle<< rt->author << endl;
					
				no = rt->subject + 48;
				ch = (char)no;
				fle<<ch<<endl;
					
				rt = rt->pre;
			}
		}	
		upd(fle,r->left);
		upd(fle,r->right);
	
	}
}
void updatestudent()
{
	ofstream file;
    file.open("student.txt");
    if (!file) {
        cerr << "Unable to open file library.txt";
        exit(1);   
    }
    upd(file,b);
    file.close();
}

//subject code
void subj()
{
	cout<<"\n\t\t 1->Maths\n\t\t 2->Digital system\n\t\t 3->Physics\n\t\t 4->Computer science\n\t\t 5->Others\n";
}

//choices fn
void choices()
{
	cout<<"\n\t\t\t******* Index ********\n";
	int ch;
	cout<<"\t\tEnter your choice\n";
	cout<<"\t\t1.Display all books\n";
	cout<<"\t\t2.Display all students\n";
	cout<<"\t\t3.Display Issued books\n";
	cout<<"\t\t4.Insert book\n";
	cout<<"\t\t5.Issue book\n";
	cout<<"\t\t6.Return book\n";
	cout<<"\t\t7.Delete book\n";
	cout<<"\t\t8.Insert student\n";
	cout<<"\t\t0.Exit\n\n\t\t";
	cin>>ch;

	switch(ch){
		case 1:{	
					showbook();
					choices();
					break;
				}
		case 2:{	
					system("cls");
					subj();
					displaystud();
					choices();
					break;
				}	
		case 3:{	
					displayissued();
					choices();
					break;
				}
		case 4:{
					insertbook();	
					choices();		
					break;
				}
		case 5:{ 
					issuebook();
					choices();
					break;
				}
		case 6:{
					returnbook();
					choices();
					break;
				}		
		case 7:{
					deletebook();
					choices();
					break;
				}
		case 8:{
					insertstud();
					choices();
					break;
				}
		case 0:{
					return;
				}
			}
}
void welcome();
void lock(){
string access;
    cout << "\t\t\t\tWELCOME TO THE LIBRARY\n\n" << "\t\tTo Exit Press (X)\n" << "\t\tEnter Access Code \n\t\t(default password : root): \n\n\t\t";
    CODE:
    cin >> access;
    cout << "\n";

    if (access=="root"){
        cout << "\t\tAccess Granted" << endl;
    }
    else if (access=="x" || access=="X")
        exit(0);
    else {
        cout << "!! Invalid Access Code !!" << endl;
        goto CODE;
    }
}
void by();
//main function
int main()
{
	welcome();
	system("cls");
	by();
	system("cls");
	lock();
	generateLibdata();
	generatestudata();
	system("cls");
	choices();
	updateLibdata();
	updatestudent();
	
	cout<<"\n\t\t\tThank you";
}

void welcome()
{
	cout<<"\n\n\n";
	cout<<"\t\t\t*            *  *****  *     *****  *****  *    *  *****   \n";
	cout<<"\t\t\t *          *   *      *     *      *   *  **  **  *       \n";
	cout<<"\t\t\t  *   **   *    ****   *     *      *   *  * ** *  ****    \n";
	cout<<"\t\t\t   * *  * *     *      *     *      *   *  *    *  *       \n";
	cout<<"\t\t\t    *    *      *****  ***** *****  *****  *    *  *****   \n";
	
	cout<<"\n\n";
	
	cout<<"\t\t\t\t\t *******  ******\n";
	cout<<"\t\t\t\t\t    *     *    *\n";
	cout<<"\t\t\t\t\t    *     *    *\n";
	cout<<"\t\t\t\t\t    *     *    *\n";
	cout<<"\t\t\t\t\t    *     ******\n";
	
	cout<<"\n\n";
	
	cout<<"\t\t\t*      *  ****   *****      *      *****  *     *  \n";
	cout<<"\t\t\t*      *  *   *  *  *      * *     *  *    *   *   \n";
	cout<<"\t\t\t*      *  ****   **       *****    * *      * *    \n";
	cout<<"\t\t\t*      *  *   *  *  *    *     *   *  *      *     \n";
	cout<<"\t\t\t*****  *  ****   *   *  *       *  *   *     *     \n";	
	
	cout<<"\n\n";
	cout<<"Press Enter\n";
	cin.ignore();
	
}

void by()
{
	cout<<"\n\n\n\t\t\t\t\tPBL Assignment APS\n";
	cout<<"\n\n\n\t\t\t\t\t\tSubmitted by:";
	cout<<"\n\t\t\t\t\t\tManan Chaudhary  (9919103178)";
	cout<<"\n\t\t\t\t\t\tAman Deep Gupta  (9919103179)";
	cout<<"\n\t\t\t\t\t\tSaransh Pateriya (9919103187)";
	cout<<"\n\t\t\t\t\t\tMegha Jain 	  (9919103188)";
	cout<<"\n\t\t\t\t\t\tKunal Mittal 	  (9919103201)";
	
	cout<<"\n\n\t\t\t\tPress Enter To continue";

	cin.ignore();
	
}
