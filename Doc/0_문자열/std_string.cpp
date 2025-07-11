#include <iostream>
#include <vector>
#include <string_view>
#include <cctype>

using namespace std;

/*********************************************************************************
*
* _________Start_StringDeepCopy()_________
* str : String Deep Copy
* assignStr : String Deep Copy
* copyStr : String Deep Copy
* str : 
* assignStr : String Deep Copy
* copyStr : String Deep Copy
* _________Exit_StringDeepCopy()_________
*
*********************************************************************************/
void StringDeepCopy(string strParam) {
	cout << "_________Start_StringDeepCopy()_________" << '\n';
	string str = strParam;
	string assignStr = str;
	string copyStr(str);
	strParam.clear();
	
	/*
	(lldb) memory read "&str"
	0x16fdfe088: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
	0x16fdfe098: 00 40 0c 06 02 00 00 10 c0 e0 df 6f 01 00 00 00  .@.........o....
	(lldb) memory read "&assignStr"
	0x16fdfe070: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
	0x16fdfe080: 00 40 0c 06 02 00 00 10 53 74 72 69 6e 67 20 44  .@......String D
	(lldb) memory read "&copyStr"
	0x16fdfe048: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
	0x16fdfe058: 00 40 0c 06 02 00 00 10 00 00 00 40 00 00 00 00  .@.........@....
	*/

	cout 	<< "str : " << str << '\n'
		<< "assignStr : " << assignStr << '\n'
		<< "copyStr : " << copyStr << '\n';
	
	str.clear();

	cout	<< "str : " << str << '\n'
		<< "assignStr : " << assignStr << '\n'
		<< "copyStr : " << copyStr << '\n';
	
	cout << "_________Exit_StringDeepCopy()_________" << '\n';
}

/*********************************************************************************
*
* _________Start_StringShallowCopy()_________
* String Shallow Copy
* str : String Shallow Copy
* charPtr : String Shallow Copy
* strRef : String Shallow Copy
* str : 
* charPtr : 
* strRef : 
* _________Exit_StringShallowCopy()_________
*
*********************************************************************************/
void StringShallowCopy(string strParam) {
	cout << "_________Start_StringShallowCopy()_________" << '\n';
	cout << strParam << '\n';
	string str = strParam;
	const char * charPtr = str.c_str();
	const string& strRef = str;
	strParam.clear();
	
	/*
	(lldb) memory read "&str"
	0x16fdfe078: 53 74 72 69 6e 67 20 53 68 61 6c 6c 6f 77 20 43  String Shallow C
	0x16fdfe088: 6f 70 79 00 69 6e 67 13 00 00 00 00 00 00 00 00  opy.ing.........
	(lldb) memory read "&strView"
	0x16fdfe068: 78 e0 df 6f 01 00 00 00 13 00 00 00 00 00 00 00  x..o............
	0x16fdfe078: 53 74 72 69 6e 67 20 53 68 61 6c 6c 6f 77 20 43  String Shallow C
	(lldb) memory read "charPtr"
	0x16fdfe078: 53 74 72 69 6e 67 20 53 68 61 6c 6c 6f 77 20 43  String Shallow C
	0x16fdfe088: 6f 70 79 00 69 6e 67 13 00 00 00 00 00 00 00 00  opy.ing.........
	(lldb) memory read "&strRef"
	0x16fdfe078: 53 74 72 69 6e 67 20 53 68 61 6c 6c 6f 77 20 43  String Shallow C
	0x16fdfe088: 6f 70 79 00 69 6e 67 13 00 00 00 00 00 00 00 00  opy.ing.........
	*/

	cout	<< "str : " << str << '\n'
		<< "charPtr : " << charPtr << '\n'
		<< "strRef : " << strRef << '\n';
	
	str.clear();
			
	cout	<< "str : " << str << '\n'
		<< "charPtr : " << charPtr << '\n'
		<< "strRef : " << strRef << '\n';

	cout << "_________Exit_StringShallowCopy()_________" << '\n';
}

