#### 1). `str.shrink_to_fit()` 
* capacity가 실제 사용하는 메모리보다 큰 경우 메모리 줄여 줌(메모리 낭비 제거)

#### 2). `str.insert(n, str2)`
* n번째 index 앞에 str2 문자열을 삽입함
* *(즉, `str2`의 시작 위치가 바로 `str[n]`이 된다는 것이다.)*

#### 3). `str.replace(n, k, str2)`
* n번째 index 부터 k개의 문자열을 `str2`로 대체함

#### 4). `str.erase(n, m)`
* `(int n, int m)` : n번째 index부터 m개의 문자를 지움 *즉 str[n]부터 str[n+m-1]까지 지운다.*
* `(string::iterator n, string::iterator m)` : iterator n부터 m 직전까지 문자열을 지움(범위: [n, m))

#### 5). `str.substr(n)` && `str.substr(n, k)`
* `str.substr(n)` : n번째 index부터 끝까지의 부분 문자열 반환
* `str.substr(n, k)` : n번째 index부터 k개의 문자로 이루어진 부분 문자열 반환

#### 6). `str.copy(arr, k, n)`
##### ① string -> char
* str의 n번째 index부터 k개의 문자를 char 배열 arr에 복사
* 주의: null terminator('\0')를 자동으로 추가하지 않음
##### ② string -> string
* **DeepCopy하려면**
  1. 대입 연산자
  2. 복사 생성자
     ```cpp
     void StringCopy() {
         string str = "String Copy";
         string assignStr = str;
         string copyStr(str);

         cout    << "str : " << str << '\n'
                 << "assignStr : " << assignStr << '\n'
                 << "copyStr : " << copyStr << '\n';
         
         str.push_back('A');
         str.insert(0, "A");

         cout    << "str : " << str << '\n'
                 << "assignStr : " << assignStr << '\n'
                 << "copyStr : " << copyStr << '\n';
         
     }
     ```
     ```shell
     > ./std_string
     str : String Copy
     assignStr : String Copy
     copyStr : String Copy
     str : AString CopyA
     assignStr : String Copy
     copyStr : String Copy
     ```
* **Shallow Copy**
  1. `string_view`
  2. `const char*`
  3. `string&`
     ```
     void StringShallowCopy() {
         cout << "StringShallowCopy" << '\n';
         string str = "String Shallow Copy";
         string_view strView = str;  // string_view는 포인터 + 길이로 구성
                                     // 원본이 커져도 string_view의 길이는 변하지 않음
         const char * charPtr = str.c_str();
         const string& strRef = str;

         cout    << "strView : " << strView << '\n'
                 << "charPtr : " << charPtr << '\n'
                 << "strRef : " << strRef << '\n';
         
                 str.push_back('A');
                 str.insert(0, "A");
                 
         cout    << "strView : " << strView << '\n'
                 << "charPtr : " << charPtr << '\n'
                 << "strRef : " << strRef << '\n';
         
     }
     ```

#### 7). `str.find("abcd")` & `str.find("abcd", n)`
* "abcd"가 str에 포함되어 있는지 확인, 찾으면 해당 부분 첫 index 반환
* n번째 index부터 "abcd"를 찾음
* 찾지 못하면 `string::npos` 반환

#### 8). `str.find_first_of("/")` && `str.find_last_of("/")`

1. "/"가 처음 나타나는 index
2. "/"가 마지막으로 나타나는 index

#### 9). `str.rfind("abcd")` & `str.rfind("abcd", n)`
* 뒤에서부터 "abcd"를 찾아 해당 부분 첫 index 반환
* n번째 index부터 뒤로 가면서 "abcd"를 찾음
* 찾지 못하면 `string::npos` 반환

> ### 참고
* [std::string 클래스 문자열 완벽 총정리](https://m.blog.naver.com/dorergiverny/223046924132)
