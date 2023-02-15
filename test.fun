# This function tests for parameter scoping

fun scoping(a, b) {
	a = 4
	b = 3
	print(a)
	print(b)
}

# Calculate number of digits in a number

fun numberOfDigits(number) {
	if (number >= 10) {
		return numberOfDigits(number/10)+1
	}
	return 1
}

# Compute a * b + c without using multiplication operator

fun abplusc(a, b, c) {
	if (b == 0) {
		return c
	}
	return a + abplusc(a,b-1,c)
}

# Compute greatest common divisor of 2 numbers

fun gcd(a, b) {
	if (!a) {
		return b
	}
	if (!b) {
		return a
	}

	if (a == b) {
		return a
	}

	if (a > b) {
		return gcd(a-b,b)
	}
	return gcd(a,b-a)
}

# Recursively compute factorial of number num
fun factorial(num) {
	if (num == 1) {
		return num
	}
	return num * factorial(num-1)
}

# Modular Exponentiation
fun power(x, y) {
    res = 1

    while (y > 0) {
        if (y % 2 == 1) {
            res = res * x
        }

        x = x * x
        y = y / 2 
    }

    return res
}

# Check to see if return works inside while loop
fun testWhile() {
	while(1) {
		print(2)
		return 2
	}
}

# Test functions with large parameters and multiple calls

fun largeParams(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams2(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams2(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams3(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams3(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams4(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams4(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams5(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams5(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams6(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams6(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams7(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams7(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams8(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams8(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return largeParams9(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen)
}

fun largeParams9(one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen) {
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	return a + b + c + d + e + one + two + three + four + five
}

fun main() {
        a = 5
	b = 2
	
# Value of a and b should not change
	scoping(a, b)
	print(a)
	print(b)

# Test nested if else statements
	if (1) {
		if (0) {
			print(20)
		} else {
			print(10)
			if (1) {
				print(30)
			}
		}
	}

    	print(numberOfDigits(11111))
	print(numberOfDigits(1111001))
	print(abplusc(3, 5, 1))
	print(abplusc(4, 6, 2))
    	print(gcd(50000, 7911))
	print(gcd(10, 15))
	print(gcd(10000, 31235))
	print(factorial(5))
    	print(factorial(10))

    	print(power(3, 5))
    	print(power(3, 6))
    	print(power(3, 7))
    	print(power(4, 2))
    	print(power(4, 3))
    	print(power(4, 4))
    	print(power(5, 2))
    	print(power(5, 3))
    	print(power(5, 4))
    	print(power(6, 2))
    	print(power(6, 3))
    	print(power(6, 4))

    	testWhile()

    	print(largeParams(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16))
}

###### Test for multiple hashtags in comments