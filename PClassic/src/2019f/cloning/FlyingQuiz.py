def findMinDiff(numbers):
    length = len(numbers)
    answer = 2147483640
    for i in range (length-1):
        t = abs(numbers[i] - numbers[i+1])
        if t < answer:
            answer = t
    return answer


if __name__ == '__main__':
    with open('FlyingQuizIN.txt', 'r') as f:
        while True:
            line = f.readline().strip()
            if line == '':
                break
            numbers = []
            for u in line.split(' '):
                numbers.append(int(u))
            print(findMinDiff(numbers))



