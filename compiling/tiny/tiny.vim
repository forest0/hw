" Vim syntax file
" Language: tiny

if exists("b:current_syntax")
  finish
endif

let b:current_syntax = "tiny"

" keywords
syn keyword tinyKeyword if then else end
syn keyword tinyKeyword repeat until

syn keyword tinyFunction read write

" syn keyword tinyTodo contained TODO FIXME NOTE

" matches
syn match tinyNumber "\d\+"
syn match tinyTodo contained "TODO"

syn region tinyComment start='{' end='}' contains=tinyTodo


highlight link tinyKeyword  Keyword
highlight link tinyFunction Function
highlight link tinyNumber   Constant
highlight link tinyComment  Comment
highlight link tinyTodo     Todo
