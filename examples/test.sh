#!/bin/sh

ECHO=echo

check() {
	$ECHO -n "test command: $@... "
	if $@ >/dev/null 2>&1; then
		$ECHO "passed"
	else
		$ECHO "failed"
		$@ 
		exit 1
	fi
}

cmp() {
	cmd=$1
	$ECHO -n "test output:  $cmd... "
	result=`$cmd`
	expected=`$ECHO "$2"`
	if test "x$result" != "x$expected"; then
		$ECHO "failed"
		$ECHO "  expected output: $expected"
		$ECHO "  actual output:   $result"
		exit 1
	else
		$ECHO "passed"
	fi
}

tests() {
	outfile=test.out
	check ./fnv1a --help
	check ./fnv1a --version
	check ./fnv1a -o$outfile
	check ./fnv1a -o=$outfile
	check ./fnv1a -o $outfile
	check ./fnv1a --output=$outfile
	check ./fnv1a --output $outfile
	check ./fnv1a -i abc
	check ./fnv1a -ic abc
	check ./fnv1a -io$outfile
	cmp "./fnv1a -ic abc" "c9ea9d13    abc"
	cmp "./fnv1a -ici abc" "c9ea9d13    abc"
	cmp "./fnv1a -ic ABC" "27823cf3    ABC"
	cmp "./fnv1a -icic ABC" "27823cf3    ABC"
	cmp "./fnv1a -ici --caseful ABC" "27823cf3    ABC"
	cmp "./fnv1a -ici ABC" "c9ea9d13    ABC"
	rm -f $outfile
}

tests

check ./echo --help
check ./echo -n
cmp "./echo 123" "123"
cmp "./echo --prefix=123 456 789" "123456 123789"
cmp "./echo -np123 456 789" "123456 123789"
cmp "./echo -n --prefix 123 456 789" "123456 123789"
cmp "./echo -np 123 456 789" "123 456 789"

echo
echo now running tests using local echo program
echo

ECHO=./echo

tests

echo
echo All tests passed
