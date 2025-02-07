Problems:
-	history after echo -n value overwriting prompt
	repro: use echo -n value, press up, press down

To do:
-	emulate zsh echo command?
-	check env ignores args
-	check pwd ignores args
-	sort export no args output
-	valgrind check builtins
-	norminette builtins
-	signals
