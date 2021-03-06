// Dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include<conio.h>
#include<stdio.h>
using namespace std;

struct letter {
	char alpha;
	letter *next;
	struct words *header;
};
struct words
{
	string word;
	string meaning;
	words *next;
};

int hashing(int j)
{

	int index;
	if (j >= 65 && j <= 90)
	{
		index = j - 65;
		return index;
	}
	else if (j >= 97 && j <= 122)
	{
		index = j - 97;
		return index;
	}
	
	
}
letter *hashingtable(letter *table,int size)
{
	int index;
	int i = 0;
	int j = 65;
	while (i < 26)
	{
		index = hashing(j);
		char k = j;
		table[index].alpha = k;
		table[index].header = NULL;
		//table[index].next = NULL;

		i++;
		j++;
	}
	return table;
}
void hashingwords(letter *table,string word,string def)
{		
	words *w = new words();
	w->word = word;
	w->meaning = def;
	
	int asci;
	asci = w->word[0];
	int wordindex = hashing(asci);
	//cout << wordindex << endl;
	if (table[wordindex].header == NULL)
	{
		table[wordindex].header = w;
	}
	else
	{
		words * curr = table[wordindex].header;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = w;
	}
	

}
void push(int top,string *stack,string word)
{
	stack[++top] = word;

}
string pop(int top,string *stack)
{
	return stack[top--];
}
bool searching(letter *table,string word,string *stack,int top)
{
	
	//int sizemeaning = 0;
	//int flag = 0;
	string line,line2;
	int ascii = word[0];
	int searchindex = hashing(ascii);
	if (table[searchindex].header == NULL)
		return false;

	if (table[searchindex].header->word == word)
	{
		cout << "Word found\n";
		
		cout <<"WORD: " << table[searchindex].header->word << endl;
		cout <<"MEANING: "<< table[searchindex].header->meaning << endl;
		line = table[searchindex].header->word;
		line2 = table[searchindex].header->meaning;
		push(top, stack, table[searchindex].header->word);
		top++;
		std::ofstream log("history.txt", std::ios_base::app | std::ios_base::out);
		//////////////
	/*	if (log.eof())
		{
			log << line << endl << line2;
		}
		/////////////
		else*/
		log << endl << line << endl << line2;

		return 1;
		}
	else
	{
	
		words *curr = table[searchindex].header->next;
		while(curr!=NULL)
		{
			if (curr->word == word)
			{
				cout << "Word found\n";
				cout <<"WORD : "<< curr->word << endl;
				cout <<"MEANING :" << curr->meaning << endl;
				push(top, stack,curr->word);
				top++;
				line = curr->word;
				line2 = curr->meaning;
				std::ofstream log("history.txt", std::ios_base::out);

				log <<endl<< line << endl << line2;
				//std::ios_base::app |
			
				return 1;
			}
			curr = curr->next;
		}
		return false;
	}
	

	
}
void recentsearches(string *stack, int top)
{
	
	while (top != -1)
	{
		string c=pop(top, stack);
		top--;
		cout <<"WORD: "<< c<<endl;

		}

}

int main()
{
	int top = -1;
	string *stack = new string[10];
	string word;
	string def;
	int size = 26;
	letter *Hashingtable = new letter[size];
	letter *tab = hashingtable(Hashingtable, size);
	//cout << "\n=======Dictionary=========\n";
	string line;
	string line2;
	ifstream fin;
	fin.open("dictionary.txt"); 
	while (fin) {

		getline(fin, line);
		getline(fin, line2);
		//cout << line << endl;
		hashingwords(tab, line, line2);
	}

	fin.close();
	/*cout << "Enter word: ";
	getline(cin, word);
	
	cout << "Enter meaning: ";
	getline(cin, def);*/
	system("CLS");
	cout << "\n=======Dictionary=========\n";
	int num;
	do {
		
		cout << "\npress 1 to search for a word\npress 2 for showing recent searches\npress 3 TO insert another word in the dictionary \npress 4 for showing word of the day\n5 to Exit\n\n ";
		//num = _getche();
		cin >> num;
		switch (num)
		{
			cout << "\n-------------------------------------------------\n";
			case 1:

			{	system("CLS");
				cout << "\nSearching...\n";
				
				cout << "Enter word to search : ";
				cin >> word;
				bool i;
				i = searching(tab, word, stack, top);
				if (i == true)
				{
					top++;
				}
				else if (i == false)
					{
					cout << "word not found\n";
					

					}
				cout << "\n-------------------------------------------------\n";
						break;
			}
			
			cout << "\n-------------------------------------------------\n";
			case 2:
			{	system("CLS");
				cout << "Your Recent Searches \n";
			cout << "-----------------------------\n";
					recentsearches(stack, top);
					break;
				}
				cout << "\n-------------------------------------------------\n";
			case 3:
			{
				//string wr, de;
				system("CLS");
				cout << "\n=======Entering another word========\n";
				cout << "Enter word: ";
				//getline(cin, word);
				cin >> word;
				cout << "Enter meaning: ";
				cin >> def;
				hashingwords(tab, word, def);
			/*	fstream outfile;
				outfile.open("dictionary.txt", ios::out | ios::in | ios::app);
				while (!outfile.eof())
				{
					outfile << word;
					//infile >> def;
				}
				outfile.close();
				*/
				std::ofstream log("dictionary.txt", std::ios_base::app | std::ios_base::out);

				log <<endl<<word<<endl<<def;


				break;
			}
			cout << "\n-------------------------------------------------\n";

			case 4:
			{
				system("CLS");
				string line3;
				int l = 0;
				cout << "       HISTORY\n\n";
				cout << "------------------------\n";
				ifstream fin;
				fin.open("history.txt");
				while (fin) {
				
					if(l==0)
					{
						getline(fin, line);
						l++;
					}
				
					getline(fin, line2);
					getline(fin, line3);
					//cout << line << endl;
					//hashingwords(tab, line, line2);
					//cout << "\n------------------------------\n";
					cout <<"Word: " << line2 << endl<<"Meaning:  "<< line3 << endl;
					cout << "\n------------------------------\n";
				}

				fin.close();			
			}
		}
} while (num != 5);
	

}

