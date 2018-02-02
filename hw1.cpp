#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <sys/resource.h>
using namespace std;
int min_ans=99;
int first_flag=0;
/****  Your homework starts here ****/
vector< vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordDictionary,int count){
	vector< vector<string> > ans;
	string cur_word;
	int word_diff;
	int char_diff;
	int i,j,idx;
	int flag;

	/* erase beginWord in wordDictionary */
	if(!first_flag)
	{
		first_flag=1;
		for (i=0;i<wordDictionary.size();i++)
		{
			cur_word = wordDictionary[i];
			word_diff = beginWord.size() - cur_word.size();
			if(word_diff==0)
			{
				char_diff = 0;
				for(j=0;j<beginWord.size();j++)
				{
					if (beginWord[j] != cur_word[j])		
						char_diff++;
				}
				if(char_diff==0)
					wordDictionary.erase(wordDictionary.begin()+i);
			}
		}
	}

	/* check Dictionary if any word inside has just 1 character different from current word */
	for(i=0;i<wordDictionary.size();i++)
	{
		if(count>min_ans)
			return ans;
		flag =0;
		cur_word = wordDictionary[i];
		word_diff = beginWord.size() - cur_word.size();

		/* check length */
		if (word_diff > 1 || word_diff < -1)			
			continue;

		/* length is match, check different character */
		else if (word_diff == 0)
		{
			char_diff = 0;
			for (idx = 0; idx < beginWord.size(); idx++)
			{
				if (beginWord[idx] != cur_word[idx])		
					char_diff++;
			}
			
			if (char_diff != 1)
				continue;
			else					
			{
				vector<string> newDictionary;
				vector< vector<string> > ans1;
				newDictionary = wordDictionary;

				/*
				cout << "begin:" << beginWord<<"		";
				cout << "cur:" << cur_word << "			";
				cout << "end:" << endWord << endl;
				*/

				/* to avoid repeated */
				newDictionary.erase(newDictionary.begin()+i);
				/* using recursive function to find answer */
				if(cur_word!=endWord)
				{
					ans1 = findLadders(cur_word,endWord,newDictionary,count+1);
					if (ans1.empty())
						continue;
					else
					{
						cout<<"dddddddddddddddddd"<<endl;
						cout<<"size:"<<ans1.size()<<endl;
						for(int ix=0;ix<ans1.size();ix++)
						{
							//vector<string> temp_ans;
							//temp_ans.push_back(cur_word);
							cout<< "cur_word:" <<cur_word<<endl;
							(ans1[ix]).insert((ans1[ix]).begin(),cur_word);
							ans.push_back(ans1[ix]);
							cout<<"bbbbbbbbbbbbbbbbbb"<<endl;
						}
						for (int ix = 0; ix < ans.size(); ix++)
						{
							cout << "ans[" << ix << "]: ";
							for (int iy = 0; iy < (ans[ix]).size()-1; iy++)
							{
								cout << (ans[ix])[iy] << " -> ";
							}
							cout << (ans[ix])[(ans[ix]).size()-1] << endl;
						}
					}
				}
				else
				{
					if(count>min_ans)
						return ans;
					min_ans = count;

					vector<string> temp_ans;
					temp_ans.push_back(beginWord);
					ans.push_back(temp_ans);

					for (int ix = 0; ix < ans.size(); ix++)
					{
						cout << "ans[" << ix << "]: ";
						for (int iy = 0; iy < (ans[ix]).size()-1; iy++)
						{
							cout << (ans[ix])[iy] << " -> ";
						}
						cout << (ans[ix])[(ans[ix]).size()-1] << endl;
					}
					cout<<"aaaaaaaaaaaaaaaaaa"<<endl;
					return ans;
				}
			}
		}

		/* length is 1 character longer */
		else if (word_diff == 1)
		{
			int str1_idx = 0;
			char_diff = 0;
			for (int idx = 0; idx < cur_word.length(); idx++)
			{
				if (beginWord[str1_idx] != cur_word[idx])
				{
					char_diff++;
					idx--;
				}
				str1_idx++;
				
				if (char_diff > 1)
				{
					flag = 1;
					break;
				}
			}
		}
		/* length is 1 character shorter */
		else if (word_diff == -1)
		{
			int str2_idx = 0;
			char_diff = 0;
			for (int idx = 0; idx < beginWord.length(); idx++)
			{
				if (beginWord[idx] != cur_word[str2_idx])
				{
					char_diff++;
					idx--;
				}
				str2_idx++;
				
				if (char_diff > 1)
				{
					flag = 1;
					break;
				}
			}
		}
		/* length is 1 character shorter */
		if ( (word_diff == 1 || word_diff == -1) && (!flag) )
		{
			vector<string> newDictionary;
			vector< vector<string> > ans1;
			newDictionary = wordDictionary;

			/*
			cout << "begin:" << beginWord<<"		";
			cout << "cur:" << cur_word << "			";
			cout << "end:" << endWord << endl;
			*/

			/* to avoid repeated */
			newDictionary.erase(newDictionary.begin()+i);
			/* using recursive function to find answer */
			if(cur_word!=endWord)
			{
				ans1 = findLadders(cur_word,endWord,newDictionary,count+1);
				if (ans1.empty())
					continue;
				else
				{
					cout<<"eeeeeeeeeeeeeeeeee"<<endl;
					cout<<"size:"<<ans1.size()<<endl;
					for(int ix=0;ix<ans1.size();ix++)
					{
						//vector<string> temp_ans;
						//temp_ans.push_back(cur_word);
						cout<< "cur_word:" <<cur_word<<endl;
						(ans1[ix]).insert((ans1[ix]).begin(),cur_word);
						ans.push_back(ans1[ix]);
						cout<<"cccccccccccccccccc"<<endl;
					}

					for (int ix = 0; ix < ans.size(); ix++)
					{
						cout << "ans[" << ix << "]: ";
						for (int iy = 0; iy < (ans[ix]).size()-1; iy++)
						{
							cout << (ans[ix])[iy] << " -> ";
						}
						cout << (ans[ix])[(ans[ix]).size()-1] << endl;
					}
				}
			}
			else
			{
				if(count>min_ans)
					return ans;
				min_ans = count;

				vector<string> temp_ans;
				temp_ans.push_back(beginWord);
				ans.push_back(temp_ans);

				for (int ix = 0; ix < ans.size(); ix++)
				{
					cout << "ans[" << ix << "]: ";
					for (int iy = 0; iy < (ans[ix]).size()-1; iy++)
					{
						cout << (ans[ix])[iy] << " -> ";
					}
					cout << (ans[ix])[(ans[ix]).size()-1] << endl;
				}
				cout<<"aaaaaaaaaaaaaaaaaa"<<endl;
				return ans;
			}
		}
	}

	for(int ix=0;ix<ans.size();ix++)
	{
		//vector<string> temp_ans;
		//temp_ans.push_back(cur_word);
		(ans[ix]).insert((ans[ix]).begin(),beginWord);
		cout<<"cccccccccccccccccc"<<endl;
		cout<<"zzzzzzzzzzzzzzzzzz"<<endl;
	}
	//cout << NOT.size() << endl;
	// Return an empty vector if you cannot find one

	return ans;
}
/****  Your homework ends here ****/









