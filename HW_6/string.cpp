#include "./string.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_STR_LEN 80





// default constructor
String::String() {
	this->length = 0;
	this->data =  new char[0];
}

// copy constructor
String::String(const String& str)
{
	this->length = str.length;
	this->data = new char[length + 1];

	strcpy(data, str.data);

}

String::String(const char* str)
{
	this->length = strlen(str);
	this->data = new char[length + 1];

	strcpy(data, str);
}

String::~String()
{
	delete[] this->data;
}

String& String::operator=(const String& rhs)
{
	if(this !=&rhs){
	if(this->data!=NULL){
		delete[] this->data;
	}
	this->length = rhs.length;
	this->data = new char[rhs.length +1];
	strcpy(this->data,rhs.data);
	
	}
	// TODO: insert return statement here
	return *this;
}

String& String::operator=(const char* str)
{
	delete[] this->data;
	this->data = new char[strlen(str) +1];
	strcpy(this->data, str);
	this->length = strlen(str);
	// TODO: insert return statement here
	return *this;
}

bool String::equals(const String& rhs) const
{
	if (strcmp(this->data, rhs.data)) {
		return false;
	}
	return true;
}

bool String::equals(const char* rhs) const
{
	if (strcmp(this->data, rhs)) {
		return false;
	}
	return true;
}



void String::split(const char* delimiters, String** output, size_t* size) const
{

	size_t output_size = 1;
	for (size_t i = 0; i < strlen(delimiters); i++) {
		for (size_t j = 0; j < this->length; j++) {
				if (this->data[j] == delimiters[i]) {
				output_size++;
			}
		}
	}
		if (output==NULL){
			if(this->length==0){
				*size=0;
				return;
			}
		*size=(output_size);
		return ;
	}

	*output = new String[output_size+1];
	
	char* tmp= strtok(this->data, delimiters);
	size_t place=0;
	
	while(tmp!=NULL){
	(*output)[place]=tmp;
	tmp = strtok(NULL, delimiters);
	place++;
	}
	
	
	*size=output_size;
	
/*	*size = 0;
	size_t position = 0;
	int i=0;
	for (size_t j= 0; j < this->length; j++)
	{
		
				//String token;
				size_t pos = strcspn(&(this->data[position]),delimiters);
				if (pos == this->length -position) {
					break;
				}
				//token.length = pos;
				//char *tmp = new char[token.length+1];
				//tmp = {0};
				//token = tmp;
				//strncpy(token.data, &(this->data[position]), token.length);
				char tmp[pos+1]= {0};
				strncpy(tmp, &(this->data[position]), pos);
				(*output)[i] = tmp;
				(*output)[i].data[pos]= '\0';
				// **output = token;
				//(*output)++;
				//(*size)++;
				i++;
				position += (pos + 1);
				//delete[] tmp;
			

		
	}
	String last_token;
	last_token.length = this->length - position;
	last_token.data = new char[last_token.length+1];
	strncpy(last_token.data, &(this->data[position]), last_token.length);
	last_token.data[last_token.length]= '\0';
	**output = (String(last_token));
	(*output) -= (output_size-1);
	(*size)++;
	*/
				
}

int String::to_integer() const
{
	 
	
	return atoi(this->data); 
}

String String::trim() const
{
	/*std::string a =this->data;
	a.erase (0,a.find_first_not_of(" \t\n\r\v\f"));
	a.erase(a.find_last_not_of(" \t\n\r\v\f")+1);
	
	char* str = new char[a.size()+1];
	String b(str);
	delete[]str;
	return b;*/
	char* start = this->data;
	while (*start == ' ' ||*start == '\n'||*start == '\t'||*start == '\f'||*start == '\r'||*start == '\v')
	{
		start++;
	}
	char* end = this->data+this->length -1; 
	while (*end == ' ' ||*end == '\n'||*end == '\t'||*end == '\f'||*end == '\r'||*end == '\v') {
		end--;
	}
	String a;
	a.length = end - start + 1;
	a.data = new char[a.length+1];
	strncpy(a.data, start, a.length);
	a.data[a.length]= '\0';
	return a; 
}
		
	




