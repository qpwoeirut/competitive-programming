" Geothermal vimrc https://pastebin.com/XaPgEVPE

syntax on "syntax highlighting

"see https://vim.fandom.com/wiki/Example_vimrc for explanations of these
set nocompatible 
set tabstop=4 softtabstop=4
set shiftwidth=4
set expandtab
set smarttab smartindent
set ruler
set number relativenumber "https://jeffkreeftmeijer.com/vim-number/ basically line numbers
set backspace=indent,eol,start

"use system clipboard
set clipboard=unnamedplus

"bracket completion
inoremap {<CR> {<CR>}<Esc>O

"use ctrl+a to copy entire file
map <C-a> <esc>gg"+yG<CR>

"send copied char for s and x cmds to a different register
noremap s "ss
noremap x "xx

"I'm using Vim on terminal so font changes are done through terminal
"Terminal > Preferences > Profiles
