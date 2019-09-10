#include <windows.h>
#include <iostream>
#include<fstream>
  using namespace std;
#define BLOCK_SIZE 512
//#define RAW_FILE "forPNG.img"
//#define DRIVE "\\\\.\\G:"
#define MAX 1000
#define SECTOR 32768
#include"functions.h"
#include"classes.h"


int main(int argc, char* argv[])
{
    char* drive = new char[MAX];
    char*outPath = new char[MAX];
     if( argc == 1)
     {
        cout<<endl<<"No arguments were passed\n";
        pathInfo path1;
        path1.askUser();
        cout<<endl<<"values stored";
        recoveryCtrl obj1(path1);
        obj1.revJpgDirect();
     }else if(argc ==2)
    {
        // Only Drive required for the recovery of the file argument were given
        cout<<endl<<"\n Drive ::"<< argv[1];
         if(!strcmp(argv[1],"/?") )
        {
            cout<<"\n recover [DRIVE:(to be recovered from)] [DRIVE PATH: (Recover file to folder)] ";
            return 0;
        }else{
            pathInfo path1(argv[2]);
            cout<<endl<<"Values stored";
            recoveryCtrl obj1(path1);
            obj1.revJpgDirect();
        }

    }else if(argc ==3)
    {
          cout<<"\n Drive ::"<< argv[1];
          cout<<"\n Storage path ::"<< argv[2];

        // All the required arguments were given by users
        pathInfo path1(argv[2],argv[3]);
        cout<<"values stored";
        recoveryCtrl obj1(path1);
        obj1.revJpgDirect();
    }
    else{

        cout<<endl<<"Invalid No of Arguments\n"<<endl;
        cout<<"\n recover [DRIVE:(to be recovered from)] [DRIVE PATH: (Recover file to folder)] ";
        return 0;
    }


}