int main(int argc, char* argv[]){
	/* Input check */
	if (argc < 3){
		cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
		return -1;
	}
	
	/* File check */
	ifstream ifs(argv[1]);
	if (!ifs.is_open()){
		cout << "Input file: " << argv[1] << " cannot be opened." << endl;
		return -1;
	}
	
	ofstream ofs(argv[2]);
	if (!ofs.is_open()){
		cout << "Output file: " << argv[2] << " cannot be opened." << endl;
		return -1;
	}
	
	/* Input data from the file */
	string beginWord, endWord;
	vector<string> wordDictionary;
	ifs >> beginWord >> endWord;
	while (!ifs.eof()){
		string tmp_str;
		ifs >> tmp_str;
		wordDictionary.push_back(tmp_str);
	}
	ifs.close();
	
	
	/* Function */
	vector< vector<string> > answer;
	
	const clock_t start_time = clock();
	answer = findLadders(beginWord, endWord, wordDictionary,0);
	double run_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;

	
	/* Simply examine the answer*/
	if (answer.size() > 0){
		// 1. Check if the begin and end words are in the answer
		for (int i = 0; i < answer.size(); i++){
			if ((answer[i])[0].compare(beginWord) != 0){
				cout << "ERROR: The word (" << (answer[i])[0] << ") is not the begin word." << endl;
				return -1;
			}
			else if ((answer[i])[(answer[i]).size()-1].compare(endWord) != 0){
				cout << "ERROR: The word (" << (answer[i])[(answer[i]).size()-1] << ") is not the end word." << endl;
				return -1;
			}
		}
		
		// 2. Check if the answer strings have the same length
		if (answer.size() > 1){
			int length = (answer[0]).size();
			for (int i = 1; i < answer.size(); i++){
				if (length != (answer[i]).size()){
					cout << "ERROR: Found different string lengths in the answer vector ([0] and [" << i << "])" << endl;
					return -1;
				}
			}
		}
		// 3. Check if the answer is not in the dictionary
		for (int i = 0; i < answer.size(); i++){
			for (int j = 1; j < (answer[i]).size(); j++){
				bool is_indic = false;
				for (int k = 0; k < wordDictionary.size(); k++){
					if ((answer[i])[j].compare(wordDictionary[k]) == 0){
						is_indic = true;
						break;
					}
				}
				if (!is_indic){
					cout << "ERROR: The word (" << (answer[i])[j] << ") is not in the dictionary." << endl;
					return -1;
				}
			}
		}
		// 4. Check repeated
		for (int i = 0; i < answer.size(); i++){
			for (int j = 0; j < (answer[i]).size(); j++){
				bool is_repeated = false;
				for (int k = j-1; k >= 0; k--){
					if ((answer[i])[j].compare((answer[i])[k]) == 0){
						is_repeated = true;
						break;
					}
				}
				
				if (is_repeated){
					cout << "ERROR: The word (" << (answer[i])[j] << ") repeated in the answer[" << i << "]." << endl;
					return -1;
				}
			}
		}
		// 5. Check legal transform
		for (int i = 0; i < answer.size(); i++){
			for (int j = 0; j < (answer[i]).size()-1; j++){
				short len_diff = ((answer[i])[j]).length() - ((answer[i])[j+1]).length();
				if (len_diff > 1 || len_diff < -1){
					cout << "ERROR: The word (" << ((answer[i])[j]) << ") and (" << ((answer[i])[j+1]) << ") has invalid length difference."  << endl;
					return -1;
				}
				else if (len_diff == 0){
					short char_diff = 0;
					for (int idx = 0; idx < ((answer[i])[j]).length(); idx++){
						if (((answer[i])[j])[idx] != ((answer[i])[j+1])[idx]){
							char_diff++;
						}
					}
					
					if (char_diff != 1){
						cout << "ERROR: The word (" << ((answer[i])[j]) << ") and (" << ((answer[i])[j+1]) << ") has invalid transformation."  << endl;
						return -1;
					}
				}
				else if (len_diff == 1){
					int str1_idx = 0;
					short char_diff = 0;
					for (int idx = 0; idx < ((answer[i])[j+1]).length(); idx++){
						if (((answer[i])[j])[str1_idx] != ((answer[i])[j+1])[idx]){
							char_diff++;
							idx--;
						}
						str1_idx++;
						
						if (char_diff > 1){
							cout << "ERROR: The word (" << ((answer[i])[j]) << ") and (" << ((answer[i])[j+1]) << ") has invalid transformation."  << endl;
							return -1;
						}
					}
				}
				else if (len_diff == -1){
					int str2_idx = 0;
					short char_diff = 0;
					for (int idx = 0; idx < ((answer[i])[j]).length(); idx++){
						if (((answer[i])[j])[idx] != ((answer[i])[j+1])[str2_idx]){
							char_diff++;
							idx--;
						}
						str2_idx++;
						
						if (char_diff > 1){
							cout << "ERROR: The word (" << ((answer[i])[j]) << ") and (" << ((answer[i])[j+1]) << ") has invalid transformation."  << endl;
							return -1;
						}
					}
				}
			}
		}
		
	}
	
	cout << "Your result is valid." << endl;
	
	struct rusage r_usage;
	getrusage(RUSAGE_SELF,&r_usage);
	printf("Memory usage: %ld k-bytes\n",r_usage.ru_maxrss);
	
	cout << "=====  Answer Report  =====" << endl;
	cout << "CPU Run time: " << run_time << endl;
	cout << "Mem Usage:    " << r_usage.ru_maxrss << endl;
	cout << "Word ladder number: " << answer.size() << endl;
	if (answer.size() > 0){
		cout << "Word ladder length: " << (answer[0]).size() << endl;
		for (int i = 0; i < answer.size(); i++){
			cout << "ans[" << i << "]: ";
			for (int j = 0; j < (answer[i]).size()-1; j++){
				cout << (answer[i])[j] << " -> ";
			}
			cout << (answer[i])[(answer[i]).size()-1] << endl;
		}
	} 
	
	
	
	ofs << "=====  Answer Report  =====" << endl;
	ofs << "CPU Run time: " << run_time << endl;
	ofs << "Mem Usage:    " << r_usage.ru_maxrss << endl;
	ofs << "Word ladder number: " << answer.size() << endl;
	if (answer.size() > 0){
		ofs << "Word ladder length: " << (answer[0]).size() << endl;
		for (int i = 0; i < answer.size(); i++){
			ofs << "ans[" << i << "]: ";
			for (int j = 0; j < (answer[i]).size()-1; j++){
				ofs << (answer[i])[j] << " -> ";
			}
			ofs << (answer[i])[(answer[i]).size()-1] << endl;
		}
	}
		
	ofs.close();
	
	
	
	return 0;
}
