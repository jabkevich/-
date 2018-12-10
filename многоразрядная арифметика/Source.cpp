#include<iostream>
#include<string>
#include <fstream> 
#include <cstring>
using namespace std;
const int MAX = 100;//100 �����
char SS[17] = { '.',  '0', '1','2','3','4','5' ,'6' ,'7' ,'8' ,'9' ,'A' ,'B' ,'C' ,'D' ,'E' ,'F' };
const int kind = 4;//������ � 4 ������
int count_to , count_after ;
struct separation_String //��������� ��� �������� ����� � ������
{
	string NUM;
	string NUM1;
	string to_comma[MAX]; //�� �������
	string after_comma[MAX];//�����
	int to_count;//���������� ���� �� ������� � NUM
	int after_count;//���������� ���� ����� ������� � NUM
	int N_to;//���-�� �������� �� �������
	int N_after;//���-�� �������� ����� �������
	int Nn_to;//���������� ���� � ��������� ������� �� �������
	int Nn_after;//���������� ���� � ��������� ������� ����� �������
};
bool ChekLong(string num);
void EQLONG(separation_String &A, separation_String& B);
bool ReadLong(separation_String &numA, separation_String &
	numB) {
	int amount_of_numbers = 0;
	string buffer;
	bool chek;//���������� ��� ������� ����� � �����
	ifstream infile("input.TXT");
	while (!infile.eof())
	{
		infile >> buffer;
		chek = ChekLong(buffer);
		if ((chek == true) && (amount_of_numbers == 0)) {
			numA.NUM = buffer;
			numA.NUM1 = buffer;
			numA.to_count = count_to;
			numA.after_count = count_after;
			amount_of_numbers++;
		}
		else if ((chek == true) && (amount_of_numbers == 1)) {
			numB.NUM = buffer;
			numB.NUM1 = buffer;
			numB.to_count = count_to;
			numB.after_count = count_after;
			amount_of_numbers++;
		}
		if (amount_of_numbers == 2) {
			EQLONG(numA, numB);
			break;
		}
	}
	if (amount_of_numbers != 2) {
		switch (amount_of_numbers)
		{
		case 1: cout << "�������� ������ ���� �����. ����� �� ���������"; system("pause"); return false;
		case 0: cout << "�� �������� �� ������ �����. ����� �� ���������"; system("pause"); return false;
		}
	}
}
bool ChekLong(string num)//�������� �����. � �� ���������� � ����������, ��� ����� �� �����, �� ����� ���
{
	bool chek = true;
	int point = 0;
	int  count; //count_to-������� �������� �� �����. count_after-�������� �������� ����� ���� 
	int g = num.size();
	count_to = 0, count_after = 0;
	for (int i = 0; i < g; i++) {
		if (num[i] == ' ') {
			num.erase(i, 1); i--;
		}
	}
	g = num.size();
	for (int i = 0; i < g; i++) {
		count = 0;
		for (int j = 0; j < 17; j++) {
			if ((num[i] == SS[j]) && (SS[j] == '.')) {
				point++;
				count++;
			}
			else if (num[i] == SS[j])
				count++;
		}
		if (point == 1)
			count_after++;
		else
			count_to++;
		if (count == 0) return false;
	}
	if (num[0] == '0') {
		for (int i = 0; i < num.find('.'); i++) {
			if (num[i] != '0')return false;
		}
	}
	g = num.size();
	if ((num[0]=='.')||(num[g-1]=='.')) return false;
	if ((point == 0) || (point > 1)) chek = false;// ���� ������� �� ����, �� �����
	if (num.size() > 99) return false;
	return chek;
}
void PrintLong(separation_String &Astr)//�������������� �����, �������� �� ������� �� 4
{
	for (int j = 0; j < Astr.NUM.size()/2; j++){ //������������� ����� 

		swap(Astr.NUM[j], Astr.NUM[Astr.NUM.size() - j - 1]);
    }
	int � = Astr.NUM.find('.');
	int g = 0;
	int N = ceil((double)(�) / kind);//�� ��� � ��������� ������� ����� �������� �����
	Astr.N_after = N;
	Astr.Nn_after = � % kind;
	for (int i = 0; i < N; i++)//�������� ����� ����� �������
	{
		if ((g + 4) > �) {
			Astr.after_comma[i] = Astr.NUM.substr(g, � - g);

		}
		else {
			Astr.after_comma[i] = Astr.NUM.substr(g, kind);
			g = g + 4;
		}
	}
	Astr.Nn_to = (Astr.NUM.size()- � -1) % kind;
	g = � + 1;
	N = ceil((static_cast<double>(Astr.NUM.size()) - � - 1) / kind);
	Astr.N_to = N;
	for (int i = 0; i < N; i++)//�������� ������������ ����� �������
	{
		if ((g + 4) >= Astr.NUM.size()) {
			Astr.to_comma[i] = Astr.NUM.substr(g, Astr.NUM.size());

	}
	else {
			Astr.to_comma[i] =Astr.NUM.substr(g, 4);
			g = g + 4;
		}
	}
	for (int j = 0; j < Astr.NUM.size() / 2; j++) { //������������� ����� 

		swap(Astr.NUM[j], Astr.NUM[Astr.NUM.size() - j - 1]);
	}
}
void chek(int &i, int &j, string NUM[MAX], int &n)
{
	for (int g = 1; g < 17; g++) {
		if (NUM[i][j] == SS[g]) {
			n = g - 1; break;
		}
	}
}
void ADD(separation_String &A, separation_String &B, separation_String &C)//�������� �����
{
	char a1;
	int g = A.after_comma[0].size();
	int a = 0, b = 0, c = 0; // ���������� � ������� � ���� ������ ����� �� ������
	C.N_to = A.N_to;
	C.N_after = A.N_after;
	for (int i = 0; i < A.N_after; i++) {
		int g = A.after_comma[i].size();
			for (int j = 0; j < g; j++) {
				chek(i, j, A.after_comma, a);
				chek(i, j, B.after_comma, b);
				a = a + b + c;
				c = 0;
				if (a >= 16) { c = +1; a -= 16; }
				if (a > 9) {
					a1 = SS[a + 1];
					C.after_comma[i] += a1;
				}
				else {
					C.after_comma[i] += std::to_string(a);
				}
			}
	}
	g = A.to_comma[0].size();
	a = 0; b = 0;
	for (int i = 0; i < A.N_to; i++) {
		g = A.to_comma[i].size();
		for (int j = 0; j < g; j++) {
			chek(i, j, A.to_comma, a);
			chek(i, j, B.to_comma, b);
			a = a + b+c;
			c = 0;
			if (a >= 16) { c = +1; a -= 16; }
			if (a > 9) {
				a1 = SS[a + 1];
				C.to_comma[i] += a1;
			}
			else {
				C.to_comma[i] += std::to_string(a);
			}
		}
		if ((c > 0) &&(i+1==A.N_to))
		{ 
			if (A.to_comma[i].size()==4)
			C.to_comma[i+1] +=std::to_string(c);
			else C.to_comma[i ] += std::to_string(c);
			C.N_to = i + 1;
		}	
	}
	for (int i = 0; i < C.N_after; i++)
	{
		C.NUM += C.after_comma[i];
	}
	C.NUM += ".";
	for (int i = 0; i < C.N_to; i++)
	{
		C.NUM += C.to_comma[i];
	}
	for (int j = 0; j < C.NUM.size() / 2; j++) { //������������� ����� 

		swap(C.NUM[j], C.NUM[C.NUM.size() - j - 1]);
	}
}
bool LessLong(separation_String &A, separation_String &B)//��������� �������� �������� �����
{
	int a, b;
	bool ch=true;
	for (int i = A.N_to-1; i >= 0; i--)
	{
		int g = A.to_comma[i].size()-1;
		for (int j = g; j >= 0; j--) {
			chek(i, j, A.to_comma, a);
			chek(i, j, B.to_comma, b);
			if (a > b) { return true; }
			else if (b > a) { return false; }
		}
	}
	for (int i = A.N_after-1; i >= 0; i--)
	{
		int g = A.after_comma[i].size()-1;
		for (int j = g; j > 0; j--) {
			chek(i, j, A.after_comma, a);
			chek(i, j, B.after_comma, b);
			if (a > b) { return true; }
			else if (b > a) { return false; }
		}
		
	}
	return true;
}
void EQLONG(separation_String &A, separation_String& B) //��������� ��������� ������
{
	if ((A.to_count==B.to_count)&&(A.after_count==B.after_count))  ;
	string ch = "";
	if ((A.to_count > B.to_count)) {
		for (int j = B.to_count; j < A.to_count; j++) {
			ch += "0";
		}
		ch += B.NUM;
		B.NUM = ch;
	}
	else if (A.to_count < B.to_count) {

		for (int j = A.to_count; j < B.to_count; j++) 
			{
				ch += "0";
			}
		ch += A.NUM;
		A.NUM = ch;
	}

	if ((A.after_count > B.after_count)) {
		for (int i = 0; i < A.after_count - B.after_count; i++)
			B.NUM += "0";
	}
	else if (A.after_count < B.after_count) {
		for (int i = 0; i < B.after_count - A.after_count; i++)
			A.NUM += "0";
	}
}
void SubLong(separation_String &A, separation_String &B, separation_String &C)
{
	char a1;
	int g = A.after_comma[0].size();
	int a = 0, b = 0, c = 0, d=0; // ���������� � ������� � ���� ������ ����� �� ������
	bool c_chek = false;
	C.N_to = A.N_to;
	C.N_after = A.N_after;
	for (int i = 0; i < A.N_after; i++) {
		int g = A.after_comma[i].size();
		for (int j = 0; j < g; j++) {
			chek(i, j, A.after_comma, a);
			chek(i, j, B.after_comma, b);
			if ((a == 0) && (c == 1)) { a += 16; c_chek = true; }
			else if ((a == b) && (c == 1)) { a += 16; c_chek = true; } else 
			if (a < b) { c_chek = true; a += 16; }
			else c_chek = false;
			a = a -b-c;
			if (c_chek == true)c = 1;else c=0;
			if (a > 9) {
				a1 = SS[a + 1];
				C.after_comma[i] += a1;
			}
			else {
				C.after_comma[i] += std::to_string(a);
			}
		}
	}
	g = A.to_comma[0].size();
	a = 0; b = 0;
	for (int i = 0; i < A.N_to; i++) {
		g = A.to_comma[i].size();
		for (int j = 0; j < g; j++) {
			chek(i, j, A.to_comma, a);
			chek(i, j, B.to_comma, b);
			if ((a == 0) && (c == 1)) { a += 16; c_chek = true; }
			else if ((a == b) && (c == 1)) { a += 16; c_chek = true; }
			else
			if (a < b) { c_chek =true; a += 16; } 
			else { c_chek = false; }
			a = a - b - c;
			if (c_chek == true) c = 1; else c = 0;
			if (a > 9) {
				a1 = SS[a + 1];
				C.to_comma[i] += a1;
			}
			else {
				C.to_comma[i] += std::to_string(a);
			}
		}
	}
	for (int i = 0; i < C.N_after; i++)
	{
		C.NUM += C.after_comma[i];
	}
	C.NUM += ".";
	for (int i = 0; i < C.N_to; i++)
	{
		C.NUM += C.to_comma[i];
	}
	for (int j = 0; j < C.NUM.size() / 2; j++) { //������������� ����� 

		swap(C.NUM[j], C.NUM[C.NUM.size() - j - 1]);
	}
	for (int i = 0; i < C.NUM.find('.')-1; i++) {
		if (C.NUM[i] == '0') { C.NUM.erase(i, 1); i--; }
		else break;
	}
	for (int i = C.NUM.size()-1; i > C.NUM.find('.')+1; i--) {
		if (C.NUM[i] == '0') { C.NUM.erase(i, 1); }
		else break;
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
 	separation_String numA;//����� �
	separation_String numB;//����� B
	separation_String SummC;//����� ����� A � B
	separation_String diffC;//�������� ����� A � B
	ofstream outfile("output.TXT");//�������� ����
	if (ReadLong(numA, numB) == false) return 0;
	PrintLong(numA);// �������������� ����� A
	PrintLong(numB);//�������������� ����� B
	ADD( numA, numB, SummC);//���������� �����
	outfile << numA.NUM1 <<" + "<<numB.NUM1<<" = " << SummC.NUM << "\n";
    if (LessLong(numA, numB)==true) {
		SubLong(numA, numB, diffC);
		outfile << numA.NUM1 << " - " << numB.NUM1 << " = " << diffC.NUM;
	}
	else { 
		SubLong(numB, numA, diffC);
	    outfile << numB.NUM1 << " - " << numA.NUM1 << " = " << diffC.NUM; 
	}

	system("pause");
	return 0;
}