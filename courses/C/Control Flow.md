- Control flow
	- if statements, loops, functions, return
		- Should cover some ideas about scoping
	- switch/case statements

Good strategy, is to write the Python version of the control flow, and then show the C version. That should make it really clear what's going on

```python
if something():
  stuff()
```

```c
if (something()) {
	stuff();
}
```

There's also the bad idea of:
```c
if (something()) stuff();
// Or
if (something())
  stuff();
```

But you shouldn't do this if you're new :) You will mess it up and be very confused (I think no one should use it btw)


do-while? :)