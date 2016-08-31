function Func_fnine()
{
	C_WARN=''
	C_STD='-std=c11'
	
	CPP_WARN=''
	CPP_STD='-std=c++11'
	
	PY_STD='python2'
	PY_SCR=0
	
	JAVA_WARN=''
	JAVA_STD='1.7'
	
	CS_STD='4'
	
	HS_WARN=''
	
	FLAG0=0 # COMPILE ONLY
	FLAG1=0 # REMOVE ADDITIONAL FILES
	
	OBJECTS=0
	
	for I in $@
	do
		case $I in
			
			# ------ GLOBAL FLAGS ------
			
			-D)
				FLAG0=0
				FLAG1=0
			;;
			-C|-C=yes)
				FLAG0=1
			;;
			-Cn|-C=no)
				FLAG0=0
			;;
			-R|-R=yes)
				FLAG1=1
			;;
			-Rn|-R=no)
				FLAG1=0
			;;
			-CR)
				FLAG0=1
				FLAG1=1
			;;
			
			# ------ C ------
			
			-c90)
				C_STD='-std=c90'
			;;
			-c99)
				C_STD='-std=c99'
			;;
			-c11)
				C_STD='-std=c11'
			;;
			-cW)
				C_WARN='-Wall -Wextra'
			;;
			
			*.c)
				OBJECTS=1
				BIN_FILE="`dirname $I`/`basename ${I%.*}`"
			
				if test -f $I
				then
					echo "gcc $C_STD $C_WARN $I -o $BIN_FILE"
					
					if test $FLAG0 -eq 1
					then
						gcc $C_STD $C_WARN $I -o $BIN_FILE
					else
						gcc $C_STD $C_WARN $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
					fi
					
					if test $FLAG1 -eq 1
					then
						echo "rm -f $BIN_FILE" && `rm -f $BIN_FILE`
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ C++ ------
			
			+c03)
				CPP_STD='-std=c++03'
			;;
			+c11)
				CPP_STD='-std=c++11'
			;;
			+c14)
				CPP_STD='-std=c++14'
			;;
			+cW)
				CPP_WARN='-Wall -Wextra'
			;;
			
			*.cpp)
				OBJECTS=1
				BIN_FILE="`dirname $I`/`basename ${I%.*}`"
				
				if test -f $I
				then
					echo "g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE"
					
					if test $FLAG0 -eq 1
					then
						g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE
					else
						g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
					fi
					
					if test $FLAG1 -eq 1
					then
						echo "rm -f $BIN_FILE" && rm -f $BIN_FILE
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ PYTHON ------
			
			-py2)
				PY_STD='python2'
			;;
			-py3)
				PY_STD='python3'
			;;
			-pyC)
				PY_INT=0
			;;
			-pyI)
				PY_INT=1
			;;
			
			*.py)
				OBJECTS=1
				PYC_FILE=${I%.*}.pyc
			
				if test -f $I
				then
					if test $PY_INT -eq 1
					then
						echo "$PY_STD $I" && $PY_STD $I
					else
						echo "$PY_STD -m py_compile $I"
					
						if test $FLAG0 -eq 1
						then
							$PY_STD -m py_compile $I
						else
							$PY_STD -m py_compile $I && echo "$PY_STD $PYC_FILE" && $PY_STD $PYC_FILE
						fi
					
						if test $FLAG1 -eq 1
						then
							echo "rm -f $PYC_FILE" && rm -f $PYC_FILE
						fi
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ JAVA ------
			
			
			-jv5)
				JAVA_STD='1.5'
			;;
			-jv6)
				JAVA_STD='1.6'
			;;
			-jv7)
				JAVA_STD='1.7'
			;;
			-jv8)
				JAVA_STD='1.8'
			;;
			-jvX)
				JAVA_WARN='-Xlint'
			;;
			
			*.java)
				OBJECTS=1
				NAME=${I%.*}
				CLASS_FILE=$NAME.class
				
				if test -f $I
				then
					echo "javac -source $JAVA_STD $I"
					
					if test $FLAG0 -eq 1
					then
						javac -source $JAVA_STD $JAVA_WARN $I
					else
						javac -source $JAVA_STD $JAVA_WARN $I && echo "java $NAME" && java $NAME
					fi
					
					if test $FLAG1 -eq 1
					then
						echo "rm -f $CLASS_FILE" && rm -f $CLASS_FILE
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ C SHARP ------
			
			-cs3)
				CS_STD='3'
			;;
			-cs4)
				CS_STD='4'
			;;
			-cs5)
				CS_STD='5'
			;;
			
			*.cs)
				OBJECTS=1
				EXE_FILE=${I%.*}.exe
				
				if test -f $I
				then
					echo "mcs -langversion:$CS_STD $I"
					
					if test $FLAG0 -eq 1
					then
						mcs -langversion:$CS_STD $I
					else
						mcs -langversion:$CS_STD $I && echo "mono $EXE_FILE" && mono $EXE_FILE
					fi
					
					if test $FLAG1 -eq 1
					then
						echo "rm -f $EXE_FILE" && rm -f $EXE_FILE
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ HASKELL ------
			
			-hsW)
				HS_WARN='-Wall'
			;;
			
			*.hs)
				OBJECTS=1
				BIN_FILE="`dirname $I`/`basename ${I%.*}`"
				HI_FILE=$BIN_FILE.hi
				HO_FILE=$BIN_FILE.ho
				
				if test -f $I
				then
					echo "ghc $I -o $BIN_FILE"
					
					if test $FLAG0 -eq 1
					then
						ghc $I -o $BIN_FILE
					else
						ghc $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
					fi
					
					if test $FLAG1 -eq 1
					then
						echo "rm -f $BIN_FILE $HI_FILE $HO_FILE" && rm -f $BIN_FILE $HI_FILE $HO_FILE
					fi
				else
					echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
				fi
			;;
			
			# ------ ERRORS ------
			
			-*)
				echo "fnine: Błędna opcja $I. Stop." && return 2
			;;
			+*)
				echo "fnine: Błędna opcja $I. Stop." && return 2
			;;
			*.*)
				echo "fnine: $I: Nieobsługiwany format pliku. Stop." && return 2
			;;
			*)
				echo "fnine: $I: Niepoprawny argument. Stop." && return 2
		esac
	done
	
	if test $OBJECTS -eq 0
	then
		echo "fnine: Nie podano obiektów. Stop." && return 2
	fi
}

Func_fnine $@

