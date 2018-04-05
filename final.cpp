#include<bits/stdc++.h>
#include<dirent.h>
#define pb push_back
using namespace std;

struct TrieNode
{
     struct TrieNode *children[256];
     bool isEndOfWord;
     int i;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < 256; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}



vector <string> conv(string line)
{			vector<string> temp;
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			string cur="";
			int start = 0;

			while(start<line.length() )
   			{
    			cur = cur + line[start];
      			start++;

      			if(line[start] == ' '|| start==line.length() )
      			{
      				temp.push_back(cur);
      				cur = "";
      				start++;
				}
			}
		return temp;
}

string detectdatetime(string s, vector <string> &outdt, vector <string> &outday, vector<string> &outdate)
{

    //cout<<"satar";
if(s[s.length()-1]=='.' && s[s.length()-2]!='m' && s[s.length()-3]!='.')
{
	s.erase(s.length()-1);
}

vector <string> time;
time.pb("a.m.");
time.pb("p.m.");
time.pb("a.m");
time.pb("p.m");
time.pb("clock");
time.pb("o'clock");


vector <string> day;
day.pb("tuesday");
day.pb("monday");
day.pb("wednesday");
day.pb("thursday");
day.pb("friday");
day.pb("saturday");
day.pb("sunday");
day.pb("today");
day.pb("tomorrow");
day.pb("yesterday");


vector <string> month;
month.pb("january");
month.pb("february");
month.pb("march");
month.pb("april");
month.pb("may");
month.pb("june");
month.pb("july");
month.pb("august");
month.pb("september");
month.pb("october");
month.pb("november");
month.pb("december");


int c1,c2,c3;


vector <string> s1 = conv(s);

vector <string> out1;
vector <string> out2;
vector <string> out3;

//vector <string> outdt;

int ii=0,ij=0,ik=0;

for(int i=0;i<s1.size();i++)
{
	if(s1[i]=="") continue;

    int ii=0,ij=0,ik=0;
	c1=0;
	for(int j=0;j<time.size();j++)
	{
	    vector <string> temp;
		if(s1[i]==time[j])
		{


			temp.push_back(time[j]);
			s1[i]="<datetime>";
			c1=1;

		if(c1==1 && i-1>0 && s1[i-1]=="o" && s1[i-2][0]>='0' && s1[i-2][0]<='9')
        {
            vector<string>::iterator it=temp.begin();
		    temp.insert(it,s1[i-1]);
		    it=temp.begin();
		    temp.insert(it,s1[i-2]);
            s1[i-2]="";
            s1[i-1]="";
            s1[i]="<datetime>";

        }
        else
		if(c1 == 1 &&i>0 && s1[i-1][0]>='0' && s1[i-1][0]<='9')
		{
		    vector<string>::iterator it=temp.begin();
		    temp.insert(it,s1[i-1]);
			s1[i-1]="";

		}
		else if(c1 == 1 &&i<(s1.size()-1) && s1[i+1][0]>='0' && s1[i+1][0]<='9')
		{
		    temp.push_back(s1[i+1]);
			s1[i+1]="";
		}

		string an="";

		for(int i=0;i<temp.size();i++)
        {
            an= an + temp[i];
            if(i!=temp.size()-1)
			an=an+" ";
        }
      //  cout<<"debug 0 "<<an <<"\n";
        out1.push_back(an);

		}
	}

	if(c1==1) continue;

	c2=0;

	for(int j=0;j<day.size();j++)
	{
		if(s1[i]==day[j])
		{
		 //   cout<<"debug 1 "<<day[j] <<"\n";
		    out2.push_back(day[j]);
			s1[i]="<day>";
			c2=1;
		}
	}

	if(c2==1) continue;

	c3=0;

	for(int j=0;j<month.size();j++)
	{
	    vector <string> temp;
		if(s1[i]==month[j])
		{
			s1[i]="<date>";
			temp.push_back(month[j]);
			c3=1;


		if(c3 == 1 && i>0 && s1[i-1][0]>='0' && s1[i-1][0]<='9')
		{
		    vector<string>::iterator it=temp.begin();
		    temp.insert(it,s1[i-1]);
			s1[i-1]="";
		}

		if(c3 == 1 && i<(s1.size()-1) && s1[i+1][0]>='0' && s1[i+1][0]<='9')
		{
		    temp.push_back(s1[i+1]);
			s1[i+1]="";
		}

		string an="";

		for(int i=0;i<temp.size();i++)
        {
            an= an + temp[i];
            if(i!=temp.size()-1)
			an=an+" ";
        }
     //   cout<<"debug 2 "<<an <<"\n";
        out3.push_back(an);
		}
	}


}

vector <string> s2;

for(int i=0;i<s1.size();i++)
{
	if(s1[i]!="")
	{
		s2.push_back(s1[i]);
	}

}



//cout<<"\n";

/*
for(int i=0;i<s2.size();i++)
{
    cout<<s2[i]<<"\n";
}
*/

//cout<<"\n";
for(int i=0;i<s2.size();i++)
{
	if(s2[i]=="<date>")
	{
		if(i>0 && s2[i-1]=="<datetime>")
		{
			s2[i-1]="<datetime>";
			s2[i]="";

            string temp= "";

            temp = temp + out1[ii];
            ii++;
            temp = temp + " ";
            temp = temp + out3[ik];
            ik++;

      //      cout<<"debug 3 "<<temp<<"\n";
            outdt.push_back(temp);
		}

        else
		if(i<(s2.size()-1) && s2[i+1]=="<datetime>")
		{
			s2[i]="<datetime>";
			s2[i+1]="";

			string temp = "";
			temp = temp + out3[ik];
			ik++;
			temp= temp + " ";
			temp = temp + out1[ii];
			ii++;
         //   cout<<"debug 4 "<<temp<<"\n";
            outdt.push_back(temp);


		}

		else
        {
      //      cout<<"debug 5 "<<out3[ik]<<"\n";
            outdate.push_back(out3[ik]);
            ik++;
        }

	}
	else
    if(s2[i]=="<day>")
	{
		if(i>0 && s2[i-1]=="<datetime>")
		{
			s2[i-1]="<datetime>";
			s2[i]="";

            string temp= "";

            temp = temp + out1[ii];
            ii++;
            temp = temp + " ";
            temp = temp + out2[ij];
            ij++;
      //      cout<<"debug 6 "<<temp<<"\n";
            outdt.push_back(temp);
		}

        else
		if(i<(s2.size()-1) && s2[i+1]=="<datetime>")
		{
			s2[i]="<datetime>";
			s2[i+1]="";

			string temp = "";
			temp = temp + out2[ij];
			ij++;
			temp= temp + " ";
			temp = temp + out1[ii];
			ii++;
      //      cout<<"debug 7 "<<temp<<"\n";
			outdt.push_back(temp);

		}
		else
        {
       //     cout<<"debug 8 "<<out2[ij]<<"\n";
            outday.push_back(out2[ij]);
            ij++;
        }


	}

	else if(s2[i]=="<datetime>")
    {

        if(i>0 && s2[i-1]=="<date>")
		{
			s2[i-1]="<datetime>";
			s2[i]="";

            string temp= "";


            temp = temp + out3[ik];
            ik++;
            temp = temp + " ";
            temp = temp + out1[ii];
            ii++;


        //    cout<<"debug 9 "<<temp<<"\n";
            outdt.push_back(temp);
		}

        else
		if(i<(s2.size()-1) && s2[i+1]=="<date>")
		{
			s2[i]="<datetime>";
			s2[i+1]="";

			string temp = "";

			temp = temp + out1[ii];
			ii++;
			temp= temp + " ";
			temp = temp + out3[ik];
			ik++;

     //       cout<<"debug 10 "<<temp<<"\n";
            outdt.push_back(temp);


		}
        else
            if(i>0 && s2[i-1]=="<day>")
		{
			s2[i-1]="<datetime>";
			s2[i]="";

            string temp= "";


            temp = temp + out1[ii];
            ii++;
            temp = temp + " ";
            temp = temp + out2[ij];
            ij++;


       //     cout<<"debug 11 "<<temp<<"\n";
            outdt.push_back(temp);
		}

        else
		if(i<(s2.size()-1) && s2[i+1]=="<day>")
		{
			s2[i]="<datetime>";
			s2[i+1]="";

			string temp = "";

			temp = temp + out1[ii];
			ii++;
			temp= temp + " ";
			temp = temp + out2[ij];
			ij++;

     //       cout<<"debug 12 "<<temp<<"\n";
            outdt.push_back(temp);


		}
		else
        {
        //    cout<<"debug 13 "<<out1[ii]<<"\n";
            outdt.push_back(out1[ii]);
            ii++;
        }
    }


}

//cout<<"\n";
/*
for(int i=0;i<outdt.size();i++)
{
    cout<<"outdt "<<i<<" "<<outdt[i]<<"\n";
}
*/

string ans="";

for(int i=0;i<s2.size();i++)
{
	if(s2[i]!="" && s2[i]!=" ")
	{
		ans=ans+s2[i];
		if(i!=s2.size()-1)
			ans=ans+" ";
	}
}



//cout<<"\n";
return ans;

}


