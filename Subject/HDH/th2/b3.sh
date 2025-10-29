# Viet chuong trinh cho phep nhap vao mot so n.
# Kiem tra neu n < 10 thi bat nhap lai.
# Tinh tong cac so tu 1 den n
# In kq ra man hinh
#!/bin/sh
echo "Nhap n:"
read n

while [ $n -lt 10 ]; do
    echo "$n < 10 roi, hay nhap lai:"
    read n
done

sum=0

for i in $(seq 1 $n); do
    sum=$((sum+i))
done

echo "Tong cac so tu 1 den $n la: $sum"
