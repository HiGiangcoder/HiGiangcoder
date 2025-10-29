## Mô tả hàm `nextMove(x, y, lastBossID)`

Hàm quyết định vị trí đích tiếp theo `(nx, ny)` dựa trên vị trí hiện tại `(x, y)` và mã boss vừa gặp/giết `lastBossID`.

Quy tắc cập nhật (logic mới theo yêu cầu):

- Nếu `lastBossID != 0`: không di chuyển theo quỹ đạo, trả về chính `{x, y}`. Nếu là lần đầu gặp Boss 36, vẫn reset/neo lại quỹ đạo nội bộ tại `(x, y)` để các lượt sau (khi không còn boss) đi theo quỹ đạo mới, nhưng lượt hiện tại vẫn trả về `{x, y}`.
- Nếu `lastBossID == 0`: di chuyển theo quỹ đạo định sẵn. Nếu đang lệch khỏi quỹ đạo thì phải kéo về đúng điểm quỹ đạo hiện tại, chỉ khi đã đứng đúng điểm quỹ đạo thì mới đi tiếp mắt xích kế.

Hàm có 2 pha hoạt động (và luôn duy trì quỹ đạo spiral nội bộ, không phụ thuộc vào việc `(x,y)` có bị kéo lệch do đuổi boss hay không):

1) Pha 1 — Hexagonal spiral (thăm dò tới khi gặp Boss 36)
- Khởi tạo spiral lục giác quanh đúng vị trí ở lần gọi đầu tiên.
- Mỗi lượt di chuyển một bước dài 100 theo 6 hướng của lưới lục giác (0°, 60°, …, 300°), tạo vòng xoắn đồng tâm: vòng k có k bước trên mỗi cạnh, sau mỗi 6 cạnh tăng vòng.
- Pha 1 tiếp tục cho tới khi `lastBossID == 36`.

2) Pha 2 — Hexagonal spiral (reset tại chỗ gặp Boss 36)
- Khi `lastBossID == 36` lần đầu, neo lại tâm spiral tại `(x, y)` lúc đó và reset trạng thái (vòng = 1, cạnh = 0, v.v.). Lưu ý: lượt gặp boss vẫn trả về `{x, y}`.
- Sau khi reset, các lượt kế tiếp khi `lastBossID == 0` sẽ tiếp tục xoáy lục giác quanh tâm mới; lúc này các giá trị `(x, y)` ở những lượt tiếp theo từ đề có thể thay đổi, nhưng kết quả `(nx, ny)` vẫn bám quỹ đạo spiral nội bộ.

### Tham số
- `x, y`: vị trí hiện thời do đề bài cung cấp.
- `lastBossID`: mã boss vừa thấy/giết ở lượt trước. Khi bằng 36, chuyển hẳn sang Pha 2 và reset spiral tại chỗ.
	
### Giá trị trả về
- Cặp `(nx, ny)` là vị trí đích tiếp theo cần di chuyển tới (số thực).

### Quy tắc "kéo về quỹ đạo" (rejoin)
- Áp dụng khi `lastBossID == 0`.
- Nếu ở một lượt nào đó ta bị lệch khỏi quỹ đạo spiral (ví dụ trước đó vừa phải bay tới một boss), hàm sẽ trả về chính điểm quỹ đạo hiện tại `(hx, hy)` để kéo về quỹ đạo trước, thay vì nhảy tiếp sang điểm spiral kế tiếp.
- Chỉ khi đang đứng gần đủ (trong ngưỡng sai số nhỏ so với bước hex) tại `(hx, hy)`, hàm mới phát lệnh di chuyển sang mắt xích kế tiếp của vòng xoáy.