//Insertion in A Trie
void insert(struct TrieNode *root, string key,int k)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i];
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
    pCrawl->i = k;
}



//String Matching LCS ans return Probability
float LCS(vector<string> A, vector<string> B){
	int n = A.size();
	int m = B.size();
	
	int lcs[n+1][m+1];
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if(i==0||j==0)
			{
				lcs[i][j] = 0;
			}
			else if(A[i-1]==(B[j-1]))
			{
				lcs[i][j] = lcs[i-1][j-1] + 1;
			}
			else
			{
				lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
			}
		}
	}
	
	
	float denom = max(A.size(), B.size());
    float prob = (float)lcs[n][m]/(float)denom;
    return prob;
}


struct probability{
	int index;
	float value;
};


//finding maximum match grammer and respective Probablity
probability maxMatchGram(vector<vector<vector<string > > > Grammar, vector<string> out)
{
	struct probability p;
	p.index = -1;
	p.value= INT_MIN;
	
	int count =0;
	for(int i=0; i<Grammar.size(); i++)
    {
    	for(int j = 0; j<Grammar[i].size(); j++)
    	{
    		float prob = LCS(out, Grammar[i][j]);
    		if(p.value<prob)
    		{
    			p.value= prob;
    			p.index = count;
			}
			count++;
    	}
    }
    
    return p;
}



