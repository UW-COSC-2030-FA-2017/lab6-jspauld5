// SortedDriver.cpp
// Jared Spaulding 10/26/2017

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.

// use 'g++ -std=c++11 SortedDriver.cpp' to run


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.cpp"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	struct iso_sides {
		double num;
		double left_side;
		double right_side;
	};

	// make initial iso set num, left_side, and right_side
	iso_sides iso;
	iso.num = number.at(0);
	iso.left_side = 0;
	iso.right_side = number.at(1) - number.at(0);

	// iterate through the vector
	for (int i = 1; i < number.size() -1; i++) {
		// make current iso to compare with original iso
		iso_sides current_iso;
		// set num, left_side, and right_side
		current_iso.num = number.at(i);
		current_iso.left_side = number.at(i) - number.at(i - 1);
		current_iso.right_side = number.at(i + 1) - number.at(i);

		// check if it is max isolation
		if (current_iso.left_side > iso.left_side || current_iso.right_side > iso.right_side) {
			if (iso.left_side < current_iso.left_side && iso.left_side < current_iso.right_side ||
				iso.right_side < current_iso.left_side && iso.right_side < current_iso.right_side) {
				iso = current_iso;
			}
		}
	}
	return iso.num;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	// init counter
	int count = 0;
	string b = " ";

	// init iterators
	std::list<string>::const_iterator iterateA = A.begin();
	std::list<string>::const_iterator iterateB = B.begin();

	// make string of B
	while (iterateB != B.end()) {
		b.append(" ").append(*iterateB);
		iterateB++;
	}

	std:size_t found;

	// iterate though A and check in b
	// used cpuspus.com as a reference cant get it any more efficient 
	while (iterateA != A.end()) {
		found = b.find(*iterateA);
		if (found == std::string::npos) 
			count++;
		iterateA++;
	}
	
	return count;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}