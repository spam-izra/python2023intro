from multiprocessing import Pool
import math

def linspace(a, b, N):
    assert N > 1
    result = [a,]
    dx = (b - a) / (N - 1)    
    for n in range(1, N - 1):
        result.append(a + dx * n)
    result.append(b)
    return result

def integrate(f, *, a, b, N):
    x = linspace(a, b, N)

    value = 0
    for left, right in zip(x[:-1], x[1:]):
        value += (F(left) + F(right)) * 0.5 * (right - left)
    return value

def F(x):
    return math.sqrt(1 - x**2)

def Task(args):
    return integrate(F, **args)

def simple():
    value = sum(map(Task, args)) * 2
    print(value)

def pool(n):
    with Pool(n) as p:
       value = sum(p.map(Task, args)) * 2
    print(value)
    
N = 5000000
steps = 100
dN = N // steps
nodes = linspace(-1, 1, steps + 1)
args = []
for a, b in zip(nodes[:-1], nodes[1:]):
    args.append(dict(a=a, b=b, N=dN))    


# python -m timeit -r 1 -n 1 -s "from mp import simple" "simple()"
# python -m timeit -r 1 -n 1 -s "from mp import pool" "pool(1)"


if __name__ == '__main__':
    simple()
    #pool(1)
    #pool(4)
    #pool(8)
    #pool(16)