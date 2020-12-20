( print "Welcome to the rock paper scissors game!" )
( print "Please choose either rock [1], paper [2], or scissors [3]" )
( set response ( read ))
( set aiMove ( random 3 ) )

( cond
	( and ( equal ( response ) ( "1" ) ) ( equal aiMove 0 ) )
	( print "You chose rock, and the computer chose rock. Result: YOU TIE." ) )
( cond
	( and ( equal ( response ) ( "1" ) ) ( equal aiMove 1 ) )
	( print "You chose rock, and the computer chose paper. Result: YOU LOSE." ) )
( cond
	( and ( equal ( response ) ( "1" ) ) ( equal aiMove 2 ) )
	( print "You chose rock, and the computer chose scissors. Result: YOU WIN." ) )

( cond
	( and ( equal ( response ) ( "2" ) ) ( equal aiMove 0 ) )
	( print "You chose paper, and the computer chose rock. Result: YOU WIN." ) )
( cond
	( and ( equal ( response ) ( "2" ) ) ( equal aiMove 1 ) )
	( print "You chose paper, and the computer chose paper. Result: YOU TIE." ) )
( cond
	( and ( equal ( response ) ( "2" ) ) ( equal aiMove 2 ) )
	( print "You chose paper, and the computer chose scissors. Result: YOU LOSE." ) )

( cond
	( and ( equal ( response ) ( "3" ) ) ( equal aiMove 0 ) )
	( print "You chose scissors, and the computer chose rock. Result: YOU LOSE." ) )
( cond
	( and ( equal ( response ) ( "3" ) ) ( equal aiMove 1 ) )
	( print "You chose scissors, and the computer chose paper. Result: YOU WIN." ) )
( cond
	( and ( equal ( response ) ( "3" ) ) ( equal aiMove 2 ) )
	( print "You chose scissors, and the computer chose scissors. Result: YOU TIE." ) )

( print "Run the program again to play again!" )
