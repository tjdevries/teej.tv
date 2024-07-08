---
title: LSP From Zero
author: teej_dv
date: 2024-03-08
---

# Introduction

> I've gotten a lot of questions about Language Servers on stream and in the comments to several of my YouTube videos. And there's no better way to demystify something you don't understand than just... building it!

Goal of the video:
- To show you **How** a Language Server works (by the most effective method: building)
	- No external dependencies
	- Only the specification as our guide


# Outline

- Create new go project
- Create new `rpc` package
	- Implement `DecodeMessage`
	- Test `DecodeMessage`
	- Implement `EncodeMessage`
		- First implement parsing `Content-Length: `
		- Test parsing `Content-Length: `
		- Implement Parsing `method`
		- Test parsing `method`
	- Implement main loop
		- Describe main loop
		- Create `bufio.NewScanner`
		- Create new `stdinReader.Split`
		- Connect new binary to Neovim
		- Log messages to a file in main loop
- Create new `lsp` package
	- Create types `Request`, `Response`, `Notification`
	- Create `initialize` request, which is the first request
		- Respond to message
	- Text Document Synchronization
		- NOTE: Not file system based... you want what the user is typing into the editor at that exact moment
		- A more advanced LSP would use incremental sync, but we will just do `Full` because it's much easier to reason about for what we're doing.
- Create new `analysis` package
	- Integrate `analysis` package into `lsp` package
- Implement more methods
	- `textDocument/hover`
	- `textDocument/definition`
	- `textDocument/completion`
- Conclusion
	- The rest kind of makes sense :)


# Golang tricks


```go
// Create a new logger
func getLogger(filename) *log.Logger {
	// Open or create the log file
	logFile, err := os.OpenFile(filename, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0666)
	if err != nil {
		log.Fatalf("error opening file: %v", err)
	}

	// Create a logger that writes to the file
	return log.New(logFile, "[educationlsp] ", log.Ldate|log.Ltime|log.Lshortfile)
}


// Switch on the type of some struct
switch msg := msg.(type) {
...
}
```


```go
package lsp

type InitializeMessage struct {
	Request
	Method string           `json:"method"`
	Params InitializeParams `json:"params"`
}

// InitializeParams defines the parameters for the initialize request.
type InitializeParams struct {
	ProcessID             int                    `json:"processId"`
	RootPath              string                 `json:"rootPath,omitempty"`
	RootURI               string                 `json:"rootUri"`
	Capabilities          ClientCapabilities     `json:"capabilities"`
	InitializationOptions map[string]interface{} `json:"initializationOptions,omitempty"`
}

// ClientCapabilities defines the capabilities provided by the client.
type ClientCapabilities struct {
	// ... capabilities can be added here
}

type InitializeResponse struct {
	Response
	Result InitializeResult `json:"result"`
}

type InitializeResult struct {
	ServerInfo   ServerInfo         `json:"serverInfo"`
	Capabilities ServerCapabilities `json:"capabilities"`
}

type ServerInfo struct {
	Name    string `json:"name"`
	Version string `json:"version"`
}

type ServerCapabilities struct {
	TextDocumentSync   int            `json:"textDocumentSync"`
	HoverProvider      bool           `json:"hoverProvider"`
	CodeActionProvider bool           `json:"codeActionProvider"`
	CompletionProvider map[string]any `json:"completionProvider"`
}

func NewInitializeResponse(id int) InitializeResponse {
	return InitializeResponse{
		Response: Response{
			RPC: "2.0",
			ID:  id,
		},
		Result: InitializeResult{
			Capabilities: ServerCapabilities{
				// You can only send me "Full document updates"
				//   If we were a smarter LSP, we would ask for incremental updates
				//   But this is just for education
				TextDocumentSync: 1,

				// We can provide the following features
				HoverProvider:      true,
				CodeActionProvider: true,
				CompletionProvider: map[string]any{},
			},
			ServerInfo: ServerInfo{
				Name:    "educationalsp",
				Version: "0.0.0.0.0-beta",
			},
		},
	}
}

```




```go
func Scan(data []byte, atEOF bool) (advance int, token []byte, err error) {
	before, after, found := bytes.Cut(data, []byte{'\r', '\n', '\r', '\n'})
	if !found {
		return 0, nil, nil
	}

	contentLengthStr := string(before[CONTENT_LENGTH:])
	contentLength, err := strconv.Atoi(contentLengthStr)
	if err != nil {
		return 0, nil, err
	}

	// We don't have enough data, got wait til later
	if len(after) < contentLength {
		return 0, nil, nil
	}

	totalLength := len(before) + 4 + contentLength
	return totalLength, data[:totalLength], nil
}
```


```lua
---@diagnostic disable: missing-fields
local client_id = vim.lsp.start_client {
  name = "educationalsp",
  cmd = { "/home/tjdevries/git/go-lsp/main" },
  on_attach = require("tj.lsp").on_attach,
}

if not client_id then
  vim.notify "Could not start educationalsp"
  return
end

vim.api.nvim_create_autocmd("Filetype", {
  pattern = "markdown",
  group = vim.api.nvim_create_augroup("educationalsp-start", { clear = true }),
  callback = function()
    vim.lsp.buf_attach_client(vim.api.nvim_get_current_buf(), client_id)
  end,
})

```