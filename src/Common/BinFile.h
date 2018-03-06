#pragma once
//+------------------------------------------------------------------+
//| ������� �����-������� ������ WinAPI (����� �� ������ 4Gb)        |
//+------------------------------------------------------------------+
class BinFile
{
public:
   static const UINT64 INVALID_POSITION;

protected:
   HANDLE            m_file;                 // ����� �����

public:
   BinFile() : m_file(INVALID_HANDLE_VALUE) {}
   ~BinFile()                               { Close(); }
   //---
   inline bool       Open(const char *lpFileName,const DWORD dwAccess,const DWORD dwShare,const DWORD dwCreationFlags,const DWORD dwAttributes=FILE_ATTRIBUTE_NORMAL);
   //---
   inline bool       OpenRead(const char *lpFileName)  { return Open(lpFileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,OPEN_EXISTING);  }
   inline bool       OpenWrite(const char *lpFileName) { return Open(lpFileName,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,CREATE_ALWAYS); }
   //---
   inline void       Close(void);
   inline UINT64     Size(void) const;
   static UINT64     Size(const char *path);
   inline FILETIME   Time(void) const;
   inline HANDLE     Handle(void)   { return(m_file);                       }
   inline bool       IsOpen() const { return(m_file!=INVALID_HANDLE_VALUE); }
   inline DWORD      Read(void  *buffer,const DWORD length);
   inline DWORD      Write(const void *buffer,const DWORD length);
   inline UINT64     Seek(const INT64 distance,const DWORD method);
   inline bool       Flush();
   inline bool       ChangeSize(const UINT64 size);
   inline UINT64     CurrPos();
   char*             Load(const char *filename,DWORD &size);
   inline BOOL       SetFileTime(const FILETIME *create,const FILETIME *access,const FILETIME *write);
   //--- ����������� ������ ���������� �������
   /*
   inline static bool CopyFile(const CStr& src,const CStr& dst);
   inline static int CopyFiles(const CStr& path,const CStr& newpath,const CStr& mask,const CStr& suffix,const bool subdir);
   inline static int CopyFiles(const CStr& path,const CStr& newpath,const CStr& mask,const bool subdir);
   inline static bool CreateDirectory(const CStr& path);
   inline static bool RemoveDirectory(const CStr& path);
   inline static bool RemoveEmptyDirectory(const CStr& path);
   inline static bool CleanDirectory(const CStr& path,const CStr& mask);
   inline static bool CleanEmptyDirectory(const CStr& path);
   */
};

