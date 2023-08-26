#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

int FREEMEM(int LENGTH, std::string s)
{
	return LENGTH - s.length();
}

bool IS_FREE(int LENGTH, std::string curString)
{
	if (FREEMEM(LENGTH, curString) != 0)
		return true;
	else return false;
}

std::string Spaces(int LENGTH, std::string curString)
{
	while (IS_FREE(LENGTH, curString))
	{
		curString = " " + curString;
		if (!IS_FREE(LENGTH, curString))
			break;
		curString = curString + " ";
	}
	return curString;
}

std::vector<std::string> Formating(int LENGTH, std::vector<std::string> words, std::vector<std::string> stringlist)
{
	std::string curString = ""; //an editable string that has not yet been added to the vector
	std::string last = ""; //
	for (auto& word : words)
	{
		last = word;
		// I) IF THE WORD LENGTH IS LESS THAN THE TOTAL CAPACITY
		if (LENGTH >= word.length()) {
			//Ia) IF THE WORD IS NOT CRAMMED INTO THE STRING
			if (FREEMEM(LENGTH, curString) <= word.length() - 1)
			{
				curString = Spaces(LENGTH, curString); //placing spaces
				stringlist.push_back(curString); //sending string to vector
				curString = "";
				curString += word; //inserting new word
				if (IS_FREE(LENGTH, curString))
					curString += " ";
			}
			//Ib) IF A WORD CAN BE CRAMMED INTO A STRING
			else
			{
				curString += word;
				if (FREEMEM(LENGTH, curString) != 0)
					curString += " ";
			}
		}
		// II) IF THE WORD LENGTH IS GREATER THAN THE TOTAL CAPACITY
		else
		{
			for (auto& sym : word) //we go through the word character by character, 
								   //insert the characters into the string (-s) curString
			{
				if (!IS_FREE(LENGTH, curString)) //if the character cannot be inserted

				{
					curString = Spaces(LENGTH, curString);
					stringlist.push_back(curString); //string goes to vector
					curString = sym; //symbol returns to the next string
				}
				else
					if (FREEMEM(LENGTH, curString) != 0)
						curString += sym; //adding symbol
			}
			if (FREEMEM(LENGTH, curString) != 0)
				curString += " "; //separator
		}
	}
	last = Spaces(LENGTH, last);
	stringlist.push_back(last);
	return stringlist;
}

void PrintList(std::vector < std::string > stringlist)
{
	for (auto& str : stringlist)
		std::cout << str << std::endl;
}

std::vector<std::string> GETTING(std::vector<std::string> initial, std::ifstream& FILE)
{
	while (!FILE.eof())
	{
		std::string buffer = "";
		std::getline(FILE, buffer);
		buffer += " ";
		initial.push_back(buffer);
	}
	return initial;
}

std::vector<std::string> SPLITTING(std::vector<std::string> initial)
{
	std::string str = "";
	for (auto& it : initial)
		str += it;
	std::stringstream ss(str);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> words(begin, end);
	return words;
}

int main(int argc, char* argv[])
{

	// 1) opening file
	std::ifstream FILE;

	std::string FileName;

	FileName = argv[0];

	FILE.open(FileName);
	if (FILE.is_open())
	{
		int LENGTH; FILE >> LENGTH;

		std::vector<std::string> initial;
		// 2) getting file by string
		initial = GETTING(initial, FILE);

		std::vector<std::string> words;
		// 3) dividing by words
		words = SPLITTING(initial);

		std::vector<std::string> stringlist;
		// 4) formating
		stringlist = Formating(LENGTH, words, stringlist);

		// 5) printing
		PrintList(stringlist);
	}
	else std::cerr << "Error. File isn't opened.";
	FILE.close();
}