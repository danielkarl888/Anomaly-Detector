#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
    void readFile(string fileName){
        ofstream out(fileName);
        string str="";
        while((str=read())!="done"){
            out<<str<<endl;
        }
        out.close();
    }


    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
};

// implement here your command classes



#endif /* COMMANDS_H_ */