/*********************************************************************************
*
* Before sdc/ssc와 After sdc/ssc 의 결과가 변함이 없다는 점에서
* StringXXXCopy(...); 내부에는 매개변수로 전달된 스트링을 Clear하는 구문이 있음에도 변함이 없는 점으로 미루어 보아
* 함수 패러미터 전달시, 레퍼런스가 아니므로, string 복사로 전달되는 모습을 알 수 있다. 
*
*********************************************************************************/
void StringCopyTest() {
	string sdc = "String Deep Copy";
	string ssc = "String Shallow Copy";
	
	cout << "Before sdc : " << sdc << '\n';	 // Before sdc : String Deep Copy
	cout << "Before ssc : " << ssc << '\n';	 // Before ssc : String Shallow Copy

	StringDeepCopy(sdc);
	StringShallowCopy(ssc);

	cout << "After sdc : " << sdc << '\n';	  // After sdc : String Deep Copy
	cout << "After ssc : " << ssc << '\n';	  // After ssc : String Shallow Copy
}

/*********************************************************************************
*
* string -> char[] : Standard Library String
* size : 25
* const char* -> string : Const Char Pointer String
* size : 25
* char[] -> vector<char> : Standard Library String
* size : 25
* string -> vector<char> : Const Char Pointer String
* size : 25
*
*********************************************************************************/
ostream& operator<<(ostream& os, vector<char>& rhs) {
	for(const auto& c : rhs) { 
		cout << c; 
	} 
	return os;
}
void CharArrToString(string strParam, const char* charPtrParam) {
	char charArray[100]; strParam.copy(charArray, strParam.size());
	string stdStr = string(charPtrParam);
	vector<char> charVectorWithCharArray(charArray, charArray + strlen(charArray));
	vector<char> charVectorWithString(stdStr.begin(), stdStr.end());

	cout 	<< "string -> char[] : " << charArray << '\n' 
		<< "size : " << strlen(charArray) << '\n';

	cout 	<< "const char* -> string : " << stdStr << '\n'
		<< "size : " << stdStr.size() << '\n';

	cout 	<< "char[] -> vector<char> : " << charVectorWithCharArray << '\n'
		<< "size : " << charVectorWithCharArray.size() << '\n';
	
	cout 	<< "string -> vector<char> : " << charVectorWithString << '\n'
		<< "size : " << charVectorWithString.size() << '\n';
}

/*********************************************************************************
*
*
*
*********************************************************************************/
void AlphaNumericConversions(string numericStrParam, int numericParam, const char* alphaStrParam) {
	string 	strConversion = to_string(numericParam);
	int 	numConversion = stoi(numericStrParam);

	int printCount;
	
	// 1 1 1 1 1 1 1 1 1 1
	printCount = 0;
	for(const auto& c : strConversion) {
		int res = isdigit(c);
		if(res > 0) {
			cout << res << ' ';
			printCount++;
		}
	} cout << '\n';
	if(printCount == 0) cout << "FAIL TO PRINT str" << '\n';
	
	// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	printCount = 0;
	vector<char> alphaCharVector(alphaStrParam + 1, alphaStrParam + strlen(alphaStrParam));
	for(const auto& c : alphaCharVector) {
		int res = isalpha(c);
		if(res > 0) {
			cout << res << ' ';
			printCount++;
		}
	} cout << '\n';
	if(printCount == 0) cout << "FAIL TO PRINT alphaStr" << '\n';

	// FAIL TO PRINT alphaStr
	printCount = 0;
	for(const auto& c : alphaCharVector) {
		int res = isdigit(c);
		if(res > 0) {
			cout << res << ' ';
			printCount++;
		}
	} cout << '\n';
	if(printCount == 0) cout << "FAIL TO PRINT alphaStr" << '\n';

}

void AlphaNumericTest() {
	char alphaStr[30] = {0,};
	for(char i = 'a'; i <= 'z'; i++)
		alphaStr[i - 'a'] = i;
	AlphaNumericConversions("1234567890", 1234567890, alphaStr);
}


int main(int argc, const char* argv[]) {

}