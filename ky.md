nil
boolean
number
string
table
function
thread

```ky
let n;  # nil
let a = 1;  # 1

let b = 1 if false else 2;  # 2

let s = "hi, {b}!";

let array = Array.new({1, 2, 3});
let i = 0;
while array[i]:
    print(array[i]);
    i++;
end

function Array.new(*elements):
    let a = {};
    let i = 0;
    while elements[i]:
        a[i] = elements[i];
    end
    a.__counter = i;
    prototype(a, Array);
    return a;
end


if true:
elif false:
else:
end

while true:
end

for v1, v2 in iterable: end

interface Caller:
    ["every"] string or nil;
    flover number;
end

[8]string
[]number or nil
[string, number]
{string}(|string|number or nil)
{string}(thread(string)number or nil)
string

function add(a, b): return a + b end
|a, b|: end

1 / 2 = 0.5;
\a, b\:
    yield a;
    yield b;
end
```
