import random

'''2019
1+2-(3+4-5-6)*7*8*9
1+2-(3*(4-5-6)-7)*8*9
1+2+(3+4)*(5+6-7)*8*9
1+2*3+4*(5-6+7*8*9)
1*(2*3*(4-5+6*7*8)+9)
(1*2+3*4*(5+6))*(7+8)+9
(1+2+3)*(4-5+6*7*8)+9
'''

op=['+','-','*',]
def dfs(l,r):
    if l==r:
        return str(l)
    m=random.randint(l,r-1)
    return '(%s%s%s)'%(dfs(l,m),op[random.randint(0,2)],dfs(m+1,r))

for i in range(10000000):
    res=dfs(1,9)
    ans=eval(res)
    if (ans==2019):
        print(res)