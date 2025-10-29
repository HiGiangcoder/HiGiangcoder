# viet chuong trinh cho phep nhap vao ten va mssv. Kiem tra mssv do khong trung voi minh thi bat nhap lai. In ra man hinh ket qua


echo "Hay nhap ma so sinh vien cua ban:"
read mssv

while [ "$mssv" != "24520011" ]; do
    echo "Ma so sinh vien sai! Vui long nhap lai:"
    read mssv
done

echo "MSSV chinh xac!"
