#include<iostream>
#include<string>
#include<windows.h>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<map>
using namespace std;
bool check_time(int y,int m,int d)
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);//获取系统时间
    if(y>sys.wYear){
        return false;
    }
    else{
        if(sys.wYear==y&&sys.wMonth<m)
            return false;
        else{
            if(sys.wYear==y&&sys.wMonth==m&&sys.wDay<d)
                return false;
        }
    }//以上检测是否输入为未发生的时间
    //接下来检测day输入是否符合实际
    int flag=1;
    if(m>12||m<1)
        return false;
    if(y%400==0||(y%4==0&&y%100!=0))//如果是闰年
    {
        switch(m){
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            if(d>31)
                flag=0;break;
        case 4:case 6:case 9:case 11:
            if(d>30)
                flag=0;break;
        case 2:
            if(d>29)
                flag=0;break;
        }
    }
    else{
        switch(m){
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            if(d>31)
                flag=0;break;
        case 4:case 6:case 9:case 11:
            if(d>30)
                flag=0;break;
        case 2:
            if(d>28)
                flag=0;break;
        }
    }
    if(flag==0)
        return false;
    else
        return true;
}
class Time
{
private:
    int year;
    int month;
    int day;
public:
    Time()
    {
        year=0;month=0;day=0;
    }
    void set_time(int y=0,int m=0,int d=0)
    {
        year=y;month=m;day=d;
    }
    void show_time()
    {
        cout<<year<<"年"<<month<<"月"<<day<<"号";
    }
    friend istream &operator>>(istream &in,Time &p)
    {
        in>>p.year>>p.month>>p.day;
        return in;
    }
    friend ostream &operator<<(ostream &out,const Time &p)
    {
        out<<p.year<<" "<<p.month<<" "<<p.day;
        return out;
    }
    bool is_leapyear()
    {
        if(year%400==0||(year%4==0&&year&100!=0))
           return true;
        else
           return false;
    }
    int get_year()
    {
        return year;
    }
    int get_month()
    {
        return month;
    }
    int get_day()
    {
        return day;
    }
    friend int operator-(Time &time1,Time &time2);
};
int operator-(Time &time2,Time &time1)//重载-运算符得到两个时间的差值，返回值为两个时间
{                                     //相差的天数,如果大于n天则需要收费
    int sum=0;
    int a1[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
    int a2[13]={0,0,31,60,91,121,152,182,213,244,274,305,335};
    if(time1.year==time2.year){//如果两个时间的年属性相同，只进行月和天的相减
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
    else if(time1.year+1==time2.year){//如果前面一个时间的年属性刚好等于后面一个
        if(time1.is_leapyear()){      //时间的年属性加一,即昨年和今年的区别,只进行
            if(time2.is_leapyear()){  //月和天属性的相减
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
class book_location
{
private:
    string classification;
    int book_shelf;
    int storey;
public:
    book_location()
    {
        book_shelf=0;
        storey=0;
    }
    void set_book_location()
    {
        cout<<"请输入图书类别:";cin>>classification;
        for(;;){
            cout<<"请输入书架数:";cin>>book_shelf;
            if(book_shelf<1){
                cout<<"输入错误，书架数必须大于等于1"<<endl;
                cout<<"请重新输入"<<endl;
            }
            else
                break;
        }
        for(;;){
            cout<<"请输入层数:";cin>>storey;
            if(book_shelf<1){
                cout<<"输入错误，层数必须大于等于1"<<endl;
                cout<<"请重新输入"<<endl;
            }
            else
                break;
        }
    }
    void show_book_location()
    {
        cout<<"类别:"<<classification<<endl;
        cout<<"书架数:"<<book_shelf<<endl;
        cout<<"层数:"<<storey<<endl;
    }
    virtual istream &input(istream& in){
        in>>classification;
        in>>book_shelf;
        in>>storey;
        return in;
    }
    friend istream &operator>>(istream &in,book_location &p)
    {
        return p.input(in);
    }
    friend ostream &operator <<(ostream &out,const book_location &book){
       return book.print(out);
    }
    virtual ostream &print(ostream& out)const{
       out<<classification<<" ";
       out<<book_shelf<<" ";
       out<<storey<<"\n";
       return out;
    }
    void revise_classification()
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
	    classification=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_book_shelf()
    {
        int s1;
	    int s2;
	    for(;;){
           cout<<"请输入本图书的新书架数:";
	       cin>>s1;
	       cout<<"请再次确认第几书架:";
	       cin>>s2;
	       if(s1!=s2||s1<1)
               cerr<<"两次输入内容不相同或输入错误，请重新输入"<<endl;
           else
               break;
	    }
	    book_shelf=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_storey()
    {
        int s1;
	    int s2;
	    for(;;){
           cout<<"请输入本图书的新层数:";
	       cin>>s1;
	       cout<<"请再次确认层数:";
	       cin>>s2;
	       if(s1!=s2||s2<1)
               cerr<<"两次输入内容不相同或输入错误，请重新输入"<<endl;
           else
               break;
	    }
	    storey=s1;
	    cout<<"修改成功"<<endl;
    }
    string get_classification()
    {
        return classification;
    }
    int get_book_shelf()
    {
        return book_shelf;
    }
    int get_storey()
    {
        return storey;
    }
};
class book_date:public book_location
{
private:
    string book_name;
    string book_author;
    string publishing_company;
    string ISBN;
    Time publishing_date;
    int order;//版次
    int amount;//数量
public:
    book_date():book_location(),publishing_date()
    {
        //string对象创建时是空string对象，故不用再赋初值
        amount=0;
        order=0;
    }
    void low_amount()
    {
        amount--;
    }
    void high_amount()
    {
        amount++;
    }
    string get_book_name()
    {
        return book_name;
    }
    string get_book_author()
    {
        return book_author;
    }
    string get_ISBN()
    {
        return ISBN;
    }
    string get_pubishing_company()
    {
        return publishing_company;
    }
    Time get_publishing_date()
    {
        return publishing_date;
    }
    int get_order()
    {
        return order;
    }
    int get_amount()
    {
        return amount;
    }
    virtual ostream &print(ostream& out)const{
        out<<book_name<<" ";
        out<<book_author<<" ";
        out<<publishing_company<<" ";
        out<<ISBN<<" ";
        out<<publishing_date<<" ";
        out<<order<<" ";
        out<<amount<<" ";
        book_location::print(out);
        return out;
    }
    void set_book_date()
    {
        cout<<"请输入图书书名:";cin>>book_name;
        cout<<"请输入图书作者:";cin>>book_author;
        cout<<"请输入图书出版社:";cin>>publishing_company;
        cout<<"请输入图书ISBN号:";cin>>ISBN;
        for(;;){
            cout<<"请输入图书版次:";cin>>order;
            if(order<=0)
                cout<<"输入错误,版次不能小于等于1"<<endl;
            else
                break;
        }
        for(;;){
            cout<<"请输入图书数量:";cin>>amount;
            if(amount<=0)
                cout<<"输入错误,数量不能小于等于1"<<endl;
            else
                break;
        }
        int year1,month1,day1;
        for(;;){
            cout<<"请输入出版日期(按年月日分别输入,中间用空格隔开):";
            cin>>year1>>month1>>day1;
            if(!check_time(year1,month1,day1))
                cout<<"日期输入错误,请重新输入"<<endl;
            else
                break;
        }
        publishing_date.set_time(year1,month1,day1);
        set_book_location();
    }
    void show_book_date()
    {
        cout<<"书名:"<<book_name<<endl;
        cout<<"作者:"<<book_author<<endl;
        cout<<"出版社:"<<publishing_company<<endl;
        cout<<"ISBN号:"<<ISBN<<endl;
        cout<<"版次:"<<order<<endl;
        cout<<"数量:"<<amount<<endl;
        show_book_location();
    }
    virtual istream &input(istream &in)
    {
        in>>book_name;
        in>>book_author;
        in>>publishing_company;
        in>>ISBN;
        in>>publishing_date;
        in>>order;
        in>>amount;
        book_location::input(in);
        return in;
    }
    void revise_name()
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
	    book_name=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_author()
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
	    book_author=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_publishing_company()
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
	    publishing_company=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_ISBN()
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
	    ISBN=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_order()
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
	    order=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_amount()
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
	    amount=s1;
	    cout<<"修改成功"<<endl;
    }
    void revise_publishing_date()
    {
        int year1,month1,day1;
        for(;;){
            cout<<"请依次输入新的出版时间,用空格分开:";
            cin>>year1>>month1>>day1;
            if(!check_time(year1,month1,day1))
                cout<<"日期输入错误,请重新输入"<<endl;
            else
                break;
        }
        publishing_date.set_time(year1,month1,day1);
    }
};
class borrow_return_book
{
private:
    Time borrow_time;
    Time return_time;
    string book_name[10];//一次最多借阅十本书
    int number;//借书的本数
    bool return_y_n;//是否归还
public:
    borrow_return_book():borrow_time(),return_time()
    {
        number=0;
        return_y_n=true;
    }
    void revise_return_y_n()
    {
        return_y_n=false;
    }
    int get_number()
    {
        return number;
    }
    string get_book_name(int i)
    {
        return book_name[i];
    }
    Time get_brtime()
    {
        return borrow_time;
    }
    Time get_rtime()
    {
        return return_time;
    }
    void show_brbook_information()
    {
        int i;
        cout<<"借阅"<<number<<"本书"<<endl;
        cout<<"书名分别为:";
        for(i=0;i<number;i++)
            cout<<book_name[i]<<" ";
        cout<<"借阅时间:";
        borrow_time.show_time();cout<<endl;
        if(!return_y_n)
            cout<<"图书状态:未归还"<<endl;
        else{
            return_time.show_time();
            cout<<"图书状态:已归还"<<endl;
        }
    }
    void set_bbook_information(int number1,string book1[10])//生成借书信息
    {
        SYSTEMTIME sys;
        GetLocalTime(&sys);//获取系统时间
        borrow_time.set_time(sys.wYear,sys.wMonth,sys.wDay);
        number=number1;
        return_y_n=false;
        int i;
        for(i=0;i<number1;i++)
            book_name[i]=book1[i];
    }
    void revise_brbook_infomation(int number1,string book1[10])
    {
        number=number1;
        return_y_n=false;
        int i;
        for(i=0;i<number1;i++)
            book_name[i]=book1[i];
    }
    void set_rbook_information(int number1,string book[10])
    {
        SYSTEMTIME sys;
        GetLocalTime(&sys);//获取系统时间
        return_time.set_time(sys.wYear,sys.wMonth,sys.wDay);
        return_y_n=true;
        number=number1;
        int i;
        for(i=0;i<number1;i++)
            book_name[i]=book[i];
    }
    friend istream &operator>>(istream &in,borrow_return_book &p)
    {
        return p.input(in);
    }
    friend ostream &operator<<(ostream &out,const borrow_return_book &p)
    {
        return p.print(out);
    }
    virtual ostream &print(ostream &out)const
    {
        int i;
        for(i=0;i<number;i++)
            out<<book_name[i]<<" ";
        out<<borrow_time<<" ";
        out<<return_time<<" ";
        out<<number<<" ";
        out<<return_y_n<<"\n";
        return out;
    }
    virtual istream &input(istream &in)
    {
        int i;
        for(i=0;i<number;i++)
            in>>book_name[i];
        in>>borrow_time;
        in>>return_time;
        in>>number;
        in>>return_y_n;
        return in;
    }
};
class people:public borrow_return_book//系统用户包括学生,老师和管理员,统称为人
{
private:
    string name;
	string id_number;//身份证号
	string phone_number;
    string id;//学号
    string password;
public:
    people():borrow_return_book()
    {

    }
    virtual ostream &print(ostream &out)const
    {
        out<<name<<" ";
        out<<id_number<<" ";
        out<<phone_number<<" ";
        out<<id<<" ";
        out<<borrow_return_book::print(out);
        return out;
    }
    string get_name()
    {
        return name;
    }
    string get_id()
    {
        return id;
    }
    void set_people(string s1,string s2,string s3,string s4,string s5)
    {
        name=s1;
        id_number=s2;
        phone_number=s3;
        id=s4;
        password=s5;
    }
    void show_people()
    {
        cout<<"姓名:"<<name<<endl;
        cout<<"身份证号:"<<id_number<<endl;
        cout<<"电话号码:"<<phone_number<<endl;
        cout<<"学号或编号:"<<id<<endl;
    }
    void revise_people_name()
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
        name=s1;
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
        phone_number=s1;
        cout<<"修改成功"<<endl;
	}
	virtual istream &input(istream& in)
	{
	    in>>name;
	    in>>id_number;
	    in>>phone_number;
	    in>>id;
	    borrow_return_book::input(in);
	    return in;
	}
};
void menu();//菜单
int user_choice(people &person);
void input_book_information();//输入书籍信息
people startcheck();
void seek_book_location();
void delete_book_infomation();
void borrow_book(people &person);//借书
void return_book(people &person);//还书
void count_book_information();//统计图书信息
void check_borrow_return_information();//查询借阅信息
void revise_personal_information(people &person);//修改密码
void revise_book_information();//修改图书信息
int main()
{
    system("color f0");//将背景设置成白色,文字设置为黑色
    people person=startcheck();//登录系统之前检查,包括登录和注册,同时获取学号
    while(1){
        if(user_choice(person)==10)//用户选择此系统的功能,同时返回用户的选择,如果为
		break;                      //10(代表退出系统),则结束循环,程序正常退出
    }
    system("exit");
    return 0;
}
people startcheck()
{
    people one;
    system("title 登录/注册主页面");
    ifstream in,ine;ofstream out;
    string id1,phone_number1,password1,id_number1,name1;
    cout<<"                 1:登录"<<endl;
    cout<<"                 2:注册"<<endl;
    int n;
    cout<<"                 请输入你的选择:";
    cin>>n;
    if(n==1){
        system("cls");
        system("title 登录");
        for(;;){
            in.open("password.txt",ios_base::app);
            if(!in){
                cerr<<"文件打开失败(文件不存在)，按任意键结束"<<endl;
                cin.get();cin.get();
                exit(0);
            }
            cout<<"                 学号:";
            cin>>id1;
            int flag=0;
            string password2,id2,id3;
            while(!in.eof()&&in.peek()!=EOF){//读取文件中保存的账号和密码
                in>>id2>>password2;
                int i=0;
                if(id1==id2){//如果检测到用户的账号
                    for(i=0;i<3;i++){//用户有三次输入密码的机会
                        cout<<"                 密码:";
                        char s[21];int j=0;
                        while((s[j]=getch())!=13&&j!=20){
                            putch('*');
                            j++;
                        }
                        s[j]='\0';
                        password1=s;
                        flag=1;
                        if(password1==password2){
                            ine.open("student.txt",ios_base::app);
                            while(!in.eof()&&ine.peek()!=EOF){
                                ine>>id3>>name1>>phone_number1>>id_number1;
                                if(id2==id3){
                                    ine.close();
                                    one.set_people(name1,id_number1,phone_number1,id1,password1);
                                    return one;
                                }
                            }
                        }
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
        system("title 注册");
        in.open("password.txt",ios_base::app);
        if(!in){
            cerr<<"文件打开失败(文件不存在)，按任意键结束"<<endl;
            cin.get();cin.get();
            exit(0);
        }
        for(;;){
            cout<<"                 学号或者编号:";cin>>id1;
            string password2,id2,password3;
            int flag=0;//检测系统是否已存在此学号
            while(in.peek()!=EOF&&in.eof()){
                in>>id2>>password2;
                if(id2==id1){
                    flag=1;
                    cout<<"系统已存在此学号,请检查学号是否输入正确或者是否已注册"<<endl;
                    break;
                }
            }
            if(flag==0){
                cout<<"                 姓名:";cin>>name1;
                cout<<"                 身份证号:";cin>>id_number1;
                cout<<"                 电话号码:";cin>>phone_number1;
                for(;;){
                    cout<<"                 密码(最多20位):";
                    char s1[21];int j=0;
                    while((s1[j]=getch())!=13&&j!=20){
                        putch('*');
                        j++;
                    }
                    s1[j]='\0';
                    password1=s1;
                    j=0;
                    cout<<"请再次确认密码:";
                    char s2[21];
                    while((s2[j]=getch())!=13&&j!=20){
                        putch('*');
                        j++;
                    }
                    s2[j]='\0';
                    password3=s2;
                    if(password1==password3)
                        break;
                    else{
                        cout<<"两次密码输入不相同,请重新输入"<<endl;
                    }
                }
                in.close();
                out.open("password.txt",ios_base::app);
                out<<id1<<" "<<password1<<"\n";
                out.close();
                out.open("student.txt",ios_base::app);
                out<<id1<<" "<<name1<<" "<<phone_number1<<" "<<id_number1<<"\n";
                out.close();
                break;
            }
        }
        cout<<"注册成功"<<endl;
        cin.get();
        cout<<"按任意键进入本系统"<<endl;
        cin.get();//创建一个临时对象，并将此对象“赋值”给person
        one.set_people(name1,id_number1,phone_number1,id1,password1);
        return one;
    }
    else{
        cout<<"选择错误,系统即将退出"<<endl;
        cin.get();
        exit(0);
    }
}
void menu()
{
    system("cls");//清屏
    system("title 主菜单-图书管理借阅系统");//将标题栏命名为---
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
    cout<<"\t\t\t\t│         8   修改个人信息         │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│         9   修改图书信息         │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│         10    退出系统           │\n";
    cout<<"\t\t\t\t└──────────────────────────────────┘\n";
}
int user_choice(people &person)
{   //已完成
    menu();
    int n;
    cout<<"请按键选择对应功能:";
    cin>>n;
    switch(n){
    case 1:input_book_information();break;
    case 2:seek_book_location();break;
    case 3:delete_book_infomation();break;
    case 4:borrow_book(person);break;
    case 5:return_book(person);break;
    case 6:count_book_information();break;
    case 7:check_borrow_return_information();break;
    case 8:revise_personal_information(person);break;
    case 9:revise_book_information();break;
    case 10:break;
    default:cerr<<"无此对应功能"<<endl;break;
    }
    return n;
}
void input_book_information()
{
    system("cls");system("title 添加书籍信息");
    ofstream out;int n;
    for(;;){
        book_date book;
        book.set_book_date();
        out.open("book.txt",ios_base::app);
        if(!out){
            cerr<<"文件打开失败"<<endl;
            cin.get();
            return;
        }
        out<<book;
        cout<<"是否继续添加?"<<endl;
        cout<<"1 :yes"<<endl;
        cout<<"0 :no"<<endl;
        cin>>n;
        if(n==0)
            break;
    }
    out.close();
    cout<<"添加成功,按任意键返回主菜单"<<endl;
    cin.get();
}
void seek_book_location()
{
    system("cls");system("title 查找图书信息");
    string book_name1;
    ifstream in;
    in.open("book.txt",ios_base::app);
    if(!in||in.eof()){
        cout<<"文件打开失败或文件无书籍信息"<<endl;
        cin.get();
        return ;
    }
    int flag=0,n;
    for(;;){
        cout<<"请输入待查询位置的书籍名:";cin>>book_name1;
        int n;book_date book;
        while(in.peek()!=EOF){
            in>>book;
            if(book.get_book_name()==book_name1){
                cout<<"已找到"<<endl;flag=1;
                break;
            }
        }
        if(flag==1){
            cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
            cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
            cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
            cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
            cout<<setw(10)<<"层数"<<"┃"<<endl;
            cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
            cout<<"┃"<<setw(10)<<book.get_book_name()<<"┃"<<setw(10)<<book.get_book_author()<<"┃";
            cout<<setw(10)<<book.get_pubishing_company()<<"┃"<<setw(10)<<book.get_ISBN()<<"┃";
            cout<<setw(4)<<book.get_publishing_date().get_year()<<"."<<setw(2)<<book.get_publishing_date().get_month();
            cout<<"."<<setw(2)<<book.get_publishing_date().get_day()<<"┃";
            cout<<setw(10)<<book.get_order()<<"┃"<<setw(10)<<book.get_amount()<<"┃";
            cout<<setw(10)<<book.get_classification()<<"┃"<<setw(10)<<book.get_book_shelf()<<"┃";
            cout<<setw(10)<<book.get_storey()<<"┃"<<endl;
            cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
        }
        else{
            cout<<"系统未找到此书籍信息"<<endl;cin.get();
        }
        cout<<"是否继续查找?"<<endl;
        cout<<"1 :yes"<<endl;
        cout<<"0 :no"<<endl;
        cin>>n;
        if(n==0)
            break;
    }
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void delete_book_infomation()
{
    system("cls");cin.get();
    string book_name1;
    book_date book;
    int m;
    for(;;){
        cout<<"请输入欲删除的书籍名称:";cin>>book_name1;
        ofstream out;ifstream in;
        in.open("book.txt");
        if(!in||in.eof()){//如果文件为空或者文件打开失败
            cerr<<"文件不存在或未录入任何书籍信息"<<endl;
            cin.get();
            return ;
        }
        int flag=0;int n=0;
        while(in.peek()!=EOF){
            in>>book;
            if(book.get_book_name()==book_name1){
                flag=1;
                in.close();break;
            }
        }
        if(flag==1){
            cout<<"确认删除以下书籍的所有信息?(1:yes   2:no)"<<endl;
            cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
            cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
            cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
            cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
            cout<<setw(10)<<"层数"<<"┃"<<endl;
            cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
            cout<<"┃"<<setw(10)<<book.get_book_name()<<"┃"<<setw(10)<<book.get_book_author()<<"┃";
            cout<<setw(10)<<book.get_pubishing_company()<<"┃"<<setw(10)<<book.get_ISBN()<<"┃";
            cout<<setw(4)<<book.get_publishing_date().get_year()<<"."<<setw(2)<<book.get_publishing_date().get_month();
            cout<<"."<<setw(2)<<book.get_publishing_date().get_day()<<"┃";
            cout<<setw(10)<<book.get_order()<<"┃"<<setw(10)<<book.get_amount()<<"┃";
            cout<<setw(10)<<book.get_classification()<<"┃"<<setw(10)<<book.get_book_shelf()<<"┃";
            cout<<setw(10)<<book.get_storey()<<"┃"<<endl;
            cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n"<<endl;
            cin>>n;
        }
        else{
            cout<<"系统未找到此书籍相关信息,无法执行删除操作"<<endl;
            in.close();cin.get();
        }
        if(n==1){
            in.open("book.txt");
            out.open("book1.txt",ios_base::app);//如果书名与欲删除的书名不同，则输入
            while(in.peek()!=EOF){//到辅助文件中，若相同则不输入到辅助文件中
                in>>book;
                if(book.get_book_name()!=book_name1)
                    out<<book;
            }
            in.close();out.close();
            out.open("book.txt",ios::trunc);//将book1.txt中的内容“复制”到book.txt
            out.close();
            out.open("book.txt",ios_base::app);
            in.open("book1.txt");
            char c;
            while(in.peek()!=EOF){
                in.get(c);
                out<<c;
            }
            out.close();
            in.close();
            out.open("book1.txt",ios::trunc);
            out.close();//清空book1.txt文件的内容
            cout<<"删除成功"<<endl;
            cin.get();
        }
        cout<<"是否继续删除?(1:yes   0:no)"<<endl;
        cin>>m;
        if(m==0)
            break;
    }
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void borrow_book(people &person)
{
    system("cls");cin.get();
    system("title 借阅书籍");
    ifstream in;ofstream out;
    people person1;
    int brbook_number;//借阅书籍本数
    in.open("brbook.txt");int flag1=0;//检测用户未归还的本数
    while(in.peek()!=EOF){
        in>>person1;
        if(person1.get_name()==person.get_name()){
            flag1=1;break;
        }
    }
    in.close();
    if(flag1==1){
        cout<<"由于你还有"<<person1.get_number()<<"本书未归还"<<endl;
        cout<<"故你现在只能最多借阅"<<10-person1.get_number()<<"本书"<<endl;
        for(;;){
            cout<<"请输入借阅本数:";cin>>brbook_number;
            if(brbook_number>10-person1.get_number()||brbook_number<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
    }
    else{
        for(;;){
            cout<<"请输入借阅本数(最多借阅十本):";cin>>brbook_number;
            if(brbook_number>10||brbook_number<=0)
                cout<<"输入错误,请重新输入"<<endl;
            else
                break;
        }
    }
    string book[10];
    int i;
    for(i=0;i<brbook_number;i++){
        cout<<"请输入第"<<i+1<<"本书书名:";
        cin>>book[i];
    }
    int n=0,flag;
    book_date book1,book2[10];//检测是否存在此书籍信息
    for(i=0;i<brbook_number;i++){
        flag=0;
        in.open("book.txt");
        while(in.peek()!=EOF){
            in>>book1;
            if(book1.get_book_name()==book[i]){
                in.close();book2[n]=book1;flag=1;++n;break;
            }
        }
        if(flag==0){
            in.close();
            cout<<"系统未找到此书籍,此书籍未收录"<<endl;
            cin.get();
        }
    }
    brbook_number=n;
    for(i=0;i<n;i++)
        book[i]=book2[i].get_book_name();
    cout<<"确认借阅以下书籍?(1:yes   2:no)"<<endl;
    int m;
    cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
    cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
    cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
    cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
    cout<<setw(10)<<"层数"<<"┃"<<endl;
    for(i=0;i<brbook_number;i++){
        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
        cout<<"┃"<<setw(10)<<book2[i].get_book_name()<<"┃"<<setw(10)<<book2[i].get_book_author()<<"┃";
        cout<<setw(10)<<book2[i].get_pubishing_company()<<"┃"<<setw(10)<<book2[i].get_ISBN()<<"┃";
        cout<<setw(4)<<book2[i].get_publishing_date().get_year()<<"."<<setw(2)<<book2[i].get_publishing_date().get_month();
        cout<<"."<<setw(2)<<book2[i].get_publishing_date().get_day()<<"┃";
        cout<<setw(10)<<book2[i].get_order()<<"┃"<<setw(10)<<book2[i].get_amount()<<"┃";
        cout<<setw(10)<<book2[i].get_classification()<<"┃"<<setw(10)<<book2[i].get_book_shelf()<<"┃";
        cout<<setw(10)<<book2[i].get_storey()<<"┃"<<endl;
    }
    cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n"<<endl;
    cin>>m;
    if(m==1){
        people person2;int flag2=0;
        in.open("brbook.txt");
        while(in.peek()!=EOF){
            in>>person2;flag2=0;
            if(person2.get_name()==person.get_name()){
                int j;
                for(j=0;j<person2.get_number();j++){
                    book[n]=person2.get_book_name(j);n++;
                }
                flag2=1;
            }
            if(flag2==1)
                break;
        }
        in.close();
        person.set_bbook_information(n,book);//如果用户不存在未归还的书籍信息
        if(flag2==1){
            out.open("brbook.txt",ios_base::app);
            out<<person;
            out.close();
        }//如果用户存在未归还的书籍信息
        else{
            in.open("brbook.txt");
            out.open("brbook1.txt",ios_base::app);
            while(in.peek()!=EOF){
                in>>person2;
                if(person2.get_name()==person.get_name())
                    out<<person;
                else
                    out<<person2;
            }
            in.close();out.close();
            char c;
            out.open("brbook.txt",ios::trunc);
            out.close();
            out.open("brbook.txt",ios_base::app);
            in.open("brbook1.txt");
            while(in.peek()!=EOF){
                in.get(c);
                out<<c;
            }
            out.close();
            in.close();
            out.open("brbook1.txt",ios::trunc);
            out.close();//将brbook1文件的内容清空
        }
        cout<<"借阅成功"<<endl;
        for(i=0;i<brbook_number;i++){//将借阅的书籍数量减1
            in.open("book.txt");
            out.open("book1.txt",ios_base::app);
            while(in.peek()!=EOF){
                in>>book1;
                if(book1.get_book_name()==book[i])
                    out<<book1;
                else{
                    book1.low_amount();
                    out<<book1;
                }
            }
        }
        in.close();out.close();
        char c;
        out.open("book.txt",ios::trunc);
        out.close();
        out.open("book.txt",ios_base::app);
        in.open("book1.txt");
        while(in.peek()!=EOF){
            in.get(c);
            out<<c;
        }
        out.close();
        in.close();
        out.open("book1.txt",ios::trunc);
        out.close();//将book1文件的内容清空
    }
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void return_book(people &person)
{
    system("cls");cin.get();
    system("title 归还书籍");
    int rbook_number;ifstream in;
    ofstream out;
    book_date book1;
    cout<<"请输入归还的书籍总数(不超过借阅书籍的总数):";
    cin>>rbook_number;
    string book[10];
    int i;
    for(i=0;i<rbook_number;i++){
        cout<<"请输入你归还的第"<<i+1<<"本书书名:";
        cin>>book[i];
    }
    int n=0;
    people person1;//检查是否是未归还的书籍
    for(i=0;i<rbook_number;i++){
        in.open("brbook.txt");int flag=0;
        while(in.peek()!=EOF){
            cin>>person1;
            if(person1.get_name()==person.get_name()){
                int j;
                for(j=0;j<person1.get_number();j++){
                    if(person1.get_book_name(j)==book[i]){
                        flag=1;n++;break;
                    }
                }
                if(flag==1){
                    in.close();break;
                }
                else{
                    cout<<"你未借阅"<<book[i]<<"此书籍"<<endl;
                    cin.get();in.close();break;
                }
            }
        }
    }
    rbook_number=n;
    out.open("rbook.txt");
    person.set_rbook_information(rbook_number,book);
    out<<person;
    out.close();//检测归还时间是否超过预定时间
    Time time1=person.get_brtime();
    Time time2=person.get_rtime();
    int time;
    time=time2-time1;
    if(time>30){
        cout<<"归还时间超过规定时间"<<endl;
        cout<<"你需要缴纳"<<0.1*(time-30)<<"元"<<endl;
        cin.get();
    }
    cout<<"归还成功"<<endl;
    for(i=0;i<rbook_number;i++){//将归还的书籍数量加1
        in.open("book.txt");
        out.open("book1.txt",ios_base::app);
        while(in.peek()!=EOF){
            in>>book1;
            if(book1.get_book_name()==book[i])
                out<<book1;
            else{
                book1.low_amount();
                out<<book1;
            }
        }
    }
    in.close();out.close();
    char c;
    out.open("book.txt",ios::trunc);
    out.close();
    out.open("book.txt",ios_base::app);
    in.open("book1.txt");
    while(in.peek()!=EOF){
        in.get(c);
        out<<c;
    }
    out.close();
    in.close();
    out.open("book1.txt",ios::trunc);
    out.close();//将book1文件的内容清空
    in.open("brbook.txt");//更改brbook.txt的借书信息
    out.open("brbook1.txt",ios_base::app);
    int j,k=0;string book3[10];
    while(in.peek()!=EOF){
        in>>person1;
        if(person1.get_name()==person.get_name()){
            for(i=0;i<person1.get_number();i++){
                int flag=0;
                for(j=0;j<person.get_number();j++){
                    if(person1.get_book_name(i)==person.get_book_name(j)){
                        flag=1;break;
                    }
                }
                if(flag==0){
                    book3[k]=person1.get_book_name(i);k++;
                }
            }//如果未全部归还
            if(k>0){
                person1.revise_brbook_infomation(k,book3);
                out<<person1;
            }
        }
        else{
            out<<person1;
        }
    }
    in.close();out.close();
    out.open("brbook.txt",ios::trunc);
    out.close();
    out.open("brbook.txt",ios_base::app);
    in.open("brbook1.txt");
    while(in.peek()!=EOF){
        in.get(c);
        out<<c;
    }
    out.close();
    in.close();
    out.open("brbook1.txt",ios::trunc);
    out.close();//将brbook1.txt文件的内容清空
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void count_book_information()
{
    system("cls");cin.get();
    system("title 统计书籍信息");
    ifstream in;int n,m;
    for(;;){
        system("cls");
        cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
        cout<<"\t\t\t\t│         图书管理借阅系统         │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│         1   统计总藏书           │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│         2   统计类别             │\n";
        cout<<"\t\t\t\t└──────────────────────────────────┘\n";
        cout<<"请输入你的选择:";cin>>n;
        if(n==1){
            int sum=0;int k;
            book_date book;
            in.open("book.txt");
            while(in.peek()!=EOF){
               in>>book;
               sum++;
            }
            in.close();sum--;
            cout<<"此图书馆共藏书"<<sum<<"册"<<endl;
            cout<<"是否继续浏览所有书籍信息?(1:yes    0:no):";
            cin>>k;
            if(k==1){
                cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
                cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
                cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
                cout<<setw(10)<<"层数"<<"┃"<<endl;
                in.open("book.txt");//此处预防最后一个换行符干扰文件操作
                while(in.peek()!=EOF&&sum){
                    in>>book;
                    cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                    cout<<"┃"<<setw(10)<<book.get_book_name()<<"┃"<<setw(10)<<book.get_book_author()<<"┃";
                    cout<<setw(10)<<book.get_pubishing_company()<<"┃"<<setw(10)<<book.get_ISBN()<<"┃";
                    cout<<setw(4)<<book.get_publishing_date().get_year()<<"."<<setw(2)<<book.get_publishing_date().get_month();
                    cout<<"."<<setw(2)<<book.get_publishing_date().get_day()<<"┃";
                    cout<<setw(10)<<book.get_order()<<"┃"<<setw(10)<<book.get_amount()<<"┃";
                    cout<<setw(10)<<book.get_classification()<<"┃"<<setw(10)<<book.get_book_shelf()<<"┃";
                    cout<<setw(10)<<book.get_storey()<<"┃"<<endl;
                    sum--;
                }
                in.close();
               cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
            }
        }
        else if(n==2){
            map<string,int>mymap;
            in.open("book.txt");//用map录入书籍类别
            book_date book;int j=1;//map可以将相同的key值(即使value的值不同)忽略掉
            while(in.peek()!=EOF){//即关键字不会重复出现
                in>>book;//这样就保证了统计时不会出现两个相同的类别
                mymap.insert(pair<string,int>(book.get_classification(),1));
            }//且时间复杂度为O(1);
            in.close();//同时map也更好操作
            auto it=mymap.begin();//唯一的缺点是用到了C++11的迭代器
            int sum=0;//必须用支持C++11的编译器编译
            for(it;it!=mymap.end();it++){
                sum++;
                it->second=j;j++;
            }
            cout<<"共收集"<<sum<<"种书籍"<<endl;
            int k,w;
            it=mymap.begin();
            cout<<"是否查询相关类别的书籍?(1:yes  0:no):";cin>>k;
            if(k==1){
                cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
                cout<<"\t\t\t\t│         书籍类别查询选择         │\n";
                for(it;it!=mymap.end();it++){
                    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                    cout<<"\t\t\t\t│        "<<setw(2)<<it->second<<":"<<setw(10)<<it->first<<"             "<<"│\n";
                }
                cout<<"\t\t\t\t└──────────────────────────────────┘\n";
                cout<<"请输入你的选择:";cin>>w;
                int flag=0;it=mymap.begin();
                for(it;it!=mymap.end();it++){
                    if(it->second==w){
                        flag=1;break;
                    }
                }
                if(flag==1){
                    in.open("book.txt");
                    cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                    cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
                    cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
                    cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
                    cout<<setw(10)<<"层数"<<"┃"<<endl;
                    while(in.peek()!=EOF){
                        in>>book;
                        if(book.get_classification()==it->first){
                            cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                            cout<<"┃"<<setw(10)<<book.get_book_name()<<"┃"<<setw(10)<<book.get_book_author()<<"┃";
                            cout<<setw(10)<<book.get_pubishing_company()<<"┃"<<setw(10)<<book.get_ISBN()<<"┃";
                            cout<<setw(4)<<book.get_publishing_date().get_year()<<"."<<setw(2)<<book.get_publishing_date().get_month();
                            cout<<"."<<setw(2)<<book.get_publishing_date().get_day()<<"┃";
                            cout<<setw(10)<<book.get_order()<<"┃"<<setw(10)<<book.get_amount()<<"┃";
                            cout<<setw(10)<<book.get_classification()<<"┃"<<setw(10)<<book.get_book_shelf()<<"┃";
                            cout<<setw(10)<<book.get_storey()<<"┃"<<endl;
                        }
                    }
                    in.close();
                    cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
                }
                else
                    cout<<"选择错误"<<endl;
            }
        }
        else{
            cout<<"选择错误"<<endl;
        }
        cout<<"是否继续统计?(1:yes    0:no):";
        cin>>m;
        if(m==0)
            break;
    }
    cin.get();
}
void check_borrow_return_information()
{
    system("cls");cin.get();
    system("title 查询借阅信息");
    people person;int i;
    ifstream in;int n,m;//m表示选选项,n表示是否继续
    for(;;){
        cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
        cout<<"\t\t\t\t│              查找选项            │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│        1   按借阅人查询          │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│        2   按借阅书籍查询        │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│        3   按借阅时间查询        │\n";
        cout<<"\t\t\t\t├──────────────────────────────────┤\n";
        cout<<"\t\t\t\t│        4   按是否归还查询        │\n";
        cout<<"\t\t\t\t└──────────────────────────────────┘\n";
        cin>>m;
        if(m==1){
            system("cls");
            string brbook_name;
            cout<<"请输入借阅人的姓名:"<<endl;cin>>brbook_name;
            in.open("brbook.txt");
            int flag=0;
            while(in.peek()!=EOF){
                in>>person;
                if(person.get_name()==brbook_name){
                    flag=1;break;
                }
            }
            in.close();
            int flag1=0;
            if(flag==0){
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;
                    if(person.get_name()==brbook_name){
                        flag1=1;break;
                    }
                }
            }
            in.close();
            if(flag==0&&flag1==0){
                cout<<"无此人的任何借阅信息"<<endl;
            }
            else{
                in.open("brbook.txt");
                cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"姓名"<<"┃"<<setw(10)<<"借书书名"<<"┃"<<setw(10)<<"借阅时间"<<"┃";
                cout<<setw(10)<<"归还时间"<<"┃"<<setw(10)<<"是否归还"<<"┃"<<endl;
                while(in.peek()!=EOF){
                    in>>person;
                    if(person.get_name()==brbook_name){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(10)<<person.get_book_name(0);
                        cout<<"┃"<<setw(4)<<person.get_brtime().get_year()<<"."<<setw(2)<<person.get_brtime().get_month();
                        cout<<"."<<setw(2)<<person.get_brtime().get_day()<<"┃"<<setw(10)<<" "<<"┃";
                        cout<<setw(10)<<"未归还"<<"┃"<<endl;
                        for(i=1;i<person.get_number();i++){
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<person.get_book_name(i);
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<endl;
                        }
                    }
                }
                in.close();
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;
                    if(person.get_name()==brbook_name){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(10)<<person.get_book_name(0);
                        cout<<"┃"<<setw(4)<<person.get_brtime().get_year()<<"."<<setw(2)<<person.get_brtime().get_month();
              cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"姓名"<<"┃"<<setw(10)<<"借书书名"<<"┃"<<setw(10)<<"借阅时间"<<"┃";
                cout<<setw(10)<<"归还时间"<<"┃"<<setw(10)<<"是否归还"<<"┃"<<endl;          cout<<"."<<setw(2)<<person.get_brtime().get_day()<<"┃";
                        cout<<setw(4)<<person.get_rtime().get_year()<<"."<<setw(2)<<person.get_rtime().get_month();
                        cout<<"."<<setw(2)<<person.get_rtime().get_day()<"┃";
                        cout<<setw(10)<<"已归还"<<"┃"<<endl;
                        for(i=1;i<person.get_number();i++){
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<person.get_book_name(i);
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<endl;
                        }
                    }
                }
                in.close();
                cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
            }
        }//按借阅书籍查询
        else if(m==2){
            system("cls");
            string book_name1;
            people person;int i;
            cout<<"请输入需要查询的书籍名称:";cin>>book_name1;
            in.open("brbook.txt");
            int flag=0;
            while(in.peek()!=EOF){
                in>>person;
                if(person.get_name()==book_name1){
                    flag=1;break;
                }
            }
            in.close();
            int flag1=0;
            if(flag==0){
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;
                    if(person.get_name()==book_name1){
                        flag1=1;break;
                    }
                }
            }
            in.close();int flag2;
            if(flag==0&&flag1==0){
                cout<<"无此书籍的任何借阅信息"<<endl;
            }
            else{
                cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"借阅人"<<"┃"<<setw(10)<<"借阅时间"<<"┃";
                cout<<setw(10)<<"归还时间"<<"┃"<<setw(10)<<"是否归还"<<"┃"<<endl;
                in.open("brbook.txt");
                while(in.peek()!=EOF){
                    in>>person;flag2=0;
                    for(i=0;i<person.get_number();i++){
                        if(person.get_book_name(i)==book_name1){
                            flag2=1;break;
                        }
                    }
                    if(flag2==1){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(4)<<person.get_brtime().get_year();
                        cout<<"."<<setw(2)<<person.get_brtime().get_month()<<".";
                        cout<<setw(2)<<person.get_brtime().get_day()<<"┃"<<setw(10)<<" "<<"┃";
                        cout<<setw(10)<<"未归还"<<endl;
                    }
                }
                in.close();
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;flag2=0;
                    for(i=0;i<person.get_number();i++){
                        if(person.get_book_name(i)==book_name1){
                            flag2=1;break;
                        }
                    }
                    if(flag2==1){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(4)<<person.get_brtime().get_year();
                        cout<<"."<<setw(2)<<person.get_brtime().get_month()<<".";
                        cout<<setw(2)<<person.get_brtime().get_day()<<"┃";
                        cout<<setw(4)<<person.get_rtime().get_year()<<"."<<setw(2)<<person.get_rtime().get_month();
                        cout<<"."<<setw(2)<<person.get_rtime().get_day()<<"┃"<<setw(10)<<"已归还"<<"┃"<<endl;
                    }
                }
                in.close();
                cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
            }
        }
        else if(m==3){
            system("cls");
            int year1,month1,day1,year2,month2,day2;
            for(;;){
                cout<<"请输入查询的起始时间(按年月日依次输入,中间用空格分开):";
                cin>>year1>>month1>>day1;
                if(!check_time(year1,month1,day1))
                    cout<<"日期输入错误,请重新输入"<<endl;
                else
                    break;
            }
            for(;;){
                cout<<"请输入查询的截止时间(按年月日依次输入,中间用空格分开):";
                cin>>year2>>month2>>day2;
                if(!check_time(year2,month2,day2))
                    cout<<"日期输入错误,请重新输入"<<endl;
                else
                    break;
            }
            Time time1,time2;
            time1.set_time(year1,month1,day1);
            time2.set_time(year2,month2,day2);
            int time_date=time2-time1;
            in.open("brbook.txt");
            int flag=0;
            while(in.peek()!=EOF){
                in>>person;
                Time time3=person.get_brtime();
                int time_date2=time3-time1;
                if(time_date2<=time_date){
                    flag=1;break;
                }
            }
            in.close();
            int flag1=0;
            if(flag==0){
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;
                    Time time3=person.get_brtime();
                    int time_date2=time3-time1;
                    if(time_date2<=time_date){
                        flag1=1;break;
                    }
                }
            }
            in.close();
            if(flag==0&&flag1==0){
                cout<<"此时间段任何借阅信息"<<endl;
            }
            else{
                in.open("brbook.txt");
                cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"姓名"<<"┃"<<setw(10)<<"借书书名"<<"┃"<<setw(10)<<"借阅时间"<<"┃";
                cout<<setw(10)<<"归还时间"<<"┃"<<setw(10)<<"是否归还"<<"┃"<<endl;
                while(in.peek()!=EOF){
                    in>>person;
                    Time time3=person.get_brtime();
                    int time_date1=time3-time1;
                    if(time_date1<=time_date){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(10)<<person.get_book_name(0);
                        cout<<"┃"<<setw(4)<<person.get_brtime().get_year()<<"."<<setw(2)<<person.get_brtime().get_month();
                        cout<<"."<<setw(2)<<person.get_brtime().get_day()<<"┃"<<setw(10)<<" "<<"┃";
                        cout<<setw(10)<<"未归还"<<"┃"<<endl;
                        for(i=1;i<person.get_number();i++){
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<person.get_book_name(i);
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<endl;
                        }
                    }
                }
                in.close();
                in.open("rbook.txt");
                while(in.peek()!=EOF){
                    in>>person;
                    Time time3=person.get_brtime();
                    int time_date1=time3-time1;
                    if(time_date1<=time_date){
                        cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                        cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(10)<<person.get_book_name(0);
                        cout<<"┃"<<setw(4)<<person.get_brtime().get_year()<<"."<<setw(2)<<person.get_brtime().get_month();
                        cout<<"."<<setw(2)<<person.get_brtime().get_day()<<"┃";
                        cout<<setw(4)<<person.get_rtime().get_year()<<"."<<setw(2)<<person.get_rtime().get_month();
                        cout<<"."<<setw(2)<<person.get_rtime().get_day()<"┃";
                        cout<<setw(10)<<"已归还"<<"┃"<<endl;
                        for(i=1;i<person.get_number();i++){
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<person.get_book_name(i);
                            cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<" "<<"┃"<<endl;
                        }
                    }
                }
                in.close();
                cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
            }
        }
        else if(m==4){
            system("cls");
            in.open("rbook.txt");
            if(!in||in.eof()){
                cout<<"无任何借阅信息"<<endl;
                cin.get();
            }
            else{
                cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
                cout<<"┃"<<setw(10)<<"姓名"<<"┃"<<setw(10)<<"借书书名"<<"┃"<<setw(10)<<"借阅时间"<<"┃"<<endl;
                while(in.peek()!=EOF){
                    in>>person;
                    cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
                    cout<<"┃"<<setw(10)<<person.get_name()<<"┃"<<setw(10)<<person.get_book_name(0);
                    cout<<"┃"<<setw(4)<<person.get_brtime().get_year()<<"."<<setw(2)<<person.get_brtime().get_month();
                    cout<<"."<<setw(2)<<person.get_brtime().get_day()<<"┃"<<endl;
                    for(i=1;i<person.get_number();i++){
                        cout<<"┃"<<setw(10)<<" "<<"┃"<<setw(10)<<person.get_book_name(i);
                        cout<<setw(10)<<" "<<"┃"<<endl;
                    }
                }
                in.close();
                cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛"<<endl;
            }
        }
        else{
            cout<<"选择错误"<<endl;cin.get();
        }
        cout<<"是否继续查询?(1:yes   0:no)"<<endl;
        cin>>n;
        if(n==0)
            break;
    }
    cin.get();
}
void revise_personal_information(people &person)
{
    system("cls");cin.get();
    system("title 修改个人信息");
    cout<<"你的个人信息如下(不包括密码)"<<endl;
    person.show_people();
    int n;
    cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
    cout<<"\t\t\t\t│              修改选项            │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│        1   修改姓名              │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│        2   修改电话号码          │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│        3   修改密码              │\n";
    cout<<"\t\t\t\t├──────────────────────────────────┤\n";
    cout<<"\t\t\t\t│        4   返回主菜单            │\n";
    cout<<"\t\t\t\t└──────────────────────────────────┘\n";
    cout<<"请输入你的选择:";cin>>n;
    if(n==1){
        person.revise_people_name();
    }
    else if(n==2){
        person.revise_phone_number();
    }
    else if(n==3){
        string password1,id,password2,password3,password4;
        ifstream in;ofstream out;
        in.open("password.txt");
        while(in.peek()!=EOF){
            in>>id>>password2;
            if(id==person.get_id()){
                in.close();break;
            }
        }
        int i;
        for(i=0;i<3;i++){
            cout<<"请输入原密码:";
            char s[21];int j=0;
            while((s[j]=getch())!=13&&j!=20){
                putch('*');
                j++;
            }
            s[j]='\0';
            password1=s;
            int n;
            if(password1==password2){
                for(;;){
                    cout<<"请输入新密码:";
                    char s1[21];int j=0;
                    while((s1[j]=getch())!=13&&j!=20){
                        putch('*');
                        j++;
                    }
                    s1[j]='\0';
                    password3=s1;
                    cout<<"请再次确认新密码:";
                    char s2[21];
                    j=0;
                    while((s2[j]=getch())!=13&&j!=20){
                        putch('*');
                        j++;
                    }
                    s2[j]='\0';
                    password4=s2;
                    if(password3==password4)
                        break;
                    else{
                        cout<<"两次密码不同,请重新输入"<<endl;
                    }
                }
            cout<<"确认将密码修改为:"<<password3<<"?(1:yes   2:no)"<<endl;
            cin>>n;
            if(n==1){
                in.open("password.txt");
                out.open("password1.txt",ios_base::app);
                while(in.peek()!=EOF){
                    in>>id>>password1;
                    if(id==person.get_id())
                        out<<id<<" "<<password3<<"\n";
                    else
                        out<<id<<" "<<password1<<"\n";
                }
                in.close();
                out.close();//将password1.txt文件中的内容负“复制”到password.txt
                out.open("password.txt",ios::trunc);
                out.close();
                out.open("password.txt",ios_base::app);
                in.open("password1.txt");
                char c;
                while(in.peek()!=EOF){
                    in.get(c);
                    out<<c;
                }
                out.close();
                in.close();
                out.open("password1.txt",ios::trunc);
                out.close();//将password1文件的内容清空
            }
        }
        else{
            if(i<2)
                cout<<"原密码输入错误,请重新输入"<<endl;
        }
    }
    if(i==3){
        cout<<"你已连续三次输入密码错误,不能继续修改密码"<<endl;
    }
    else
        cout<<"密码修改成功"<<endl;
    }
    else if(n==4){
        return;
    }
    else
        cout<<"选择错误"<<endl;
    if(n==1&&n==2){
        ifstream in;ofstream out;
        string id1,name1,phone_number1,id_number1;
        in.open("student.txt");
        out.open("student1.txt",ios_base::app);
        while(in.peek()!=EOF){
            in>>id1>>name1>>phone_number1>>id_number1;
            if(person.get_id()==id1)
                out<<person;
            else
                out<<id1<<" "<<name1<<" "<<phone_number1<<" "<<id_number1<<"\n";
        }
        in.close();
        out.close();
        out.open("student.txt",ios::trunc);
        out.close();
        out.open("student.txt",ios_base::app);
        in.open("student1.txt");
        char c;
        while(in.peek()!=EOF){
            in.get(c);
            out<<c;
        }
        out.close();
        in.close();
        out.open("student1.txt",ios::trunc);
        out.close();//将student1文件的内容清空
    }
    cin.get();
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
void revise_book_information()
{
    system("cls");cin.get();
    system("title 修改书籍信息");
    ifstream in,ine;ofstream out;
    int n;
    string book_name1;
    book_date book;
    for(;;){
        system("cls");
        cout<<"请输入你想修改信息的书籍名:";cin>>book_name1;
        ine.open("book.txt");int flag=0;
        while(ine.peek()!=EOF){
            ine>>book;
            if(book.get_book_name()==book_name1){
                flag=1;ine.close();break;
            }
        }
        int m,choice;
        if(flag==1){
            cout<<"确认修改以下书籍的相关信息?(1:yes  0:no)"<<endl;
            cout<<"┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓"<<endl;
            cout<<"┃"<<setw(10)<<"书名"<<"┃"<<setw(10)<<"作者"<<"┃"<<setw(10)<<"出版社"<<"┃";
            cout<<setw(10)<<"ISBN"<<"┃"<<setw(10)<<"出版时间"<<"┃"<<setw(10)<<"版次"<<"┃";
            cout<<setw(10)<<"数量"<<"┃"<<setw(10)<<"类别"<<"┃"<<setw(10)<<"书架数"<<"┃";
            cout<<setw(10)<<"层数"<<"┃"<<endl;
            cout<<"┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫"<<endl;
            cout<<"┃"<<setw(10)<<book.get_book_name()<<"┃"<<setw(10)<<book.get_book_author()<<"┃";
            cout<<setw(10)<<book.get_pubishing_company()<<"┃"<<setw(10)<<book.get_ISBN()<<"┃";
            cout<<setw(4)<<book.get_publishing_date().get_year()<<"."<<setw(2)<<book.get_publishing_date().get_month();
            cout<<"."<<setw(2)<<book.get_publishing_date().get_day()<<"┃";
            cout<<setw(10)<<book.get_order()<<"┃"<<setw(10)<<book.get_amount()<<"┃";
            cout<<setw(10)<<book.get_classification()<<"┃"<<setw(10)<<book.get_book_shelf()<<"┃";
            cout<<setw(10)<<book.get_storey()<<"┃"<<endl;
            cout<<"┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n"<<endl;
            cin>>m;
            if(m==1){
                system("cls");
                cout<<"\t\t\t\t┌──────────────────────────────────┐\n";
                cout<<"\t\t\t\t│      请选择你想要修改的内容      │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              1   书名            │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              2   作者            │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              3   ISBN号          │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              4   出版社          │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              5   出版时间        │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              6   版次            │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              7   数量            │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              8   类别            │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              9   书架数          │\n";
                cout<<"\t\t\t\t├──────────────────────────────────┤\n";
                cout<<"\t\t\t\t│              10  层数            │\n";
                cout<<"\t\t\t\t└──────────────────────────────────┘\n";
                cin>>choice;
                switch(n){
                    case 1:book.revise_name();
                    case 2:book.revise_author();
                    case 3:book.revise_ISBN();
                    case 4:book.revise_publishing_company();
                    case 5:book.revise_publishing_date();
                    case 6:book.revise_order();
                    case 7:book.revise_amount();
                    case 8:book.revise_classification();
                    case 9:book.revise_book_shelf();
                    case 10:book.revise_storey();
                    default:cout<<"选择错误"<<endl;break;
                }
                in.open("book.txt");
                book_date book1;
                out.open("book1.txt",ios_base::app);
                while(in.peek()!=EOF){
                    cin>>book1;
                    if(book1.get_book_name()!=book.get_book_name())
                        out<<book1;
                    else
                        out<<book;
                }
                in.close();
                out.close();
                out.open("book.txt",ios::trunc);
                out.close();
                out.open("book.txt",ios_base::app);
                in.open("book1.txt");
                char c;
                while(in.peek()!=EOF){
                    in.get(c);
                    out<<c;
                }
                out.close();
                in.close();
                out.open("book1.txt",ios::trunc);
                out.close();//将book1文件的内容清空
                cout<<"修改成功"<<endl;
                cin.get();
            }
        }
        else{
            ine.close();
            cout<<"未找到此书籍信息"<<endl;
            cout<<"请确认书籍信息是否输入正确"<<endl;cin.get();
        }
        cout<<"是否继续修改?(1:yes   2:no)"<<endl;
        cin>>n;
        if(n==0)
            break;
    }
    cout<<"按任意键返回主菜单"<<endl;
    cin.get();
}
