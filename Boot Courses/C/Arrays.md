
- Fixed-size, (generally known) at compile time
- `int hello[5] = {1, 2, 3, 4, 5}`
	 - What happens if you access `hello[6]`?
	 - What happens if you access `hello[5]`?
	 - What happens if we try to set those?
 - (better) `int hello[] = {1, 2, 3, 4, 5}`

- What is their size
- How do array indexes (TRULY THEY ARE OFFSETS) work
	- Why do they start 0?
	- `hello[3] -> (hello + 3)`
	- Then C does kind of magic with pointer arithmetic to know that 3 is multiplied by the sizeof the type
- Array is "just" a pointer to N elements (where C doesn't keep track of how many things are in N)

X is Y
"an array is a pointer"
Y is X
"a pointer is an array"

TODO: Look for some great definitions of these words from the interwebs that we can learn from.

Or more like static arrays are like their own unique types. Like int[1] and int[2] are different types so it's not that C knows how big the arrays is. It just knows that int[2] is (sizeof(int) * 2) bytes big