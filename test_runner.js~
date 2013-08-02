var tempFileName = "temp.c";
var tempExecName = "temp";
var async = require("async");
var child_process = require("child_process");
Array.prototype.contains = function(el){
    return ~this.indexOf(el);
}
String.prototype.endsWith = function(substr){
    return (this.lastIndexOf(substr)+substr.length) === this.length;
}



console.log("\n-----------------C Test Runner---------------\n")

var fs = require("fs");
var runFile,otherfiles;

processCommandLineArgs();
file = getFile();
tests = extractTests(file);

async.mapSeries(tests,runTest,function(err,results){
    console.log("It :");
    var passed = 0;
    results.forEach(function(result){
        if(result.code !== 0){
            var base = "\t \033[31m✘\033[0m Test '"+result.title+"' failed ";
            if(result.out){
                base += "(out: "+result.out+ ")";
            }
            if(result.err){
                base += "(out: "+result.out+ ")";
            }
            console.log(base);
        }else{
            passed++;
            console.log("\t","\033[32m✔\033[0m",result.title);
        }
    });
    console.log("\nPassed "+passed+"/"+results.length+" tests.\n");
    if(passed !== results.length){
        console.log("\n  --\033[31mError - spec failing.\033[0m \n");
    }else {
        console.log("\n  --\033[32mAll Tests pass :)\033[0m \n");
    }
    
});

function runTest(test,cb){
    var deps = otherfiles.map(function(name){ return name+".c";});
    async.waterfall([function(callback){
        writeTestToTempFile(test,callback);
    },function(callback){
        child_process.exec("gcc -Wall "+tempFileName+" "+deps.join(" ")+" -o "+tempExecName,function(error,stdout,stderr){
        callback(error,stdout,stderr);
        });
    },function(stderr,stdout,callback){
        if(stderr.trim() !== ""){
            return callback(new Error(stderr));
        }
        var std,codeO,stde;
        var ex = child_process.exec("./"+tempExecName,function(err,stdout,stderr){
            if(codeO !== undefined) callback(null,codeO,stdout,stderr);
            std = stdout;
            stde = stderr;
        });
        ex.on("exit",function(code,signal){
            if(std !== undefined) callback(null,code,std,stderr);
            codeO = code;
        });
    }],function (err, exit,stdout,stderr) {
        cb(null,{code:exit,out:stdout,err:stderr,title:test.title});
    });
}

function writeTestToTempFile(test,callback){
    var deps = otherfiles.map(function(dep){
        return '#include "'+dep+'.h"';
    }).join("\n").concat("\n");
    boilterplate = "#include <stdio.h>\n"+
                   "#include <stdlib.h>\n"+
                   "#include <math.h>\n"+
                   "#include <stdbool.h>\n"+
                   "#include <string.h>\n"+
                   "#include <stdarg.h>\n"+
                   "#define ok(...) __ok_hidden((ok_hidden_args){__VA_ARGS__});\n"+
                   "#define equal(...) __equal_hidden((equal_hidden_args){__VA_ARGS__});\n"+
                   deps+
                   "typedef struct { bool predicate; char * message;} ok_hidden_args;\n"+
                   "typedef struct { void * first; void * second; char * message;} equal_hidden_args;\n"+
                   "\nvoid __ok_hidden(ok_hidden_args inp) {\n"+
                   "    inp.message= inp.message ? inp.message : \"\";\n"+
                   "    printf(\"%s\",inp.message);\n"+
                   "    if(!inp.predicate) exit(-1); \n}\n"+
                   "                  \n"+
                   "\nvoid __equal_hidden(equal_hidden_args inp) {\n"+
                   "    inp.message= inp.message ? inp.message : \"\";\n"+
                   "    printf(\"%s\",inp.message);\n"+
                   "    if(inp.first != inp.second) { printf(\"\\nExpected %d to be equal %d\",inp.first,inp.second);exit(-1); }\n}\n"+
                   "                  \n"+
                   "int main(void){ \n"+
                   test.code +
                   "return 0;\n"+
                   "}\n";
    try{
        fs.writeFileSync(tempFileName,boilterplate);
        callback(null);

    }catch(e){
        callback(new Error("PROBLEM WRITING TEST",test,"TO FILE"));
    }
}

function extractTests(content){
    var startPatternHead = "It ";
    var endPatternHead = "===>";
    var endPattern = "\n<===";
    var insideTest = false;
    var extractedTests = [];
    var currentTestTitle = "";
    var currentTest = null;
    for(var i=0;i<content.length;i++){

        if(insideTest){

            if(content.substring(i,i+endPattern.length) === endPattern){
                insideTest = false;
                i=i+endPattern.length;
                extractedTests.push({code:currentTest,title:currentTestTitle});
            }else{
                currentTest+=content[i];
            }
        }else{
            if(content.substring(i,i+startPatternHead.length) === startPatternHead){
                var buffer = "";
                i = i+startPatternHead.length
                while(content.substring(i,i+endPatternHead.length) !== endPatternHead){
                    buffer+=content[i];
                    i++;
                    if(content[i] === undefined) break;
                }
                currentTestTitle = buffer.substring(buffer.indexOf('"')+1,buffer.lastIndexOf('"'));

                i+=endPatternHead.length;
                insideTest = true;
                currentTest = "";
            }
        }
    }
    return extractedTests;
}

function processCommandLineArgs(){
    if(["nodejs","node"].contains(process.argv[0])){
        // nodejs test_runner
        runFile = process.argv[2];
        otherfiles = process.argv.slice(3);
    }else{
        runFile = process.argv[1];
        otherfiles = process.argv.slice(2);
    }

    if((runFile === undefined) || (!runFile.toLowerCase().endsWith(".c"))){
        console.log("Usage is: nodejs test_runner <YOURFILE.c> <OTHERFILES.c>\n\n\n");
        process.exit(-1);
    }
}

function getFile(){
    try{
        var content = fs.readFileSync(runFile);
    }catch(e){
        console.log("Can not open",runFile);
        process.exit(-2);
    }
    return content.toString();
}
