/*
 * FileHandling.h
 *
 *  Created on: May 30, 2018
 *      Author: vision
 */

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
class FileHandling {
private:
	vector<string> rawTweets;
	vector<string> tweetsStoppedWordRemoved;
	vector<string> testingTweets;
	vector<string> testingTweetsStoppedWordRemoved;
	set<string> stoppingWords;
	string fileName;
public:
	FileHandling();
	virtual ~FileHandling();
	void setFileName(string fileName);
	string getFileName();
	vector<string> getRawTweets();
	vector<string> getTestingTweets();
	bool IsStopWord(string word);
	void ReadInputFile(string fileName);
	void ReadStopWordsFile(string fileName);
	vector<string> Tokenizer(string tweet);
	vector<string> RemoveStopWords(vector<string> tweets);
	void FileWriter();
	void eraseAllSubStr(string & mainStr, const string & toErase);
	double CosineSimilarity(string text1, string text2);
	string Trim(string const& str);
	string toUpper(string word);
        string RemoveCarriageReturn(string line);
        void convert(string& word);
};
class Values
{
public:
	int val1;
	int val2;
	Values(int v1, int v2);
	void UpdateValue(int v1, int v2);
	Values();
	~Values();
private:

};


inline Values::Values(int v1, int v2)
{
	this->val1 = v1;
	this->val2 = v2;
}

inline void Values::UpdateValue(int v1, int v2)
{
	this->val1 = v1;
	this->val2 = v2;
}

inline Values::Values()
{
}

inline Values::~Values()
{
	val1 = 0;
	val2 = 0;
}
#endif /* FILEHANDLING_H_ */
