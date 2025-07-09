#### Terminal Clear
```bash
# LLDB 밖에서 (터미널에서)
clear
# 또는
cmd + k  # macOS Terminal에서
```

#### BreakPoint

```shell
(lldb) br s -n StringDeepCopy
Breakpoint 1: where = std_string`StringDeepCopy() + 12 at std_string.cpp:7:10, address = 0x00000001000004f4
(lldb) br s -n StringShallowCopy
Breakpoint 2: where = std_string`StringShallowCopy() + 28 at std_string.cpp:26:10, address = 0x0000000100000880
(lldb) run
```

#### step
```shell
(lldb) run
Process 94962 launched: '/Users/escatrgot/Library/Mobile Documents/com~apple~CloudDocs/Markdown/SelfStudy/Algorithm/Cpp-Algorithm-Enviroment/Doc/0_문자열/std_string' (arm64)
Process 94962 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x00000001000004f4 std_string`StringDeepCopy() at std_string.cpp:7:10
   4    using namespace std;
   5   
   6    void StringDeepCopy() {
-> 7        cout << "StringDeepCopy" << '\n';
   8        string str = "String Deep Copy";
   9        string assignStr = str;
   10       string copyStr(str);
Target 0: (std_string) stopped.
(lldb) s
StringDeepCopy
Process 94962 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x0000000100000518 std_string`StringDeepCopy() at std_string.cpp:8:18
   5   
   6    void StringDeepCopy() {
   7        cout << "StringDeepCopy" << '\n';
-> 8        string str = "String Deep Copy";
   9        string assignStr = str;
   10       string copyStr(str);
   11  
Target 0: (std_string) stopped.
(lldb) s
Process 94962 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x0000000100000528 std_string`StringDeepCopy() at std_string.cpp:9:24
   6    void StringDeepCopy() {
   7        cout << "StringDeepCopy" << '\n';
   8        string str = "String Deep Copy";
-> 9        string assignStr = str;
   10       string copyStr(str);
   11  
   12       cout    << "str : " << str << '\n'
Target 0: (std_string) stopped.
(lldb) s
Process 94962 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x0000000100000534 std_string`StringDeepCopy() at std_string.cpp:10:12
   7        cout << "StringDeepCopy" << '\n';
   8        string str = "String Deep Copy";
   9        string assignStr = str;
-> 10       string copyStr(str);
   11  
   12       cout    << "str : " << str << '\n'
   13               << "assignStr : " << assignStr << '\n'
Target 0: (std_string) stopped.
(lldb) s
Process 94962 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x0000000100000544 std_string`StringDeepCopy() at std_string.cpp:12:13
   9        string assignStr = str;
   10       string copyStr(str);
   11  
-> 12       cout    << "str : " << str << '\n'
   13               << "assignStr : " << assignStr << '\n'
   14               << "copyStr : " << copyStr << '\n';
   15       
Target 0: (std_string) stopped.
```

#### 변수 메모리 읽기

```shell
Stack:  0x16f000000 ~ 0x170000000  ← 여기에 해당!
Heap:   0x100000000 ~ 0x200000000 (대략적)
Data:   0x100000000 근처
Code:   0x100000000 근처
```

```shell
(lldb) memory read "&str"

    0x16fdfe088: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
    (lldb) memory region 0x16fdfe088
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

    0x16fdfe098: 00 40 0c 06 02 00 00 10 c0 e0 df 6f 01 00 00 00  .@.........o....
    (lldb) memory region 0x16fdfe098
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

(lldb) memory read "&assignStr"

    0x16fdfe070: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
    (lldb) memory region 0x16fdfe070
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

    0x16fdfe080: 00 40 0c 06 02 00 00 10 53 74 72 69 6e 67 20 44  .@......String D
    (lldb) memory region 0x16fdfe080
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

(lldb) memory read "&copyStr"

    0x16fdfe048: 53 74 72 69 6e 67 20 44 65 65 70 20 43 6f 70 79  String Deep Copy
    (lldb) memory region 0x16fdfe048
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

    0x16fdfe058: 00 40 0c 06 02 00 00 10 00 00 00 40 00 00 00 00  .@.........@....
    (lldb) memory region 0x16fdfe058
    [0x000000016f604000-0x000000016fe00000) rw-
    Modified memory (dirty) page list provided, 3 entries.
    Dirty pages: 0x16fdf4000, 0x16fdf8000, 0x16fdfc000.

```

```
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
```