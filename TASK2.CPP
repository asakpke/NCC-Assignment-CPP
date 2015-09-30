// Task 2: Class, Sorting, Data structure, Exception handling
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include <graphics.h>
#include <stdio.h>
#include <process.h>
//class cls;
template <class t_el> // a class template
class set {
private:
	t_el e[50];
public:
	int max;
	char set_name[20];
set() { max = 0; }
void insert( int i ) { e[max++] = i; }
	void union_stu( set * );
	void intersection_stu( set * );
	void diff_stu( set * );
	void disp_stu();
	void sort();
	void q_sort( int, int );
	void swap( int &, int & );
};
set<int> c1, c2, non;
struct student {
	char name[20];
	int rn;	//roll no
	char cls[10];
	char co1; //course 1
	char co2;
};
class cls {
private:
	int rec_no;
public:
	student st[30];
cls() { rec_no = 0; }
	void insert();
	void p();
} bs;
void pak() { //press any key
	cout << "\n\n[Press any key to continue]";
}
void gc() {
	getch();
}
int left, top, right, bottom;
int szopt = 8;
char op[][50] = {	"1. Add New Student", "2. Show Student in course"
	,"3. List of Student not taking any course", "4. Simple Sort List"
	,"5. Quick Sort List", "6. Show Student Record"
	,"7. Show Students course lists", "8. Exit"};
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
	outtextxy( left-50, top-20, "Task 2: Class, Sorting, Data structure, "
		"Exception handling");
	rectangle(left,top,right,bottom);
	for( int l=1; l <= szopt;  l++ )
		d_op(l, 0 ,CYAN);
}
void main() {
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
	right = getmaxx() / 4 + 300;
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
				char add_stu;
				do {
					bs.insert();
					cout << "\nAdd more (y/n): ";
					add_stu = getch();
				} while( add_stu != 'n' );
				break;
			case 2:
				cout << endl;
				c1.disp_stu();
				c2.disp_stu();
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
				cout << "\n\nSimple Sorted values"
					<< "\n--------------------\n";
				c1.disp_stu();
				c2.disp_stu();
				non.disp_stu();
				pak(); gc();
				break;
			case 5:
				c1.q_sort( 1, c1.max );
				c2.q_sort( 1, c2.max );
				non.q_sort( 1, non.max );
				cout << "\n\nQuick Sorted values"
					<< "\n-------------------\n";
				c1.disp_stu();
				c2.disp_stu();
				non.disp_stu();
				pak(); gc();
				break;
			case 6:
				bs.p(); pak(); gc();
				break;
			case 7:
				cout << endl;
				c1.disp_stu();
				c2.disp_stu();
				non.disp_stu();
				cout << "\n\nStudents course lists taking;";
				c1.diff_stu( &c2 );
				c1.union_stu( &c2 );
				c1.intersection_stu( &c2 );
				pak(); gc();
				break;
			case 8: exit(0); break;
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
template <class t_el>  // a class template for class function
void set<t_el>::union_stu( set<t_el> *set2) {
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
	cout << "\n2. CO101 or CO102 or both " << "\t= \t{ ";
	for( l=0; l < r; l++ ) {
		cout << bs.st[u[l]].name;
		if( l != r-1 ) cout << ", ";
	}
	if( r == 0 )
		cout << "Non";
	cout << " }";
}
template <class t_el>  // a class template for class function
void set<t_el>::intersection_stu( set<t_el> *set2 ) {
	int i[50];
	int r = 0;
	for( int l = 0; l < max; l++ ) {
		if( set2->max == 0 )
			break;
		for( int il = 0; il < set2->max; il++ )
			if( e[l] == set2->e[il] ) {
				i[r] = e[l];
				r++;
				break;
			}
	}
	cout << "\n3. CO101 and CO102 " << "\t\t= \t{ ";
	if( r==0 ) { cout << "Non }"; return; }
	for( l=0; l < r; l++ ) {
		cout << bs.st[i[l]].name;
		if( l != r-1 )
			cout << ", ";
	}
	cout << " }";
}
template <class t_el>  // a class template for class function
void set<t_el>::diff_stu( set<t_el> *set2 ) {
	char display, disp_non='y';
	cout << "\n1. CO101 but not taking CO102" << "\t= \t{  ";
	for( int l = 0; l < max; l++ ) {
		display = 'y';
		for( int il = 0; il < set2->max; il++ )
			if( e[l] == set2->e[il] )
				display = 'n';
		if( display == 'y' ) {
			cout << bs.st[e[l]].name << ", ";
			disp_non = 'n';
		}
	}
	if( disp_non == 'y' )
		cout << "\b\b Non }";
	else
		cout << "\b\b  }";
}
template <class t_el>  // a class template for class function
void set<t_el>::disp_stu() {
	cout << endl << set_name << " \t\t= \t{ ";
	for( int l=0; l < max; l++ ) {
		cout << bs.st[e[l]].name;
		if( l < max-1 ) cout << ", ";
	}
	if( max == 0 )
		cout << "Non";
	cout << " }";
}
template <class t_el>  // a class template for class function
void set<t_el>::sort(){
//sorting
	int i, j, temp;
	for( i=0; i< max-1; i++ )
		for( j=0; j< max-i-1; j++ )
			if( strcmpi( bs.st[e[j]].name, bs.st[e[j+1]].name ) > 0 )
				{
				temp = e[j];
				e[j] = e[j+1];
				e[j+1] = temp;
				}
}
template <class t_el>  // a class template for class function
void set<t_el>::q_sort( int l, int r ) {
	int l1, r1;
	if( l < r ) {
		l1 = l;
		r1 = r;
		do {
			while( l1 < r &&
					strcmpi( bs.st[e[l1-1]].name, bs.st[e[l-11]].name ) <= 0 )
				l1++;
			while( l < r1 &&
					strcmpi( bs.st[e[r1-1]].name, bs.st[e[l-1]].name ) >= 0 )
				r1--;
			if( l1 < r1 )
				swap( e[l1-1], e[r1-1] );
		} while( l1 < r1 );
		swap( e[l-1], e[r1-1] );
		q_sort( l, r1-1 );
		q_sort( r1+1, r );
	}
}
void set<t_el>::swap( int &a, int &b ) {
	int t = a;
	a = b;
	b = t;
}
// cls function
void cls::insert() {
	if( rec_no == 30 ) {
		cout << "\n\n\tStudent Array is full";
		getch();
		return;
	}
	char c='n';
	cout << "\n\n\tEnter Student Information"
		"\n\t\tName: ";	cin >> st[rec_no].name;
	do {
		for( int l=0; l < rec_no; l++ ) {
			c = 'n';
			if( strcmpi( st[l].name, st[rec_no].name ) == 0 ) {
				c = 'y';
				cout << "\nStudent with name \'" << st[rec_no].name
					<< "\' already exists.\nEnter new value: ";
				cin >> st[rec_no].name;
				break;
			}
		}
	} while( c == 'y' );
	cout << "\t\tRoll no: "; cin >> st[rec_no].rn;
	cout << "\t\tClass: "; cin >> st[rec_no].cls;
	cout << "\t\tAdmission in CO101 (y/n): "; c = getche();
	st[rec_no].co1 = c;
	if( c != 'n' ) {
		c1.insert( rec_no );
		st[rec_no].co1 = 'y';
	}
	else
		st[rec_no].co1 = 'n';
	char ct;
	cout << "\n\t\tAdmission in CO102 (y/n): "; ct = getche();
	if( ct != 'n' ) {
		c2.insert( rec_no );
		st[rec_no].co2 = 'y';
	}
	else
		st[rec_no].co2 = 'n';
	if( c == 'n' && ct == 'n' )
		non.insert( rec_no );
	rec_no++;
}
void cls::p()
{
	if( rec_no == 0 ) {
		cout << "\n\nNo Student Record";
		return;
	}
	cout << "\n\n\t\tStudent Details"
		  "\n\tName\tRoll#.\tClass\tCo101\tCo102"
		  "\n\t-------------------------------------";
	for( int lv=0; lv < rec_no; lv++ )
		cout << "\n\t" << st[lv].name << '\t'
			<< st[lv].rn << "\t" << st[lv].cls << '\t' << st[lv].co1
			<< '\t' << st[lv].co2;
	}