#include<iostream>
#include<iomanip>
using namespace std;
struct people{
  int number;
  int year;
  int month;
  int day;
  char name[11];
  char ID[20]; //身份证号码
  struct people *next;
};
typedef struct people people;
people *create_NULL_link_list(); //创建一个空链表
people *create_link_list(people *head); //创建一个完整的链表
void show_link_list(people *head);
people *addinformation_in_link_list(people *head); //添加人民信息
people *delpeopleinformation_in_link_list(people *head);//删除人民信息
int main()
{
  people *head;
  head=create_NULL_link_list();
  head=create_link_list(head);
  show_link_list(head);
  /*cout<<"增加人民信息"<<endl;
  head=addinformation_in_link_list(head);
  show_link_list(head);*/
  cout<<"删除人民信息"<<endl;
  delpeopleinformation_in_link_list(head);
  show_link_list(head);
  return 0;
}
people *create_NULL_link_list()
{
  people *head;
  head=new people;
  head->next=NULL;
  return head;
}
people *create_link_list(people *head)
{
  people *p1,*p2; 
  char ch='y';
  p2=head;
  while(ch=='y'||ch=='Y'){
	p1=new people;
	cout<<"请输入人民序号;";cin>>p1->number;
    cout<<"请输入姓名:";cin>>p1->name;
	cout<<"请输入身份证号码:";cin>>p1->ID;
	cout<<"请输入出身年月日:";cin>>p1->year>>p1->month>>p1->day;
	p2->next=p1;
	p2=p1;
	cout<<"DO YOU WANT TO CONTINUE?(Y/N)";cin>>ch;
  }
  p2->next=NULL; 
  return head;
}
void show_link_list(people *head)
{
  people *p;
  p=head;
  if(head->next==NULL)
	  cout<<"信息尚未录入"<<endl;
  else{
	  cout<<setw(10)<<"序号"<<setw(10)<<"姓名"<<setw(10)<<"证件号";
	  cout<<setw(10)<<"年"<<setw(10)<<"月"<<setw(10)<<"日"<<endl;
     while(p->next!=NULL){
		 p=p->next;
         cout<<setw(10)<<p->number<<setw(10)<<p->name<<setw(10)<<p->ID;
		 cout<<setw(10)<<p->year<<setw(10)<<p->month<<setw(10)<<p->day<<endl;	     
	   }
  }
}
people *addinformation_in_link_list(people *head)
{
  people *p0,*p1,*p2;
  p1=new people;
  cout<<"请输入人民序号;";cin>>p1->number;
  cout<<"请输入姓名:";cin>>p1->name;
  cout<<"请输入身份证号码:";cin>>p1->ID;
  cout<<"请输入出身年月日:";cin>>p1->year>>p1->month>>p1->day;
  p0=head->next;
  if(p0->number>p1->number){
	  head->next=p1;
	  p1->next=p0;
  }
  else{
	  while(p0->number<=p1->number&&p0->next!=NULL){
	    p2=p0;p0=p0->next;
	  }
	  if(p0->number>p1->number){
	    p2->next=p1;p1->next=p0;
	  }
	  else{
	    p0->next=p1;p1->next=NULL;
	  }
  }
  return head;
}
people *delpeopleinformation_in_link_list(people *head)
{
	if(head->next==NULL){
	  cout<<"无人民信息,无法执行此操作"<<endl;
	}
	else{
       people *p1,*p2;
	   char a[11];
       cout<<"请输入你想删除的人民姓名:";cin>>a;
       p1=head->next;
	   if(strcmp(p1->name,a)==0){  //删除点为头结点
	     head->next=p1->next;
		 delete p1;  //释放p1指向的内存空间
		 cout<<"删除成功"<<endl;
	   }
	   else{
           while(strcmp(p1->name,a)!=0&&p1->next!=NULL){
             p2=p1;p1=p1->next;
		   }
           if(strcmp(p1->name,a)==0){
              if(p1->next==NULL) //删除点末结点
                  p2->next=NULL;
			  else
				  p2->next=p1->next;
			  delete p1;
			  cout<<"删除成功"<<endl;
		   }
           else
             cout<<"未找到此人,无法执行删除操作"<<endl;
	   }
	   }
    return head;
}
//未完成