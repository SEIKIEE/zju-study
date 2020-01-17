#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define MAXLENGTH 1000

int main()
{
    /*The program in user mode reads out the output of the kernel module 
     *from the / var / log / kern. log (ubuntu) file
     */
    string file = "/var/log/kern.log";
    string mark = "Process log:";    //mark in the module
    
    int count = 0;  //count the number of inf occur

    char buffer[MAXLENGTH]; //store the one line log information
    string temp;

    fstream fs;
    fs.open(file, ios::in);
    
    while(!fs.eof())
    {
        fs.getline(buffer,MAXLENGTH,'\n');
        temp = buffer;
        if(temp.find(mark)!=string::npos)
        {
            count++;    //if inf occurs, count is added by 1
        }
    }
    fs.close();

    int flag = 0;
    fs.open(file, ios::in);
    while(!fs.eof())
    {
        fs.getline(buffer,MAXLENGTH,'\n');
        temp = buffer;
        if(temp.find(mark)!=string::npos)
        {
            flag++;
        }
        if(flag == count)   //if meet the last inf print the information
        {
            cout<<buffer<<endl;
        }
    }
    fs.close();

    return 0;    
}
