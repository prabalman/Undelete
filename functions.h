bool jpgComp(BYTE buffer[BLOCK_SIZE])
{
    BYTE signature1[4] = {0xff, 0xd8, 0xff, 0xe0};
    BYTE signature2[4] = {0xff, 0xd8, 0xff, 0xe1};
      if (buffer[0] == signature1[0] && buffer[1] == signature1[1] && buffer[2] == signature1[2] && buffer[3] == signature1[3] )
    {
             return true;
    }
      if (buffer[0] == signature2[0] && buffer[1] == signature2[1] && buffer[2] == signature2[2] && buffer[3] == signature2[3] )
    {
             return true;
    }
    return false;
}


short ReadSect
       (const char *_dsk,    // disk to access
       char *&_buff,         // buffer where sector will be stored
       unsigned int _nsect   // sector number, starting with 0
       )
{
DWORD dwRead;
HANDLE hDisk=CreateFile(_dsk,GENERIC_READ,FILE_SHARE_VALID_FLAGS,0,OPEN_EXISTING,0,0);
if(hDisk==INVALID_HANDLE_VALUE) // this may happen if another program is already reading from disk
  {
     CloseHandle(hDisk);
     return 1;
  }
SetFilePointer(hDisk,_nsect*512,0,FILE_BEGIN); // which sector to read

ReadFile(hDisk,_buff,512,&dwRead,0);  // read sector
CloseHandle(hDisk);
return 0;
}
