#include<iostream>
#include<assert.h>
#include<fstream>
#include<string.h>
#include "assert.h"


using namespace std;

class String {
private:
	char* str;
	int current_size;
	int n;	
		
public:
	String(const String&);
	String();
	~String();
	char* getStr(istream&);
	char* setStroka(char*);
	String(fstream&);
	bool init(fstream&);
	void show();
	char* getStr()const;
	void strcpy(char*);
	char getElem(int i){return str[i];}
	char operator[](int i)const{ return str[i]; }
	const int getLength()const{ return n;}	
	const int getSize()const{ return current_size;}
	const String& operator=(const String &);
	void concat(char*);
	int strcmp_(const String&);
	String operator+(String&);
	bool operator>(const String&);	
	bool operator<(const String&);
	friend ostream &operator<<(ostream &, const String&);
};

String::~String(){
	if(str)
		delete[]str;
}

bool String::init(fstream& file){
	str = getStr(file);
	if(str)
		return true;
	return false;
}

int String::strcmp_(const String &right){
	return strcmp(str, right.getStr());
}

bool String::operator>(const String &right){
	return (strcmp_(right)>0);
}


bool String::operator<(const String &right){
	return (strcmp_(right)<0);
}

const String& String::operator=(const String &right){
	strcpy(right.getStr());
	return *this;
};

ostream & operator<<(ostream &output, const String &elem){
	output << elem.getStr() ;

}

String String::operator+(String &right){
	String newString(*this);
	newString.concat(right.getStr());
	return newString;
}


void String::concat(char* str2){
	int len = strlen(str2);
	if(len <= current_size - n + 1){
		memcpy(&str[n], str2, len+1);
		return ;	
	}
	char *tmp = new char[n];
	memcpy(tmp, str, n);
	delete[] str;
	str = new char[n+len+1];
	memcpy(str, tmp, n);
	memcpy(&str[n], str2, len+1);
	n += len;
	current_size = n;
}

char *String::getStr(istream& file){
	const size_t buff = 10;
	current_size = buff;
	char *buffer = new char[current_size];
	n = 0;
	char c = 0;
	while(file.get(c) && c != ' ' && c!= '\n' && !file.eof()){  
		if (n + 1 > current_size){ 
			current_size *= 2;
			char *new_buffer = new char[current_size];
			memcpy(new_buffer, buffer, n);
			delete [] buffer; 
			buffer = new_buffer;
		}
		buffer[n++] = c;
	}
	char *final_buffer = new char[n+1]; 
	memcpy(final_buffer, buffer, n); 
	final_buffer[n] = '\0'; 
	delete [] buffer; 
	if(file.eof() && n == 0)
		return NULL;
	return final_buffer;
}

char* String::getStr() const{
 	return str;
}


char* String::setStroka(char* string_){
	str = string_;
	return str;
	
} 

void String::show() {
	cout << "\nSTR: " << str << "\n n: "<< n << "\n size: " << current_size << "\n\n";
		
}

void String::strcpy(char *str2){
	n = strlen(str2);
	current_size = n;
	str = new char[n+1];
	for(int i = 0; i < n; i++)
		str[i] = str2[i];
	str[n] = '\0';
}

String::String(const String &oth){
	strcpy(oth.getStr());	
}

String::String():
str(NULL), current_size(0), n(0){}

String::String(fstream& file){
	n = 0;
	current_size = 0;
	str = getStr(file);	
}

class Testbench{
private:
	String*  arr;
	int size;
	int curr;
public:
	Testbench(int, fstream&);
	~Testbench();
	void show();
	void sort();
	void swap(String&, String&);
	bool mem(int);a
	bool init(fstream&);
	Testbench();
};

bool Testbench::mem(int newSize){
	if(arr == NULL){
		arr = new String[newSize];
	}else{	
		String* tmp = new String[size];
		for(int i = 0; i < size; i++)
			tmp[i] = arr[i];
		delete [] arr;
		arr = new String[newSize];
		for(int i = 0; i < size; i++)
			arr[i] = tmp[i];
		delete [] tmp;
		}
	size = newSize;
	return arr;
}

Testbench::~Testbench(){
	if(arr)
		delete [] arr;
}

void Testbench::swap(String &str1, String& str2){
	String str3 = str1;
	str1 = str2;
	str2 = str3;
}

void Testbench::sort(){
	cout << "\nSORT";
	for(int i = 0; i < curr; i++)
		for(int j = 0; j < curr; j++)
			if(arr[i] < arr[j])
				swap(arr[i], arr[j]);
}

Testbench::Testbench(int N, fstream &file){
	size = N;
	curr = N;
	arr = new String[size];
	for(int i = 0; i < N; i++){
		arr[i].init(file);
	}
}

Testbench::Testbench():
arr(NULL), size(0){}


bool Testbench::init(fstream &file){
	size = 1;
	mem(size);
	curr = 0;
	while(1){
		if(size == curr && mem(size*2));
		/*
		if(size == curr) mem(size*2);
		*/
		if(arr[curr++].init(file))	
			continue;
		curr--; 
		break;
	}
}

void Testbench::show(){
	cout << "\nSHOW\n";
	for(int i = 0; i < curr; i++)
		cout << arr[i] << " ";
}

int main(int argc, char* argv[]) {
	fstream file("./test");
	Testbench tb;
	tb.init(file);
	tb.show();
	tb.sort();
	tb.show();
	file.close();
	return 0;
}
