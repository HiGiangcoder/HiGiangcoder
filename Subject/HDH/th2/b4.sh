#!/bin/sh
echo "Hay nhap vao mot chuoi:"
read schuoi

file=$1

# -f: file, 
# -d: directory, 
# -e: file hay directory deu duoc, 
# -s: file ton tai va khong rong
if [ ! -f "$file" ]; then
    echo "File test.txt khong ton tai!"
    exit 1
fi

# -q: quiet, 
# -i: ignore
if grep -qi "$schuoi" $file; then 
    echo "Chuoi '$schuoi' ton tai trong file $file."
else
    echo "Chuoi '$schuoi' khong ton tai trong file $file"
fi
