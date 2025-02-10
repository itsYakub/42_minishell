<						error
< blah					error
< file					similar to < file | more
<file					same as above
< file > file2			copy file to file2
< file >				error
cmd >					error
blah > file				error, creates file
< blah > file			error, doesn't create file
blah >> file			interactive mode, ? written to file every line
>> file					interactive mode, lines appended to file
< file >> file2			file appended to file2
blah <					error
cmd <					error
> file cmd				works like cmd > file

good
ls
"ls"
'ls'
ls|wc
ls |wc
ls| wc
ls | wc
"ls"|"wc"

bad
"ls -l"
'ls -l"
"|"
