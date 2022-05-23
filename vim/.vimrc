"                                   
"                    ██▒   █▓ ██▓ ███▄ ▄███▓ ██▀███   ▄████▄  
"                   ▓██░   █▒▓██▒▓██▒▀█▀ ██▒▓██ ▒ ██▒▒██▀ ▀█  
"                    ▓██  █▒░▒██▒▓██    ▓██░▓██ ░▄█ ▒▒▓█    ▄ 
"                     ▒██ █░░░██░▒██    ▒██ ▒██▀▀█▄  ▒▓▓▄ ▄██▒
"                      ▒▀█░  ░██░▒██▒   ░██▒░██▓ ▒██▒▒ ▓███▀ ░
"                      ░ ▐░  ░▓  ░ ▒░   ░  ░░ ▒▓ ░▒▓░░ ░▒ ▒  ░
"                      ░ ░░   ▒ ░░  ░      ░  ░▒ ░ ▒░  ░  ▒   
"                        ░░   ▒ ░░      ░     ░░   ░ ░        
"                         ░   ░         ░      ░     ░ ░      
"                        ░                           ░        
"
"                        Author: https://github.com/mohabaks
"

" Set Vundle {{{
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'ycm-core/YouCompleteMe'
Plugin 'SirVer/ultisnips'
Plugin 'xolox/vim-easytags'
Plugin 'xolox/vim-misc'
Plugin 'scrooloose/nerdtree'
Plugin 'tpope/vim-commentary'
call vundle#end()            " required
filetype plugin indent on    " required
"}}}
 " Set Colorscheme {{{
set background=dark
colorscheme nord
"}}} 
" General Settings {{{ 
syntax on
filetype on
set encoding=utf-8
set tw=79
set nowrap
set smartindent
set colorcolumn=80
set visualbell
set nocompatible   
set noerrorbells
set autowrite
set mouse+=a
set cursorline
set lazyredraw
set showmatch
set autoindent
set expandtab
set splitbelow
set splitright
set backspace=indent,eol,start
"}}}  
" Tabs Settings {{{

" Go to tab by number
noremap <leader>1 1gt
noremap <leader>2 2gt
noremap <leader>3 3gt
noremap <leader>4 4gt
noremap <leader>5 5gt
noremap <leader>6 6gt
noremap <leader>7 7gt
noremap <leader>8 8gt
noremap <leader>9 9gt
noremap <leader>0 :tablast<cr>

" Go to last active tab
au TabLeave * let g:lasttab = tabpagenr()
nnoremap <silent> <c-l> :exe "tabn ".g:lasttab<cr>
vnoremap <silent> <c-l> :exe "tabn ".g:lasttab<cr>
"}}}
" Split Layouts {{{
""specify different areas of the screen
set splitbelow
set splitright
""split navigations
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>
"}}}
" Searching {{{ 
set incsearch             " search as characters are entered
set hlsearch              " highight matches

"" turn off search highlight
nnoremap <leader><space> :nohlsearch<CR> 
"}}} 
" File Browsing {{{ 
"" Open NERDTree when no files are specified
map <C-n> :NERDTreeToggle<CR>
let NERDTreeIgnore=['\.pyc$', '\~$']

"" hide .pyc files
let NERDTreeIgnore=['\.pyc$', '\~$'] "ignore files in NERDTree
"}}}
" Code Block Settings {{{
"Code Folding 
set foldmethod=indent
set foldlevelstart=10     " open most folds by default
set foldlevel=99
set foldnestmax=10        " 10 nested fold max

"" space open/closes folds
nnoremap <space> za
set foldmethod=indent     " fold based on indent level

""  Moving Code Blocks
"" easier moving of code blocks
"" Try to go into visual mode (v), thenselect several lines of code here and
"" then press ``>`` several times.
vnoremap < <gv              " better indentation
vnoremap > >gv              " better indentation
"" Commenting blocks of code
autocmd FileType c,cpp,java,scala let b:comment_leader = '// '
autocmd FileType sh,ruby,python   let b:comment_leader = '# '
autocmd FileType conf,fstab       let b:comment_leader = '# '
autocmd FileType tex              let b:comment_leader = '% '
autocmd FileType mail             let b:comment_leader = '> '
autocmd FileType vim              let b:comment_leader = '" '
noremap <silent> ,cc :<C-B>silent <C-E>s/^/<C-R>=escape(b:comment_leader,'\/')<CR>/<CR>:nohlsearch<CR>
noremap <silent> ,cu :<C-B>silent <C-E>s/^\V<C-R>=escape(b:comment_leader,'\/')<CR>//e<CR>:nohlsearch<CR>
"}}}
" Vim Shortcut {{{
"" Leader
let mapleader=","

