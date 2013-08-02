ctestrunner
===========

Playing around with C and Node in C Test Runner.

 - Requires NodeJS
 
###Usage:
 
 Run `nodejs test_runner.js <YOURFILE.c> dependencies`
 
 To run the example run:
 
     nodejs test_runner.js test.c add
     
     
###Example:

Test file:

    It "Says 1+1 = 2" ===>
        if(add(1,1) != 2){
            return 1; // error result
        }else{
            return 0; // yay
        }
        
    <===


    It "Works with ok" ===>
        ok(1==1,"YEAH");    
    <===


    It "Works with equals" ===>
        equal(10,10,"10 is 10");    
    <===
    
Code Files:

    // .h file
    int add(int a,int b);

    // .c file
    
    int add(int a,int b){
        return a+b;
    }
    
Usage: 
    nodejs test_runner.js test.c add

>It :

>	 ✔ Says 1+1 = 2

>	 ✔ Works with ok

>	 ✔ Works with equals

