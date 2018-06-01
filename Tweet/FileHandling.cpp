
#include "FileHandling.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <math.h>
#include <string>         // std::string
#include <locale>
#include <list>
#include <strings.h>
#include <map>

FileHandling::FileHandling() {
    // TODO Auto-generated constructor stub

}

/*
 this function is used to read the input text file
 and stripping Testing tweets and Training Tweets and store it
 in the required data structure;
 */
void FileHandling::ReadInputFile(string fileName) {
    string text;
    string path = "../Tweet/";
    setFileName(fileName);
    ifstream file;
    file.open(path + fileName);
    bool flag = false;
    if (!file) {
        cout << "file is not opened" << endl;
    } else {
        cout << "file is  opened"<<endl;
        while (getline(file, text)) {
            //getline(file, text);
            //this is used to skip the lines with carriage return "/r"
            if (text.length() < 2) {
                flag = true;
                continue;
            } else if (!flag) {
                rawTweets.push_back(RemoveCarriageReturn(text));
                //cout << text;

            } else if (flag) {
                testingTweets.push_back(RemoveCarriageReturn(text));
                //cout << text << endl;
            }
        }
    }

    file.close();
}

/*
        this function is used to read Stopwords text file and store them in the
        Set data structure
 */
void FileHandling::ReadStopWordsFile(string fileName) {
    string text;
    //here we are using relative path
    string path = "../Tweet/";
    ifstream file(path + fileName);

    if (!file.is_open()) {
        cout << "file is not opened" << endl;
    } else {
        while (getline(file, text)) {
            if (text == "") {
                continue;
            } else {
                text = Trim(text);
                stoppingWords.insert(RemoveCarriageReturn(text));
            }
        }
    }

    file.close();

}

/*
        this function is used to remove stop words from all the tweets
 */
vector<string> FileHandling::RemoveStopWords(vector<string> tweets) {
    vector<string> tempTweet = vector<string>();
    for (int i = 0; i < tweets.size(); i++) {
        vector<string> temp = Tokenizer(tweets[i]);
        string line = "";
        for (int j = 0; j < temp.size(); ++j) {
            if (IsStopWord(temp[j])) {
                continue;
            } else {
                line = line + " " + temp[j];
            }
        }
        convert(line);
        cout << line << endl;
        tempTweet.push_back(line);
        temp.clear();
    }
    return tempTweet;
}

/*
        this function is used to write all the result to the file
 */
void FileHandling::FileWriter() {
    ofstream ofs;
    string path = "/home/vision/eclipse-workspace/testing/src/";
    ofs.open("cosine similarity.txt", ofstream::out | ofstream::app);
    string temp = toUpper(getFileName());
    eraseAllSubStr(temp, ".txt");
    //	locale loc;
    //	for(string::size_type i=0; i<temp.length(); ++i){
    //		toupper(temp[i],loc);
    //	}
    //	transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

    ofs << temp << " " << "COSINE SIMILARITY" << endl;
    testingTweetsStoppedWordRemoved = RemoveStopWords(testingTweets);
    tweetsStoppedWordRemoved = RemoveStopWords(rawTweets);
    for (int i = 0; i < testingTweets.size(); i++) {
        ofs << testingTweets[i] << endl;
        for (int j = 0; j < rawTweets.size(); j++) {
            double value = (CosineSimilarity(testingTweetsStoppedWordRemoved[i], tweetsStoppedWordRemoved[j]));
            ofs << fixed << setprecision(3) << value << "\t" << rawTweets[j] << endl;
        }
        ofs << endl;
    }

    ofs << endl;
    ofs.close();
}

/*
 * Erase all Occurrences of given substring from main string.
 */

