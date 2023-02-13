fun f1(x,y,z){
    if(y!=0){
        return f1(x,y+1,z)
    }
    else{
        return 1
    }
}

#random comment

fun f2(x,y,z){
    while (x!=50){
        x = x+1
    }
    return f1(x,y,z)  
}

fun func3(x,y,z){
    while (z!=10){
        z = z+1
    }
    return f2(x,y,z)  
}

fun testOperators(x, y, z){

    x = 1
    y = 1
    z = 1
    print (!x)
    print (5*x)
    print (5/(5*x))
    z = 10
    print (10%5)
    print (x<z)
    print (x<=y)
    print (x<y)
    print (x>y)
    print (x>=y)
    print (z==z)
    print (z!=z)
    print (1||0)
    print (0||1)
    print (0||0)
    print (1||1)
    print (1&&0)
    print (0&&1)
    print (0&&0)
    print (1&&1)
    a = 410

}


fun main(){
    x = 20
    y = 18446744073709551616
    z = 1
    a = 420
    ifs = 0 
    whiles = 0
    funct = 0


    print (f1(x,y,x-1))




    print (func3(x,y,z))
    print (x)
    print (y)
    print (z)


    print (a)
    print (testOperators(x,y,a))
    print (!1)
    print (!!1)
    print (a)
}
#random comment w new line

#random comment w no new line