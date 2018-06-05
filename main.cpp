#include <iostream>
#include<windows.h>
#include<fstream>
#include<iomanip>
using namespace std;
class Time  //用来记录时间(包括借阅时间，出版日期)
{
private:
  int year;
  int month;
  int day;
public:
	Time(int a=0,int b=0,int c=0)
	{
	  year=a;
	  month=b;
	  day=c;
	}
	void set_time(int a=0,int b=0,int c=0)
	{
	  year=a;
	  month=b;
	  day=c;
	}
	void show_time()
	{
	  cout<<year<<"年"<<month<<"月"<<day<<"日"<<endl;
	}
	bool is_leapyear()
	{
      if(year%400==0||year%100!=0&&year%4==0)
        return true;
      else
        return false;
	}
	friend int operator-(Time &time1,Time &time2);
};
//运算符重载
int operator-(Time &time1,Time &time2)
{
    int sum=0;
    int a1[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
    int a2[13]={0,0,31,60,91,121,152,182,213,244,274,305,335};
    if(time1.year==time2.year){
        if(time1.is_leapyear()){
            if(time2.is_leapyear()){
                sum+=a2[time2.month]+time2.day-a2[time1.month]-time1.day;
                return sum;
            }
            else{
                sum+=a1[time2.month]+time2.day-a2[time1.month]-time1.day;
                return sum;
            }
        }
        else{
            if(time2.is_leapyear()){
                sum+=a2[time2.month]+time2.day-a1[time1.month]-time1.day;
                return sum;
            }
            else{
                sum+=a1[time2.month]+time2.day-a1[time1.month]-time1.day;
                return sum;
            }
        }
        }
    else if(time1.year+1==time2.year){
        if(time1.is_leapyear()){
            if(time2.is_leapyear()){
                sum+=a2[time2.month]+time2.day+(366-a2[time1.month]-time1.day);
                return sum;
            }
            else{
                sum+=a1[time2.month]+time2.day+(366-a2[time1.month]-time1.day);
                return sum;
            }
            }
        else{
            if(time2.is_leapyear()){
                sum+=a2[time2.month]+time2.day+(365-a1[time1.month]-time1.day);
                return sum;
            }
            else{
                sum+=a1[time2.month]+time2.day+(365-a1[time1.month]-time1.day);
                return sum;
            }
      }
    }
    else{
        int i;
        for(i=time1.year+1;i<=time2.year-1;i++){
            if(i%400==0||i%4==0&&i%100!=0)
                sum+=366;
            else
                sum+=365;
        }
        if(time1.is_leapyear()){
         if(time2.is_leapyear()){
            sum+=a2[time2.month]+time2.day+(366-a2[time1.month]-time1.day);
            return sum;
            }
         else{
            sum+=a1[time2.month]+time2.day+(366-a2[time1.month]-time1.day);
            return sum;
            }
        }
      else{
         if(time2.is_leapyear()){
            sum+=a2[time2.month]+time2.day+(365-a1[time1.month]-time1.day);
            return sum;
            }
         else{
            sum+=a1[time2.month]+time2.day+(365-a1[time1.month]-time1.day);
            return sum;
            }
      }
    }
}
class book_date
{
private:
    Time date;
	string book_name;
	string ISBN;
    string book_author;
    string publishing_company;
	int order;//版次
	int count;//数量
public:
    book_date(string s1="",string s2="",string s3="",string s4="",int order1=0,int count1=0,
              int year1=0,int month1=0,int day1=0)
	:date(year1,month1,day1)
	{
        book_name=s1;
        ISBN=s2;
        book_author=s3;
        publishing_company=s4;
        order=order1;
        count=count1;
	}
    void show_book_date_information()
	{
	  cout<<"书名:"<<book_name<<endl;
	  cout<<"ISBN号:"<<ISBN<<endl;
	  cout<<"作者:"<<book_author<<endl;
	  cout<<"出版社:"<<publishing_company<<endl;
	  cout<<"出版日期:";
	  date.show_time();
	  cout<<"此图书馆现存数量:"<<count<<endl;
	}
	void revise_book_date_name()
	{
	    string s1;
	    string s2;
	    for(;;){
           cout<<"请输入本图书的新名字:";
	       cin>>s1;
	       cout<<"请再次确认名字:";
	       cin>>s2;
	       if(s1!=s2)
               cerr<<"两次输入内容不相同，请重新输入"<<endl;
           else
               break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_ISBN()
	{
	    string s1;
	    string s2;
	    for(;;){
            cout<<"请输入本图书的新ISBN号:";
	        cin>>s1;
            cout<<"请再次确认ISBN号:";
            cin>>s2;
            if(s1!=s2)
                cerr<<"两次输入内容不相同，请重新输入"<<endl;
            else
                break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_author()
	{
	    string s1;
	    string s2;
	    for(;;){
            cout<<"请输入本图书的新作者姓名:";
            cin>>s1;
            cout<<"请再次确认作者姓名:";
            cin>>s2;
            if(s1!=s2)
                cerr<<"两次输入内容不相同，请重新输入"<<endl;
            else
                break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_publishing_company()
	{
	    string s1;
	    string s2;
	    for(;;){
            cout<<"请输入本图书的新出版社:";
            cin>>s1;
            cout<<"请再次确认出版社:";
            cin>>s2;
            if(s1!=s2)
                cerr<<"两次输入内容不相同，请重新输入"<<endl;
            else
                break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_order()
	{
	    int s1;
	    int s2;
	    for(;;){
            cout<<"请输入本图书的新版次:";
            cin>>s1;
            cout<<"请再次确认版次:";
            cin>>s2;
            if(s1!=s2)
                cerr<<"两次输入内容不相同，请重新输入"<<endl;
            else
                break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_count()
	{
	    int s1;
	    int s2;
	    for(;;){
            cout<<"请输入本图书的新数量:";
            cin>>s1;
            cout<<"请再次确认数量:";
            cin>>s2;
            if(s1!=s2)
                cerr<<"两次输入内容不相同，请重新输入"<<endl;
            else
                break;
	    }
	    cout<<"修改成功"<<endl;
	}
};
class book_location:public book_date
{
private:
    string classification;//类别
    int book_shelf;//书架数
    int storey;//层数
public:
    book_location(string s1="",int book_shelf1=0,int storey1=0,string s2="",string s3="",string s4="",string s5="",
                  int order1=0,int count1=0,int year1=0,int month1=0,int day1=0)
    :book_date(s2,s3,s4,s5,order1,count1,year1,month1,day1)
    {
        classification=s1;
        book_shelf=book_shelf1;
        storey=storey1;
    }
    void set_book_location(string classification1="",int book_shelf1=0,int storey1=0)
    {
        classification=classification1;
        book_shelf=book_shelf1;
        storey=storey1;
    }
    void show_book_location_information()
    {
        cout<<"类别:"<<classification<<endl;
        cout<<"书架数:"<<book_shelf<<endl;
        cout<<"层数:"<<storey<<endl;
    }
    void revise_book_location_classification()
	{
	    string s1;
	    string s2;
	    for(;;){
           cout<<"请输入本图书的新类别:";
	       cin>>s1;
	       cout<<"请再次确认类别:";
	       cin>>s2;
	       if(s1!=s2)
               cerr<<"两次输入内容不相同，请重新输入"<<endl;
           else
               break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_location_book_shelf()
	{
	    int s1;
	    int s2;
	    for(;;){
           cout<<"请输入本图书的新书架数:";
	       cin>>s1;
	       cout<<"请再次确认第几书架:";
	       cin>>s2;
	       if(s1!=s2)
               cerr<<"两次输入内容不相同，请重新输入"<<endl;
           else
               break;
	    }
	    cout<<"修改成功"<<endl;
	}
	void revise_book_date_name()
	{
	    int s1;
	    int s2;
	    for(;;){
           cout<<"请输入本图书的新层数:";
	       cin>>s1;
	       cout<<"请再次确认层数:";
	       cin>>s2;
	       if(s1!=s2)
               cerr<<"两次输入内容不相同，请重新输入"<<endl;
           else
               break;
	    }
	    cout<<"修改成功"<<endl;
	}
};
class borrow_return_book
{
private:
	Time borrow_time;
	Time return_time;
	book_date book[10];//一次最多借十本书
	int count;//用来记录用户借书的本数
	bool return_yes_or_not;//用来记录用户是否还书,1代表已归还或者未借书
public:
	/*borrow_return_book()
	{
	  borrow_time.set_time(0,0,0);
	  return_time.set_time(0,0,0);
	  count=0;
	  return_yes_or_not=true;
	}*/
    borrow_return_book(int y1=0,int m1=0,int d1=0,int y2=0,int m2=0,int d2=0,int a=0,bool b=true)
	:borrow_time(y1,m1,d1),return_time(y2,m2,d2)
	{
	  count=a;
      return_yes_or_not=b;
	}
	void show_borrow_return_book_information()
	{
	  cout<<"借阅时间:";
	  borrow_time.show_time();
	  cout<<"图书状态:";
	  if(return_yes_or_not==false){
	    cout<<"未归还"<<endl;
	  }
	  else{
	    cout<<"已归还"<<endl;
		cout<<"归还时间:";
		return_time.show_time();
	  }
	  int i;
	  cout<<"借阅书籍:"<<endl;
	  for(i=0;i<count;i++)
		book[i].show_book_date_information();
	}
};
class student:public borrow_return_book
{
private:
	string name;
	string id_number;//身份证号
	string phone_number;
    string student_id;//学号
    string password;
public:
	student(string s1="",string s2="",string s3="",string s4="",string s5="")
	:borrow_return_book()
	{
       name=s1;
	   id_number=s2;
	   password=s3;
	   phone_number=s4;
	   student_id=s5;
	}
	void show_student_information()
	{
	  cout<<"姓名:"<<name<<endl;
	  cout<<"身份证号:"<<id_number<<endl;
	  cout<<"电话号码:"<<phone_number<<endl;
	  cout<<"学号:"<<student_id<<endl;
	}
	void revise_name()
	{
	  string s1,s2;
	  for(;;){
        cout<<"请输入新姓名:"<<endl;
	    cin>>s1;
	    cout<<"请再次确认你的新姓名:"<<endl;
	    cin>>s2;
        if(s1!=s2)
          cerr<<"两次输入内容不相同，请重新输入"<<endl;
        else
          break;
	  }
      cout<<"修改成功"<<endl;
	}
	void revise_id_number()
	{
	  string s1,s2;
	  for(;;){
        cout<<"请输入新身份证号:"<<endl;
	    cin>>s1;
	    cout<<"请再次确认你的身份证号:"<<endl;
	    cin>>s2;
        if(s1!=s2)
          cerr<<"两次输入内容不相同，请重新输入"<<endl;
        else
          break;
	  }
      cout<<"修改成功"<<endl;
	}
    void revise_phone_number()
	{
	  string s1,s2;
	  for(;;){
        cout<<"请输入新电话号码:"<<endl;
	    cin>>s1;
	    cout<<"请再次确认你的电话号码:"<<endl;
	    cin>>s2;
        if(s1!=s2)
          cerr<<"两次输入内容不相同，请重新输入"<<endl;
        else
          break;
	  }
      cout<<"修改成功"<<endl;
	}
    void revise_student_id()
	{
	  string s1,s2;
	  for(;;){
        cout<<"请输入新学号:"<<endl;
	    cin>>s1;
	    cout<<"请再次确认你的学号:"<<endl;
	    cin>>s2;
        if(s1!=s2)
          cerr<<"两次输入内容不相同，请重新输入"<<endl;
        else
          break;
	  }
      cout<<"修改成功"<<endl;
	}
	void revise_password()
	{

	}
};
void menu();//菜单
int user_choice();
void startcheck();
void input_book_information();
void seek_book_location();
void delete_book_infomation();
void borrow_book();
void return_book();
void count_book_information();
void check_borrow_information();
void revise_password();
void revise_book_information();
int main()
{
  system("color f0");
  //startcheck();
  while(1){
    if(user_choice()==10)
		break;
  }
  system("exit");
  return 0;
}
void menu()
{
  system("cls");
  system("title 主菜单-图书管理借阅系统");
  cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
  cout<<"\t\t\t\t│         图书管理借阅系统         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         1   输入图书信息         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         2   查找图书位置         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         3   删除图书信息         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         4     借阅图书           │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         5     归还图书           │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         6   统计图书信息         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         7   查询借阅信息         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         8   修改登录密码         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         9   修改图书信息         │\n";
  cout<<"\t\t\t\t├──────────────────────────────────┤\n";
  cout<<"\t\t\t\t│         10    退出系统           │\n";
  cout<<"\t\t\t\t└──────────────────────────────────┘\n";
}
int user_choice()
{   //已完成
    menu();
    int n;
    cout<<"请按键选择对应功能:";
    cin>>n;
    switch(n){
    case 1:input_book_information();break;
    case 2:seek_book_location();break;
    case 3:delete_book_infomation();break;
    case 4:borrow_book();break;
    case 5:return_book();break;
    case 6:count_book_information();break;
    case 7:check_borrow_information();break;
    case 8:revise_password();break;
    case 9:revise_book_information();break;
    case 10:break;
    default:cerr<<"无此对应功能"<<endl;break;
    }
    return n;
}
void startcheck()
{   //已完成
    system("title 登录/注册主页面");
    student one;ifstream in;ofstream out;
    string student_id1,phone_number1;string password1,id_number1,name1;
    cout<<"                 1:登录"<<endl;
    cout<<"                 2:注册"<<endl;
    int n;
    cout<<"              请输入你的选择:";
    cin>>n;
    //cin.get();
    if(n==1){
        system("cls");
        for(;;){
            in.open("password.txt",ios_base::app);
            if(!in){
                cerr<<"文件打开失败(文件不存在)，按任意键结束"<<endl;
                cin.get();cin.get();
                exit(0);
            }
            cout<<"                 学号:";
            cin>>student_id1;
            student_id1+='/';
            char c;int flag=0;
            string password2,student_id2;
            while(!in.eof()){
                while(c!='/'&&!in.eof()){
                    in.get(c);
                    student_id2+=c;
                }
                while(c!='\n'&&!in.eof()){
                    in.get(c);
                    password2+=c;
                }
                //cout<<password2<<endl;
                int i=0,j=0;
                if(student_id1==student_id2){
                    for(i=0;i<3;i++){
                        cout<<"                 密码:";
                        cin>>password1;
                        password1+='\n';
                        flag=1;
                        if(password1==password2)
                            return;
                        else
                            cout<<"密码错误,请重新输入"<<endl;
                    }
                    in.close();
                    if(i==3){
                        cout<<"你已经连续三次未输入正确密码,系统即将退出"<<endl;
                        exit(0);
                    }
                }
            }
            if(flag==0){
                cout<<"系统未检测到此学号,请确认学号是否正确或者是否未注册"<<endl;
            }
        }
    }
    else if(n==2){
        system("cls");
        in.open("password.txt",ios_base::app);
        if(!in){
            cerr<<"文件打开失败(文件不存在)，按任意键结束"<<endl;
            cin.get();cin.get();
            exit(0);
        }
        for(;;){
            cout<<"                 学号:";cin>>student_id1;
            string password2,student_id2;
            char c;int flag=0;
            while(!in.eof()){
                while(c!='/'&&!in.eof()){
                    in.get(c);
                    student_id2+=c;
                    cout<<student_id2<<endl;
                }
                while(c!='\n'&&!in.eof()){
                    in.get(c);
                    password2+=c;
                }
                if(student_id2==student_id1){
                    flag=1;
                    cout<<"系统已存在此学号,请检查学号是否输入正确或者是否已注册"<<endl;
                    break;
                }
            }
            if(flag==0){
                cout<<"                 姓名:";cin>>name1;
                cout<<"                 身份证号:";cin>>id_number1;
                cout<<"                 电话号码:";cin>>phone_number1;
                cout<<"                 密码:";cin>>password1;
                in.close();
                out.open("password.txt",ios_base::app);
                out<<student_id1<<"/"<<password1<<"\n";
                out.close();
                out.open("student.txt",ios_base::app);
                out<<id_number1<<"/"<<name1<<"/"<<phone_number1<<"/"<<student_id1<<"\n";
                out.close();
                break;
            }
        }
        cout<<"注册成功"<<endl;
        cin.get();
        cout<<"按任意键进入本系统"<<endl;
        cin.get();
        return;
    }
    else{
        cout<<"选择错误,系统即将退出"<<endl;
        cin.get();
        exit(0);
    }
}
void input_book_information()
{   //已完成
    system("cls");cin.get();
    ofstream out;int n;
    string book_author1,book_name1,publishing_company1,ISBN1,classification1;
    int count1,order1,book_shelf1,storey1;
    int year1,month1,day1;
    out.open("book.txt",ios_base::app);
    if(!out){
        cerr<<"文件打开失败(文件不存在)，按任意键结束"<<endl;
        cin.get();
        return ;
    }
    for(;;){
        cout<<"请输入作者:";cin>>book_author1;
        cout<<"请输入书名:";cin>>book_name1;
        cout<<"请输入ISBN号:";cin>>ISBN1;
        cout<<"请输入出版社:";cin>>publishing_company1;
        for(;;){
            cout<<"请输入版次:";cin>>order1;
            if(order1<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
        for(;;){
            cout<<"请输入数量:";cin>>count1;
            if(count1<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
        cout<<"请输入图书类别:";cin>>classification1;
        for(;;){
            cout<<"请输入图书在第几个书架:";cin>>book_shelf1;
            if(book_shelf1<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
        for(;;){
            cout<<"请输入图书所在书架的层数:";cin>>storey1;
            if(storey1<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
        SYSTEMTIME sys;
        GetLocalTime(&sys);
        for(;;){
            cout<<"请输入出版日期(按年月日分别输入,中间用空格隔开):";
            cin>>year1>>month1>>day1;
            if(sys.wYear<year1||sys.wYear==year1&&sys.wMonth<month1||
               sys.wYear==year1&&sys.wMonth==month1&&sys.wDay<day1)
                cout<<"日期输入错误,请重新输入"<<endl;
            else
                break;
        }
        out<<book_name1<<"/"<<book_author1<<"/"<<count1<<"/"<<ISBN1<<"/"<<order1;
        out<<"/"<<publishing_company1<<"/"<<year1<<"/"<<month1<<"/";
        out<<day1<<"/"<<classification1<<"/"<<book_shelf1<<"/"<<storey1<<".\n";
        cout<<"继续吗?(1/0)";
        cin>>n;
        if(n==0){
            out.close();break;
        }
    }
    cout<<"输入成功"<<endl;
    cin.get();
    cout<<"按任意键返回"<<endl;
    cin.get();
}
void seek_book_location()
{   //已完成
    system("cls");cin.get();
    string book_name1,book_name2,other_book_information;
    ifstream in;
    in.open("book.txt",ios_base::app);
    if(!in){
        cout<<"文件打开失败"<<endl;
        cin.get();
        return ;
    }
    cout<<"请输入待查询位置的书籍名:";cin>>book_name1;
    char c;int flag=0;
    while(!in.eof()){
        in.get(c);
        while(c!='/'){
            book_name2+=c;
            in.get(c);
        }
        //cout<<book_name2<<endl;
        //in.get(c);
        if(book_name1==book_name2){
            while(c!='.'){
                other_book_information+=c;
                in.get(c);
            }
            flag=1;
            cout<<"已找到"<<endl;
            cout<<setw(10)<<"图书名"<<setw(10)<<"作者"<<setw(10)<<"数量"<<setw(10)<<"ISBN号"<<setw(10)<<"版次";
            cout<<setw(10)<<"出版社"<<setw(10)<<"出版日期"<<setw(10)<<"类别"<<setw(10)<<"书架数"<<setw(10)<<"层数"<<endl;
            //cout<<endl;
            cout<<setw(10)<<book_name1<<" "<<other_book_information<<endl;
            cin.get();
            in.close();
            break;
        }
    }
    if(flag==0){
        cout<<"系统未找到此书籍,请确认书籍名是否正确"<<endl;
    }
    cout<<"按任意键返回"<<endl;
    cin.get();
}
void delete_book_infomation()
{   //已完成
    system("cls");cin.get();
    string book_name1,book_name2,othor_book_information;
    cout<<"请输入欲修改的书籍名称:";cin>>book_name1;
    ofstream out;ifstream in;
    in.open("book.txt");
    if(!in||in.eof()){
        cerr<<"文件不存在或未录入任何书籍信息"<<endl;
        cin.get();
        return ;
    }
    char c;
    while(in.peek()!=EOF){
        in.get(c);
        while(c!='/'){
            book_name2+=c;
            in.get(c);
        }
        while(c!='.'){
            othor_book_information+=c;
            in.get(c);
        }
        //cout<<book_name2<<endl;
        if(book_name1!=book_name2){
            out.open("book1.txt",ios_base::app);
            if(!out){
                cerr<<"文件打开失败"<<endl;
                cin.get();
                return ;
            }

            cout<<othor_book_information<<endl;
            out<<book_name2<<"/"<<othor_book_information<<".\n";
            out.close();
        }
    }
    in.close();
    out.open("book.txt",ios::trunc);
    in.open("book1.txt");
    while(in.peek()!=EOF){
        in.get(c);
        out<<c;
    }
    out.close();
    in.close();
    cout<<"删除成功"<<endl;
    cin.get();
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void borrow_book()
{   system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void return_book()
{   system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void count_book_information()
{   system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void check_borrow_information()
{   system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void revise_password()
{   system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void revise_book_information()
{
    system("cls");cin.get();
    cout<<"此功能暂未实现"<<endl;
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
