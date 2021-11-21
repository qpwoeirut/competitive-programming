# -*- coding: utf-8 -*-
import queue
"""
Created on Sun Nov 17 11:13:29 2019

@author: Andrew Zhao
"""
    
f = open("RaceIN.txt")

def race(m, edges):
    temppair = bfs(0, edges)
    answer = bfs(temppair[0],edges)
    return answer


def bfs(no, edges):
    q = queue.Queue()
    tpair = (no, 0)
    q.put(tpair)
    end = (no, 0)
    visited = []
    while (q.empty() == False):
        for i in range(0, n):
            visited.append(0)
        pair = q.get()
        node = pair[0]
        length = pair[1]
        visited[node] = 1
       # print(str(visited[node]) + " " + str(node))
        for v in edges[node]:
            if (visited[v] != 0):
                #print(visited[v])
                continue
            if (visited[v] == 0):
                newpair = (v, length+1)
                end = newpair
                q.put(newpair)
                #print(str(newpair))
                #print(visited[v])

    return end
        

      
        
        
if __name__ == '__main__':

    with open("RaceIN.txt", 'r') as f:

        while True:
            n = f.readline()
            if n == '':
                break
            n = int(n)
            edge_list = []

            for i in range (0, n):
                temp = []
                edge_list.append(temp)

            for i in range (0, n):
                for v in f.readline().split():
                    temp = int(v)
                    edge_list[i].append(temp)  
                    
            ret = race(n,edge_list)
            print(ret[1])
    f.close()
#f = open("RaceOUT.txt", "w")
#f.write(str(answer[1]))
#f.close()


        


    


    
    
    

