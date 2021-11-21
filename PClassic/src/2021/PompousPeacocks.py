def unbeatable(peacocks):
    pass


# do not modify below
total = int(input().strip())
for i in range(total):
    sumos = []
    while True:
        s = input().strip()
        if s == '':
            break
        sumo = s.split(" ")
        sumo[0] = int(sumo[0])
        sumo[1] = int(sumo[1])
        sumos.append(sumo)
    print(unbeatable(sumos))
