# Boa
[The Boa Programming Language](https://eunoiac.github.io/Boa/)
## Download
Go to the latest release and download the installer asset.
Run the installer

## Running boa
Run the code using the following command in the terminal, cd into a directory or use an absolute filepath and replace 'file.boa' with the file you want to run.
```
boa file.boa
```

# Docs

## 🧑‍ Input

```py
name = input("Wut is ur name?")
```

- `input(prompt)`: Prompts the user for input and stores the result.

---

##  Conditional Statements

```my-lang
if name == "Aadi" or name == "Mike" or name == "Jan" do {
print("U are an amazing person, " + name + "!")
} else do {
print("U are a person, " + name + ".")
}
```

- `if`...`else`: Standard conditional structure.
- `or`: Logical OR operator.
- `do { ... }`: Block start.

---

##  Loops

```my-lang
for i = 0 to 10 do {
print("Hi " + name + ", this is message number " + toStr(i) + ".")
}
```

- `for i = start to end do { ... }`: A basic for loop.
- `toStr(value)`: Converts a number to string for concatenation.

---

## ➕ Operators & Precedence

```my-lang
numba = 1 + 2 / 3 * 4 % 5
```

- Supports `+`, `-`, `*`, `/`, `%` with **standard precedence**.
- Evaluated left-to-right with correct precedence.

---

##  Lists & Indexing

```my-lang
list = [1, 2, 3, 4, 5]
print(list ? 3)
```

- `?` operator retrieves the value at the specified index.
- Indexing starts at 0.

---

##  Functions

```my-lang
op add(a, b) do {
return a + b
}
```

- `op name(params) do { ... }`: Defines a function.
- `return`: Returns a value.

### Function Call

```my-lang
print("The sum of 5 and 10 is: " + toStr(add(5, 10)))
```

---

##  Output

```my-lang
print("Hello world")
```

- `print(value)`: Outputs to the console.

---

##  Summary

| Feature       | Syntax Example                        |
|---------------|----------------------------------------|
| Input         | `input("Enter name")`                 |
| If / Else     | `if cond do { ... } else do { ... }`  |
| Loops         | `for i = 0 to 10 do { ... }`          |
| Lists         | `list ? 2`                            |
| Functions     | `op name(a, b) do { ... }`            |

---



