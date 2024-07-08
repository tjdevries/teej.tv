---
title: Embedding Neovim HTML into Obsidian
permalink: /blog/embedding-neovim-html-into-obsidian
date: 2024-07-05
---
# Embedding Neovim HTML Into Obsidian

What started off as just a crazy idea on America Day (fueled by the spirit of independence and freedom) has resulted in me yak-shaving on my blog for many hours (and don't get me started on the `Copy Code` button either).

Below is the end result - a syntax highlighted code block, including highlighting of errors in exactly the way it looks inside of my editor <sup>(Neovim, btw)</sup>

```neovim something
<pre>

<span class="-keyword"><span class="DiagnosticUnderlineError">let</span></span><span class="DiagnosticUnderlineError"><span class="Special">%</span><span class="PreProc">query</span> <span class="Delimiter">(</span><span class="-keyword">module</span> <span class="-module">UserName</span><span class="Delimiter">)</span> <span class="Delimiter">=</span> <span class="String">&quot;<span class="-keyword">SELECT</span> <span class="-type">User</span><span class="Delimiter">.</span><span class="-variable"><span class="DiagnosticUnderlineError">idd</span></span><span class="Delimiter">,</span> <span class="-type">User</span><span class="Delimiter">.</span><span class="-variable">name</span> <span class="-keyword">FROM</span> <span class="-type">User</span>&quot;</span></span><span class="String"></span>
<span class="DiagnosticError"></span><span class="DiagnosticError">│</span><span class="DiagnosticError">                                         </span><span class="DiagnosticError">└──── </span><span class="DiagnosticError">Unbound type constructor User.Fields.idd</span>
<span class="DiagnosticError"></span><span class="DiagnosticError">│</span><span class="DiagnosticError">                                         </span><span class="DiagnosticError">      </span><span class="DiagnosticError">Hint: Did you mean id?</span>
<span class="DiagnosticError"></span><span class="DiagnosticError">└──── </span><span class="DiagnosticError">Unbound value User.Fields.serialize_idd</span>
<span class="DiagnosticError"></span><span class="DiagnosticError">      </span><span class="DiagnosticError">Hint: Did you mean serialize_id?</span>
</pre>
```

_The example is from my project about generating type-safe SQL for OCaml, but you can read more about that at the start of the series: [[2024-07-02 - SQL In OCaml (Part 1)|SQL In OCaml]]_

## Problem

I wanted to be able to create perfectly highlighted code snippets for this website - but without any screenshots. I've never really been a fan of screenshots in technical blogs, but I also find that most syntax highlighting solutions are a bit lackluster in the browser (this includes in Electron based editors, btw).
## Solution

What if I...:
- Used Neovim's scripting capabilities to generate HTML with the correct highlight groups attached to each span in a `<pre>` block
- Make it easy to copy the HTML from Neovim and/or edit text files and insert them back into Obsidian
- Write a small plugin in Obsidian to override the display of `neovim` codeblocks, so the HTML is displayed correctly and styled.

It's only a matter of time when you start thinking about writing your markdown-based "simple blog" that you come to such madness. But onward! Onward with our generated HTML, custom codeblocks, and a touch of dangerously-sett-inner-HTML (exactly like the web was designed for)! Onward to displaying the HTML directly and beautifully, with the final result being an over-engineered syntax highlighting replicating that of my beloved editor!

(Onward, because we definitely don't want to look back now!)
# Implementation

## Custom `:TOhtml` command

I've long been a fan of the `:TOhtml` command in Vim and Neovim. In fact, quite a long time ago I attempted to add some HTML generation from the early days of tree-sitter and Neovim here (very good commits, as always in my personal projects):

- [Start working on some 'to html' stuff](https://github.com/tjdevries/colorbuddy.nvim/commit/0e7ecae265301303d359df0336f5b2f92e2432db)
- [Add Lua HTML Stuff](https://github.com/tjdevries/colorbuddy.nvim/commit/faf847d551eba6123f1997152a1959c951e1735f)

Unfortunately I hit a dead end, partially the Lua integration in 2018 wasn't quite what it is today, but primarily because I didn't care about anything in a browser.

That is, until Neovim 0.10 was released and the new [TOhtml](https://neovim.io/doc/user/lua.html#_lua-module:-tohtml) command was created! Now there was an incredibly easy way to get all of the Neovim specific highlights generated correctly.

> [!note] Contact Me!
> If you'd like to hear more about any of those differences and why Neovim needed specific handling for a feature that's been around in Vim for a long time, feel free reach out to me on [X](https://x.com/teej_dv) or similar and let me know. Happy to write more random Neovim tidbits down.

However, the builtin `:TOhtml` didn't quite fit exactly what I was looking for:
- It generated a complete HTML document, (`DOCTYPE`, `head` and all)
- It always included styling information in a `style` tag, and only the styles used in the block
- It couldn't be used to generate only a range of lines

So I did what any self-respecting Neovimmer would do - copied the entire file into my Neovim configuration, removed the parts of the code that I didn't like and spent even more time writing custom code so it would be just the way I liked it.
- You can see the commit [here](https://github.com/tjdevries/config.nvim/commit/892ec7ebbb2755d057e05e4934c320a162be2266)

After this I had accomplished the three primary things I needed from `:TOhtml`
- Generate a file of all the styles from any highlight set in my Neovim configuration
- Generate only a range of the file as HTML
- Generate a file/Copy to clipboard/Write to stderr the generated HTML of a file

I also added a few "quirks" that I like including:
- Stripping leading whitespace from the HTML (particularly useful when grabbing snippets)
- Automatically placing the HTML into my clipboard register, so I can paste it whenever I want.

## Easily copy a file into Obsidian

Now that we've gained the capability of generating HTML from a Neovim buffer, we need some way to actually place that HTML into Obsidian. Believe it or not, I actually enjoy writing non-technical things *outside of Neovim*. I think Obsidian is an elegant piece of technology and does it's job very well - and if I ever change my mind, at least Obsidian is [[2024-07-06 - File over App|File Over App]].

![[Pasted image 20240706014217.png]]
Using my custom `:TOhtml` command, I'm able to create a Neovim command that takes a range, so I can put the HTML directly into my clipboard and paste it into Obsidian. This method works really well for one-off scripts / references that do not need to get updated, or that have some custom highlights/diagnostics applied to the selection.

```neovim
<pre>
vim<span class="Delimiter">.</span><span class="-variable">api</span><span class="Delimiter">.</span><span class="-variable">nvim_create_user_command</span><span class="-function-bracket">(</span><span class="String">&quot;ObsidianHTML&quot;</span><span class="Delimiter">,</span> <span class="-keyword">function</span>(<span class="-variable">args</span>)
  <span class="-variable">package</span><span class="Delimiter">.</span><span class="-variable">loaded</span><span class="Delimiter">[</span><span class="String">&quot;custom.to-obsidian-html&quot;</span><span class="Delimiter">]</span> <span class="Operator">=</span> <span class="Special">nil</span>

  <span class="-keyword">local</span> <span class="-variable">opts</span> <span class="Operator">=</span> <span class="Delimiter">{</span><span class="Delimiter">}</span>
  <span class="-keyword">if</span> <span class="-variable">args</span><span class="Delimiter">.</span><span class="-variable">range</span> <span class="Operator">~=</span> <span class="-number">0</span> <span class="-keyword">then</span>
    <span class="-variable">opts</span><span class="Delimiter">.</span><span class="-variable">filter</span> <span class="Operator">=</span> <span class="-keyword">function</span>(<span class="-variable">row</span>)
      <span class="-keyword">return <span class="-variable">row</span> <span class="Operator">&gt;=</span> <span class="-variable">args</span><span class="Delimiter">.</span><span class="-variable">line1</span> <span class="-keyword">and</span> <span class="-variable">row</span> <span class="Operator">&lt;=</span> <span class="-variable">args</span><span class="Delimiter">.</span><span class="-variable">line2</span></span>
    <span class="-keyword">end</span>
  <span class="-keyword">end</span>

  <span class="-variable"><span class="-function-call-lua">require</span></span><span class="-function-bracket">(</span><span class="String">&quot;custom.to-obsidian-html&quot;</span><span class="-function-bracket">)</span><span class="Delimiter">.</span><span class="-variable"><span class="-function-call-lua">tohtml</span></span><span class="-function-bracket">(</span><span class="-number">0</span><span class="Delimiter">,</span> <span class="-variable">opts</span><span class="-function-bracket">)</span>
<span class="-keyword">end</span><span class="Delimiter">,</span> <span class="Delimiter">{</span> <span class="-variable">range</span> <span class="Operator">=</span> <span class="-boolean">true</span> <span class="Delimiter">}</span><span class="-function-bracket">)</span><span class="-variable"></span></pre>
```

Now I can select a range of code and easily paste the entire code block into Obsidian (since the `lines` includes the `neovim` codeblock demarcation)
## Update referenced in Obsidian

But now I'm asking myself:

> What about for files that can change? Or is it possible to include files without copy and pasting?

Fortunately, Obsidian has a great plugin API and with Typescript it's easy to write code that I'll regret later.

You can make an Obsidian plugin locally, and the easiest way I found was to use the [Sample Plugin](https://github.com/obsidianmd/obsidian-sample-plugin). Once you've got that running, it's pretty easy to explore and iterate quickly on your plugin. You can also use the [Hot Reload Plugin](https://github.com/pjeby/hot-reload) to make it really quick to check different options within your running Obsidian session.

Once I had my own Obsidian plugin, I created new commands. The first commands allows me to update `INCLUDE NEOVIM` blocks.

```neovim
<pre>
<span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">addCommand</span></span><span class="Delimiter">(</span><span class="Delimiter">{</span>
    <span class="-variable">id</span><span class="Delimiter">:</span> <span class="String">'update-include-neovim-blocks'</span><span class="Delimiter">,</span>
    <span class="-variable">name</span><span class="Delimiter">:</span> <span class="String">'Update INCLUDE NEOVIM blocks'</span><span class="Delimiter">,</span>
    <span class="-variable"><span class="-function">callback</span></span><span class="Delimiter">:</span> <span class="Delimiter">(</span><span class="Delimiter">)</span> <span class="Operator">=&gt;</span> <span class="Delimiter">{</span>
        <span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">updateNeovimHighlightBlocksCommand</span></span><span class="Delimiter">(</span><span class="Delimiter">)</span><span class="Delimiter">;</span>
    <span class="Delimiter">}</span>
<span class="Delimiter">}</span><span class="Delimiter">)</span><span class="Delimiter">;</span></pre>
```

An `INCLUDE NEOVIM` block looks like this in plain text:

```
%% INCLUDE NEOVIM <filepath> %%
'''neovim
<contents of file as highlight HTML>
'''
```

The `%% INCLUDE NEOVIM <filepath> %%`  is stripped out on Publish (it's basically a comment in Markdown), so it won't show up in the published site. The following codeblock is the `neovim` codeblock that we'll talk about later (it uses a custom `registerMarkdownCodeBlockProcessor`).

The command just looks for lines like the `INCLUDE` line, parses out the `filepath` and then executes a Neovim process like so:

```neovim
<pre>
<span class="-keyword">const</span> <span class="-variable">absolutePath</span> <span class="Operator">=</span> <span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">fileToPath</span></span><span class="Delimiter">(</span><span class="-variable">resolved</span><span class="Delimiter">)</span><span class="Delimiter">;</span>
<span class="-keyword">const</span> <span class="-variable">output</span> <span class="Operator">=</span> <span class="-keyword">await</span> <span class="-variable"><span class="-function">captureStderr</span></span><span class="Delimiter">(</span>
    <span class="String">'nvim'</span><span class="Delimiter">,</span>
    <span class="Delimiter">[</span><span class="String">'--headless'</span><span class="Delimiter">,</span> <span class="String">'-c'</span><span class="Delimiter">,</span> <span class="String">`RunObsidian <span class="-none"><span class="-none"><span class="Special">${</span><span class="-variable">absolutePath</span><span class="Delimiter"><span class="Special">}</span></span></span></span>`</span><span class="Delimiter">,</span> <span class="String">'-c'</span><span class="Delimiter">,</span> <span class="String">'q'</span><span class="Delimiter">]</span>
<span class="Delimiter">)</span><span class="Delimiter">;</span></pre>
```

Which captures the `stderr` from Neovim, executes it in a headless session, calls the `RunObsidian` command with the absolute path of the file, and then quits when it's done.

That's it! Now I can use Obsidian to update the Neovim blocks whenever I want.  A future improvement could be to run this automatically when file changes are detected, but I don't really think that's useful since I'm only going to be editing the files when I'm updating a blog post.

![[Pasted image 20240707151413.png]]

## Custom Code Block Processor

Obsidian's API for the local Obsidian Vault and Obsidian Publish contains a function: `registerMarkdownCodeBlockProcessor`.

```neovim
<pre>
<span class="Comment"><span class="-spell"><span class="Comment">/**
 * Register a special post processor that handles fenced code given a language and a handler.
 * This special post processor takes care of removing the &lt;pre&gt;&lt;code&gt; and create a &lt;div&gt; that
 * will be passed to the handler, and is expected to be filled with custom elements.
 * <span class="-keyword"><span class="-nospell">@see</span></span> {<span class="-type"><span class="-nospell">@link ...</span></span>}
 * <span class="-keyword"><span class="-nospell">@public</span></span>
 */</span></span></span>
<span class="-variable"><span class="-function">registerMarkdownCodeBlockProcessor</span></span><span class="Delimiter">(</span>
    <span class="-variable"><span class="-variable">language</span></span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type-builtin">string</span><span class="Delimiter">,</span>
    <span class="-variable"><span class="-variable">handler</span></span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="Delimiter">(</span>
        <span class="-variable"><span class="-variable">source</span></span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type-builtin">string</span><span class="Delimiter">,</span>
        <span class="-variable"><span class="-variable">el</span></span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type">HTMLElement</span><span class="Delimiter">,</span> <span class="-variable"><span class="-variable">ctx</span></span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type">MarkdownPostProcessorContext</span><span class="Delimiter">)</span> <span class="Operator">=&gt;</span> <span class="-type">Promise</span><span class="Operator"><span class="Delimiter">&lt;</span></span><span class="-type-builtin">any</span><span class="Operator"><span class="Delimiter">&gt;</span></span> <span class="Operator"><span class="Delimiter">|</span></span> <span class="-type-builtin">void</span><span class="Delimiter">,</span>
        <span class="-variable"><span class="-variable">sortOrder</span></span><span class="Special">?</span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type-builtin">number</span>
<span class="Delimiter">)</span><span class="Delimiter"><span class="Delimiter">:</span></span> <span class="-type">MarkdownPostProcessor</span><span class="Delimiter">;</span></pre>
```

This lets you control the handling of the `<language>`  of code blocks inside of Obsidian. Since we have this exposed to us, we can do exactly the thing that React has told you is dangerous for many years:

```neovim
<pre>
<span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">registerMarkdownCodeBlockProcessor</span></span><span class="Delimiter">(</span><span class="String">&quot;neovim&quot;</span><span class="Delimiter">,</span> <span class="-keyword">async</span> <span class="Delimiter">(</span><span class="-variable"><span class="-variable">content</span></span><span class="Delimiter">,</span> <span class="-variable"><span class="-variable">el</span></span><span class="Delimiter">,</span> <span class="-variable"><span class="-variable">_ctx</span></span><span class="Delimiter">)</span> <span class="Operator">=&gt;</span> <span class="Delimiter">{</span>
    <span class="-variable">el</span><span class="Delimiter">.</span><span class="-variable">innerHTML</span> <span class="Operator">=</span> <span class="-variable">content</span><span class="Delimiter">;</span>
<span class="Delimiter">}</span><span class="Delimiter">)</span><span class="Delimiter">;</span></pre>
```

We just set the HTML to the content inside of the codeblock. I know that I'm generated valid HTML from the plugin, I already have the styles set up by placing them in my [publish.css](https://help.obsidian.md/Obsidian+Publish/Customize+your+site#Static+assets), so let's just tell Obsidian to display it as the embedded HTML!

That's actually it! So inside of the code block it looks like:

![[Pasted image 20240707154722.png]]

But the display is what you see above! I think this is a pretty fun strategy, particularly because in the end, if I ever want to switch off of Obsidian or publish somewhere besides Obsidian Publish, I have all the HTML for all of my codeblocks already generated and included in the documents!

## Edit in Neovim

Now that I have an easy way to both View and Update code snippets within Obsidian and get the corresponding Neovim highlights, we need a way to edit them quickly!

First, we register a new command for Obsidian in our plugin.

```neovim
<pre>
<span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">addCommand</span></span><span class="Delimiter">(</span><span class="Delimiter">{</span>
    <span class="-variable">id</span><span class="Delimiter">:</span> <span class="String">'edit-neovim-block'</span><span class="Delimiter">,</span>
    <span class="-variable">name</span><span class="Delimiter">:</span> <span class="String">'Edit a NEOVIM block'</span><span class="Delimiter">,</span>
    <span class="-variable"><span class="-function">callback</span></span><span class="Delimiter">:</span> <span class="Delimiter">(</span><span class="Delimiter">)</span> <span class="Operator">=&gt;</span> <span class="Delimiter">{</span>
        <span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">editNeovimHighlightBlockInNeovim</span></span><span class="Delimiter">(</span><span class="Delimiter">)</span><span class="Delimiter">;</span>
    <span class="Delimiter">}</span>
<span class="Delimiter">}</span><span class="Delimiter">)</span><span class="Delimiter">;</span></pre>
```

Then, we open up a terminal (for me, `ghostty` at the moment) and instruct Neovim to open the referenced file in the current Neovim block:

```neovim
<pre>
<span class="-keyword">await</span> <span class="-variable"><span class="-function">captureStderr</span></span><span class="Delimiter">(</span><span class="String">'ghostty'</span><span class="Delimiter">,</span> <span class="Delimiter">[</span><span class="String">'-e'</span><span class="Delimiter">,</span> <span class="String">'nvim'</span><span class="Delimiter">,</span> <span class="String">'-c'</span><span class="Delimiter">,</span> <span class="String">`&quot;EditObsidian <span class="-none"><span class="-none"><span class="Special">${</span><span class="-variable">absolutePath</span><span class="Delimiter"><span class="Special">}</span></span></span></span>&quot;`</span><span class="Delimiter">]</span><span class="Delimiter">)</span><span class="Delimiter">;</span>

<span class="-keyword">let</span> <span class="-variable">activeFile</span> <span class="Operator">=</span> <span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable">app</span><span class="Delimiter">.</span><span class="-variable">workspace</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">getActiveFile</span></span><span class="Delimiter">(</span><span class="Delimiter">)</span><span class="Operator">!</span>
<span class="-keyword">let</span> <span class="-variable">activeFileContents</span> <span class="Operator">=</span> <span class="-keyword">await</span> <span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable">app</span><span class="Delimiter">.</span><span class="-variable">vault</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">cachedRead</span></span><span class="Delimiter">(</span><span class="-variable">activeFile</span><span class="Delimiter">)</span>
<span class="-variable-builtin">this</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">updateNeovimHighlightBlock</span></span><span class="Delimiter">(</span><span class="-variable">activeFile</span><span class="Delimiter">,</span> <span class="-variable">cursor</span><span class="Delimiter">.</span><span class="-variable">line</span><span class="Delimiter">,</span> <span class="-variable">activeFileContents</span><span class="Delimiter">.</span><span class="-variable"><span class="-function">split</span></span><span class="Delimiter">(</span><span class="String">&quot;<span class="SpecialChar">\n</span>&quot;</span><span class="Delimiter">)</span><span class="Delimiter">)</span></pre>
```

We just await until Neovim is closed (so when I `:wq`) and then update the current Neovim highlight block (we re-use the code that we had done previous in 
# Various Code Block Examples

Included OCaml highlighting

Before:
```ocaml
type t =
  | String of string
  | Int of int
  | Float of float
  | Bool of bool

let string (s : string) -> t = String s
let int (i : int) -> t = Int i
let float (f : float) -> t = Float f
let bool (b : bool) -> t = Bool b
```

After:
%% INCLUDE NEOVIM: why-i-like-ocaml-int-or-string.ml %%
```neovim
<pre>
<span class="-keyword">type</span> <span class="-type">t</span> <span class="Delimiter">=</span>
  <span class="Delimiter">|</span> <span class="Special">String</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">string</span></span>
  <span class="Delimiter">|</span> <span class="Special">Int</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">int</span></span>
  <span class="Delimiter">|</span> <span class="Special">Float</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">float</span></span>
  <span class="Delimiter">|</span> <span class="Special">Bool</span> <span class="-keyword">of</span> <span class="-type-builtin"><span class="-type">bool</span></span>

<span class="-keyword">let</span> <span class="-variable"><span class="-function">string</span></span> <span class="Delimiter">(</span><span class="-variable">s</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">string</span></span><span class="Delimiter">)</span> <span class="Delimiter">-&gt;</span> <span class="-variable">t</span> <span class="Delimiter">=</span> <span class="Special">String</span> <span class="-variable">s</span>
<span class="-keyword">let</span> <span class="-variable"><span class="-function">int</span></span> <span class="Delimiter">(</span><span class="-variable">i</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">int</span></span><span class="Delimiter">)</span> <span class="Delimiter">-&gt;</span> <span class="-variable">t</span> <span class="Delimiter">=</span> <span class="Special">Int</span> <span class="-variable">i</span>
<span class="-keyword">let</span> <span class="-variable"><span class="-function">float</span></span> <span class="Delimiter">(</span><span class="-variable">f</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">float</span></span><span class="Delimiter">)</span> <span class="Delimiter">-&gt;</span> <span class="-variable">t</span> <span class="Delimiter">=</span> <span class="Special">Float</span> <span class="-variable">f</span>
<span class="-keyword">let</span> <span class="-variable"><span class="-function">bool</span></span> <span class="Delimiter">(</span><span class="-variable">b</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">bool</span></span><span class="Delimiter">)</span> <span class="Delimiter">-&gt;</span> <span class="-variable">t</span> <span class="Delimiter">=</span> <span class="Special">Bool</span> <span class="-variable">b</span>
</pre>
```

Scroll bars instead of wrapping:

%% INCLUDE NEOVIM: 1720205717935.ml %%
```neovim
<pre>
<span class="-keyword">let</span> <span class="-variable">_</span> <span class="Delimiter">=</span> <span class="-variable"><span class="-function">print_endline</span></span> <span class="String">&quot;testing 1 2 3 4 5 this is longer and again wow!!!! A really long string won't wrap, it will scroll&quot;</span>

<span class="-keyword">module</span> <span class="-module">Something</span> <span class="Delimiter">=</span> <span class="-keyword">struct</span>
  <span class="-keyword">type</span> <span class="-type">t</span> <span class="Delimiter">=</span> <span class="-type-builtin"><span class="-type">int</span></span>
  <span class="-keyword">let</span> <span class="-variable"><span class="-function">make</span></span> <span class="Delimiter">(</span><span class="-variable">x</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">int</span></span><span class="Delimiter">)</span> <span class="Delimiter">:</span> <span class="-type-builtin"><span class="-type">int</span></span> <span class="Delimiter">-&gt;</span> <span class="-type">t</span> <span class="Delimiter">=</span> <span class="-variable">t</span>
<span class="-keyword">end</span>
</pre>
```

Can do other languages (although why would you want to write anything besides OCaml)

%% INCLUDE NEOVIM: 1720205765886.c %%
```neovim
<pre>
<span class="-keyword">#include</span> <span class="String">&lt;stdio.h&gt;</span>

<span class="-type-builtin">int</span> <span class="-variable"><span class="-function">main</span></span><span class="Delimiter">(</span><span class="Delimiter">)</span> <span class="Delimiter">{</span>
  <span class="-variable"><span class="-function">printf</span></span><span class="Delimiter">(</span><span class="String">&quot;Hello <span class="Character">%s</span>!!<span class="SpecialChar">\n</span>&quot;</span><span class="Delimiter">,</span> <span class="String">&quot;world&quot;</span><span class="Delimiter">)</span><span class="Delimiter">;</span>

  <span class="-keyword">return</span> <span class="-number">0</span><span class="Delimiter">;</span>
<span class="Delimiter">}</span>
</pre>
```

And for the cherry on top, we even get cool stuff like including errors and highlights from the code!

I plan on also using this feature to be able to add custom messages to code, to easily illustrate what part of the code I am talking about, like below!

```neovim
<pre>
  <span class="-keyword">local</span> <span class="-variable">opts</span> <span class="Operator">=</span> <span class="Delimiter">{</span><span class="Delimiter">}</span>
  <span class="-keyword">local</span> <span class="-variable">lines</span> <span class="Operator">=</span> <span class="-variable"><span class="-function-call-lua">require</span></span><span class="-function-bracket">(</span><span class="String">&quot;custom.to-obsidian-html&quot;</span><span class="-function-bracket">)</span><span class="Delimiter">.</span><span class="-variable"><span class="-function-call-lua">tohtml</span></span><span class="-function-bracket">(</span><span class="-number">0</span><span class="Delimiter">,</span> <span class="-variable">opts</span><span class="-function-bracket">)</span>
  <span class="-variable">io</span><span class="Delimiter">.</span><span class="-variable">stderr</span>:<span class="-variable">write</span><span class="-function-bracket">(</span><span class="String">&quot;Trying to open &quot;</span> <span class="Operator">..</span> <span class="-variable">filename</span> <span class="Operator">..</span> <span class="String">&quot;\n&quot;</span><span class="-function-bracket">)</span>
  <span class="-variable"><span class="DiagnosticUnderlineHint">io</span></span><span class="DiagnosticUnderlineHint"><span class="Delimiter">.</span><span class="-variable">stderr</span></span><span class="-variable"></span>:<span class="-variable">write</span><span class="-function-bracket">(</span><span class="String">&quot;Current working directory: &quot;</span> <span class="Operator">..</span> <span class="-variable">vim</span><span class="Delimiter">.</span><span class="-variable">fn</span><span class="Delimiter">.</span><span class="-variable">getcwd</span><span class="-function-bracket">(</span><span class="-function-bracket">)</span> <span class="Operator">..</span> <span class="String">&quot;\n&quot;</span><span class="-function-bracket">)</span>
<span class="DiagnosticHint">  </span><span class="DiagnosticHint">└──── </span><span class="DiagnosticHint">Incredibly useful message</span>
  <span class="-variable">io</span><span class="Delimiter">.</span><span class="-variable">stderr</span>:<span class="-variable">write</span><span class="-function-bracket">(</span><span class="-variable"><span class="-identifier">table</span></span><span class="Delimiter">.</span><span class="-variable"><span class="-function-call-lua">concat</span></span><span class="-function-bracket">(</span><span class="-variable">lines</span><span class="Delimiter">,</span> <span class="String">&quot;\n&quot;</span><span class="-function-bracket">)</span><span class="-function-bracket">)</span></pre>
```

I set this with a 'simple' command like this, but would be able to do this automatically with a script as well in the future.
```
lua vim.diagnostic.set(vim.api.nvim_create_namespace("Blog"), 0, { { lnum = 20, col = 2, end_col = 11, severity = vim.diagnostic.severity.HINT, message = "Incredibly useful message" } })
```
# Conclusion

Sometimes, it's good to just do something for fun and because you like it. It doesn't matter if I've written more code than blog posts, I'm happy.

See you in the next post (hopefully)