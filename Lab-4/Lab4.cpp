//
//

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

using namespace std;


const vector<char> MODS = { '+', '-', '*' };
const char SEPARATOR = ',';
const char DICE_MARKER = 'd';


// Is a symbol a Modifier

bool isModifier(char c, vector<char> mods = MODS) {
	
	bool isMod = false;
	
	for (int i = 0; i < mods.size(); i++) {
		
		if (mods[i] == c) {
			isMod = true;
		}
	}

	return isMod;
}


// Use operator on dice points

int Operator(int firstElem, string s, vector<char> mods = MODS) {
	
	int result, secondElem;
	string newLine;

	for (int i = 1; i < s.size(); ++i) {
		newLine += s[i];
	}

	secondElem = stoi(newLine);

	// Which one to use

	switch (s[0])
	{
	case '+':
		result = firstElem + secondElem;
		break;

	case '-':
		result = firstElem - secondElem;
		break;

	case '*':
		result = firstElem * secondElem;
		break;
	}

	return result;
}


// Split the string

vector<string> split(string s, char separator = SEPARATOR) {
	vector<string> splitDices;
	string tempDice = "";

	for (int i = 0; i < s.size(); i++) {
		
		// Split with Modifier

		if (isModifier(s[i])) {
			
			if (tempDice != "") {
				splitDices.push_back(tempDice);
				tempDice = "";
			}
		}
		
		// Complete getting string

		if (s[i] != separator && s[i] != ' ') {
			tempDice += s[i];
		}
		
		// End of string or Separator

		if (i == (s.size() - 1) || s[i] == separator) {
			splitDices.push_back(tempDice);
			tempDice = "";
		}
	}

	return splitDices;
}


// Get random number for a dice

int getRandom(int min = 1, int max = 100)
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> res(min, max); 
	
	return(res(rng));
}


// Dices, Dices & more Dices

int dice(string input, char separator_ = SEPARATOR, bool getMax=false) {
	
	vector<string> outputDices;
	int result = 0;


	// Split input dices

	outputDices = split(input, separator_);

	for (int i = 0; i < outputDices.size(); i++) {
		
		if (!isModifier(outputDices[i][0])) {
			

			// Split dice count and dice weight

			auto playDice = split(outputDices[i], DICE_MARKER);

			int dicesCount = stoi(playDice[0]);
			int diceWeight = stoi(playDice[1]);


			// Getting random!

			for (int j = 0; j < dicesCount; ++j) {
				
				int ran = getRandom(1, diceWeight);
				
				//cout << ran;  // testing True Random!
				
				result += ran;
			}

		}
	}


	// Get dice Max Points instead of Random Result

	if (getMax) {
		
		result = 0;

		for (int i = 0; i < outputDices.size(); i++) {

			if (!isModifier(outputDices[i][0])) {

				auto playDice = split(outputDices[i], DICE_MARKER);
				int dicesCount = stoi(playDice[0]);
				int diceWeight = stoi(playDice[1]);

				for (int j = 0; j < dicesCount; ++j) {

					result += diceWeight;
				}

			}
		}

	}
	
	// Use Operators

	for (int i = 0; i < outputDices.size(); i++) {
		
		if (isModifier(outputDices[i][0])) {
			result = Operator(result, outputDices[i]);
		}
	}

		// result

	return result;
}



//  = = = HERE GOES TRUE DICE RANDOM = = =

int main() {
	
	// Dices, throw counts

	vector<string> diceSet = {"1d6","2d6","3d6","1d10","2d10","3d10","6d10"};
	int diceCount = 10000;


	int maxMax = 1; // for data saving
	int dataMax = 0; // also for data saving


	// Create array for data

	int size = diceSet.size();
	int** data = (int**)malloc(sizeof(int*) * size);

	cout << "Dice set:" << endl;

	for (int i = 0; i < size; i++) {
		string diceString = diceSet[i];
		
		// get max point using 'dice'

		int maxPoints = dice(diceString, SEPARATOR, true);
		cout << diceString << endl;

		if (maxMax < maxPoints) maxMax = maxPoints;		
		
	}
	

	for (int i = 0; i < size; i++) {

		data[i] = (int*)malloc(sizeof(int) * maxMax);
	}

	cout << endl << "Trying " << diceCount << " throws..." << endl << endl;

	// Open file

	ofstream f("dice.csv");
	

	// Try each dice combination from the Set

	
	
	for (int i = 0; i < size; i++) {

		// get current dice set

		string diceString = diceSet[i];

		// For data list
		
		int maxPoints = dice(diceString, SEPARATOR, true);
		vector<int> throws(maxPoints, 0);
		

		// Get Dice points

		for (int k = 0; k < diceCount; ++k) {

			int thisThrow_ = dice(diceString);

			throws[thisThrow_ - 1]++;
		}
		
		// Get data

		for (int j = 0; j < throws.size(); ++j) {
					
			data[i][j] = throws[j];
			
			if (dataMax < data[i][j]) dataMax = data[i][j];
			
		}

		cout << diceString << " throws done" << endl;

	}


	// Save data

	for (int j = 0; j < maxMax; j++) {

		for (int i = 0; i < size; i++) {

			if (data[i][j] > 0 && data[i][j] <= dataMax) {

				f << data[i][j] << ";";
			}
			else f << "" << ";"; // for better .csv diagram appearance
		}
		f << endl;

	}

	cout << endl << "Throws finished!" << endl;

	return 0;
}