Problems:
-	history after echo -n value overwriting prompt
	repro: use command, press up, press down

To do:
-	emulate zsh echo command?
-	change env linked list to array?
-	ms_export
	no args = ms_env
	one arg, add arg=
	with equals, add arg=val
	no space allowed
-	ms_unset
-	check env no args
-	check pwd no args