//Give Path to all files of a Folder
void explore(char* dir_name,vector<string> &s)
{
	DIR *dir; //pointer to open directory
	struct dirent *entry; //stuff inside the direct

	dir = opendir(dir_name);
	if (!dir) {
 		cout << "Directory was not found";
  		return;
 	}
 
 	while ((entry = readdir(dir)) != NULL)
 	{
  		if (entry->d_name[0] != '.')
  		{
   			string path = string(dir_name) + '/' + string(entry->d_name);
   			s.push_back(path);
  		}
 	}
 	closedir(dir);
}



//Creation of List of Files in a Folder
void createlist(char* dir_name,vector<string> &s, string x)
{
	DIR *dir; //pointer to open directory
	struct dirent *entry; //stuff inside the direct

	dir = opendir(dir_name);
	if (!dir) {
 		cout << "Directory was not found";
  		return;
 	}
 
 	while ((entry = readdir(dir)) != NULL)
 	{
  		if (entry->d_name[0] != '.')
  		{
  		string st = string(entry->d_name);
  		string path;
  		if(x=="Concept")
   			path = '{' + st.substr(0,st.length()-4) + '}';
   		else if(x=="PlaceHolder")
   			path = '<' + st.substr(0,st.length()-4) + '>';
   		else if(x=="Grammar")
   			path = st.substr(0,st.length()-4);
   		s.push_back(path);
  		}
 	}
 	closedir(dir);
}



