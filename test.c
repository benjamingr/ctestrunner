

It "Adds 0+0" ===>
	int a;
    int b;
    a = b = 0;
    if(add(a,b) != 0){
        return 1;
    }else{
        return 0;
    }
    
<===


It "Adds 2+2" ===>
	int a;
    int b;
    a = b = 2;
    if(add(a,b) != 4){
        return 1;
    }else{
        return 0;
    }
    
<===



It "Adds 2+ -52" ===>
	int a;
    int b;
    a = 2;
    b = -52;
    if(add(a,b) != -50){
        return 1;
    }else{
        return 0;
    }
    
<===

It "Says 1+1 = 2" ===>
	int a;
    int b;
    a = 1;
    b = 1;
    if(add(a,b) != 2){
        return 1;
    }else{
        return 0;
    }
    
<===


It "Works with ok" ===>
    ok(1==1,"YEAH");    
<===


It "Works with equals" ===>
    equal(10,10,"10 is 10");    
<===

