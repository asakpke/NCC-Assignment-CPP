// Task 3-B: Lint Processing, Class, Inheritance, Polymorphism
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include <graphics.h>
#include <stdio.h>
#include <process.h>
class student;
struct set_el { // set_elements
	student *stu_link; // for storing address of students
	set_el *next;
};
class set {
private:
	set_el *first_el;
	set_el *last_el;
	int max;
public:
	char set_name[20];
set() { max = 0; first_el = last_el = NULL;}
void insert( student *);
void union_stu( set * );
void intersection_stu( set * );
void diff_stu( set * );
void disp_stu();
void sort();
} c1, c2, non;
class person { // Generic Class
public:
	char name[20];
	person *next;
virtual void display() { // Virtual function for Polymorphism
	cout << "\n\t" << name;
}
};
class student : public person { // Class Inheritance
public:
	int rn;	//roll no
	char cls[10];
	char co1; //course 1
	char co2;
virtual void display() { // Virtural function of child class
	person::display();
	cout << '\t' << rn << "\t" << cls << '\t' << co1
		<< '\t' << co2;
}
};
class cls {
private:
	student *first_stu;
	student *last_stu;
public:
cls() { first_stu = last_stu = NULL; }
void insert();
void p();
} bs;
set s[10];
int sn=0;//set no.
void pak() { //press any key
	cout << "\n\n[Press any key to continue]";
}
void gc() {
	getch();
}
int left, top, right, bottom;
int szopt = 9;
char op[][60] = {	"1. Add New Student", "2. Show Student in courses",
		"3. List of Student not taking any course", "4. Sort List",
		"5. Show Student Record",
		"6. Student list taking CO101 but not taking CO102",
		"7. Student list taking both CO101 and CO102",
		"8. Student list  taking either CO101, CO102 or both",
		"9. Exit"};
