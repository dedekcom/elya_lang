function zeruj()	{
	if( bbylpsax==1 )	{
		print "\tpsax"
	}
	if( bbylret==1 )	{
		print "\tret"
	}
	if( bbylpush==1 )	{
		print "\tpush "lastreg
	}
	if( bbylspushs==1 )	{
		print "\tspushs"
	}
	if( bbylspush==1)	{
		print "\tspush "lastreg
	}
	bbylpush=0;
	bbylspush=0;
	bbylpop=0;
	bbylpsax=0;
	bbylpopax=0;
	bbylret=0;
	bbylspushs=0;
}
BEGIN	{
		idreg = "[\$][a-z]"
		idloc = "[\$][0-9]"
		idendm = "[\t]*end method"
		idret = "[\t]*ret"

		fout = $1

		bbylpush=0;
		bbylpsax=0;
		bbylpopax=0;
		bbylret=0;
		bbylspushs=0;
		bbylspush=0;
		lastreg="";
	}
/^[\t]*ret/	{
	zeruj();
	bbylret=1;
	next
}
/^[\t]*end method/	{
	bbylret = 0;
	zeruj();
	print
	next
}

/^[\t]*psax/	{
	zeruj();
	bbylpsax=1;
	next
}
/^[\t]*spushs/	{
	if( bbylpsax == 1 )	{
		print "\tspush $a"
		bbylpsax=0
		zeruj();
	} else if (bbylpush==1)	{
		bbylpush=0
		print "\tspush "lastreg		
	} else {
		zeruj();
		bbylspushs=1;
	}
	next
}

/^[\t]*popax/ {
	if( bbylpsax==0 )	{
		zeruj();
		print
	} else {
		bbylpsax=0;
		zeruj();
	}
	next
}

/^[\t]*spush \$[a-z]|^[\t]*spush \$[0-9]+|[\t]*spush [0-9]+|^[\t]*spush [_a-zA-Z][_a-zA-Z0-9]*|^[\t]*spush [0-9]\.[0-9]+/ {
	zeruj();
	bbylspush=1;
	lastreg=$2
	next
}
/^[\t]*spop \$[a-z]|^[\t]*spop \$[0-9]|^[\t]*spop [_a-zA-Z][_a-zA-Z0-9]*/ {
	if( bbylspush==1 )	{
		if( $2 != lastreg )	{
			print "\tmov "$2","lastreg
		}
		bbylspush = 0;
		zeruj();
	} else if( bbylspushs==1 )	{
		if( $2=="$a" )	{
			print "\tpopax"
		} else {
			print "\tpop "$2
		}
		bbylspushs=0
		zeruj()
	} else {
		zeruj();
		print
	}
	next
}

/^[\t]*push \$[a-z]|^[\t]*push \$[0-9]+|[\t]*push [0-9]+|^[\t]*push [_a-zA-Z][_a-zA-Z0-9]*|^[\t]*push [0-9]\.[0-9]+/ {
	zeruj();
	bbylpush=1;
	lastreg=$2
	next
}

/^[\t]*pop \$[a-z]|^[\t]*pop \$[0-9]|^[\t]*pop [_a-zA-Z][_a-zA-Z0-9]*/ {
	if( bbylpush==1 )	{
		if( $2 != lastreg )	{
			print "\tmov "$2","lastreg
		}
		bbylpush = 0;
		zeruj();
	} else {
		zeruj();
		print
	}
	next
}

	{
	zeruj();
	print 
}
