#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <iomanip>
#include <stack>
using namespace std;
const int maxnlen = 1e4;
class Grammar {
private:
	set<char>Vn;
	set<char>Vt; 
	char S;
	map<char, set<string> > P;
	map<char,set<char> >FIRST;
	map<char,set<char> >FOLLOW;
	map<string, string>Table;
public:
	Grammar(string filename) {
		Vn.clear();
		Vt.clear();
		P.clear();
		FIRST.clear();
		FOLLOW.clear();
		ifstream in(filename);
		if (!in.is_open()) {
			cout << "�ķ�  �ļ���ʧ��" << endl;
			exit(1);
		}
		char *buffer = new char[maxnlen];
		in.getline(buffer, maxnlen, '#');
		string temps = "";
		bool is_sethead = 0;
		for (int i = 0; i < strlen(buffer); i++) {
			if (buffer[i] == '\n' || buffer[i] == ' ')continue;
			if (buffer[i] == ';') {
				if (!is_sethead) {
					this->setHead(temps[0]);
					is_sethead = 1;
				}
				this->add(temps);
				temps = "";
			}
			else
				temps += buffer[i];
		}
		delete buffer;
		/*
			���Vn��Vt��set
			
		*/
		
	}
	void setHead(char c) {
		S = c;
	}
	void add(string s) {
		char s1 = s[0];
		string s2="";
		int num = 0;
		for (int i = 0; i < s.length() ; i++) {
			if (s[i] == '>')num=i;
			if (num == 0)continue;
			if (i > num)
				s2 += s[i];
		}
		s2 += ';';
		Vn.insert(s1);
		string temp = "";
		//set<char>::iterator iter1 = s2.begin();
		for (int i = 0; i < s2.length() ; i++) {//char s : s2
			char s=s2[i];
			if (!isupper(s) && s != '|'&&s != ';'&&s!='@')Vt.insert(s);
			if (s == '|' || s == ';') {
				P[s1].insert(temp);
				temp = "";
			}
			else {
				temp += s;
			}
		}
	}
	void print() {
		cout << "��ǰ�����ķ�Ϊ��" << endl << endl;
		for (set<char>::iterator it = Vn.begin(); it != Vn.end(); it++) {
			char cur_s = *it;
			for (set<string>::iterator it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
				string cur_string = *it1;
				cout << cur_s << "->" << cur_string << endl;
			}
		}
	}
	void getFirst() {
		FIRST.clear();
		//�жϵ�������
		int iter = 4;
		while (iter--) {
			for (set<char>::iterator it = Vn.begin(); it != Vn.end(); it++) {
				char cur_s = *it;
				/*����ʵ�����¹���
				***************************************************************************************
				cur_s->cur_string[0]
					a�ӵ�A��FIRST��
				cur_s->cur_string[0]
					B��FITRST���ӵ�A��FIRST��
				*/
				









			}
		}
		//���FIRST��
		cout << "FIRST��Ϊ��" << endl << endl;
		for (set<char>::iterator it = Vn.begin(); it != Vn.end();it++) {
			char cur_s = *it;
			cout << "FIRST()   " << cur_s ;
			for (set<char>::iterator it1 = FIRST[cur_s].begin(); it1 != FIRST[cur_s].end(); it1++) {
				 cout<<"       " << *it1 ;
			}
			cout << endl;
		}
	}
	void getFollow() {
		FOLLOW.clear();
		FOLLOW[S].insert('#');
		//�жϵ�������
		int iter = 4;
		while (iter--) {
			for (set<char>::iterator it = Vn.begin(); it != Vn.end(); it++) {
				char cur_s = *it;
				/*����ʵ�����¹���
				***************************************************************************************
				cur_s->cur_string[0]
				a�ӵ�A��FIRST��
				cur_s->cur_string[0]
				B��FITRST���ӵ�A��FIRST��
				*/
				for (set<string>::iterator it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
					string cur_string = *it1;
					for (int i = 0; i < cur_string.length() - 1; i++) {
						/*��һ����
							B->Ac
							��c�ӵ�A��follow��
						*/



						
						/*�ڶ�����
							B->AC
							��C��first���ӵ�A��follow��
						*/



						
					   //������������C��firstȥ��@���ӵ�A��follow��
							


					/* ���Ĳ���
					AC/ACKΪ���������������
					B->AC
					B->ACK(K��first������@)
					��B��follow�����뵽C��follow��
					*/				



					}
				}
			}
		}
		//���FOLLOW��
		cout << "FOLLOW��Ϊ��" << endl << endl;
		for (set<char>::iterator it = Vn.begin(); it != Vn.end(); it++) {
			char cur_s = *it;
			cout << "FOLLOW()  " << cur_s;
			for (set<char>::iterator it1 = FOLLOW[cur_s].begin(); it1 != FOLLOW[cur_s].end(); it1++) {
				cout << "       " << *it1;
			}
			cout << endl;
		}
	}
	void getTable() {
		set<char>Vt_temp;
		//int i = 0; i < s2.length() ; i++
		//set<char>::iterator iter1;
		for (set<char>::iterator iter1 =Vt.begin(); iter1!=Vt.end();iter1++ ) {
			//char c=Vt[iter1];
			Vt_temp.insert(*iter1);
		}
		Vt_temp.insert('#');
		for (auto it = Vn.begin(); it != Vn.end(); it++) {
			char cur_s = *it;
			for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
				/*
				����ʽΪ
					cur_s->cur_string
				*/
				string cur_string = *it1;
				if (isupper(cur_string[0])) {
					char first_s = cur_string[0];
					for (auto it2 = FIRST[first_s].begin(); it2 != FIRST[first_s].end(); it2++) {
						string TableLeft = "";
						TableLeft = TableLeft +cur_s + *it2;
						Table[TableLeft] = cur_string;
					}
					
				}
				else {
					string TableLeft = "";
					TableLeft = TableLeft+ cur_s + cur_string[0];
					Table[TableLeft] = cur_string;
				}	
			}
			if (FIRST[cur_s].count('@') > 0) {
				for (auto it1 = FOLLOW[cur_s].begin(); it1 != FOLLOW[cur_s].end(); it1++) {
					string TableLeft = "";
					TableLeft =TableLeft+ cur_s + *it1;
					Table[TableLeft] = "@";
				}
			}
		}
		/*
			��������Ϣ���������û�г��ֹ���
		*/
		
		
		for (auto it = Vn.begin(); it != Vn.end(); it++) {
			for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
				string TableLeft = "";
				TableLeft =TableLeft+ *it + *it1;
				if (!Table.count(TableLeft)) {
					Table[TableLeft] = "error";
				}
			}
		}
		
		/*����ʵ�����¹���
		***************************************************************************************				
			��ʾTable�������ʽ��ӡ��cout << *it << "->" << setw(7) << Table[iter];
		*/
		cout << "��ʾtable��" << endl << endl;
		












	}
	/*
		ÿһ�η���һ�����봮
		SignΪ����ջ,��ջ�ַ�Ϊx
		�����ַ�����ǰ�ַ�Ϊa
	*/
	bool AnalyzePredict(string inputstring){
		stack<char>Sign;
		Sign.push('#');
		Sign.push(S);
		int StringPtr = 0;
		char a = inputstring[StringPtr++];
		bool flag = true;
		while (flag) {
			char x = Sign.top();
			Sign.pop();
			//������ս��,ֱ���Ƴ�����ջ
			if (Vt.count(x)) {
				if (x == a)a = inputstring[StringPtr++];
				else
					return false;
			}
			else {
				/*����ʵ�����¹���
				***************************************************************************************
				*/
				//��һ������������ս���������ĩβ����
				
				//�ڶ���������Ƿ��ս������Ҫ�ƽ�����




				
				
			}		
		}
		return true;
	}
	/*
		������ݹ��㷨����P124
	*/
	void remove_left_recursion(){
		string tempVn = "";
		for (auto it = Vn.begin(); it != Vn.end(); it++) {
			tempVn += *it;
		}
		
		for (int i = 0; i < tempVn.length(); i++) {
			char pi = tempVn[i];
			/*����ʵ��������ݹ���滻�������
				***************************************************************************************
			*/















			remove_left_gene(pi);
		}
	}
	/*
		����ֱ����ݹ�
	*/
	void remove_left_gene(char c) {
		char NewVn;
		for (int i = 0; i < 26; i++) {
			NewVn = i + 'A';
			if (!Vn.count(NewVn)) {
				break;
			}
		}
		bool isaddNewVn = 0;
		for (auto it = P[c].begin(); it != P[c].end(); it++) {
			string right = *it;
			
			if (right[0] == c) {
				isaddNewVn = 1;
				
				break;
			}
		}
		if (isaddNewVn) {
			set<string>NewPRight;//�������·��ս��NewVn���Ҳ�
			set<string>NewPNewVn;//�·��ս�����Ҳ�
			for (auto it = P[c].begin(); it != P[c].end(); it++) {
				string right = *it;
				if (right[0] != c) {
					right += NewVn;
					NewPRight.insert(right);
				}
				else {
					right = right.substr(1);
					right += NewVn;
					NewPNewVn.insert(right);
				}
			}
			Vn.insert(NewVn);
			NewPNewVn.insert("@");
			P[NewVn] = NewPNewVn;
			P[c] = NewPRight;
		}
	}
	void ShowByTogether() {
		for (auto it = Vn.begin(); it != Vn.end(); it++) {
			cout << *it << "->";
			char c = *it;
			for (auto it1 = P[c].begin(); it1 != P[c].end(); it1++) {
				if (it1 == P[c].begin())cout << *it1;
				else
					cout << "|" << *it1;
					
			}
			cout << endl;
		}
	}
};
int main() {
	/*
	�ķ�����
	E->T|E+T;
	T->F|T*F;
	F->i|(E);

	A->+TA|@;
	B->*FB|@;
	E->TA;
	F->(E)|i;
	T->FB;
	ֱ�ӽ���������������������parse_test1.txt��parse_test2.txt��
	*/
	string filename_gramer = "D:\\parse_test1.txt";
	Grammar *grammar=new Grammar(filename_gramer);
	cout << "/-------------------------û��������ݹ�-----------------------------/" << endl;
	cout << "�����ʾ��" << endl;
	grammar->ShowByTogether();
	cout << endl;
	grammar->getFirst();
	cout << endl;
	grammar->getFollow();
	cout << endl;
	grammar->getTable();
	
	cout << "/--------------------------------------------------------------------/" << endl<<endl<<endl;


	cout << "/-------------------------�Ѿ�������ݹ�-----------------------------/" << endl;
	/*
	������ݹ�֮����ж�
	*/
	grammar->remove_left_recursion();
	cout << "�����ʾ��" << endl;
	cout << endl;
	grammar->ShowByTogether();
	grammar->getFirst();
	cout << endl;
	grammar->getFollow();
	cout << endl;
	grammar->getTable();
	
	
	cout << "/--------------------------------------------------------------------/" << endl << endl << endl;
	cout << "/-------------------------�Դʷ����з���----------------------------/" << endl;
	/*
		Ŀǰ���뷨��ʹ�õ�һ��ʵ��������ͬ�ĵ��ʣ��Ե��ʲ�����
		�������Ϊ+��*�������������������i;
		����ֱ��ʹ��lex.cpp���к������ı�out1.txt
	*/
	string filename= "D:\\Parsing\\out1.txt";
	ifstream in(filename);
	char buffer[200];
	string inf="";
	int num = 0;
//	cout << "�ķ��������Ϊ��" << endl << endl;
	if (in.is_open()) {
		while (!in.eof()) {
			in.getline(buffer, 100);
//			cout << buffer << endl;
			inf += buffer;
			num++;
		}
	}
	string row = "";
	for (int i = 0; i < num-1; i++) {
		int ptr = i * 13;
		string temp = "";
		for (int j = 1; j <= 5; j++) {
			if (inf[j+ptr] == ' ')continue;
			else
				temp += inf[ptr+j];
		}
		if (temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == ">" || temp == "<" || temp == "=" || temp == "(" || temp == ")") {
			row += temp;
		}
		else {
			if (temp == ";") {
				row += "#";
				cout << "��ǰrowΪ:   " << row << endl;

				if (grammar->AnalyzePredict(row)) {
					cout << "                                         ��ȷ" << endl;
				}
				else
					cout << "                                         ����" << endl;
				row = "";
			}
			else {
				row += "i";
			}
		}
	}
	cout << "/--------------------------------------------------------------------/" << endl << endl << endl;
	system("pause");
	return 0;
}