//Search and create Equivalent Grammer
vector<string> CreateGrammer(struct TrieNode *root, string input, vector<string> CPList, vector<string> &P, vector<string> &C)
{
	vector<string> out;
	struct TrieNode *pCrawl = root;
	int start = 0;
	int i =0;
    while(i < input.length() )
    {
        int index = input[i];
		
        if(pCrawl != NULL && pCrawl->isEndOfWord)  
 		{
 			out.push_back(CPList[pCrawl->i]);
 			if(CPList[pCrawl->i] == "<contact_name>" || CPList[pCrawl->i] == "<place>")
 			{
 				string cur="";
            	int j = start;
            	while( j<i &&  j<input.length() )
            	{
            		cur = cur + input[j];
            		j++;
				}
 				if(CPList[pCrawl->i] == "<contact_name>" )
 					C.push_back(cur);
 				else if(CPList[pCrawl->i] == "<place>" )
 					P.push_back(cur);
			}
			
 			start = i+1;
 			pCrawl = root;
 			i = i+1;
 			continue;
 		}
 		
        else if(pCrawl != NULL && !(pCrawl->children[index]))
    	{
    		string cur="";
            int j = start;
            while(input[j] != ' ' && j<input.length() )
            {
            	cur = cur + input[j];
            	j++;
			}
			start = j+1;
			out.push_back(cur);
			i = j+1;
			pCrawl = root;
			continue;
		}
 		i++;
 		if(pCrawl)
        	pCrawl = pCrawl->children[index];
    }
 
    if(pCrawl != NULL && pCrawl->isEndOfWord)
    {
    	out.push_back(CPList[pCrawl->i]);
    	if(CPList[pCrawl->i] == "<contact_name>" || CPList[pCrawl->i] == "<place>")
 			{
 				string cur="";
            	int j = start;
            	while( j<i &&  j<input.length() )
            	{
            		cur = cur + input[j];
            		j++;
				}
 				if(CPList[pCrawl->i] == "<contact_name>" )
 					C.push_back(cur);
 				else if(CPList[pCrawl->i] == "<place>" )
 					P.push_back(cur);
			}
    	start = i+1;
	}
	
	
	string cur="";
    while(input[start] != ' ' && start<input.length() )
    {
    	cur = cur + input[start];
      	start++;
	}			
	out.push_back(cur);
	
	int j =0;
	int k =0;
	for(int i=0; i<out.size(); i++)
		{
			if(i+1<out.size() &&  out[i+1]==out[i] && out[i]=="<contact_name>")
			{
				out.erase(out.begin() + i+1);
				C[j] = C[j] + " " + C[j+1];
				C.erase(C.begin() + j+1);
			}
			else if(out[i] == "<contact_name>")
				j++;
			else if(out[i] == "<place>")
				k++;
		}
		
	return out;
}



bool case_f(string S){
	if(S[0]=='C' && S[1] =='a' && S[2]=='s' && S[3]=='e' && S[4]=='#'){
		return true;
	}
	else return false;
}



vector<string> openphase(vector<string> all, vector<string> gram)
{
	vector<string> ans;
	for(int i=0; i<all.size(); i++)
	{
		if(find(gram.begin(), gram.end(), all[i]) != gram.end())
			ans.push_back(all[i]);
	}
	return ans;
}

