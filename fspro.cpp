#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<regex>


using namespace std;
class employee
{
        public: string ssn;
                string name;
                string email;
                string mob;
                string desig;
                int count;
                int length=0;
                int n=0;
                string ssn_list[1000];
                int add_list[1000];
                string buffer;
                int iter;
                
                void read_data();
                void pack();
                void write_to_file();
                void create_index();
                int remove(string);
                void search(string);
                int search_index(string);
                string extract_ssn();
                void sort_index();
                void modify(string);
                
};
void employee::read_data()
{
        int valid1,valid2,valid3,valid4,valid5;
        regex a("[a-zA-Z]*");
        regex b("e[0-9]*");
        regex c("[a-zA-Z0-9]*@[a-zA-Z]*.[a-zA-Z]*");
        regex d("[0-9]{10}");
        regex f("[a-zA-Z]*");
        cout<<"________________________________________________________"<<endl;
        cout<<"__                                                    __"<<endl;
        while(valid1!=1)
        {
                valid1=1;
                cout<<"SSN:";
                cin>>ssn;
                if(!regex_match(ssn,b))
                {
                        cout<<"Invalid Input for SSN. Please try once again :)"<<endl;
                        valid1=0;
                }
        }
        
        while(valid2!=1)
        {
                valid2=1;
                cout<<"Name:";
                cin>>name;
                if(!regex_match(name,a))
                {
                        cout<<"Invalid input for Name. Please try once again :)"<<endl;
                        valid2=0;
                }
         }
                
        while(valid3!=1)
        {
                valid3=1;
                cout<<"Email Address:";
                cin>>email;
                if(!regex_match(email,c))
                {
                        cout<<"Invalid email. Please try once again :)"<<endl;
                        valid3=0;
                }
        }
        while(valid4!=1)
        {
        valid4=1;
        cout<<"Mobile Number:";
        cin>>mob;
        if(!regex_match(mob,d))
        {
                cout<<"Invalid Mobile Number. Please try once again :)"<<endl;
                valid4=0;
        }
        }
        
        while(valid5!=1)
        {
                valid5=1; 
                cout<<"Designation:";
                cin>>desig;
                if(regex_match(desig,f))
                {
                        cout<<"Invalid input for designation. Please try again :)"<<endl;
                        valid5=0;
                }
        }
        cout<<"__                                                    __"<<endl;
        cout<<"________________________________________________________"<<endl;
        
}

void employee::pack()
{
        buffer.erase();
        buffer=ssn+"|"+name+"|"+email+"|"+mob+"|"+desig+"$\n";
}

void employee::write_to_file()
{
        int pos;
        fstream file;
        file.open("emp.txt",ios::out|ios::app);
        pos=file.tellp();
        file<<buffer;
        ssn_list[++count]=ssn;
        add_list[count]=pos;
        sort_index();
        file.close();
}

void employee::create_index()
{
        
        fstream file;
        int pos; string ssn;
        count=-1;
        file.open("emp.txt",ios::in);
        while(!file.eof())
        {
                pos=file.tellg();
                
                buffer.erase();
                getline(file,buffer);
                if(buffer[0]=='*'){
                        count++;
                }
                else if(buffer[0]!='*')
                {
                       if(buffer.empty())break;
                        ssn=extract_ssn();
                        ssn_list[++count]=ssn;
                        add_list[count]=pos;
                }
                buffer.erase();
        }
                
        file.close();
        sort_index();
        
}


string employee::extract_ssn()
{
        string ssn;
        int i=0;
        ssn.erase();
        while(buffer[i]!='|')
                ssn+=buffer[i++];
        return ssn;
}

void employee::sort_index()
{
        int i,j,temp_Address;
        string temp_ssn;
        for(int i=0;i<=count;i++)
        {
                for(int j=i+1;j<=count;j++)
                {
                        if(ssn_list[i]>ssn_list[j])
                        {
                                temp_ssn=ssn_list[i];      
                                ssn_list[i]=ssn_list[j];
                                ssn_list[j]=temp_ssn;
                                temp_Address=add_list[i];
                                add_list[i]=add_list[j];
                                add_list[j]=temp_Address;
                        }
                }
        }
}  


int employee::search_index(string key)
{
       int low=0,high=count,mid=0,flag=0,pos;
        
        iter=0;
        while(low<=high)
        {
                mid=(low+high)/2;
                if(ssn_list[mid]==key)
                {
                        flag=1;
                        break;
                 }
                 else if(ssn_list[low]==key)
                 {
                        flag=2;
                        break;
                        
                 }
                 else if(ssn_list[high]==key)
                 {
                        flag=3;
                        break;
                 }
                else if(ssn_list[mid]>key)
                {
                        high=mid-1;
                        low++;
                }
                
                else if(ssn_list[mid]<key)
                {
                        low=mid+1;
                        high--;
                }
                else return -1;
                iter++;
        }
        if(flag==1)
        {
                return mid;
        }
        else if(flag==2)
        {
                return low;
        }
        else if(flag==3)
        {
                return high;
        }
        else
        {
                return -1;
        }
        
        
}

