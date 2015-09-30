// Task 1: Array manipulations, Class, Exception handling, Generic Class
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include <graphics.h>
#include <stdio.h>
#include <process.h>
template <class t_el> // a class template
class set {
private:
	t_el e[50]; // class data
	int max;
public:
	char set_name[20];
	void input(); // class functions
	void Union( set *set2);
	void intersection( set *set2 );
	void diff( set *set2 );
	void memb( set *set2 );
	void disp();
}; // cls end
set<int>  s[10];//use of template
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
char op[][30] = { "1. Add New Set", "2. Display All Sets"
	, "3. Perform Set Funcitons", "0. Exit" };
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
	outtextxy( left-50, top-20, "Task 1: Array manipulations, Class, Exception"
		" handling, Generic Class");
	rectangle(left,top,right,bottom);
	for( int l=1; l <= szopt;  l++ )
		d_op(l, 0 ,CYAN);
}
void main()
	{
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
				char s1[20], s2[20];// for set1 & set2 name input
				int i1=-1, i2=-1;//for if set1 & set2 name fount in set array
				disp();
				if( sn < 2 ) {//Exception Handling: two sets required
					cout << "\n\nThere should be at least two sets";
					pak();
					gc();
					break;
				}
				cout << "\nEnter name for set # 1: "; cin >> s1;
				int l;
				for( l=0; l < sn; l++ )
					if( strcmpi( s[l].set_name, s1 ) == 0 ) {
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
					if( strcmpi( s[l].set_name, s2 ) == 0 ) {
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
					s[i1].memb( &s[i2] );
					s[i1].diff( &s[i2] );
					pak();
				}
				getch();
				break;
			case 4: exit(0); break;
			default:
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
}
// set class functions
template <class t_el>  // a class template for class function
void set<t_el>::input() {
	cout << "\nEnter set name: "; cin >> set_name;
	int l;
	for( l=0; l < sn; l++ ) {//Exception Handling: set name should not repeat
		if( strcmpi( set_name, s[l].set_name ) == 0 ) {
			cout << "\nSet with this name already exists. Enter other"
				" set name: ";
			cin >> set_name;
			l = -1;
		}
	}
	cout << "How many elements would be in a set? "; cin >> max;
	while( max < 1 || max > 50 ) {
		cout << "\nEnter value b/w 1-50: "; cin >> max; }
	for( l=0; l < max; l++ ) {
		cout << "Enter value for element # " << l+1 << " = ";
		cin >> e[l];
		for( int il=l-1; il >= 0; il-- )
			if( e[l] == e[il] ) {//Exception Handling: set value should not repeat
				cout << "\nTry new value. This value already exists in set at value # " << il+1 << endl;
				l--;
			}
	}
}
template <class t_el>// a class template for class function
void set<t_el>::Union( set<t_el> *set2) {
	int u[100];
	char m;
	int l;
	for( l=0; l < max; l++ ) u[l] = e[l];
	int r = max;
	for( l=0; l < set2->max; l++ ) {
		m = 'f';
		for( int il=0; il < max; il++ )
			if( set2->e[l] == e[il] ) {
				m = 't';
				break;
			}
			if( m == 'f' ) {
				u[r] = set2->e[l];
				r++;
			}
		}
		cout << "\nUnion (" << set_name << " U " << set2->set_name
			<< ") \t\t= { ";
		for( l=0; l < r; l++ ) {
			cout << u[l];
			if( l != r-1 ) cout << ", ";
		}
		cout << " }";
	}
template <class t_el>// a class template for class function
void set<t_el>::intersection( set<t_el> *set2 ) {
	int i[50];
	int r = 0;
	for( int l = 0; l < max; l++ )
		for( int il = 0; il < 5; il++ )
			if( e[l] == set2->e[il] ) {
				i[r] = e[l];
				r++;
				break;
			}
	cout << "\nIntersection (" << set_name << " ^ " << set2->set_name
		<<") \t= { ";
	if( r==0 ) { cout << "Non }"; return; }
	for( l=0; l < r; l++ ) {
		cout << i[l];
		if( l != r-1 )
			cout << ", ";
	}
	cout << " }";
}
template <class t_el>// a class template for class function
void set<t_el>::diff( set<t_el> *set2 ) {
	char display, disp_non='y';
	cout << "\nDifference (" << set_name << " - " << set2->set_name
		<< ") \t= {  ";
	for( int l = 0; l < max; l++ ) {
		display = 'y';
		for( int il = 0; il < set2->max; il++ )
			if( e[l] == set2->e[il] )
				display = 'n';
		if( display == 'y' ) {
			cout << e[l] << ", ";
			disp_non = 'n';
		}
	}
	if( disp_non == 'y' )
		cout << "\b\b non }";
	else
		cout << "\b\b  }";
}
template <class t_el>// a class template for class function
void set<t_el>::memb( set<t_el> *set2 ) {
	char ms='y'; //membership;
	char m; // member
	cout << "\nMembership \t\t= ";
	for( int l = 0; l < set2->max; l++ ) {
		m = 'n';
		for( int il = 0; il < max; il++ )
			if( set2->e[l] == e[il] )
				m = 'y';
		if( m != 'y' ) ms = 'n';
	}
	cout << "set " << set2->set_name << " is ";
	if( ms != 'y' )
		cout << "not ";
	cout << "a member of set " << set_name;
}
template <class t_el>// a class template for class function
void set<t_el>::disp() {
	cout << endl << set_name << " \t\t\t= { ";
	for( int l=0; l < max; l++ ) {
		cout << e[l];
		if( l < max-1 ) cout << ", ";
	}
	cout << " }";
}