vector<string> swr(vector<string> a)
{
	long long int len= a.size(),i;
	
	string arr[] = {"ourselves", "hers’", "between", "yourself", "but", "again", "there", "about", "once", "during", "out", "very", "having", "with", "they", "own", "an", "be", "some", "for", "do", "its", "ours", "such", "into", "of", "most", "itself", "other", "off", "is", "s", "am", "or", "who", "as", "from", "him", "each", "the", "themselves", "until", "below", "are", "we", "these", "your", "his", "through", "don", "nor", "me", "were", "her", "more", "himself", "this", "down", "should", "our", "their", "while", "above", "both", "up", "to", "ours", "had", "she", "all", "no", "when", "at", "any", "before", "them", "same", "been", "have", "in", "will", "on", "does", "yourselves", "then", "that", "because", "what", "over", "why", "so", "can", "did", "not", "now", "under", "he", "you", "herself", "has", "just", "where", "too", "only", "myself", "which", "those", "i", "after", "few", "whom", "t", "being", "if", "theirs", "my", "against", "a", "by", "doing", "it", "how", "further", "was", "here", "than"};
	int n = sizeof(arr)/sizeof(arr[0]);
	vector<string> words(arr, arr+n);
	words.push_back("this");
	words.push_back("is");
	words.push_back("the");
	words.push_back("a");
	words.push_back("an");
	words.push_back("are");
	words.push_back("then");
	words.push_back("that");
	words.push_back("their");
	words.push_back("to");
	words.push_back("was");
	words.push_back("were");
	words.push_back("at");
	words.push_back("have");
	words.push_back("about");
	words.push_back("it");
	words.push_back("in");
	words.push_back("will");
	words.push_back("on");
	words.push_back("from");
	words.push_back("do");
	words.push_back("here");
	words.push_back("so");
	words.push_back("into");
	words.push_back("let");
	words.push_back("or");
	words.push_back("for");
	words.push_back("with");
	words.push_back("me");
	words.push_back("i");
	words.push_back("want");
	words.push_back("now");
	for(i=0;i<len;i++)
	{
		if(find(words.begin(),words.end(),a[i])!=words.end())
		{
			a.erase(a.begin()+i);
			len=a.size();
			i--;
		}
	}
	return a;
}

float distance2(map<string,float>m1,map<string,float>m2){
	set<string>s;
	float ans=0;
	map<string,float>::iterator it;
	for(it=m1.begin();it!=m1.end();it++)
	s.insert(it->first);
	for(it=m2.begin();it!=m2.end();it++)
	s.insert(it->first);
	set<string>::iterator it2;
	for(it2=s.begin();it2!=s.end();it2++)
	{
		ans=ans+(m1[*it2]-m2[*it2])*(m1[*it2]-m2[*it2]);
	}
	float k = 0.5f;
		ans = powf(ans , k);
	return ans;
}

set<string> Bagofwords(vector<vector<vector<string > > >b){
	set<string> s;
	for(int i=0;i<b.size();i++){
		for(int j=0;j<b[i].size();j++){
			for(int k =0;k<b[i][j].size();k++){
				s.insert(b[i][j][k]);
			}
		}
	}
	return s;
}

map<string,float> idf(vector<vector<vector<string > > >b , set<string> s, int no){
	//cout<<no;
	map<string,float> m;
	set <string> :: iterator itr;
	for (itr = s.begin(); itr != s.end(); ++itr){
		int count = 0;
		for(int i=0;i<b.size();i++){
			for(int j=0;j<b[i].size();j++){
				for(int k =0;k<b[i][j].size();k++){
					if(b[i][j][k] == *itr){
						count++;
						break;
					}
				}
			}
		}
		//cout<<*itr<<" "<<count<<" ";
		float idf = logf ((float)no/(float)(1+count));
		m[*itr] = idf;
		
		//cout<<*itr<<" "<<m[*itr]<<endl;
	}
	return m;
}

