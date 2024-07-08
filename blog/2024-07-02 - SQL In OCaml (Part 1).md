---
title: SQL In Ocaml (Part 1)
permalink: /blog/sql-in-ocaml-1
date: 2024-07-02
---
# SQL In OCaml (Part 1)

This is showing how we have inner joins working now for my sql-in-ocaml library.

We have a simple inner join on Users to Post, which is then type safe and makes sure that we only access both tables that are part of the query, as well as only fields that exist on those tables (and then, correspondingly gets type checked correctly).

You might also notice the WHERE clause is also type checked (the ids are integers), and that is enforced at compile time

![[Pasted image 20240703150544.png]]

If you tried to select something (like the name of post, instead of the title) you'll get an error

![[Pasted image 20240703150535.png]]

If you're interested to know about why I like OCaml, you can check out: [[2024-07-04 - Why I Like OCaml]]