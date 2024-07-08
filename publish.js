var link = document.querySelector("link[rel~='icon']");
if (!link) {
  link = document.createElement("link");
  // @ts-ignore
  link.rel = "icon";
  document.head.appendChild(link);
}

// @ts-ignore
link.href =
  "https://pbs.twimg.com/profile_images/1613151603564986368/dZoNeRKn_400x400.jpg";

function updateArticleNames() {
  document.querySelectorAll('.tree-item-inner').forEach(item => {
    const text = item.textContent;
    const match = text.match(/\d\d\d\d-\d\d-\d\d - (.+)/);
    if (match) {
      item.textContent = match[1];
    }
  });
}

var setupComplete = false;
publish.on('navigated', () => {
  setupComplete = false;
});

// (el: HTMLElement, ctx: MarkdownPostProcessorContext): Promise<any> | void;
publish.registerMarkdownPostProcessor(async (_, ctx) => {
  if (setupComplete) {
    return;
  }

  if (ctx.frontmatter && ctx.frontmatter.title) {
    document.title = ctx.frontmatter.title;
  }

  setupComplete = true;
});

const clipboardContent = `
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-clipboard" viewBox="0 0 16 16">
  <path d="M4 1.5H3a2 2 0 0 0-2 2V14a2 2 0 0 0 2 2h10a2 2 0 0 0 2-2V3.5a2 2 0 0 0-2-2h-1v1h1a1 1 0 0 1 1 1V14a1 1 0 0 1-1 1H3a1 1 0 0 1-1-1V3.5a1 1 0 0 1 1-1h1z"/>
  <path d="M9.5 1a.5.5 0 0 1 .5.5v1a.5.5 0 0 1-.5.5h-3a.5.5 0 0 1-.5-.5v-1a.5.5 0 0 1 .5-.5zm-3-1A1.5 1.5 0 0 0 5 1.5v1A1.5 1.5 0 0 0 6.5 4h3A1.5 1.5 0 0 0 11 2.5v-1A1.5 1.5 0 0 0 9.5 0z"/>
</svg>
`;

publish.registerMarkdownCodeBlockProcessor('neovim',  async (content, el, ctx) => {
  const child = document.createElement('div');
  child.style.position = "relative";
  child.innerHTML = content;


  const clipboardSvg = document.createElement('div');
  clipboardSvg.innerHTML = clipboardContent;

  const btn = document.createElement('button');
  btn.addClass('copy-button');
  btn.textContent = 'Copy';
  btn.prepend(clipboardSvg);

  btn.addEventListener('click', async () => {
    console.log(btn.nextElementSibling.textContent.slice(0, 10));
    navigator.clipboard.writeText(btn.nextElementSibling.textContent);

    btn.textContent = '[x̂] Copied!';
    setTimeout(() => {
      btn.textContent = 'Copy';
      btn.prepend(clipboardSvg);
    }, 2000);
  });

  child.prepend(btn);

  el.replaceChildren(child);
});

// Create a MutationObserver to listen for changes to the DOM
const observer = new MutationObserver((_) => {
  updateArticleNames();
});

// Start observing the entire document for changes
observer.observe(document.body, {
  childList: true,
  subtree: true
});
