fun myfunction(a, b, c, d, e) {
    print(100)
    return a*b*c*d*e
}

fun fib(a) {
    if(a <= 2) {
        return 1
    }
    ret = fib(a-1) + fib(a-2)
    return ret
}

fun fibUpTo(x) {
    count = 1
    while (count <= x) {
        print(fib(count))
        count = count + 1
    }
}

fun noReturn() {
    print(0-1)
}

fun recur1(a,b) {
    return recur2(a+b,a-b)
}

fun recur2(a,b) {
    if(a-b > 1000) {
        print(0-1)
        print(a)
        print(b)
        return a*b
    }
    return recur1(a*b, a-b)
}

fun act(){}

fun main() {
# test comment
    testBasicPrintingAndVariables = 0

    print(10)
    x = 5
    y = 9

    print(x)
    print(y)

    testExpressions = 0

    print(x>y)
    print(x<y)
    print(x>=y)
    print(x<=y)
    print(x==5)
    print(x==y)
    print(x!=y)
    print(x!=5)
    print(x*y)
    print(x+y)
    print(x-y)
    print(y/3)
    print(x%3)
    print(1&&1||0&&1||0)
    print(x&&y*0+x||y||10+12)
    print((x+y)/2+(x*(y-5))%(x))
    print((x+y)/2+(x*(y-5))%(x) > 2)
    print(!!!!!!!!!x)
    print(!0 + !1||0)
    print(!10||!0 * 12-x+y/3)
    print(0 < 0 < 0 < 0 < 0 < 0)
    print(1 < 1 < 1 < 1 < 1 < 1)
    print(0 > 0 > 0 > 0 > 0 > 0)
    print(1 > 1 > 1 > 1 > 1 > 1)
    print(0 >= 0 <= 0 >= 0 <= 0 >= 0)
    print(1 >= 1 <= 1 >= 1 <= 1 >= 1)
    print(0 == 0 == 0 == 0 == 0 == 0)
    print(1 == 1 == 1 == 1 == 1 == 1)
    print(0 != 0 != 0 != 0 != 0 != 0)
    print(1 != 1 != 1 != 1 != 1 != 1)


    definedVariable = 0
    z = 0

    testWeirdSpacing = 0
    true = 1
    false = 0
    if     (true||                           false) {
#               test comment  2   

        print   (    true* false    + true||false  )
        true        =1000
        print       (true-99)
        false=      1
        while(   false <=true){
            false = 2*false
        }
        print(      false )
    }

    testConditionalsAndNestedIf = 0

    if(z != 0) {
        print(5)
    } else {
        if (100>10 && (y < 2 * x || x*y == 50) && x != y){
            print(99)
            if(definedVariable * (x + y) != 0){
                print(0)
            }else{
                print(50)
            }
        }else{
            print(0)
        }
    }




    testNestedWhile = 0

    x = 1
    y = 1
    while(x <= 5) {
        a = 0
        y = x
        while(a < 5) { 
            print(y)
            y = y + x
            a = a + 1
        }
        x = x + 1
    }

    testNamingVariablesContainingKeywords = 0

    func = 10
    print(func)
    ifelse = 11
    print(ifelse)
    elseif = 12
    print(elseif)
    whileif = 13
    print(whileif)
    if(0) {
        doSomething = 0
    }
    elseVar = 14
    print(elseVar)
    returnval = 15
    print(returnval)
    printing = 16
    print(printing)

    testsWithFunctions = 0

    print(myfunction(1, 2, 3, 4, 5))

    act()
    print(act())
    act = 10
    print(act()+act)


    print(recur2(6,5))

    print(recur1(10,5))

    print(noReturn())


    fibUpTo(5)
    fibUpTo(15)


    print(fib(1))
    print(fib(2))
    print(fib(10))
    print(fib(20))
}