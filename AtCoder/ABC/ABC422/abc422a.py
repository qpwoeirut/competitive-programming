i, j = map(int, input().split('-'))
if j == 8:
  print(f"{i+1}-1")
else:
  print(f"{i}-{j+1}")
