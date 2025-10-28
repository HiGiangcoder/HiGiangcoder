## Hướng dẫn dành cho Windows

Trước hết hãy cd đến thư mục của bài mà bạn muốn sinh test và kiểm tra kết quả: Bai_1, Bai_2, Bai_3.

### Cho phép chạy script PowerShell:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
```

### Sinh test:

```powershell
python gen.py 1234
```

### Kiểm tra kết quả:

```powershell
python check.py solution.cpp
```