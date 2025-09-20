# NEEDLE

```needle

```

.ndl

source -> scanner -> parser -> compiler -> VM

- bytecode fragments
- swiss hash tables
- go cobra cli
- prototype-based

# FUNCTION

```needle
let f = |args type| type do
    body;
end;
let f_block = do |args type|
    body;
end;

|| type1, type2 do
    return value1, value2;
end;

function f_sugar(args type) type do body; end
function t.inner(args type) type { body; }
function t:method(args type) type { body; }  # auto self
```

# THREAD

```needle
let th = /args type/ type { body; };
let th_block = {/args type/ body; };

// type1, type2 { return value1, value2; };

thread th_sugar(args type) type { body; }
thread t.inner(args type) type { body; }
thread t:method(args type) type { body; }  # auto self
```

# VARARGS

```needle
let f = |arg1, arg2, {args}, arg_last| { body; }
f(1, 2, 3)        # args = nil
f(1, 2, nil, 3)   # args = {}
f(1, 2, 3, 4, 5)  # args = { 3, 4 }
```

# CONDITIONS

- not
- and
- or

# FLOW

```needle
for arg1, arg2 in iterable {
    body;
}
for iterable {
    body;
}

while condition {
    body;
}
until condition {
    body;
}

repeat {
    body;
} while condition;
repeat {
    body;
} until condition;

if condition {
    body;
} elif {
    body;
} else {
    body;
}
unless condition {
    body;
}

switch variable {
    case value1, value2:
        body;
        fall;
    default:
        body;
}

```

## CLASSES

```needle
class Animal {
    constructor
    speak(self) {
        print "sound";
    }
}
```

# TYPES

1. nil (`nil`)
2. boolean (`true`)
3. number (`81.3`)
4. string (`"hello"`)
5. table (`{ isTable = true }`)
6. function (`|arg| { print arg; }`)
7. thread (`/arg/ { yield arg; }`)

# TYPE ANNOTATION

- any `any`
- unknown `unknown`

- boolean `boolean`
- number `number`
- string `string`

- table `table`
- array `[]string, [number, string]`
- class `ClassName`
- interface `interface Inter { attrs }`

- function `|args| returns`
- thread `/args/ returns`
- self `|self|`

```needle
class Dog << Animal {
    speak() {
        print "WOF!";
    }
}
interface Greeter {
    greet |self, string| nil;
}
let d = Dog();
let g = {
    greet = {|self, name string|
        print "Hello, {name}!";
    }
};
function greet_dog(dog Dog, greeter Greeter) number, bool {
    greeter:greet("Dog");
    dog:speak();
    return 1, true;
}
```

# META

|     math     | cond |   prop    |  type   |   iter   | spec |
| :----------: | :--: | :-------: | :-----: | :------: | :--: |
|     plus     |  eq  |   index   | boolean | iterator | call |
|    minus     |  lt  | new_index | string  |   next   | type |
|     star     |  le  |           | number  |          |      |
|    slash     |      |           |         |          |      |
|  unary_plus  |      |           |         |          |      |
| unary_minus  |      |           |         |          |      |
| double_star  |      |           |         |          |      |
| double_slash |      |           |         |          |      |

```

def add(a, b):
    return a + b

def add(a int, b int) int: return a + b;;
sort(|a, b| bool: return a < b;;);

```