"" jk is escape
inoremap jk <esc>

"" Quicksave command
noremap  <C-Z> :update<CR>
vnoremap <C-Z> <C-C>:update<CR>
inoremap <C-Z> <C-O>:update<CR>
"}}}
" Buffer Navigation {{{ 
"" Ctrl Left/h & Right/l cycle between buffers
noremap <silent> <C-left> :bprev<CR>
noremap <silent> <C-h> :bprev<CR>
noremap <silent> <C-right> :bnext<CR>
noremap <silent> <C-l> :bnext<CR>

"" <Leader>q Closes the current buffer
nnoremap <silent> <Leader>q :Bclose<CR>

"" <Leader>Q Closes the current window
nnoremap <silent> <Leader>Q <C-w>c
"}}}
" Backups Settings {{{
set backup
set backupdir=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp
set backupskip=/tmp/*,/private/tmp/*
set directory=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp
set writebackup
  "}}} 
" Easytags Settings {{{
let g:easytags_suppress_ctags_warning = 1
"}}}
" IDE Settings {{{
"" PEP8 Settings
au BufNewFile,BufRead *.py
    \ set tabstop=4 |
    \ set softtabstop=4 |
    \ set shiftwidth=4 |
    \ set textwidth=79 |
    \ set expandtab |
    \ set autoindent |
    \ set fileformat=unix |

au BufNewFile,BufRead *.js,*.html,*.css
    \ set tabstop=2 |
    \ set softtabstop=2 |
    \ set shiftwidth=2 |

"" enable all Python syntax highlighting feautures
let python_highlight_all = 1

"" YouCompleteMe
let g:ycm_autoclose_preview_window_after_completion=1
let g:ycm_collect_identifiers_from_tags_files = 1       " Let YCM read tags from Ctags file
let g:ycm_use_ultisnips_completer = 1                   " Default 1, just ensure
let g:ycm_seed_identifiers_with_syntax = 1              " Completion for programming language's keyword
let g:ycm_complete_in_comments = 0                      " Completion in comments
let g:ycm_complete_in_strings = 0                       " Completion in string
let g:ycm_global_ycm_extra_conf = '~/vim/.ycm_extra_conf.py'
let g:ycm_confirm_extra_conf = 0
let g:ycm_python_binary_path = '/usr/bin/python3'
map <leader>g :YcmCompleter GoToDefinitionElseDeclaration<CR>

"" Ultisnips.vim
let g:UltiSnipsExpandTrigger       = "<c-j>"
let g:UltiSnipsJumpForwardTrigger  = "<c-j>"
let g:UltiSnipsJumpBackwardTrigger = "<c-p>"
let g:UltiSnipsListSnippets        = "<c-k>"
"" Java IDE Settings
let g:EclimCompletionMethod = 'omnifunc'
" vim:foldmethod=marker:foldlevel=0
let g:ycm_global_ycm_extra_conf = '~/vim/.ycm_extra_conf.py'
let g:ycm_confirm_extra_conf = 0
let g:ycm_python_binary_path = '/usr/bin/python3'
map <leader>g :YcmCompleter GoToDefinitionElseDeclaration<CR>
"" Ultisnips.vim
let g:UltiSnipsExpandTrigger       = "<c-j>"
let g:UltiSnipsJumpForwardTrigger  = "<c-j>"
let g:UltiSnipsJumpBackwardTrigger = "<c-p>"
let g:UltiSnipsListSnippets        = "<c-k>"

"" Java IDE Settings
let g:EclimCompletionMethod = 'omnifunc'
" }}}
" Organization {{{
set modelines=1
"}}}
" vim:foldmethod=marker:foldlevel=0
