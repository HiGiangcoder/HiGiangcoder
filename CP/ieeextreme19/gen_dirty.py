from collections import defaultdict

data = defaultdict(dict)
with open('log.txt') as f:
    for line in f:
        s,n,val = map(int,line.split())
        data[s][n] = val

for s in sorted(data):
    print(f"{{{s}, {{", end="")
    print(",".join(f"{{{n},{v}}}" for n,v in sorted(data[s].items())), end="")
    print("}},")
