---
title: tree-sitter Injections Are Cool
permalink: /blog/tree-sitter-injections-are-cool
date: 2024-07-03
---
# `tree-sitter` Injections Are Cool

Tree-sitter is really cool (and it can do lots more cool stuff than just highlighting) and having it accessible to users is really fun.

I have been working on embedding SQL inside of OCaml to give type-safe SQL queries in OCaml (parameterized, corresponding to modules, etc). However, it's kind of lame to write SQL in unhighlighted green string text.... so, it can be fixed in just a few lines of tree-sitter queries.

In neovim, if you include a file in something like `queries/<lang>/injections.scm` somewhere in your `runtimepath`, Neovim will automatically load this for the `<lang>` and then Neovim can inject the highlighting inside of the current file.

```scheme
((value_definition
  (attribute_id) @_attribute_id
  (let_binding
    body: (string (string_content) @injection.content)))
 (#contains? @_attribute_id "query")
 (#set! injection.language "sql"))
```

In the code snippet, you can see that we set the injection.language to "sql", which instructs Neovim to highlight everything in the injection.content range as SQL.

That gives us the beautiful SQL highlighting you can see here:

![[Pasted image 20240703150052.png]]