void FileHandling::eraseAllSubStr(string & mainStr, const string & toErase) {
    size_t pos = std::string::npos;

    // Search for the substring in string in a loop until nothing is found
    while ((pos = mainStr.find(toErase)) != std::string::npos) {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}

/*
        here in this function finding the Cosine Similarity between two strings
 */
double FileHandling::CosineSimilarity(string text1, string text2) {
    double sim_score = 0.0000000;
    //1. Identify distinct words from both strings
    vector<string> word_seq_text1 = Tokenizer(text1);
    vector<string> word_seq_text2 = Tokenizer(text2);

    map <string, Values> word_freq_vector = map<string, Values>();
    vector<string> Distinct_words_text_1_2;

    //2. prepare word frequency vector by using Text1
    for (int i = 0; i < word_seq_text1.size(); i++) {
        string tmp_wd = word_seq_text1.at(i);
        if (tmp_wd.length() > 0) {

            if (word_freq_vector.find(tmp_wd) != word_freq_vector.end()) {
                Values vals1 = word_freq_vector.at(tmp_wd);
                // Values vals1 = word_freq_vector.get(tmp_wd);
                int freq11 = (vals1.val1 + 1);
                int freq12 = vals1.val2;
                vals1.UpdateValue(freq11, freq12);
                word_freq_vector[tmp_wd] = vals1;
                vals1.~Values();
            } else {
                Values vals1 = Values(1, 0);

                //word_freq_vector.put(tmp_wd, vals1);
                word_freq_vector.emplace(tmp_wd, vals1);
                vals1.~Values();
                Distinct_words_text_1_2.push_back(tmp_wd);
            }
        }
    }

    //3 prepare word frequency vector by using Text2
    for (int i = 0; i < word_seq_text2.size(); i++) {
        string tmp_wd = Trim(word_seq_text2[i]);
        if (tmp_wd.length() > 0) {

            if (word_freq_vector.find(tmp_wd) != word_freq_vector.end()) {

                Values vals2 = word_freq_vector.at(tmp_wd);

                int freq1 = vals2.val1;
                int freq2 = (vals2.val2 + 1);
                vals2.UpdateValue(freq1, freq2);
                word_freq_vector[tmp_wd] = vals2;

                vals2.~Values();
            } else {
                Values vals1 = Values(0, 1);
                //word_freq_vector.emplace(tmp_wd, vals1);
                word_freq_vector.emplace(tmp_wd, vals1);
                Distinct_words_text_1_2.push_back(tmp_wd);
                vals1.~Values();
            }
        }
    }

    //calculate the cosine similarity score.
    double VectAB = 0.0000000;
    double VectA_Sq = 0.0000000;
    double VectB_Sq = 0.0000000;

    for (int i = 0; i < Distinct_words_text_1_2.size(); i++) {

        Values vals12 = word_freq_vector.at(Distinct_words_text_1_2[i]);
        double freq1 = (double) vals12.val1;
        double freq2 = (double) vals12.val2;
        cout << Distinct_words_text_1_2[i] << "#" << freq1 << +"#" << freq2 << endl;

        VectAB = VectAB + (freq1 * freq2);

        VectA_Sq = VectA_Sq + (freq1 * freq1);
        VectB_Sq = VectB_Sq + (freq2 * freq2);
    }


    cout << "VectAB " << VectAB << " VectA_Sq " << VectA_Sq << " VectB_Sq " << VectB_Sq << endl;
    sim_score = ((VectAB) / (sqrt(VectA_Sq) * sqrt(VectB_Sq)));


    return sim_score;
}

/*
        this function is used for trimming strings if it containing any white spaces
 */
string FileHandling::Trim(string const & str) {
    string word;
    stringstream stream(str);
    stream >> word;

    return word;
}

/*
        this function is used to tokenize the tweet into words based on a single space between them
 */
vector<string> FileHandling::Tokenizer(string tweet) {
    string buff{ ""};
    vector<string> v;

    for (auto n : tweet) {
        if (n != ' ') buff += n;
        else
            if (n == ' ' && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

/*
 this function will check each word in the tweet whether it is stop word or not
 */
bool FileHandling::IsStopWord(string word) {

    if (stoppingWords.find(word) != stoppingWords.end()) {
        return true;
    }
    return false;

}

void FileHandling::setFileName(string fileName) {
    this->fileName = fileName;
}

string FileHandling::getFileName() {
    return fileName;
}

vector<string> FileHandling::getRawTweets() {
    return rawTweets;
}

vector<string> FileHandling::getTestingTweets() {
    return testingTweets;
}

string FileHandling::toUpper(string word) {

    for (string::size_type i = 0; i < word.length(); ++i) {
        word[i] = toupper(word[i]);
    }
    return word;
}

void FileHandling::convert(string& word) {

    for (string::size_type i = 0; i < word.length(); ++i) {
        word[i] = toupper(word[i]);
    }

}

string FileHandling::RemoveCarriageReturn(string line) {
    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);

    return line;
}

FileHandling::~FileHandling() {
    // TODO Auto-generated destructor stub
}