const __declspec(selectany) UINT64 BinFile::INVALID_POSITION=_UI64_MAX;
//+------------------------------------------------------------------+
//| �������� ����� ��� ������                                        |
//+------------------------------------------------------------------+
inline bool BinFile::Open(const char *lpFileName,const DWORD dwAccess,const DWORD dwShare,const DWORD dwCreationFlags,const DWORD dwAttributes)
{
//--- ������� �� ������ ������ ���������� ����
    Close();
//--- ��������
    if(lpFileName)
        m_file=CreateFile(lpFileName,dwAccess,dwShare,NULL,dwCreationFlags,dwAttributes,NULL);
//--- ������ ���������
    return(m_file!=INVALID_HANDLE_VALUE);
}
//+------------------------------------------------------------------+
//| �������� �����                                                   |
//+------------------------------------------------------------------+
inline void BinFile::Close()
{
    if(m_file != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_file);
        m_file=INVALID_HANDLE_VALUE;
    }
}
//+------------------------------------------------------------------+
//| ������ �����                                                     |
//+------------------------------------------------------------------+
inline UINT64 BinFile::Size() const
{
    LARGE_INTEGER li={0};
//--- ��������
    if(m_file==INVALID_HANDLE_VALUE) return(0);
//--- ��� ������������� � WinMobile ���������� GetFileSize
    if((li.LowPart=::GetFileSize(m_file,(LPDWORD)&li.HighPart))==INVALID_FILE_SIZE)
        if(GetLastError()!=NO_ERROR) return(0);
// ���������� ���������
    return((UINT64)li.QuadPart);
}
//+------------------------------------------------------------------+
//| ������ �����                                                     |
//+------------------------------------------------------------------+
inline UINT64 BinFile::Size(const char *path)
{
    LARGE_INTEGER             li={0};
    WIN32_FILE_ATTRIBUTE_DATA fad;
//--- ������� ��������� ����� ��� ������
    if(GetFileAttributesEx(path,GetFileExInfoStandard,&fad))
    {
        li.LowPart =fad.nFileSizeLow;
        li.HighPart=(LONG)fad.nFileSizeHigh;
    }
//--- ���������� ���������
    return((UINT64)li.QuadPart);
}
//+------------------------------------------------------------------+
//| ������ �����                                                     |
//+------------------------------------------------------------------+
inline FILETIME BinFile::Time() const
{
    FILETIME ft={0};
//--- ��������
    if(m_file!=INVALID_HANDLE_VALUE) GetFileTime(m_file,NULL,NULL,&ft);
//--- ���������� ���������
    return(ft);
}
//+------------------------------------------------------------------+
//| ������ ������ ��������� ����� � ����                             |
//+------------------------------------------------------------------+
inline DWORD BinFile::Read(void *buffer,const DWORD length)
{
    DWORD readed=0;
//--- ��������
    if(m_file==INVALID_HANDLE_VALUE || buffer==NULL || length<1) return(0);
//--- ������� � ������ ���������
    if(ReadFile(m_file,buffer,length,&readed,NULL)==0) readed=0;
//--- ������ ���-�� ��������� ����
    return(readed);
}
//+------------------------------------------------------------------+
//| ������ ������ ��������� ����� � ����                             |
//+------------------------------------------------------------------+
inline DWORD BinFile::Write(const void *buffer,const DWORD length)
{
    DWORD written=0;
//--- ��������
    if(m_file!=INVALID_HANDLE_VALUE && buffer && length>0)
    {
        //--- ������� ������
        if(WriteFile(m_file,buffer,length,&written,NULL)==0)
            written=0;
    }
//--- ������ ���-�� ���������� ����
    return(written);
}
//+------------------------------------------------------------------+
//| ����������� ��������� ���������                                  |
//+------------------------------------------------------------------+
inline UINT64 BinFile::Seek(const INT64 distance,const DWORD method)
{
    LARGE_INTEGER li={0};
    //--- ��������
    if(m_file==INVALID_HANDLE_VALUE) return(INVALID_POSITION);
    //---
    li.QuadPart=distance;
    li.LowPart=SetFilePointer(m_file,(LONG)li.LowPart,&li.HighPart,method);
    //--- ������?
    if(li.LowPart==INVALID_SET_FILE_POINTER && GetLastError()!=NO_ERROR) return(INVALID_POSITION);
    //--- ���������� ��������
    return((UINT64)li.QuadPart);
}
//+------------------------------------------------------------------+
//| ����� ����� �� ����                                              |
//+------------------------------------------------------------------+
inline bool BinFile::Flush()
{
    if(m_file!=INVALID_HANDLE_VALUE) return(::FlushFileBuffers(m_file)!=0);
    return(false);
}
//+------------------------------------------------------------------+
//| ��������� ������� �����                                          |
//+------------------------------------------------------------------+
inline bool BinFile::ChangeSize(const UINT64 size)
{
    return(BinFile::Seek((INT64)size,FILE_BEGIN)==size && SetEndOfFile(m_file));
}
//+------------------------------------------------------------------+
//| ������� ��������� ��������� ���������                            |
//+------------------------------------------------------------------+
inline UINT64 BinFile::CurrPos()
{
    return(BinFile::Seek(INT64(0),FILE_CURRENT));
}
//+------------------------------------------------------------------+
//| ������ � ���������� ����� ����� �����                            |
//+------------------------------------------------------------------+
inline char* BinFile::Load(const char *filename,DWORD &size)
{
    DWORD  readed=0;
    char  *buffer;
//--- ��������
    if(filename==NULL)                     return(NULL);
    if(!OpenRead(filename))                return(NULL);
    if((size=(DWORD)Size())==0)
    {
        Close();
        return(NULL);
    }
//--- ������� �����
    if((buffer=new(std::nothrow) char[size+16])==NULL)
    {
       Close();
       return(NULL);
    }
//--- ������� � ������ ���������
    if(size>0)
        if(ReadFile(m_file,buffer,size,&readed,NULL)==0)
        {
            //--- ��������� �����
            delete[] buffer;
            buffer=NULL;
        }
//--- ������� ���� � ������ ������ �� �����
    Close();
    return(buffer);
}
//+------------------------------------------------------------------+
//| ��������� ��������� ������� �����                                |
//+------------------------------------------------------------------+
inline BOOL BinFile::SetFileTime(const FILETIME *create,const FILETIME *access,const FILETIME *write)
{
//--- ��������
    if(m_file==INVALID_HANDLE_VALUE) return(FALSE);
//--- ������������� �����
    return(::SetFileTime(m_file,create,access,write));
}

