# NEEDLE

```needle

```

.ndl

source -> scanner -> parser -> compiler -> VM

- bytecode fragments
- swiss hash tables
- go cobra cli
- prototype-based

# FLOW

- |args| { body }
- {|args| body }
- return

- repeat
- while
- until
- break
- continue

- if
- unless
- else

- switch
- case
- default
- fall

# TYPES

1. nil (`nil`)
2. boolean (`true`)
3. number (`81.3`)
4. string (`"hello"`)
5. table (`{ isTable = true }`)
6. function (`function say(arg) { print arg }`)

# META

|     math     | cond |   prop    |  type   |   iter   |  spec  |
| :----------: | :--: | :-------: | :-----: | :------: | :----: |
|     plus     |  eq  |   index   | boolean | iterator | length |
|    minus     |  lt  | new_index | string  |   next   |  type  |
|     star     |  le  |           | number  |          |  call  |
|    slash     |      |           |         |          |        |
|  unary_plus  |      |           |         |          |        |
| unary_minus  |      |           |         |          |        |
| double_star  |      |           |         |          |        |
| double_slash |      |           |         |          |        |