void employee::search(string key)
{
        int pos,address; 
        fstream file; 
        buffer.erase();
        pos=search_index(key);
        if(pos==-1)
        {       
                cout<<"________________________________________________________"<<endl;
                cout<<"__                                                    __"<<endl;
                cout << endl << "record not found" << endl;
                cout<<"__                                                    __"<<endl;
                cout<<"________________________________________________________"<<endl;
        }
        else if(pos>=0)
        {
                buffer.erase();
                file.open("emp.txt");
                address=add_list[pos];
                file.seekp(address,ios::beg);
                getline(file,buffer);
                cout<<"________________________________________________________"<<endl;
                cout<<"__                                                    __"<<endl;
                cout<<"\nrecord found....\n"<<buffer<<endl;
                cout<<"__                                                    __"<<endl;
                cout<<"________________________________________________________"<<endl;
                cout<<"__                                                    __"<<endl;
                cout<<"Number of iterations = "<<iter<<endl;
                cout<<"__                                                    __"<<endl;
                cout<<"________________________________________________________"<<endl;
                file.close();
        }
}

int employee::remove(string key)
{
        int pos=0,i,address;
        fstream file;
        pos=search_index(key);
        if(pos>=0)
        {
                file.open("emp.txt",ios::out|ios::in);
                address=add_list[pos];
                file.seekp(address,ios::beg);
                file.put('*');
                file.close();
                cout<<"________________________________________________________"<<endl;
                cout<<"__                                                    __"<<endl;
                cout << endl << "record Deleted" << endl;
                cout<<"__                                                    __"<<endl;
                cout<<"________________________________________________________"<<endl;
                for(i=pos;i<count;i++)
                {
                ssn_list[i]=ssn_list[i+1];
                add_list[i]=add_list[i+1];
                }
                count--;
                return 1;
        }
        else
        {
                 cout<<"________________________________________________________"<<endl;
                cout<<"__                                                    __"<<endl;
                cout << endl << "record not found" << endl;
                cout<<"__                                                    __"<<endl;
                cout<<"________________________________________________________"<<endl;
                return 0;
        }
}


void employee::modify(string key)
{
        int valid5,valid2,valid3,valid4;
        regex a("[a-zA-Z]*");
        regex c("[a-zA-Z0-9]*@[a-zA-Z]*.[a-zA-Z]*");
        regex d("[0-9]{10}");
        regex f("[a-zA-Z]*");
        if(remove(key))
        {
        
        cout<<"________________________________________________________"<<endl;
        cout<<"__                                                    __"<<endl;
        ssn=key;
                while(valid2!=1)
        {
                valid2=1;
                cout<<"Name:";
                cin>>name;
                if(!regex_match(name,a))
                {
                        cout<<"Invalid input for Name. Please try once again :)"<<endl;
                        valid2=0;
                }
         }
                
        while(valid3!=1)
        {
                valid3=1;
                cout<<"Email Address:";
                cin>>email;
                if(!regex_match(email,c))
                {
                        cout<<"Invalid email. Please try once again :)"<<endl;
                        valid3=0;
                }
        }
        while(valid4!=1)
        {
        valid4=1;
        cout<<"Mobile Number:";
        cin>>mob;
        if(!regex_match(mob,d))
        {
                cout<<"Invalid Mobile Number. Please try once again :)"<<endl;
                valid4=0;
        }
        }
        
        while(valid5!=1)
        {
                valid5=1; 
                cout<<"Designation:";
                cin>>desig;
                if(regex_match(desig,f))
                {
                        cout<<"Invalid input for designation. Please try again :)"<<endl;
                        valid5=0;
                }
        }
        cout<<"__                                                    __"<<endl;
        cout<<"________________________________________________________"<<endl;
        
        

                pack();
                write_to_file();
        }
}

int main()
{
        int choice,
        count1,i;
        string key;
        employee s1;
        s1.create_index();
             cout<<"________________________________________________________"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                        ADMIN                       __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                    EMPLOYEE DATA                   __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"________________________________________________________"<<endl;
        while(1)
        {
             cout<<"________________________________________________________"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                1.ADD EMPLYOEE                      __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                2.SEARCH EMPLOYEE                   __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                3.DELETE EMPLOYEE                   __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                4. Modify                           __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                5. Exit                             __"<<endl;
             cout<<"________________________________________________________"<<endl;
                cout<<"Enter the choice:";
                cin>>choice;
                switch(choice)
                {
                case 1: cout<<"\nhow many records to insert\n";
                cin>>count1;
                for(i=0;i<count1;i++)
                {
                        cout<<"data\n";
                        s1.read_data();
                        s1.pack();
                        s1.write_to_file();
                }
                break;
                case 2: 
                cout<<"\nEnter the ssn\n"; 
                cin>>key;
                s1.search(key);
                break;
                case 3:cout<<"\n\nEnter the ssn\n";
                cin>>key;
                s1.remove(key);
                break;
                case 4:cout<<"Enter key:";
                cin>>key;
                s1.modify(key);
                break;
                case 5: return 0;
                
                default:cout<<"\n\nWrong choice\n"; 
                
                }
        }
}

