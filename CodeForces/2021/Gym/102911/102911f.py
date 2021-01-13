n, k = map(int, input().split())

songs = input().split()

if k*2 > n:
    print("NO")
else:
    songs = songs[k:] + songs[:k]
    print("YES")
    print(*songs)

