import time

now = time.time()
for i in range(0, 1000000):
    pass
print(f"Time taken: {(time.time() - now) * 1000} ms")