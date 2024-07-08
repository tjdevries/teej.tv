---
title: Why I Like OCaml
permalink: /blog/why-i-like-ocaml
date: 2024-07-04
---
# Why I  Like OCaml

People often ask me "Hey, teej, you're a cool streamer (on twitch.tv/teej_dv btw). Why do you like OCaml so much?"[^1]. Many such cases.

## Type System

OCaml has a Hindley-Milner type system, which is just a really fancy way of saying "Everything can always only be one type a time" and "Very cool type inference". Don't let the Haskellers trick you into thinking academic words are scary - that's how they keep their monopoly on writing academic papers.

Let's look at an example. The following code defines a `user` type, that has a `name` field, which contains a string and an `age` field, which contains an `int`.

```ocaml
type user = { name: string; age: int }
```

If we write a function in the same scope, like:

```ocaml
let make_user name age = { name; age }
```

The signature of the function will look like:

```ocaml
string -> int -> user
```

Which is to say, pass a `string` and then an `int` and you'll get a `user`. Not, you'll get something with the fields `name` and `age`, you'll get a `user`. Now, this might not seem too interesting yet.

```ocaml
let average_age users = 
	let total_age = List.fold_left (fun acc u -> acc + u.age) 0 users in
	let num_users = List.length users in
	total_age / num_users
```
^average-age

and the corresponding type signature:

```ocaml
val average_age: user list -> int
```

This function can **only** take a `list of users`, which we know because we access the `u.age` field in the `fold_left` in [[2024-07-04 - Why I Like OCaml#^average-age|average-age]] and we know that it must return an integer because `age` is an int. It's not possible to have the scenario like you might have in "Type"script:

If we start with a function like this:

```typescript
function average_age(users: User[]) {
  let age = 0;
  for (let user of users) {
	age += user.age;
  }

  return age / users.length;
}
```

and then do:

```typescript
function average_age(users: User[]) {
  let age = 0;
  for (let user of users) {
	age += user.age;
  }

  if (age > 100) { return "hello"; }
  return age / users.length;
}
```


Typescript then just says "Oh, OK. You want a function that returns a `number | string`. What? No, Nobody actually wants that. And then don't get ThePrimeagen started on what you can do with `number | string` with arrays. It's not gonna be a good time for anyone. And also, I'm **NOT** going to start the twitter discourse again on whether you should annotate return types in Typescript. I don't care. I'm going to keep writing OCaml instead and trying to make it SAAS ready!!!

On a serious note, if you wanted to return a union of types in OCaml, you would need to create a separate type that can hold each of the types.

```neovim
<pre>
<span class="-keyword">type</span> <span class="-type">id</span> <span class="Delimiter">=</span>
  <span class="Delimiter">|</span> <span class="Special">Int</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">int</span></span>
  <span class="Delimiter">|</span> <span class="Special">String</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">string</span></span>

<span class="-keyword">let</span> <span class="-variable"><span class="-function">print_id</span></span> <span class="-variable">id</span> <span class="Delimiter">=</span> 
  <span class="-keyword">match</span> <span class="-variable">id</span> <span class="-keyword">with</span>
  <span class="Delimiter">|</span> <span class="Special">Int</span> <span class="-variable">i</span> <span class="Delimiter">-&gt;</span> <span class="-variable"><span class="-function">print_int</span></span> <span class="-variable">i</span>
  <span class="Delimiter">|</span> <span class="Special">String</span> <span class="-variable">s</span> <span class="Delimiter">-&gt;</span> <span class="-variable"><span class="-function">print_string</span></span> <span class="-variable">s</span>
</pre>
```






[^1]:  Proof: ![[Pasted image 20240704113210.png]] ![[Pasted image 20240704123909.png]]