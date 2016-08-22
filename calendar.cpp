#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
using namespace std;


COORD cord{0,0};

void gotoxy(int x,int y)
{
	cord.X = x;
	cord.Y = y;
	SetConsoleCursorPosition((GetStdHandle(STD_OUTPUT_HANDLE)),cord);
}

void setConsoleColors(WORD attribs)
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hconsole,&cbi);
	cbi.wAttributes = attribs;
	SetConsoleScreenBufferInfoEx(hconsole,&cbi);
}

bool isleapyear(int y)
{
	if(y%4 == 0)
	{
		if(y%100 == 0)
		{
			if(y%400 == 0)
			{
				return true;
			}
			else
			return false;
		}
		else
		return true;
	}
	else
	return false;
}

int mon_day[13] = {31,28,31,30,31,30,31,31,30,31,30,31};
int findDay(int d,int m,int y)
{
	int month_days[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
	int days = 0;
	int pre_leap,pre_100,pre_400,div_4,div_100,div_400;
	if(y>=1970)
	{
		days = month_days[m-1]+d-1;
		if(isleapyear(y))
		days += 1;
		pre_leap = y-1-(y-1)%4;
		if(pre_leap<1972)
		{
			div_4 = 0;
		}
		else
		{
			div_4 = (pre_leap-1972)/4+1;
		}
		pre_100 = y-1-(y-1)%100;
		if(pre_100<2000)
		{
			div_100 = 0;
		}
		else
		{
			div_100 = (pre_100-2000)/100+1;
		}
		pre_400 = y-1-(y-1)%400;
		if(pre_400<2000)
		{
			div_400 = 0;
		}
		else
		{
			div_400 = (pre_400-2000)/400+1;
		}
		days += (y-1970)*365+div_4-div_100+div_400;
		return (days%7);
	}
	else
	{
		if(m<=2)
		{
			if(isleapyear(y))
			days = 1;
		}
		days += mon_day[m]-d;
		int md[13] = {0,334,306,275,245,214,184,153,122,92,61,31};
		if(m<12)
		{
			days += md[m];
		}
		int y_;
		y_ = y+1;
		
		if(y_%4 == 0)
		{
			pre_leap = y_;
		}
		else
		{
			pre_leap = y_+(4-y_%4);
		}
		if(pre_leap>1968)
		{
			div_4 = 0;
		}
		else
		{
			div_4 = (1968-pre_leap)/4+1;
		}
		
		if(y_%100 == 0)
		{
			pre_100 = y_;
		}
		else
		{
			pre_100 = y_+(100-y_%100);
		}
		if(pre_100>1900)
		{
			div_100 = 0;
		}
		else
		{
			div_100 = (1900-pre_100)/100+1;
		}
		
		if(y_%400 == 0)
		{
			pre_400 = y_;
		}
		else
		{
			pre_400 = y_+(400-y_%400);
		}
		if(pre_400>1600)
		{
			div_400 = 0;
		}
		else
		{
			div_400 = (1600-pre_400)/400+1;
		}
		
		days += (1970-y_)*365+div_4-div_100+div_400;
		return (6-days%7);
	}
	
}

string dayName[7] = {"Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday"};

void finDay()
{
	system("cls");
	//clscr();
	setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
	gotoxy(25,10);
	cout<<"Enter the date (dd/mm/yyyy):\n";
	gotoxy(25,12);
	string s;
	cin>>s;
	int day,month,year;
	int ln = s.length(),i;
	int temp = 0,count = 0;
	for(i = 0;i<ln;i++)
	{
		if(s[i] == '/')
		{
			if(count == 0)
			{
				day = temp;
				count++;
				temp = 0;
			}
			else
			{
				month = temp;
				count++;
				temp = 0;
			}
		}
		else
		{
			int t = s[i]-'0';
			temp = temp*10+t;
		}
	}
	year = temp;
	
	//cout<<"\n"<<day<<"\n"<<month<<"\n"<<year<<"\n";
	int d = findDay(day,month,year);
	system("cls");
	setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
	gotoxy(17,7);
	cout<<"Day corresponding to : "<<day<<"-"<<month<<"-"<<year<<" is "<<dayName[d];
	
	gotoxy(1,17);
	char ch;
	cout<<"Press any key to continue...";
	ch = getche();
	return;
}

void printNum(int num,int x,int y)
{
	gotoxy(x,y);
	cout<<num;
}

void fullMonth(int month,int year)
{
	int day = 1;
	int d = findDay(day,month,year);
	int m,i,y = 7;
	if(month == 2&&isleapyear(year))
	{
		m = mon_day[month-1]+1;
	}
	else
	{
		m = mon_day[month-1];
	}
	
	system("cls");
	gotoxy(29,2);
	if(month<10)
	cout<<"0"<<month<<"/"<<year;
	else
	cout<<month<<"/"<<year;
	gotoxy(23,5);
	cout<<"S";
	gotoxy(26,5);
	cout<<"M";
	gotoxy(29,5);
	cout<<"T";
	gotoxy(32,5);
	cout<<"W";
	gotoxy(35,5);
	cout<<"T";
	gotoxy(38,5);
	cout<<"F";
	gotoxy(41,5);
	cout<<"S";
	
	for(i = 1;i<=m;i++)
	{
		if(d<3)
		{
			printNum(i,35+3*d,y);
		}
		else
		{
			printNum(i,35-3*(7-d),y);
		}
		if(d == 2)
		y += 2;
		d = (d+1)%7;
	}
}

void printMonth()
{
	system("cls");
	setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
	gotoxy(25,10);
	cout<<"Enter month and year (mm/yyyy) :\n";
	gotoxy(25,12);
	string s;
	cin>>s;
	int day,month,year;
	int ln = s.length(),i;
	int temp = 0,count = 0;
	for(i = 0;i<ln;i++)
	{
		if(s[i] == '/')
		{
			month = temp;
			temp = 0;
		}
		else
		{
			int t = s[i]-'0';
			temp = temp*10+t;
		}
	}
	year = temp;
	fullMonth(month,year);
	gotoxy(1,20);
	char ch;
	cout<<"Press n/N for next or p/P for previous month or v/V to view note or m/M for main page...";
	ch = getche();
	while(ch == 'n'||ch == 'N'||ch == 'p'||ch == 'P'||ch == 'v'||ch == 'V')
	{
		if(ch == 'n'||ch == 'N')
		{
			if(month == 12)
			{
				year++;
				month = 1;
				fullMonth(1,year);
			}
			else
			{
				month++;
				fullMonth(month,year);
			}
		}
		else if(ch == 'p'||ch == 'P')
		{
			if(month == 1)
			{
				year--;
				month = 12;
				fullMonth(12,year);
			}
			else
			{
				month--;
				fullMonth(month,year);
			}
		}
		else if(ch == 'v'||ch == 'V')
		{
			system("cls");
			setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
			gotoxy(1,1);
			cout<<"\nEnter only the date : ";
			cin>>day;
			string s;
			s = "Note";
			int wd,yn,wy,g = month,h = year;
			char da,ch;
			if(day>=1&&day<=9)
			{
				//wd = 1;
				da = day+48;
				s = s+da;
			}
			else
			{
				wd = day%10;
				day = day/10;
				da = day+48;
				s = s+da;
				da = wd+48;
				s = s+da;
			}
			s = s+'_';
			if(month>=1&&month<=9)
			{
				//wd = 1;
				da = month+48;
				s = s+da;
			}
			else
			{
				wd = month%10;
				day = month/10;
				da = month+48;
				s = s+da;
				da = wd+48;
				s = s+da;
			}
			yn = year;
			wy = 1;
			yn = yn/10;
			while(yn>0)
			{
				wy *= 10;
				yn /= 10;
			}
			s = s+'_';
			while(year>0)
			{
				yn = year/wy;
				da = yn+48;
				s = s+da;
				year = year-yn*wy;
				wy = wy/10;
			}
			s = s+".txt";
			//cout<<s<<"\n";
			//cin>>da;
			ifstream fp;
			fp.open(s,ios::in);
			if(fp == NULL)
			{
				cout<<"No note added for this day";
			}
			else
			{
				//fp>>ch;
				cout<<"\nNote added : \n";
				while(!fp.eof())
				{
					//cout<<ch;
					fp>>ch;
					cout<<ch;
				}
			}
			cout<<"\nEnter b/B to go back";
			ch = getche();
			month = g;
			year = h;
			system("cls");
			fullMonth(month,year);
			//ch = 'n';
			//continue;
		}
		gotoxy(1,20);
		cout<<"Press n/N for next or p/P for previous month or v/V to view note or m/M for main page...";
		ch = getche();
	}
	
}

void event()
{
	system("cls");
	//setConsoleColors(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY|FOREGROUND_BLUE);
	setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
	gotoxy(1,1);
	cout<<"Enter Date : ";
	string s;
	cin>>s;
	int day,month,year;
	int ln = s.length(),i;
	int temp = 0,count = 0;
	for(i = 0;i<ln;i++)
	{
		if(s[i] == '/')
		{
			if(count == 0)
			{
				day = temp;
				count++;
				temp = 0;
			}
			else
			{
				month = temp;
				count++;
				temp = 0;
			}
			s[i] = '_';
		}
		else
		{
			int t = s[i]-'0';
			temp = temp*10+t;
		}
	}
	year = temp;
	gotoxy(5,3);
	for(i = 5;i<=70;i++)
	{
		cout<<"_";
	}
	for(i = 4;i<=17;i++)
	{
		gotoxy(4,i);
		cout<<"|";
	}
	gotoxy(5,17);
	for(i = 5;i<=70;i++)
	{
		cout<<"_";
	}
	for(i = 4;i<=17;i++)
	{
		gotoxy(71,i);
		cout<<"|";
	}
	gotoxy(5,5);
	char ch;
	
	ofstream fp;
	string s1 = "Note"+s+".txt";
	fp.open(s1);
	if(fp == NULL)
	{
		cout<<"Unable to open file\n";
		//return;
	}
	char data[400];
	int x_ = 5,y_ = 5;
	while((ch = getche())!='*')
	{
		fp<<ch;
		x_++;
		if(x_ == 70)
		{
			if(y_ == 15)
			{
				while((ch = getch())!='*')
				{
					cout<<'\a';
					//cin>>ch;
				}
				break;
			}
			else
			{
				y_ += 2;
				gotoxy(5,y_);
			}
			x_ = 5;
		}
	}
	fp.close();
	//cin.getline(data,400);
	
}

int main()
{
	while(1)
	{
		/*HANDLE hconsole;
		hconsole = GetStdHandle(STD_OUTPUT_HANDLE);*/
		system("cls");
		setConsoleColors(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
		gotoxy(30,8);
		cout<<"1). Find out the day\n";
		gotoxy(30,10);
		cout<<"2). View entire month\n";
		gotoxy(30,12);
		cout<<"3). Add a note.\n";
		gotoxy(30,14);
		cout<<"4). Exit.\n";
		gotoxy(30,16);
		char choice;
		//cin>>choice;
		fflush(stdin);
		choice = getche();
		
		switch(choice)
		{
			case '1':
				finDay();
				break;
			case '2':
				printMonth();
				break;
			case '3':
				event();
				break;
			case '4':
				exit(0);
		}
	}
}






