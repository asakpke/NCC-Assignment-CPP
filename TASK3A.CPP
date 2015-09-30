//	Task 3-A: Lint Processing, Class, Inheritance, Polymorphism
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<alloc.h>
#include <graphics.h>
#include <stdio.h>
#include <process.h>
template <class t_el> // a class template
struct element {
	t_el e;
	element *next;
};
class set {
private:
	set *next;
	element<int> *first;
	element<int> *last;
	long max;
public:
set() {
	first = last = NULL;
}
	char set_name[20];
	void input(); // class functions
	void Union( set * );
	void intersection( set * );
	void diff( set * );
	void memb( set * );
	void disp();
}; // cls end
set s[10];
int sn=0;//set no.
void disp() {
	if( sn == 0 ) {
		cout << "\nThere is no set";
		return;
	}
	cout << "\nSets";
	for( int l=0; l < sn; l++ )
		s[l].disp();
}
void pak() { //press any key
	cout << "\n\n[Press any key to continue]";
}
void gc() {
	getch();
}
int left, top, right, bottom;
int szopt = 4;
char op[][25] = {	"1. Add New Set", "2. Display All Sets"
	,"3. Perform Set Funcitons", "4. Exit"};
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
	outtextxy( left-50, top-20, "Task 3-A: Lint Processing, Class, "
		"Inheritance, Polymorphism" );
	rectangle(left,top,right,bottom);
	for( int l=1; l <= szopt;  l++ )
		d_op(l, 0 ,CYAN);
}
void main()
{
//
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
	right = getmaxx() / 4 + 200;
	bottom = getmaxy() / 4 + 50;
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
			case 1: //add new set
				if( sn != 10 ) //Exception Handling: 10 element array
				{
					char new_set_choice;
					do
					{
						s[sn].input();
						sn++;
						cout << "\nDo you want to add more set (y/n): ";
						new_set_choice = getch();
					}
					while( new_set_choice != 'n' );
				}
				else//Exception Handling Message
				{
					cout << "\n\nOnly ten sets are allowed!";
					pak(); gc();
				}
				break;
			case 2://display all sets
				disp();
				getch();
				break;
			case 3://perform set functions
				char s1[20], s2[20];
				int i1=-1, i2=-1;
				disp();
				if( sn < 2 ) {
					cout << "\nThere should be at least two sets";
					pak();
					gc();
					break;
				}
				cout << "\nEnter name for set # 1: "; cin >> s1;
				int l;
				for( l=0; l < sn; l++ )
					if( strcmp( s[l].set_name, s1 ) == 0 ) {
						i1 = l;
						break;
					}
				if( i1 == -1 ) {
					cout << "\nSet not found";
					pak(); gc();
					break;
				}
				cout << "Enter name for set # 2: "; cin >> s2;
				for( l=0; l < sn; l++ ) {
					if( strcmp( s[l].set_name, s2 ) == 0 ) {
						i2 = l;
						break;
					}
				}
				if( i2 == -1 ) {
					cout << "\nSet not found";
					pak(); gc();
					break;
				}
				if( i1 != -1 && i2 != -1 ) {
					s[i1].disp();
					s[i2].disp();
					s[i1].Union( &s[i2] );
					s[i1].intersection( &s[i2] );
					s[i1].diff( &s[i2] );
					s[i1].memb( &s[i2] );
					pak();
				}
				getch();
				break;
			case 4:
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
//set class functions
void set::input()
{
	cout << "\nEnter set name: "; cin >> set_name;
	cout << "How many elements would be in a set? "; cin >> max;
	while( max < 1 )
	{
		cout << "\nEnter value > 1: ";
		cin >> max;
	}
	element<int> *newp;
	for( int l=0; l < max; l++ )
	{
		newp = new element<int>;
		cout << "Enter value # " << l+1 << " = ";
		cin >> newp->e;
		element<int> *temp=first;
		while( temp != NULL )
		{//Exception Handling: set value should not repeat
			if( temp->e == newp->e  )
			{
				cout << "\nTry new value. This value already exists :";
				cin >> newp->e;
				temp = first;
				continue;
			}
			temp = temp->next;
		}
		newp->next = NULL;
		if( first == NULL )
			first = last = newp;
		else
		{
			last->next = newp;
			last = newp;
		}
	}
}
void set::Union( set *set2) {
	char m;
	int l;
	cout << "\nUnion (" << set_name << " U " << set2->set_name
			<< ") \t\t= { ";
	element<int> *temp = first;
	for( l=0; l < max; l++ ) {
		cout << temp->e << ", ";
		temp = temp->next;
	}
	int r = max;
	element<int> *s1, *s2=set2->first;
	for( l=0; l < set2->max; l++ ) {
		m = 'f';
		s1 = first;
		for( int il=0; il < max; il++ ) {
			if( s2->e == s1->e ) {
				m = 't';
				break;
			}
			s1 = s1->next;
		}
		if( m == 'f' )
			cout << s2->e << ", ";
	s2 = s2->next;
	}
	cout << "\b\b }";
}
void set::intersection( set *set2 ) {
	int i[50];
	int r = 0;
	element<int> *s1=first, *s2;
	cout << "\nIntersection (" << set_name << " ^ " << set2->set_name
		<<") \t= { ";
	for( int l = 0; l < max; l++ ) {
		s2 = set2->first;
		for( int il = 0; il < 5; il++ ) {
			if( s1->e == s2->e ) {
				cout << s1->e << ", ";
				r++;
				break;
			}
			s2 = s2->next;
		}
		s1 = s1->next;
	}
	if( r==0 ) { cout << "Non }"; return; }
	cout << "\b\b }";
}
void set::diff( set *set2 ) {
	char display, disp_non='y';
	cout << "\nDifference (" << set_name << " - " << set2->set_name
		<< ") \t= {  ";
	element<int> *s1=first, *s2;
	for( int l = 0; l < max; l++ ) {
		display = 'y';
		s2 = set2->first;
		for( int il = 0; il < set2->max; il++ ) {
			if( s1->e == s2->e )
				display = 'n';
			s2 = s2->next;
		}
		if( display == 'y' ) {
			cout << s1->e << ", ";
			disp_non = 'n';
		}
		s1 = s1->next;
	}
	if( disp_non == 'y' )
		cout << "\b\b Non }";
	else
		cout << "\b\b  }";
}
void set::memb( set *set2 ) {
	char ms='y'; //membership;
	char m; // member
	cout << "\nMembership \t\t= ";
	element<int> *s1, *s2=set2->first;
	for( int l = 0; l < set2->max; l++ ) {
		m = 'n';
		s1 = first;
		for( int il = 0; il < max; il++ ) {
			if( s2->e == s1->e )
				m = 'y';
			s1 = s1->next;
		}
		if( m != 'y' ) ms = 'n';
		s2 = s2->next;
	}
	cout << "set " << set2->set_name << " is ";
	if( ms != 'y' )
		cout << "not ";
	cout << "a member of set " << set_name;
}
void set::disp() {
	cout << endl << set_name << " \t\t\t= { ";
	element<int> *temp = first;
	for( int l=0; l < max; l++ ) {
		cout << temp->e;
		temp = temp->next;
		if( l < max-1 ) cout << ", ";
	}
	cout << " }";
}