import math
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset


# ======================
# 1. Dataset đơn giản
# ======================
class TextDataset(Dataset):
    def __init__(self, text, seq_len=64):
        chars = sorted(list(set(text)))
        self.vocab_size = len(chars)
        self.char2idx = {ch: i for i, ch in enumerate(chars)}
        self.idx2char = {i: ch for i, ch in enumerate(chars)}

        self.data = torch.tensor([self.char2idx[c] for c in text], dtype=torch.long)
        self.seq_len = seq_len

    def __len__(self):
        return len(self.data) - self.seq_len

    def __getitem__(self, idx):
        x = self.data[idx : idx + self.seq_len]
        y = self.data[idx + 1 : idx + self.seq_len + 1]
        return x, y


# ======================
# 2. Mô hình Transformer
# ======================
class TransformerLM(nn.Module):
    def __init__(
        self, vocab_size, emb_size=256, nhead=8, num_layers=4, ff_dim=1024, max_len=512
    ):
        super().__init__()
        self.tok_emb = nn.Embedding(vocab_size, emb_size)
        self.pos_emb = nn.Embedding(max_len, emb_size)

        encoder_layer = nn.TransformerEncoderLayer(
            d_model=emb_size, nhead=nhead, dim_feedforward=ff_dim, dropout=0.1
        )
        self.transformer = nn.TransformerEncoder(encoder_layer, num_layers=num_layers)
        self.lm_head = nn.Linear(emb_size, vocab_size)

    def forward(self, x):
        B, T = x.size()
        positions = torch.arange(0, T, device=x.device).unsqueeze(0)
        tok_emb = self.tok_emb(x)
        pos_emb = self.pos_emb(positions)
        h = tok_emb + pos_emb
        h = self.transformer(h)
        logits = self.lm_head(h)
        return logits


# ======================
# 3. Hàm huấn luyện
# ======================
def train_model(
    model,
    dataset,
    epochs=10,
    batch_size=32,
    lr=3e-4,
    device="cuda" if torch.cuda.is_available() else "cpu",
):
    model = model.to(device)
    dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True)
    optimizer = torch.optim.AdamW(model.parameters(), lr=lr)

    for epoch in range(epochs):
        model.train()
        total_loss = 0
        for x, y in dataloader:
            x, y = x.to(device), y.to(device)
            logits = model(x)
            loss = F.cross_entropy(logits.view(-1, dataset.vocab_size), y.view(-1))
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            total_loss += loss.item()
        print(f"Epoch {epoch+1}/{epochs} - Loss: {total_loss/len(dataloader):.4f}")


# ======================
# 4. Sinh văn bản
# ======================
@torch.no_grad()
def generate_text(model, dataset, prompt="a", length=200, device="cpu"):
    model.eval()
    input_ids = (
        torch.tensor([dataset.char2idx[c] for c in prompt], dtype=torch.long)
        .unsqueeze(0)
        .to(device)
    )

    for _ in range(length):
        logits = model(input_ids)
        probs = F.softmax(logits[:, -1, :], dim=-1)
        next_token = torch.multinomial(probs, num_samples=1)
        input_ids = torch.cat([input_ids, next_token], dim=1)

    out = "".join([dataset.idx2char[int(i)] for i in input_ids[0]])
    return out


# ======================
# 5. Chạy thử
# ======================
if __name__ == "__main__":
    text = (
        "This is a simple example text for training a small Transformer language model. "
        "You can replace this with your own dataset to train a custom model."
    ) * 50  # nhân lên để có dữ liệu dài hơn

    dataset = TextDataset(text, seq_len=64)
    model = TransformerLM(
        vocab_size=dataset.vocab_size, emb_size=256, nhead=8, num_layers=4
    )

    train_model(model, dataset, epochs=5)
    print("\nGenerated text:")
    print(generate_text(model, dataset, prompt="Th", length=200))
