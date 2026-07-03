#include <iostream>
#include <list>
#include <iterator>
#include <cstdio>

using namespace std;

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	for (int t = 1; t <= 10; ++t)
	{
		int N; scanf("%d", &N);
		list<int> lst;
		for (int i = 0; i < N; ++i)
		{
			{
				int temp; scanf("%d", & temp);
				lst.push_back(temp);
			}
		}
		int M; scanf("%d", &M);
		for (int i = 0 ; i < M; ++i)
		{
			char cmdName; int x, y;
			scanf(" %c", &cmdName);
			if (cmdName == 'I')
			{
				scanf("%d %d", &x, &y);
				// printf("%c %d %d\n", cmdName, x, y); // DEBUG
				list<int> tmpLst;
				for (int j = 0; j < y; ++j)
				{
					{
						int temp; scanf("%d", &temp);
						tmpLst.push_back(temp);
					}
				}
				auto it = lst.begin();
				advance(it, x);
				lst.splice(it, tmpLst);
			}
			else if (cmdName == 'D')
			{
				scanf("%d %d", &x, &y);
				auto sit = lst.begin(); advance(sit, x);
				auto eit = sit; 	advance(eit, y);
				lst.erase(sit, eit);
			}
			else if (cmdName == 'A')
			{
				scanf("%d", &y);
				list<int> tmpLst;
				for (int j = 0; j < y; ++j)
				{
					{
						int temp; scanf("%d", &temp);
						tmpLst.push_back(temp);
					}
				}
				lst.splice(lst.end(), tmpLst);
			}
		}

		printf("#%d ", t);
		int pcnt = 0;
		auto it = lst.begin();
		for (pcnt = 0, it; pcnt < 10 && it != lst.end(); pcnt++, it++) {printf("%d ", *it);}
		printf("\n");
	}
}