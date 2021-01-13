" Geothermal vimrc https://pastebin.com/XaPgEVPE

syntax on
set nocompatible
set tabstop=4 softtabstop=4
set shiftwidth=4
set expandtab
set smarttab
set smartindent
set ruler
set number relativenumber "https://jeffkreeftmeijer.com/vim-number/
set backspace=indent,eol,start
set clipboard=unnamedplus

inoremap {<CR> {<CR>}<Esc>O
map <C-a> <esc>gg"+yG<CR>
noremap s "ss
noremap x "xx

