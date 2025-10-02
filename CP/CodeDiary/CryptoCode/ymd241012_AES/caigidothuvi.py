import random

# Nhập tên của bạn
name = input("Hãy nhập tên của bạn: ")

# Chuyển đổi tên sang chữ cái in hoa và thay thế vài chữ cái
transformed_name = name.upper().replace('A', '@').replace('E', '3').replace('I', '1').replace('O', '0').replace('S', '$')

# Tạo thêm một chuỗi ngẫu nhiên gồm số và ký tự đặc biệt
special_chars = "!@#$%^&*"
random_chars = ''.join(random.choice(special_chars) for _ in range(3))

# Tạo thêm một chuỗi số ngẫu nhiên
random_digits = ''.join(random.choice('0123456789') for _ in range(4))

# Trộn tất cả vào một mật khẩu đầy thú vị
password = transformed_name + random_chars + random_digits

# Trộn các ký tự của mật khẩu để làm nó khó đoán hơn
password = ''.join(random.sample(password, len(password)))

print(f"Mật khẩu bí ẩn của bạn là: {password}")