void d_op(int o, int dir, int col=RED, int x=0, int y=0)
{
	setcolor(CYAN);
	switch( dir ) {
	case 1:
		outtextxy( left+5, top+5+((o-1-1)*15), op[o-1-1]);
		setcolor(col);
		outtextxy( left+5, top+5+((o-1)*15), op[o-1]);
		break;
	case -1:
		outtextxy( left+5, top+5+((o-1+1)*15), op[o-1+1]);
		setcolor(col);
		outtextxy( left+5, top+5+((o-1)*15), op[o-1]);
		break;
	case 0:
		setcolor(col);
		outtextxy( left+5, top+5+((o-1)*15), op[o-1]);
		break;
	}
	setcolor(CYAN);
}
void mainmenu() {
	setcolor(GREEN);
	outtextxy( left-50, top-20, "Task 3-B: Lint Processing, Class, "
		"Inheritance, Polymorphism");
	rectangle(left,top,right,bottom);
	for( int l=1; l <= szopt;  l++ )
		d_op(l, 0 ,CYAN);
}
void main()
{
	strcpy( c1.set_name, "CO101's Student" );
	strcpy( c2.set_name, "CO102's Student" );
	strcpy( non.set_name, "Not taking Course" );
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "..\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}
	left = getmaxx() / 4 - 50;
	top = getmaxy() / 4 - 50;
	right = getmaxx() / 4 + 400;
	bottom = getmaxy() / 4 + 100;
	int selopt = 1;
	mainmenu();
	d_op(1, 0);
	char cursor;
	do {
		cursor = getch();
		switch( cursor )
		{
		case 80://B
			if( selopt < szopt ) {
				selopt++;
				d_op(selopt, 1);
			}
			break;
		case 72://up
			if( selopt > 1 ) {
				selopt--;
				d_op(selopt, -1);
			}
			break;
		case 13:
			cleardevice();
			gotoxy( 1, 1 );
			switch(selopt)
			{
			case 1: //add new student
				bs.insert();
				break;
			case 2:
				cout << endl;
				c1.disp_stu();
				cout << endl;
				c2.disp_stu();
				cout << endl;
				non.disp_stu();
				pak(); gc();
				break;
			case 3:
				cout << endl;
				non.disp_stu();
				pak(); gc();
				break;
			case 4:
				c1.sort();
				c2.sort();
				non.sort();
				cout << "\n\nSorted values"
					<< "\n--------------------\n";
				c1.disp_stu();
				c2.disp_stu();
				non.disp_stu();
				pak(); gc();
				break;
			case 5:
				bs.p(); pak(); gc();
				break;
			case 6:
				cout << endl;
				c1.disp_stu();
				cout << endl;
				c2.disp_stu();
				cout << endl;
				c1.diff_stu( &c2 );
				pak(); gc();
				break;
			case 7:
				cout << endl;
				c1.disp_stu();
				cout << endl;
				c2.disp_stu();
				cout << endl;
				c1.union_stu( &c2 );
				pak(); gc();
				break;
			case 8:
				cout << endl;
				c1.disp_stu();
				cout << endl;
				c2.disp_stu();
				cout << endl;
				c1.intersection_stu( &c2 );
				pak(); gc();
				break;
			case 9:
				exit(0);
				break;
			default:
				cout << "\n\nWrong option ";
				pak(); gc();
				break;
			}
			cleardevice();
			mainmenu();
			d_op(selopt, 0);
			break;
		default:
			break;
		}
	} while( cursor != 27 );
	closegraph();
}// end main
//set function
void set::insert( student *new_stu )
{
	set_el *new_el = new set_el;
	new_el->stu_link = new_stu;
	new_el->next = NULL;
	if( first_el == NULL )
		first_el = new_el;
	else
		last_el->next = new_el;
	last_el = new_el;
	max++;
}
void set::disp_stu() {
	set_el *current_el = first_el;
	cout << "\nStudent of "<< set_name << endl;
	for( int l=0; l < max; l++ ) {
		cout << '\t' << current_el->stu_link->name << endl;
		current_el = current_el->next;
	}
}
void set::union_stu( set *set2) {
	char m;
	int l;
	cout << "\n\nStudents course lists taking CO101 or CO102 or both\n" ;
	set_el *t = first_el;
	for( l=0; l < max; l++ ) {
		cout << '\t' << t->stu_link->name << endl;
		t = t->next;
	}
	int r = max;
	set_el *s1, *s2=set2->first_el;
	for( l=0; l < set2->max; l++ ) {
		m = 'f';
		s1 = first_el;
		for( int il=0; il < max; il++ ) {
			if( strcmpi(s2->stu_link->name, s1->stu_link->name) == 0 ) {
				m = 't';
				break;
			}
			s1 = s1->next;
		}
		if( m == 'f' )
			cout << '\t' << s2->stu_link->name << endl;
		s2 = s2->next;
	}
}
void set::intersection_stu( set *set2 ) {
	int r = 0;
	set_el *s1=first_el, *s2;
	cout << "\n\nStudents course lists taking CO101 and CO102\n";
	for( int l = 0; l < max; l++ ) {
		s2 = set2->first_el;
		for( int il = 0; il < 5; il++ ) {
			if( strcmpi( s1->stu_link->name, s2->stu_link->name ) == 0 ) {
				cout << '\t' << s1->stu_link->name << endl;
				r++;
				break;
			}
			s2 = s2->next;
		}
		s1 = s1->next;
	}
}
void set::diff_stu( set *set2 )
{
	char display, disp_non='y';
	cout << "\n\nStudents course lists taking CO101 but not taking CO102\n";
	set_el *s1=first_el, *s2;
	for( int l = 0; l < max; l++ ) {
		display = 'y';
		s2 = set2->first_el;
		for( int il = 0; il < set2->max; il++ ) {
			if( strcmpi( s1->stu_link->name, s2->stu_link->name ) == 0 )
				display = 'n';
			s2 = s2->next;
		}
		if( display == 'y' ) {
			cout << '\t' << s1->stu_link->name << endl;
			disp_non = 'n';
		}
		s1 = s1->next;
	}
}
void set::sort(){
// linked list sorting
	set_el *current, *next;
	for( int i=0; i< max-1; i++ )
	{
		current = first_el;
		for( int j=0; j < max-i-1; j++ )
		{
			next = current->next;
			if( strcmpi( current->stu_link->name, next->stu_link->name ) > 0 )
			{
				student *temp = current->stu_link;
				current->stu_link = next->stu_link;
				next->stu_link = temp;
			}
		current = current->next;
		}
	}
}
// cls function
void cls::insert() {
	char cho;
	do
	{
		student *new_stu = new student;
		cout << "\n\n\tEnter Student Information"
			"\n\t\tName: ";	cin >> new_stu->name;
		cout << "\t\tRoll no: "; cin >> new_stu->rn;
		cout << "\t\tClass: "; cin >> new_stu->cls;
		char c;
		cout << "\t\tAdmission in CO101 (y/n): "; c = getche();
		if( c != 'n' ) {
			c1.insert( new_stu );
			new_stu->co1 = 'y';
		}
		else
			new_stu->co1 = 'n';
		char ct;
		cout << "\n\t\tAdmission in CO102 (y/n): "; ct = getche();
		if( ct != 'n' ) {
			c2.insert( new_stu );
			new_stu->co2 = 'y';
		}
		else
			new_stu->co2 = 'n';
		if( c == 'n' && ct == 'n' )
			non.insert( new_stu );
		new_stu->next = NULL;
		if( first_stu == NULL )
			first_stu = new_stu;
		else
			last_stu->next = new_stu;
		last_stu = new_stu;
		cout << "\nAdd more [Press enter for yes] (y/n): "; cho = getche();
	} while( cho != 'n' );
}
void cls::p()
{
	person *disp_stu = first_stu;//Important note: Here we declare a pointer
	// of type person class but assign a first pointer of student class that
	// is child of person class. So that Polymorphism can be possible for us.
		cout << "\n\n\t\tStudent Details";
	 cout << "\n\tName\tRoll#.\tClass\tCo101\tCo102"
		  "\n\t-------------------------------------";
	while( disp_stu != NULL )
	{
		disp_stu->display();
		disp_stu = disp_stu->next;
	}
}
