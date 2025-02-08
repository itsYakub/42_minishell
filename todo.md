Problems:
-	history after echo -n value overwriting prompt
	repro: use echo -n value, press up, press down
-	exit builtin doesn't exit anymore
-	current exit shows new line
-	ctrl+c twice quits

To do:
-	emulate zsh echo command?
-	signals
-	error messages
-	reject options on builtins?
-	check exit builtin cleanup
