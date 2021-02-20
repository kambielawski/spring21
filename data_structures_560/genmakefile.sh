#!/usr/bin/env bash 

thisfile="./readfile.sh"

# check if main.cpp exists
if [[ ! -e main.cpp ]]; then
  echo "error: main does not exist"
  exit 1 
fi

CC="g++"
includes=()
TEMPLATES=()
OBJS=()
DEPS=""

# loop thru files in directory
for filename in {*.h,*.cpp}; do
  [ -e "$filename" ] || continue
  # check if file is templated
  if [[ -n `grep "template <typename" $filename` ]]; then
    TEMPLATES+=($filename)
  else
    # otherwise we'll make a .o out of it
    OBJS+=($filename)
  fi
  includes=()
done

# replace .cpp and .h with .o's
for object in "${OBJS[@]}"; do
  OBJS+=(${object/.cpp/.o})
  OBJS+=(${object/.h/.o})
done

# remove .cpp and .h files from OBJS array
OBJS=( ${OBJS[@]/*.cpp/} )
OBJS=( ${OBJS[@]/*.h/} )

# remove duplicates from OBJS array
OBJS=($(printf "%s\n" "${OBJS[@]}" | sort -u))

makefile=$"
main: ${OBJS[@]}
	$CC ${OBJS[@]} -o main

%.o: %.cpp $DEPS ${TEMPLATES[@]}
	$CC -c $<

clean:
	rm -f main
	rm -f *.o
"

echo "$makefile" > Makefile
