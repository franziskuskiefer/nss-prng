set verbose off
set confirm off
set print address off
set logging redirect on
set logging file /dev/null
set logging on


define tracefunc
break $arg0
commands
silent
set logging on
call fflush(0)
set logging off
#up-silently 1
echo \n
bt
#echo \n
cont
end
end
tracefunc SHA256_Begin
#tracefunc SHA256_Update
#tracefunc SHA256_End
set logging off
run
quit
