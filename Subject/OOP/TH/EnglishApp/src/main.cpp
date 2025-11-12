/*
### `main.cpp`

**Chức năng:**

- Điểm khởi đầu của chương trình.
- Khởi tạo `EnglishApp` và chạy CLI hoặc GUI.

**Khi code:**

- CLI: `app.runCLI()`
- GUI: `QApplication app(argc, argv); MainWindow window; window.show();`
*/

#include "EnglishApp.h"

int main() {
    EnglishApp app;
    app.run(); // chạy CLI
    return 0;
}