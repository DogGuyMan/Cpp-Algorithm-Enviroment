clang++ -g -O0 -std=c++17 -Wl,-map,memory_map.txt std_string.cpp -o std_string
# 디버거로 실행
lldb ./std_string
(lldb) run
(lldb) image list  # 메모리 세그먼트 정보
(lldb) memory read --size 8 --format x --count 4 0x주소