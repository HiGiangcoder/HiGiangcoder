p=29
ints=[14,6,11]

for i in range(29):
    num  =i*i % p
    if num in ints:
        print(i, num)