vector<map<string,float > > tfidf(vector<vector<vector<string > > >b ,map<string,float> idf1){
	vector<map<string,float > > m;
	for(int i=0;i<b.size();i++){
		for(int j=0;j<b[i].size();j++){
			map<string ,float> tf;
			map<string ,float> tfidf1;
			map<string ,float> :: iterator itr;
			for(int k =0;k<b[i][j].size();k++){
				tf[b[i][j][k]]++;
				//cout<<b[i][j][k]<<" "<<tf[b[i][j][k]]<<"  ";
			}
			for(int k =0;k<b[i][j].size();k++){
				tfidf1[b[i][j][k]] = tf[b[i][j][k]] * idf1[b[i][j][k]];
				//cout<<b[i][j][k]<<" "<<tfidf1[b[i][j][k]]<<"  ";
			}
			//cout<<endl;
			float sum = 0.0f;
			for(itr = tfidf1.begin(); itr != tfidf1.end(); itr++){
				//cout<<itr->second<<" ";
				sum += (itr->second * itr->second);
			}
			/*float k = 0.5f;
			sum = powf(sum , k);
			for(itr = tfidf1.begin(); itr != tfidf1.end(); itr++){
				itr->second = (itr->second) / sum;
			}
			m.push_back(tfidf1);*/
		}
	}
	return m;
}

pair<int,float> compareWithGrammar(vector<map<string,float> > Tfidf, vector<string> input,map<string,float> idf1){
	float prob = 10000000.0f;
	int point = 0;
	set<string> s;
	for(int i=0;i<input.size();i++){
		s.insert(input[i]);
	}
	map<string ,float> tf;
	map<string ,float> tfidf1;
	map<string ,float> :: iterator itr;
	for(int i=0;i<input.size();i++){
		tf[input[i]]++;
		for(int k =0;k<input.size();k++){
			tfidf1[input[i]] = tf[input[i]] * idf1[input[i]];
		}
		float sum = 0;
		for(itr = tfidf1.begin(); itr != tfidf1.end(); itr++){
			sum += (itr->second * itr->second);
		}
		float k = 0.5f;
		sum = powf(sum , k);
		for(itr = tfidf1.begin(); itr != tfidf1.end(); itr++){
			itr->second = (itr->second) / sum;
		}
	}
	
	for(int i=0;i<Tfidf.size();i++){
		float a = distance2(Tfidf[i],tfidf1);
		//cout<<a<<"  ";
		if(a<prob){
			prob  = a;
			point = i;
		}
	}
	pair<int,float> pair1 = make_pair(point,prob);
	return pair1;
}


vector<string> allopen()
{
	string line;
    vector<string> A;
    ifstream myfile;
	myfile.open("PlaceHolder/PlaceHolderDetail.txt");

    if(!myfile)
    {
        cout<<"Error opening input file"<<endl;
        system("pause");
        return A;
    }
    int i;
    while (getline(myfile, line))
	{
		string s="";
		int flag=0;
		for(i=0;i<line.length();i++){
		s=s+line[i];
		if(line[i+1]=='	')
		{
			if(line[i+2]=='o')
			flag=1;
			break;
		}
	}
		if(flag==1)
		A.push_back(s);
    }
    return A;
}



