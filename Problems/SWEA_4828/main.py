TC = int(input())

for t in range(1, TC + 1):
    mn = int(1e10)
    mx = -mn
    N = int(input())
    nums = list(map(int, input().split()))
    for tmp in nums:
        if mn > tmp:
            mn = tmp
        if mx < tmp:
            mx = tmp
    print(f"#{t} {mx - mn}")
