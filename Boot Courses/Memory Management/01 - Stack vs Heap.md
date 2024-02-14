
(note to self, don't put this joke directly in the course - possibly could be in the video section, because chat likes it)

Ok, up until now, you've only used garbage (collected) languages in this course. You might be wondering, "I thought I was going to be a software developer, not a garbage man?" to which I would reply "stop using js then, especially on the backend"

## What is garbage collection?

Before we can ask that, we first need to understand what is "garbage".

## What is garbage?

Memory that we had data stored in before that we don't need anymore.

Now, the difficulty in this is actually figuring out what we don't need!

```javascript
let my_array = [];
for (let i = 1; i < 1_000_000; i++) {
	my_array.push(i);
}

console.log(my_array);

// and now we never use it again
// Why doesn't this stay in memory til the end of the program?
// How does the memory get re-used/freed before that?
```

(my_array is 64 MB right now (or just a lot of memory))
(note: could use browser tools to look at this? could be cool)
(could do something with delete here?)

```c
int main() {
	int x = 5;
	int numbers[5] = { 1, 2, 3, 4, 5 };
}
```




(linux when you run out of memory)
![[Pasted image 20240108151332.png]]