#include<iostream>
#include<string>
#include <fstream> 
#include <cstring>
using namespace std;

const int MAX = 100;//100 чисел
char SS[17] = { '.',  '0', '1','2','3','4','5' ,'6' ,'7' ,'8' ,'9' ,'A' ,'B' ,'C' ,'D' ,'E' ,'F' };
const int kind = 4;//разряд в 4 ячейки
int count_to , count_after ;

struct separation//структуры для хранения числа
{
	int to_comma[MAX]; //до запятой
	int after_comma[MAX];//после
};
struct separation_String //структуры для хранения числа в строке
{
	string NUM;
	string to_comma[MAX]; //до запятой
	string after_comma[MAX];//после
	int to_count;
	int after_count;
	int N_to;//кол-во разрядов до запятой
	int N_after;//кол-во разрядов после запятой
	int Nn_to;//количество цифр в последнем разряде до запятой
	int Nn_after;//количество цифр в последнем разряде после запятой
};

bool ReadLong(string num)//проверка числа. Я НЕ РАЗОБРАЛСЯ В МНОЖЕСТВАХ, ТАМ КАКАЯ ТО ЕБАЛА, ПО ЭТОМУ ТАК
{
	bool a = true;
	int point = 0;
	int  count; //count_to-счетчик значений до знака. count_after-счтетчик значений после знка 
	int g = num.size();
	int h = num.length();
	count_to = 0, count_after = 0;
	for (int i = 0; i < h; i++) {
		if (num[i] == ' ') {
			num.erase(i, 1); i--;
		}
	}

	if (num[0] == '0') return false;
		
	
	h = num.length();
	if ((num[h - 1] == '.') || (num[0] == '.')) return false;



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
	if ((num[h - 1] == '.') || (num[0] == '.'));
	if ((point == 0) || (point > 1)) a = false;// если запятая не одна, то выход
	if (num.size() > 99) a = false;
	return a;
}

