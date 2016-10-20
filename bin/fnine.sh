# FNINE : COMPILE SOURCE CODES AND RUN THEM

NEXT_LANG=''
PREV_LANG=''
DEF_FLAGS=1

# C FLAGS
C_WARN=''
C_STD='-std=c11'

# C++ FLAGS
CPP_WARN=''
CPP_STD='-std=c++11'

# PYTHON FLAGS
PY_STD='python2'
PY_CMPL=0

# JAVA FLAGS
JAVA_WARN=''
JAVA_STD='-source 1.7'

# C# FLAGS
CS_STD='-langversion:5'

# HASKELL FLAGS
HS_WARN=''

# FILE FLAGS
CMPL=0 # ONLY COMPILE FILES
RM=0 # REMOVE ADDITIONAL FILES

function Func_defaults()
{
	if test $1 != 'C'
	then
		C_WARN=''
		C_STD='-std=c11'
	fi
	
	if test $1 != 'CPP'
	then
		CPP_WARN=''
		CPP_STD='-std=c++11'
	fi
	
	if test $1 != 'PYTHON'
	then
		PY_STD='python2'
		PY_SCR=0
	fi
	
	if test $1 != 'JAVA'
	then
		JAVA_WARN=''
		JAVA_STD='-source 1.7'
	fi
	
	if test $1 != 'CSHARP'
	then
		CS_STD='-langversion:5'
	fi
	
	if test $1 != 'HASKELL'
	then
		HS_WARN=''
	fi
	
	if test $1 != $PREV_LANG -a $DEF_FLAGS -eq 1
	then
		CMPL=0
		RM=0
	fi
}

