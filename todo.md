Problems:
-	history after echo -n value overwriting prompt
	repro: use command, press up, press down
-	builtin redirection

To do:
-	emulate zsh echo command?
-	copy export list?
	env unset/empty values are not listed
-	ms_export
	no args = ms_env
	one arg, add arg=
	with equals, add arg=val
	no space allowed
-	ms_unset
-	check env no args
-	check pwd no args
