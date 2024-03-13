---
permalink: /presentations/lsp-in-five-minutes
---

- LSP Explained (in 5 Minutes)

![](https://www.youtube.com/watch?v=LaS32vctfOY)

# Notes

# The Five W's of LSP

- Who?
- When?
- What?
- Where?
- Why?

# LSP: Who?

Created by Microsoft, alongside collaboration with Red Hat and Codenvy

# LSP: When?

Open sourced in June of 2016

# LSP: What?

Language Server Protocol

> The Language Server Protocol (LSP) defines the protocol used between an editor and
> a language server that provides language features like auto complete, go to definition etc.


# LSP: Where?

In your editor!!

<!-- stop -->

(Ok... this one is a bit more of a stretch, but here me out)

# LSP: Where?

In your editor!!

- A `Language Server` communicates with a `Client` (your editor)

# LSP: Where?

## Notification

> "Hey, I changed the contents of a file"

```
|
|                `textDocument/didChange`
|        +--------------+      +--------------+
|        |              |----->|              |
|        |    Client    |      |    Server    |
|        |              |      |              |
|        +--------------+      +--------------+
|
```

# LSP: Where? (Notification)

```json
{
  "method": "textDocument/didChange",
  "params": {
    "textDocument": {
      "uri": "file:///path/to/the/file.js",
      "version": 2
    },
    "contentChanges": [
      {
        "range": {
          "start": { "line": 0, "character": 0 },
          "end": { "line": 0, "character": 1 }
        },
        "rangeLength": 1,
        "text": "console.log('Hello, World!');\n"
      }
    ]
  }
}
```

# LSP: Where?

## Request

> "Hey, Please tell me where this thing is defined"

```
|
|                `textDocument/definition`
|        +--------------+      +--------------+
|        |              |----->|              |
|        |    Client    |      |    Server    |
|        |              |<-----|              |
|        +--------------+      +--------------+
|                      `Location`
|
```

# LSP: Where? (Request)

```json
{
  "id": 1,
  "method": "textDocument/definition",
  "params": {
    "textDocument": {
      "uri": "file:///path/to/the/file.js"
    },
    "position": { "line": 10, "character": 5 }
  }
}
```

# LSP: Where? (Response)

```json
{
  "id": 1,
  "result": [
    {
      "uri": "file:///path/to/the/definition/file.js",
      "range": {
        "start": { "line": 15, "character": 4 },
        "end": { "line": 15, "character": 22 }
      }
    }
  ]
}
```

# LSP: Where?

## Notification

> "Yo, your code is bad!!"

```
|
|        +--------------+      +--------------+
|        |              |      |              |
|        |    Client    |      |    Server    |
|        |              |<-----|              |
|        +--------------+      +--------------+
|          `textDocument/publishDiagnostics`
|
```

# LSP: Where? (Notification)

```json
{
  "method": "textDocument/publishDiagnostics",
  "params": {
    "uri": "file:///path/to/the/file.js",
    "diagnostics": [
      { "range": { ... },
        "severity": 1,
        "code": "1000",
        "message": "Missing semicolon."
      },
      { "range": { ... },
        "severity": 2,
        "code": "1001",
        "message": "Undefined variable 'abc'."
      }
    ]
  }
}
```

# LSP: Why?

It is one method of trying to make a large `M x N` problem into a `M + N` problem.

- `M` editors
- `N` languages
# How's LSP?

People always ask "What's LSP?" but they never ask "How's LSP?".
# How's LSP?

People always ask "What's LSP?" but they never ask "How's LSP?".

It seems to me it's doing quite well these days!

(maybe [[casting.c]] goes here?)