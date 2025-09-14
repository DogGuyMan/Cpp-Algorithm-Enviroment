```cpp
// MAX_BUCKET 이게 세그폴트가 났다!!!
for (int i = 0; i <= MAX_BUCKET; i++) ❌
{
    if(BUCKET[i].cnt == mx) {SORTED_STR_ELEMENTS.push_back(BUCKET[i].key);}
}
```