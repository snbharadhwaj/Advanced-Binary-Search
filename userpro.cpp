#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
using namespace std;
class employee
{
        public: string ssn;
                string name;
                string email;
                string mob;
                string desig;
                int count;
                string ssn_list[1000];
                int add_list[1000];
                string buffer;
                int iter;
                
               
                void create_index();
                void search(string);
                int search_index(string);
                string extract_ssn();
                void sort_index();
                
};

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
       int low=1,high=count,mid=0,flag=0,pos;
       
        iter=0;
        
        while(low<=high)
        {
                
                
                mid=(low+high)/2;
                if(ssn_list[mid]==key)
                {
                        flag=1;
                        break;
                 }
                 
                else if(ssn_list[mid]>key)
                {
                        high=mid-1;
                        
                }
                else if(ssn_list[mid]<key)
                {
                        low=mid+1;
                        
                }
                else return -1;
                iter++;
                
        }
        
        if(flag==1)
        {
                return mid;
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
        cout << endl << "record not found" << endl;
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


int main()
{
        int choice=1;
        
        string key;
        employee s1;
        s1.create_index();
         
        while(choice)
        {
             cout<<"________________________________________________________"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                     USER VIEW                      __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"__                                                    __"<<endl;
             cout<<"________________________________________________________"<<endl;
             cout<<"\n \n \n";
             cout<<"Enter the SSN to be searched: ";
             cin>>key;
             cout<<"\n \n";
             s1.search(key);
             cout<<"\n \n";
             cout<<"Enter 1 to search 0 to exit";
             cin>>choice;
        }
        return 0;
}




























