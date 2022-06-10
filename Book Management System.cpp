#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class Book{
	int id;
	char name[20];
	float price;
	public:
		
	Book(){
		id=0;
		strcpy(name, "No title");
		price=0;
	}
	
	void setdata();
	void showdata();
	int storedata();
	void viewalldata();
	void searchdata(char*);
	void deletedata(char*);
	void updatedata(char*);
};

void Book::setdata(){
	cout<<"Enter the Id, title and Price: "<<endl;
	cin>>id;
	cin.ignore();
	cin.getline(name,19);
	cin>>price;
}

void Book::showdata(){
	cout<<"ID: "<<id<<endl<<"Title: "<<name<<endl<<"Price: "<<price<<endl;
}
int Book::storedata(){
	
	if(id==0 && price==0){
		cout<<"\nData not inialize"<<endl;
		return 0;
	}else{
			ofstream fout;
	fout.open("Books.txt", ios::app);
	fout.write((char*)this, sizeof(*this));
	fout.close();
}
}

void Book::viewalldata(){
	ifstream fin;
	fin.open("Books.txt", ios::in);
	if(!fin){
		cout<<"\nFile not found"<<endl;
	}else{
		fin.read((char*)this, sizeof(*this));
		while(!fin.eof()){
			showdata();
			cout<<endl;
			fin.read((char*)this, sizeof(*this));
		}
		fin.close();
	}
}

void Book::searchdata(char* t){
	int count=0;
	ifstream fin;
	fin.open("Books.txt", ios::in);
	if(!fin){
		cout<<"\nFile not found"<<endl;
	}else{
		fin.read((char*)this, sizeof(*this));
		while(!fin.eof()){
			if(!strcmp(t, this->name)){
				showdata();
				count++;
			}
			fin.read((char*)this, sizeof(*this));
		}
		if(count==0){
			cout<<"Data not found"<<endl;
		}
		fin.close();
	}
}

void Book::deletedata(char* t){
	ifstream fin;
	ofstream fout;
	fin.open("Books.txt", ios::in);
	if(!fin){
		cout<<"\nFile not exist"<<endl;
	}else{
		fout.open("Tempo.txt", ios::out);
		fin.read((char*)this, sizeof(*this));
		while(!fin.eof()){
			if(strcmp(name,t)){
				fout.write((char*)this, sizeof(*this));
			}
			fin.read((char*)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("Books.txt");
		rename("Tempo.txt", "Books.txt");
			}
}
	
void Book::updatedata(char* t){
	fstream file;
	file.open("Books.txt", ios::in | ios::out | ios::ate);
	file.seekg(0);
	file.read((char*)this, sizeof(*this));
	while(!file.eof()){
		if(!strcmp(t, name)){
			setdata();
			file.seekp(file.tellp()-sizeof(*this));
			file.write((char*)this, sizeof(*this));
		}
		file.read((char*)this, sizeof(*this));
	}
	file.close();
}

int menu(){
	int choice;
	cout<<"\t\t----------------------";
	cout<<"\n\t\tBook Menagment System"<<endl;
	cout<<"\t\t----------------------"<<endl;
	cout<<"\n\t\t====================";
	cout<<"\n\t\t1. Insert Data ";
	cout<<"\n\t\t2. Viewalldata ";
	cout<<"\n\t\t3. Search data ";
	cout<<"\n\t\t4. Delete data ";
	cout<<"\n\t\t5. Update data ";
	cout<<"\n\t\t6. Exit ";
	cout<<"\n\t\tEnter your choice: ";
	cout<<"\n\t\t====================\n";
	cin>>choice;
	return choice;
}

main(){
	Book b1;
	char namee[20];
	while(1){
		system("cls");
		switch(menu())
		{
			case 1:
				b1.setdata();
				b1.storedata();
				cout<<"Store Data Successfully..."<<endl;
				break;
			case 2:
				b1.viewalldata();
				break;
			case 3:
				cout<<"Enter the title for search data"<<endl;
				cin.ignore();
				cin.getline(namee, 19);
				b1.searchdata(namee);
				break;
			case 4:
				cout<<"Enter the Tittle for Delete"<<endl;
				cin.ignore();
				cin.getline(namee,19);
				b1.deletedata(namee);
				break;
			case 5:
				cout<<"Enter the Tittle for update"<<endl;
				cin.ignore();
				cin.getline(namee, 19);
				b1.updatedata(namee);
				break;
			case 6:
				cout<<"\nThankyou for using this Application"<<endl;
				system("cls");
				exit(0);
				break;
			default:
				cout<<"Invalid input"<<endl;
	}
		system("pause");
	}
}
