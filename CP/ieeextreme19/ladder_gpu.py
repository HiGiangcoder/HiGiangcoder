import torch

@torch.jit.script
def simulate_gpu(s, n):
    f = torch.zeros_like(s)
    na = torch.zeros_like(s)
    ng = torch.zeros_like(s)
    a = torch.ones_like(s) * -19 * 1919
    r = torch.ones_like(s) * -19
    C = (1 << 63) | 13
    mask = (a < s * s * 1919)
    while mask.any():
        na[mask] += 1
        pre_f = f.clone()
        ng[mask] += s[mask] * 19
        f[mask] = torch.round(ng[mask] / na[mask])
        a[mask] = torch.where(f == pre_f, a + 1, torch.zeros_like(a))
        mask = (a < s * s * 1919)
    return f

s = torch.arange(1, 101, device='cuda').repeat_interleave(100)
n = torch.arange(1, 101, device='cuda').repeat(100)
out = simulate_gpu(s, n)
print(out.view(100, 100))