//Driver Function
int main()
{
//Create Lists
	string line;
	vector<string> CPList, GList;
	createlist((char*)"Concept",CPList, "Concept");
	createlist((char*)"PlaceHolder",CPList, "PlaceHolder");
	createlist((char*)"Grammar",GList, "Grammar");

/*
//Print the Concept And Place Holder Lists
	for(int i=0; i<CPList.size(); i++)
		cout<<CPList[i]<<endl;

//Print all the Grammer names
	for(int i=0; i<GList.size(); i++)
		cout<<GList[i]<<endl;
*/

//Path to files of concept And Placeholder and Grammar
	vector<string> S, G;
	explore((char*)"Concept",S);
	explore((char*)"PlaceHolder",S);
	explore((char*)"Grammar",G);

/*for(int i=0; i<S.size(); i++)
	cout<<S[i]<<endl;
*/
	
//Create Trie for Concept And PlaceHolder
	struct TrieNode *root = getNode();
	for(int i=0;i<S.size();i++){
		string a= S[i];
		const char* b = a.c_str();
		ifstream myfile(b);
		if(!myfile)
    	{
        	cout<<"Error opening input file"<<endl;
        	system("pause");
        	return -1;
    	}
    	if(S[i] != "PlaceHolder/contact_name.txt" && S[i] != "Concept/weather_activity.txt")
    		while (std::getline(myfile, line))
			{
				transform(line.begin(), line.end(), line.begin(), ::tolower);
				insert(root,line,i);
    		}
    	
    	else
    	{
	    	while (std::getline(myfile, line))
			{
				transform(line.begin(), line.end(), line.begin(), ::tolower);
				insert(root,line,i);
				string cur="";
				int start = 0;
	    		while(start<line.length() )
	   			{
	    			cur = cur + line[start];
	      			start++;
	      			if(line[start] == ' '|| start==line.length() )
	      			{
	      				insert(root,cur,i);
	      				cur = "";
	      				start++;
					}
				}					
	    	}	
		}
	}
	
	

//Preproccesing the Grammar Folder	and Store in the Grammer Vector
	vector<vector<vector<string> > > Grammar;
	
	for(int i=0;i<G.size();i++)
	{	
		string a= G[i];
		const char* b = a.c_str();
		ifstream myfile(b);
		if(!myfile)
    	{
        	cout<<"Error opening input file"<<endl;
        	system("pause");
        	return -1;
    	}
    	
    	vector<vector<string> > Grammar1;
		while (std::getline(myfile, line))
		{
			vector<string> temp;
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			string cur="";
			int start = 0;
    		
			while(start<line.length() )
   			{
    			cur = cur + line[start];
      			start++;
      			if(line[start] == ' '|| line[start] == '{' || line[start] == '<'|| start==line.length() )
      			{
      				temp.push_back(cur);
      				cur = "";
      				while(line[start] == ' ' && line[start+1] == ' ')
      					start++;
      				if(line[start] != '{' && line[start] != '<')
					  start++;
				}
			}
			Grammar1.push_back(temp);		
    	}
    	Grammar.push_back(Grammar1);
    }



//Print all the Given Grammer in Folder
   int count= 0;
   map<int,pair<int,int> > Gno;
    for(int i=0; i<Grammar.size(); i++)
    {
    	cout<<GList[i]<<endl;
    	for(int j = 0; j<Grammar[i].size(); j++)
    	{
    		Gno[count] = make_pair(i,j);
    		cout<<count<<"  -> ";
    		for(int k=0; k<Grammar[i][j].size(); k++)
    			cout<<Grammar[i][j][k]<<" ";
    		cout<<endl;
    		count++;
		}
		
    		
    	cout<<endl;
	}

	
//Conjuction array
	string con[] = {"and", "or", "meanwhile", "therefore", "thus", "also", "but", "because", "although", "so", "while"};
	int conSize = sizeof(con)/sizeof(con[0]);


//Input
	vector<string> A;
    ifstream myfile("Testing/input.txt");
    if(!myfile)
    {
        cout<<"Error opening input file"<<endl;
        system("pause");
        return -1;
    }
    while (std::getline(myfile, line))
	{
    	if(line.length()>1 && !case_f(line))
        	A.push_back(line);
    }
	
// grammar2
	int no=0;
	vector<vector< vector<string> > > Grammar2;
	for(int i =0;i<Grammar.size();i++){
		vector< vector<string>  > Grammar2_temp;
		for(int j=0;j<Grammar[i].size();j++){
			vector< string> temp2 = swr(Grammar[i][j]);
			Grammar2_temp.push_back(temp2);
			no++;
		}
		Grammar2.push_back(Grammar2_temp);
	}
	
	/*count = 0;
	for(int i=0; i<Grammar2.size(); i++)
    {
    	cout<<GList[i]<<endl;
    	for(int j = 0; j<Grammar2[i].size(); j++)
    	{
    		cout<<count<<"  -> ";
    		for(int k=0; k<Grammar2[i][j].size(); k++)
    			cout<<Grammar2[i][j][k]<<" ";
    		cout<<endl;
    		count++;
		}
		
    		
    	cout<<endl;
	}
	*/
//tfidf pre
cout<<no<<"yersssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	set<string> s = Bagofwords(Grammar2);
	map<string,float > IDF = idf(Grammar2 ,s,no);
	vector<map<string,float > >  TFIDF = tfidf(Grammar2,IDF);

//Output File
	ofstream ofile; 
	ofile.open ("Testing/output.txt");
	for(int icount =0 ; icount<A.size(); icount++)
	{
		vector<string> P,C,DT,Day,Date;
		string input = detectdatetime(A[icount], DT, Day, Date);
	
//Equivalent Grammer
		
		vector<string> out = CreateGrammer(root, input, CPList, P, C);
		
		/*
		for(int i=0; i<P.size(); i++)
			cout<<"<places>  :"<<P[i]<<endl;
		for(int i=0; i<C.size(); i++)
			cout<<"<contact_name>  :"<<C[i]<<endl;
		for(int i =0; i<D.size(); i++)
			cout<<"<datetime>  :"<<D[i]<<endl; 
		*/
//Search
		probability p = maxMatchGram(Grammar,out);
		 
		vector<string> all = allopen();
		vector<string> oPhase = openphase(all, Grammar[Gno[p.index].first][Gno[p.index].second]) ;
		for(int i =0; i<oPhase.size(); i++)
		{
			cout<<oPhase[i]<<endl;
		}
		/*
//Search for conj case
		probability p1, p2, pf;
		pf.value = p.value;
		
		for(int i =0; i<out.size(); i++)
		{
			for(int j =0; j<conSize; j++)
			{
				if(con[j] == out[i])
				{
					vector<string> out1(out.begin() , out.begin() + i-1);
					vector<string> out2(out.begin()+i+1, out.end());
					probability temp1 = maxMatchGram(Grammar,out1);
					probability temp2 = maxMatchGram(Grammar,out2);
					
					if((temp1.value + temp2.value )/2 > pf.value)
					{
						p1.index = temp1.index;
						p1.value = temp1.value;
						p2.index = temp2.index;
						p2.value = temp2.value;
						pf.value = (temp1.value + temp2.value )/2;
					}
				}
				
			}
		}
		*/
		
		
//Print the parsed input Equivalent Grammar		
		for(int i=0; i<out.size(); i++)
			cout<<out[i]<<" ";
		cout<<endl;
		
//tfidf
		out = swr(out);
		pair<int,float> p11 =  compareWithGrammar(TFIDF, out,IDF);
		
		if(oPhase.size()>0)
		{
			vector<string> out1;
			for(int i =0; i<out.size(); i++)
				out1.push_back(out[i]);
			for(int i=0;i<oPhase.size();i++)
			{
				out1.push_back(oPhase[i]);
			}
	
			pair<int,float> p22 =  compareWithGrammar(TFIDF, out1, IDF);
	
			if(p22.second<=p11.second)
			{
				p.index = p22.first;	
			}
			
			else
				p.index = p11.first;
		}
		else
		{
			p.index = p11.first;
		}
		
		
//OutPut
		ofile<<"Case# "<<icount+1<<":";
		/*if(pf.value  > p.value)
		{
			ofile<<endl<<GList[Gno[p1.index].first]<<endl<<GList[Gno[p2.index].first];
		}
		else*/
			ofile<<endl<<GList[Gno[p.index].first]<<endl;
			for(int i=0; i<P.size(); i++)
				ofile<<"<places> : "<<P[i]<<endl;
			for(int i=0; i<C.size(); i++)
				ofile<<"<contact_name> : "<<C[i]<<endl;
			for(int i =0; i<DT.size(); i++)
				ofile<<"<datetime> : "<<DT[i]<<endl;
			for(int i =0; i<Day.size(); i++)
				ofile<<"<day> : "<<Day[i]<<endl;
			for(int i =0; i<Date.size(); i++)
				ofile<<"<date> : "<<Date[i]<<endl;
			
		ofile<<endl;
	}
	

return 0;
}