void PrintLong(separation_String &Astr)//переворачивает чсило
{

	for (int j = 0; j < Astr.NUM.size()/2; j++){ //переворачиваю число 

		swap(Astr.NUM[j], Astr.NUM[Astr.NUM.size() - j - 1]);
    }

	
	int р = Astr.NUM.find('.');
	int g = 0;
	int N = ceil(static_cast<double>(р) / kind);//ну тут я определяю сколько всего разрядов будет
	Astr.N_after = N;
	Astr.Nn_after = р % kind;
	for (int i = 0; i < N; i++)//печатаем целую часть массива
	{
		if ((g + 4) > р) {
			Astr.after_comma[i] = Astr.NUM.substr(g, р - g);

		}
		else {
			Astr.after_comma[i] = Astr.NUM.substr(g, kind);
			g = g + 4;
		}
	}
	Astr.Nn_to = (Astr.NUM.size()- р -1) % kind;
	g = р + 1;
	N = ceil((static_cast<double>(Astr.NUM.size()) - р - 1) / kind);
	Astr.N_to = N;
	
	for (int i = 0; i < N; i++)//печатаем вещественную часть массива
	{
		if ((g + 4) >= Astr.NUM.size()) {
			Astr.to_comma[i] = Astr.NUM.substr(g, Astr.NUM.size());

	}
	else {
			Astr.to_comma[i] =Astr.NUM.substr(g, 4);
			g = g + 4;
		}
	}
}
void chek(int &i, int &j, separation_String &NUM, int &n);
void chek1(int &i, int &j, separation_String &NUM, int &n);
char chek2(int &n);
void ADD(separation_String &A, separation_String &B, separation_String &C)//Сложение чисел
{
	char a1;
	int g = A.after_comma[0].size();
	int a = 0, b = 0, c = 0; // переменные в которые я буду класть число из строки
	C.N_to = A.N_to;
	C.N_after = A.N_after;
	for (int i = 0; i < A.N_after; i++) {

		int g = A.after_comma[i].size();
			for (int j = 0; j < g; j++) {

				chek(i, j, A, a);
				chek(i, j, B, b);
				a = a + b + c;
				c = 0;
				if (a >= 16) { c = +1; a -= 16; }
				if (a > 9) {
					a1 = chek2(a);
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
			chek1(i, j, A, a);
			chek1(i, j, B, b);
			a = a + b+c;
			c = 0;
			if (a >= 16) { c = +1; a -= 16; }
			if (a > 9) {
				a1 = chek2(a);
				C.to_comma[i] += a1;
			}
			else {
				C.to_comma[i] += std::to_string(a);
			}
		}
		if (c > 0) 
		{ 
			if (A.to_comma[i].size()==4)
			C.to_comma[i+1] +=std::to_string(c);
			else C.to_comma[i ] += std::to_string(c);
			C.N_to = i + 1;
		}
		
		
	}
	cout << endl;
	for (int i = 0; i < C.N_after; i++)
	{
		C.NUM += C.after_comma[i];
	}
	C.NUM += ".";
	for (int i = 0; i < C.N_to; i++)
	{
		C.NUM += C.to_comma[i];
	}
	for (int j = 0; j < C.NUM.size() / 2; j++) { //переворачиваю число 

		swap(C.NUM[j], C.NUM[C.NUM.size() - j - 1]);
	}
	
	
}

char chek2(int &n)
{

	switch (n)
	{
	
	case 10: return 'A'; break;
	case 11: return 'B'; break;
	case 12: return 'C'; break;
	case 13: return 'D'; break;
	case 14: return'E'; break;
	case 15: return 'F'; break;
	}
}
void chek(int &i, int &j, separation_String &NUM, int &n)
{
	
	switch (NUM.after_comma[i][j])
	{
	case '0': n = 0; break;
	case '1': n = 1; break;
	case '2': n = 2; break;
	case '3': n = 3; break;
	case '4': n = 4; break;
	case '5': n = 5; break;
	case '6': n = 6; break;
	case '7': n = 7; break;
	case '8': n = 8; break;
	case '9': n = 9; break;
	case 'A': n = 10; break;
	case 'B': n = 11; break;
	case 'C': n = 12; break;
	case 'D': n = 13; break;
	case 'E': n = 14; break;
	case 'F': n = 15; break;
	}
}
void chek1(int &i, int &j, separation_String &NUM, int &n)
{

	switch (NUM.to_comma[i][j])
	{
	case '0': n = 0; break;
	case '1': n = 1; break;
	case '2': n = 2; break;
	case '3': n = 3; break;
	case '4': n = 4; break;
	case '5': n = 5; break;
	case '6': n = 6; break;
	case '7': n = 7; break;
	case '8': n = 8; break;
	case '9': n = 9; break;
	case 'A': n = 10; break;
	case 'B': n = 11; break;
	case 'C': n = 12; break;
	case 'D': n = 13; break;
	case 'E': n = 14; break;
	case 'F': n = 15; break;
	}
}
bool LessLong(separation &A, separation &B)//процедура проверки большего числа
{
	return 0;
}
void EQLONG(separation_String &A, separation_String& B) //процедура проверки равенства длинны 
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

int main()
{
	setlocale(LC_ALL, "rus");
	int amount_of_numbers = 0;
	
	separation_String numA;
	separation_String numB;
	separation_String numC;
	ifstream infile("input.TXT");
	ofstream outfile("output.TXT");
	string buffer;

	bool chek;
	while (!infile.eof())
	{
		infile >> buffer;

		chek = ReadLong(buffer);
		if ((chek == true) && (amount_of_numbers == 0)) {
			numA.NUM = buffer;
			numA.to_count = count_to;
			numA.after_count = count_after;
			amount_of_numbers++;
		}
		else if ((chek == true) && (amount_of_numbers == 1)) {
			numB.NUM = buffer;
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
		case 1: cout << "найденно только одно число. Выход из программы"; system("pause"); return 0;
		case 0: cout << "не найденно ни одного числа. Выход из программы"; system("pause"); return 0;
		}
	}
	PrintLong(numA);// переворачиваем число A
	PrintLong(numB);//переворачиваем число B
	ADD( numA, numB, numC);//складываем числа
	outfile << numC.NUM;
	system("pause");
}