/*
//+------------------------------------------------------------------+
//| ����������� �����                                                |
//+------------------------------------------------------------------+
inline bool CBinFile::CopyFile(const CStr& src,const CStr& dst)
  {
   CBinFile  src_file,dst_file;
   BYTE     *buffer;
   DWORD     readed,src_size;
   enum    { BUFFER_SIZE=4*1024*1024 };
//--- ��������
   if(src.Len()<1 || dst.Len()<1) return(false);
//--- ������� �������� � ��������
   if(!src_file.Open(src,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN) ||
      !dst_file.Open(dst,GENERIC_WRITE,0,CREATE_ALWAYS,FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN))
      return(false);
   src_size=(DWORD)src_file.Size();
//--- �������� ������
   if((buffer=(BYTE*)::VirtualAlloc(NULL,BUFFER_SIZE,MEM_COMMIT,PAGE_READWRITE))==NULL)
      return(false);
//--- ��������� �������� ����� ��������������
   while((readed=src_file.Read(buffer,BUFFER_SIZE))==BUFFER_SIZE && dst_file.Write(buffer,BUFFER_SIZE)==BUFFER_SIZE)
      src_size-=readed;
   dst_file.Close();
//--- ���������� � ������� �������
   if(src_size!=readed                                                       || // ������ ������ ����������?
      !dst_file.Open(dst,GENERIC_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL)|| // ������ ������� ����?
       dst_file.Seek(INT64(0),FILE_END)==CBinFile::INVALID_POSITION          || // ����� �������������������?
       dst_file.Write(buffer,readed)!=readed)                                   // ��������?
     {
      VirtualFree(buffer,0,MEM_RELEASE);
      DeleteFile(dst.Str());
      return(false);
     }
//--- ����������� �������
   dst_file.Close();
   src_file.Close();
   VirtualFree(buffer,0,MEM_RELEASE);
//--- � ����� � ��� ������ �������� ����!
   return(true);
  }
//+------------------------------------------------------------------+
//| ����������� ������ �� �����                                      |
//+------------------------------------------------------------------+
inline int CBinFile::CopyFiles(const CStr& path,const CStr& newpath,const CStr& mask,const CStr& suffix,const bool subdir)
  {
   CStr512         src,dst,name;
   HANDLE          hSearch;
   WIN32_FIND_DATA fnd;
   int             count=0,pos;
//--- ���� �����
   src.Format(L"%s\\%s",path.Str(),mask.Str());
   if((hSearch=FindFirstFile(src.Str(), &fnd))!=INVALID_HANDLE_VALUE)
     {
      do
        {
         //--- ���������� �������� �������
         if(CStr::Compare(fnd.cFileName,L".")==0 || CStr::Compare(fnd.cFileName,L"..")==0) continue;
         //--- ��� �������?
         if(!(fnd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
           {
            //--- ��������� ���� ���������
            src.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- ��������� ����� ��� � ������ ��������
            name.Assign(fnd.cFileName);
            if((pos=name.FindRChar('.'))>=0) name.Insert((UINT)pos,suffix);
            else                             name.Append(suffix);
            //--- ��������� ���� ���������
            dst.Format(L"%s\\%s",newpath.Str(),name.Str());
            //--- �������� ����
            if(::CopyFile(src.Str(),dst.Str(),FALSE)!=FALSE) count++;
           }
         else
            if(subdir)
              {
               //--- ���������� ����
               src.Format(L"%s\\%s",path.Str(),fnd.cFileName);
               dst.Format(L"%s\\%s",newpath.Str(),fnd.cFileName);
               //--- �������� ����� ����������
               CreateDirectory(dst);
               //--- ��������
               count+=CopyFiles(src,dst,mask,subdir);
              }
        } while(FindNextFile(hSearch,&fnd)!=0);
      //--- ��������� �����
      FindClose(hSearch);
     }
//---
   return(count);
  }
//+------------------------------------------------------------------+
//| ����������� ������ �� �����                                      |
//+------------------------------------------------------------------+
inline int CBinFile::CopyFiles(const CStr& path,const CStr& newpath,const CStr& mask,const bool subdir)
  {
   return(CopyFiles(path,newpath,mask,CStr32(L""),subdir));
  }
//+------------------------------------------------------------------+
//| �������� ������������������ ���������� � ������������ � �����    |
//+------------------------------------------------------------------+
inline bool CBinFile::CreateDirectory(const CStr& path)
  {
   wchar_t *cp,temp[MAX_PATH];
   DWORD    attr;
//--- ���� ����� ����������?
   if((attr=GetFileAttributes(path.Str()))!=INVALID_FILE_ATTRIBUTES)
     {
      //--- ��� �������?
      if(attr & FILE_ATTRIBUTE_DIRECTORY)
         return(true);
      //--- ��� ���-�� ���, �� ����� ������� ����� �������
      return(false);
     }
//--- ���������
   CStr::Copy(temp,path.Str());
//--- ������ ���� ��������������� �������� ����������
   for(cp=temp;*cp!=L'\0';cp++)
      if(*cp==L'\\')
        {
         *cp=L'\0';
         if(GetFileAttributes(temp)==INVALID_FILE_ATTRIBUTES)
            if(!::CreateDirectory(temp,NULL)) return(false);
         *cp=L'\\';
        }
//--- �������
   if(GetFileAttributes(temp)==INVALID_FILE_ATTRIBUTES)
      if(!::CreateDirectory(temp,NULL)) return(false);
//--- �� ��
   return(true);
  }
//+------------------------------------------------------------------+
//| ������ ����������                                                |
//+------------------------------------------------------------------+
inline bool CBinFile::CleanDirectory(const CStr& path,const CStr& mask)
  {
   HANDLE          hSearch;
   WIN32_FIND_DATA fnd;
   CStrPath        tmp;
   bool            res=true;
//--- �������� �� ��������
   if(path.Empty() || path.Len()<=3) return(false);
//--- ���������� ����
   tmp.Format(L"%s\\%s",path.Str(),mask.Str());
//--- �������� �����
   if((hSearch=FindFirstFile(tmp.Str(),&fnd))!=INVALID_HANDLE_VALUE)
     {
      do
        {
         //--- ������� ��� ���
         if(fnd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
           {
            //--- ������� ���������� ���� ����������
            if(CStr::Compare(fnd.cFileName,L".")==0 || CStr::Compare(fnd.cFileName,L"..")==0)
               continue;
            //--- ���������� ���� ��� �������� ����� � ���� ����������
            tmp.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- ������ ��� ������ ���� ����������
            CleanDirectory(tmp,mask);
            //--- ������ ���� ���������
            res=::RemoveDirectory(tmp.Str()) && res;
           }
         else
           {
            //--- ���������� ��� �����
            tmp.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- ������ ���
            res=::DeleteFile(tmp.Str()) && res;
           }
        }
      while(FindNextFile(hSearch,&fnd));
      //--- ������� �� �����
      FindClose(hSearch);
     }
//--- �����
   return(res);
  }
//+------------------------------------------------------------------+
//| ������� ������ ����������                                        |
//+------------------------------------------------------------------+
inline bool CBinFile::CleanEmptyDirectory(const CStr& path)
  {
   HANDLE          hSearch;
   WIN32_FIND_DATA fnd;
   CStrPath        tmp;
   bool            empty=true;
//--- �������� �� ��������
   if(path.Empty() || path.Len()<=3)               return(false);
//--- ���������� ����
   tmp.Format(L"%s\\*.*",path.Str());
//--- �������� �����
   if((hSearch=FindFirstFile(tmp.Str(),&fnd))!=INVALID_HANDLE_VALUE)
     {
      do
        {
         //--- ������� ��� ���
         if(fnd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
           {
            //--- ������� ���������� ���� ����������
            if(CStr::Compare(fnd.cFileName,L".")==0 || CStr::Compare(fnd.cFileName,L"..")==0)
               continue;
            //--- ���������� ���� ��� �������� ����� � ���� ����������
            tmp.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- ������ ��� ������ ���� ����������
            if(CleanEmptyDirectory(tmp))
              {
               //--- ������ �������
               ::RemoveDirectory(tmp.Str());
               //--- ���� ������
               continue;
              }
           }
         //--- �� �����
         empty=false;
        }
      while(FindNextFile(hSearch,&fnd));
      //--- ������� �� �����
      FindClose(hSearch);
     }
//--- ������ ���������
   return(empty);
  }
//+------------------------------------------------------------------+
//| �������� ����������                                              |
//+------------------------------------------------------------------+
inline bool CBinFile::RemoveDirectory(const CStr& path)
  {
   return(CleanDirectory(path,CStr16(L"*")) && ::RemoveDirectory(path.Str()));
  }
//+------------------------------------------------------------------+
//| �������� ����� ����������                                        |
//+------------------------------------------------------------------+
inline bool CBinFile::RemoveEmptyDirectory(const CStr& path)
  {
   return(CleanEmptyDirectory(path) && ::RemoveDirectory(path.Str()));
  }
//+------------------------------------------------------------------+
*/