function Func_fnine()
{
	OBJECTS=0
	
	for I in $@
	do
		case $I in
			
			# ------ FILE FLAGS ------ 
			
			-c)
				CMPL=1
				DEF_FLAGS=0
			;;
			+c)
				CMPL=0
				DEF_FLAGS=0
			;;
			-r)
				RM=1
				DEF_FLAGS=0
			;;
			+r)
				RM=0
				DEF_FLAGS=0
			;;
			-cr|-rc)
				CMPL=1
				RM=1
				DEF_FLAGS=0
			;;
			+cr|+rc)
				CMPL=0
				RM=0
				DEF_FLAGS=0
			;;
			
			# ------ C ------
			
			--c90)
				C_STD='-std=c90'
				NEXT_LANG='C'
			;;
			--c99)
				C_STD='-std=c99'
				NEXT_LANG='C'
			;;
			--c11)
				C_STD='-std=c11'
				NEXT_LANG='C'
			;;
			--cW)
				C_WARN='-Wall -Wextra'
				NEXT_LANG='C'
			;;
			
			*.c)
				if test $NEXT_LANG = 'C' -o -z $NEXT_LANG
				then
					OBJECTS=1
					BIN_FILE="`dirname $I`/`basename ${I%.*}`"
					
					Func_defaults 'C'
					
					PREV_LANG='C'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						echo "gcc $C_STD $C_WARN $I -o $BIN_FILE"
					
						if test $CMPL -eq 1
						then
							gcc $C_STD $C_WARN $I -o $BIN_FILE
						else
							gcc $C_STD $C_WARN $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
						fi
					
						if test $RM -eq 1
						then
							echo "rm -f $BIN_FILE" && `rm -f $BIN_FILE`
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka C. Stop." && return 2
				fi
			;;
			
			# ------ C++ ------
			
			--cp03)
				CPP_STD='-std=c++03'
				NEXT_LANG='CPP'
			;;
			--cp11)
				CPP_STD='-std=c++11'
				NEXT_LANG='CPP'
			;;
			--cp14)
				CPP_STD='-std=c++14'
				NEXT_LANG='CPP'
			;;
			--cpW)
				CPP_WARN='-Wall -Wextra'
				NEXT_LANG='CPP'
			;;
			
			*.cpp)
				if test $NEXT_LANG = 'CPP' -o -z $NEXT_LANG
				then
					OBJECTS=1
					BIN_FILE="`dirname $I`/`basename ${I%.*}`"
					
					Func_defaults 'CPP'
					
					PREV_LANG='CPP'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						echo "g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE"
					
						if test $CMPL -eq 1
						then
							g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE
						else
							g++ $CPP_STD $CPP_WARN $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
						fi
					
						if test $RM -eq 1
						then
							echo "rm -f $BIN_FILE" && rm -f $BIN_FILE
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka C++. Stop." && return 2
				fi
			;;
			
			# ------ PYTHON ------
			
			--py2)
				PY_STD='python2'
				NEXT_LANG='PYTHON'
			;;
			--py3)
				PY_STD='python3'
				NEXT_LANG='PYTHON'
			;;
			--pyI)
				PY_CMPL=0
				NEXT_LANG='PYTHON'
			;;
			--pyC)
				PY_CMPL=1
				NEXT_LANG='PYTHON'
			;;
			
			*.py)
				if test $NEXT_LANG = 'PYTHON' -o -z $NEXT_LANG
				then
					OBJECTS=1
					PYC_FILE=${I%.*}.pyc
					
					Func_defaults 'PYTHON'
					
					PREV_LANG='PYTHON'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						if test $PY_CMPL -eq 1
						then
							echo "$PY_STD -m py_compile $I"
					
							if test $CMPL -eq 1
							then
								$PY_STD -m py_compile $I
							else
								$PY_STD -m py_compile $I && echo "$PY_STD $PYC_FILE" && $PY_STD $PYC_FILE
							fi
					
							if test $RM -eq 1
							then
								echo "rm -f $PYC_FILE" && rm -f $PYC_FILE
							fi
						else
							echo "$PY_STD $I" && $PY_STD $I
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka Python. Stop." && return 2
				fi
			;;
			
			# ------ JAVA ------
			
			--jv5)
				JAVA_STD='1.5'
				NEXT_LANG='JAVA'
			;;
			--jv6)
				JAVA_STD='1.6'
				NEXT_LANG='JAVA'
			;;
			--jv7)
				JAVA_STD='1.7'
				NEXT_LANG='JAVA'
			;;
			--jv8)
				JAVA_STD='1.8'
				NEXT_LANG='JAVA'
			;;
			--jvX)
				JAVA_WARN='-Xlint'
				NEXT_LANG='JAVA'
			;;
			
			*.java)
				if test $NEXT_LANG = 'JAVA' -o -z $NEXT_LANG
				then
					OBJECTS=1
					NAME=${I%.*}
					CLASS_FILE=$NAME.class
					
					Func_defaults 'JAVA'
					
					PREV_LANG='JAVA'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						echo "javac -source $JAVA_STD $I"
					
						if test $CMPL -eq 1
						then
							javac $JAVA_STD $JAVA_WARN $I
						else
							javac $JAVA_STD $JAVA_WARN $I && echo "java $NAME" && java $NAME
						fi
					
						if test $RM -eq 1
						then
							echo "rm -f $CLASS_FILE" && rm -f $CLASS_FILE
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka Java. Stop." && return 2
				fi
			;;
			
			# ------ C# ------
			
			--cs3)
				CS_STD='3'
				NEXT_LANG='CSHARP'
			;;
			--cs4)
				CS_STD='4'
				NEXT_LANG='CSHARP'
			;;
			--cs5)
				CS_STD='5'
				NEXT_LANG='CSHARP'
			;;
			--cs6)
				CS_STD='6'
				NEXT_LANG='CSHARP'
			;;
			
			*.cs)
				if test $NEXT_LANG = 'CSHARP' -o -z $NEXT_LANG
				then
					OBJECTS=1
					EXE_FILE=${I%.*}.exe
					
					Func_defaults 'CSHARP'
					
					PREV_LANG='CSHARP'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						echo "mcs -langversion:$CS_STD $I"
					
						if test $CMPL -eq 1
						then
							mcs $CS_STD $I
						else
							mcs $CS_STD $I && echo "mono $EXE_FILE" && mono $EXE_FILE
						fi
					
						if test $RM -eq 1
						then
							echo "rm -f $EXE_FILE" && rm -f $EXE_FILE
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka C#. Stop." && return 2
				fi
			;;
			
			# ------ HASKELL ------
			
			--hsW)
				HS_WARN='-Wall'
				NEXT_LANG='HASKELL'
			;;
			
			*.hs)
				if test $NEXT_LANG = 'HASKELL' -o -z $NEXT_LANG
				then
					OBJECTS=1
					BIN_FILE="`dirname $I`/`basename ${I%.*}`"
					HI_FILE=$BIN_FILE.hi
					HO_FILE=$BIN_FILE.ho
					
					Func_defaults 'HASKELL'
					
					PREV_LANG='HASKELL'
					NEXT_LANG=''
					DEF_FLAGS=1
					
					if test -f $I
					then
						echo "ghc $I -o $BIN_FILE"
					
						if test $CMPL -eq 1
						then
							ghc $I -o $BIN_FILE
						else
							ghc $I -o $BIN_FILE && echo "$BIN_FILE" && $BIN_FILE
						fi
					
						if test $RM -eq 1
						then
							echo "rm -f $BIN_FILE $HI_FILE $HO_FILE" && rm -f $BIN_FILE $HI_FILE $HO_FILE
						fi
					else
						echo "fnine: $I: Nie ma takiego pliku. Stop." && return 2
					fi
				else
					echo "fnine: $I: Nie podano plików języka Haskell. Stop." && return 2
				fi
			;;
			
			# ------ ERRORS ------
			
			-*)
				echo "fnine: Błędna opcja $I. Stop." && return 2
			;;
			+*)
				echo "fnine: Błędna opcja $I. Stop." && return 2
			;;
			--*)
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

