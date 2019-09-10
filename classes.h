class pathInfo
{
    char *drive;
    char *outpath;

public:
       void createValidPath(char *d, char *o)
    {
        cout<<"\nCreating Valid Path";
        //For the Drive to be recovered
        drive = new char[10000];
        strcpy(drive,"\\\\.\\");
        strcat(drive,d);
        //For the Output File Path
        outpath = new char[10000];
        strcpy(outpath, o);
        checkDir(outpath);
        cout<<"\nCreated Valid Path";
    }
    pathInfo()
    {

    }
    pathInfo(char*x)
    {

        char o[1000];
        cout<<"Enter Path for Saving Recovered File >>> \n";
        cin>>o;
        char *d = new char[sizeof(x)+1];
        strcpy(d,x);
        createValidPath(d,o);
    }
    pathInfo(char*x, char*y)
    {
        cout<<"\nTaken two arg";
         createValidPath(x,y);
    }
    pathInfo(pathInfo& temp )
    {
        drive = temp.drive;
        outpath = temp.outpath;

    };
    void askUser()
    {
        char d[1000],o[1000];
        cout<<"Enter the Drive to be Recovered >>> \n";
        cin>>d;
        cout<<"Enter Path for Saving Recovered File >>> \n";
        cin>>o;
        createValidPath(d,o);
    }
    void checkDir( char* path)
    {
        if ((GetFileAttributes(path)) == INVALID_FILE_ATTRIBUTES) // Checking wheather the Directory exist or not
        {
            cout <<endl<< "Directory doesn't exist\n";
            CreateDirectory(reinterpret_cast<LPCTSTR>(path), 0);// Creating the Folder
            if ((GetFileAttributes(path)) == INVALID_FILE_ATTRIBUTES) //if the Folder is still  not created after the Creation then stoping the program
            {
                 cout<<endl<<"invalid Directory Name";
                exit(1); // Exiting the Prgram

            }else{
               cout<<endl<< "Directory Created\n";
            }

        }
    }


    char* retDrive()
    {
        return drive;
    }
    char* retOutPath()
    {
        return outpath;
    }
};

class generateFile
{
protected:
    int cnt ;
    ofstream a_file;
    char filename[100];
    char* outFileIn;
public:

    generateFile(pathInfo p1)
    {
        cnt  = 0 ;
        outFileIn = new char[sizeof(p1.retOutPath())+1];
        strcpy(outFileIn, p1.retOutPath());
        //filename = new char[sizeof(o)+100];
    }
    void makeFile(BYTE buffer[BLOCK_SIZE])
    {

        snprintf(filename, sizeof(filename), "%s%s%d%s", outFileIn,"/rev", cnt ,".jpg"); //concatinating String and int Filenames
      // strcat(outFileIn,filename);
        //cout<<"\n outFileIn -- "<<outFileIn<<endl;
        cout<<endl<<"Filename --"<<filename<<endl;
        a_file.open( filename, ios::trunc |ios::binary);
        a_file.write(reinterpret_cast<char*>(buffer), BLOCK_SIZE);
    }
    void appendFile(BYTE buffer[BLOCK_SIZE])
    {
        a_file.write(reinterpret_cast<char*>(buffer), BLOCK_SIZE);
    }
    void close()
    {
        cnt++;
        a_file.close();
    }
};


class recoveryCtrl
{
    int match;
    BYTE buffer[BLOCK_SIZE];
    ifstream rawFile;
    pathInfo path;
public:
    recoveryCtrl(pathInfo p1)
    {
        match = 0;
        path = p1; // Copying the Object so that it can be passed to the File Creator Class aswell

    }


      void revJpgDirect()
    {
        bool clock = true;
        int sector=0;
        char * dsk= path.retDrive();

        char *buff=new char[512];


        generateFile creatorObject(path) ;// Creating Generate File class with agrguement as the drive ant path storage

            cout<<endl<<"Drive Opened \n";

            while(sector < SECTOR )
            {
                if(clock == true)
                {
                     ReadSect(dsk,buff,sector);
                     sector++;
                     cout<<".";

                }

                if (jpgComp(reinterpret_cast<BYTE*>(buff)))
                {

                    match++;

                    clock = false;

                    creatorObject.makeFile(reinterpret_cast<BYTE*>(buff));
                    cout<<"\nMatch Found : "<< match;
                    do
                    {
                        sector++;
                        ReadSect(dsk,buff,sector);

                        creatorObject.appendFile(reinterpret_cast<BYTE*>(buff));

                    }while (!jpgComp(reinterpret_cast<BYTE*>(buff)));
                    creatorObject.close();
                }

            }
        delete[]buff;
    }

};



