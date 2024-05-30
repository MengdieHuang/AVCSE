
// EncVideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EncVideo.h"
#include "EncVideoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEncVideoDlg �Ի���



CEncVideoDlg::CEncVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncVideoDlg::IDD, pParent)
	, PlainPath(_T(""))
	, CipherPath(_T(""))
	//, EncMBNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_PLAINFILE, PlainPath);
	DDX_Text(pDX, IDC_EDIT2, CipherPath);
	//DDX_Text(pDX, IDC_EDIT1, EncMBNum);
}

BEGIN_MESSAGE_MAP(CEncVideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_READFILE, &CEncVideoDlg::OnBnClickedButton1Readfile)
	ON_BN_CLICKED(IDC_BUTTON2_WRITEFILE, &CEncVideoDlg::OnBnClickedButton2Writefile)
	ON_BN_CLICKED(IDC_BUTTON3_ENCRYPT, &CEncVideoDlg::OnBnClickedButton3Encrypt)
	ON_EN_CHANGE(IDC_EDIT1, &CEncVideoDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CEncVideoDlg ��Ϣ�������

BOOL CEncVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEncVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEncVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEncVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEncVideoDlg::OnBnClickedButton1Readfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog CScanFileDlg(TRUE,NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T(".264(*.264)|*.264|.h264(*.h264)|*.h264||All Files(*.*)|*.*||"), this);
	if(CScanFileDlg.DoModal() == IDOK)
	{
		PlainPath= CScanFileDlg.GetPathName();
		PlainName= CScanFileDlg.GetFileName();
		PlainExt = CScanFileDlg.GetFileExt();
		UpdateData(false);
	}
}


void CEncVideoDlg::OnBnClickedButton2Writefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString str;
	CString CipherName;
	str="(����)";
	CipherName = str+PlainName;

	CString CipherExtSet=_T("");
	CString CipherExt1,CipherExt2,CipherExt3,CipherExt4;
	CipherExt1=".";
	CipherExt2="(*.";
	CipherExt3=")";
	CipherExtSet=CipherExt1+PlainExt+CipherExt2+PlainExt+CipherExt3;//�����ļ���ʽ�������ı���һ��

	CFileDialog CSaveFileDlg(FALSE,NULL,CipherName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,this);
	CSaveFileDlg.m_ofn.lpstrFilter = CipherExtSet;
	CipherExtSet.ReleaseBuffer();
	CSaveFileDlg.m_ofn.lpstrTitle = _T("���ܺ���ļ����Ϊ");
	
	if(CSaveFileDlg.DoModal() == IDOK)
	{
		CipherPath=CSaveFileDlg.GetPathName();
		UpdateData(false);
	}

}



void CEncVideoDlg::OnBnClickedButton3Encrypt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int EncMBNum=524;
	//memset(Encdata,0x00,EncMBNum);
	//EncMBNum=49;
	GetEncDataInfo(GetConfTxtPath(),EncMBNum);

	EncInfo *SortedEncData;
	//SortedEncData=new EncInfo[EncMBNum];
	//EncMBNum=49;
	//SortedEncData=insert_MBsort(Encdata,EncMBNum);

	//for(int i=0;i<EncMBNum;i++)
	//{
	//	TRACE("%d\n",SortedEncData[i].start);
	//}

	CFile PlainFile;
	PlainFile.Open(PlainPath,CFile::typeBinary,NULL);
	int PlainLen=	PlainFile.GetLength();
	CFile CipherFile(CipherPath,CFile::modeCreate|CFile::modeReadWrite);

	BYTE *ReceBuf=new BYTE[PlainLen];
	memset(ReceBuf,0x00,PlainLen);
	BYTE *OutBuf=new BYTE[PlainLen];
	memset(OutBuf,0x00,PlainLen);

	//�Ȱ�ԭ�ļ�����һ�鵽������
	PlainFile.Read(ReceBuf,PlainLen);
	CipherFile.Write(ReceBuf,PlainLen);
	CipherFile.Flush();
	PlainFile.Close();
	memset(ReceBuf,0x00,PlainLen);
	
	//EncMBNum=49;
	for(int j=0;j<EncMBNum;j++)
	{
		int len=Encdata[j].length;
		//�������ж�ȡһ�����ȵ���������ReceBuf�����ܺ����OutBUf����д������
		CipherFile.SeekToBegin();	//�����ļ�ָ��ص��ļ���
		CipherFile.Seek(Encdata[j].start,CFile::begin);	//��MB[0]����ʼλ��ʼ��
		CipherFile.Read(ReceBuf,len);		//��MB[0]���ֽڳ���

		//���ɵȳ��������
		CString RndStr=Rnd(Encdata[j].length);
		int RndStrLen=WideCharToMultiByte(CP_ACP,0,RndStr,RndStr.GetLength(),NULL,0,NULL,NULL);
		char* RndChar=new char[RndStrLen+1];
		memset(RndChar,0x00,RndStrLen+1);
		WideCharToMultiByte(CP_ACP,0,RndStr,RndStr.GetLength(),RndChar,RndStrLen,NULL,NULL);

		//ReceBuf��RndChar���
		
		for(int i=0;i<len;i++)
		{
			OutBuf[i]=ReceBuf[i] ^ RndChar[i];
		}

		//��OutBufд��Cipher
		CipherFile.Seek(Encdata[j].start,CFile::begin);
		CipherFile.Write(OutBuf,len);
		CipherFile.Flush();
		delete[] RndChar;
		RndChar=NULL;
	}

	/*TRACE("%dλ�������%s",SortedEncData[0].length,str);*/
	//CipherFile.Seek(32,CFile::current);
	//CipherFile.Flush();

	//SortedEncData=NULL;
	//delete[] SortedEncData;
	//SortedEncData=NULL;
	//PlainFile.Close();
	CipherFile.Close();
	delete[] ReceBuf;
	ReceBuf=NULL;
	delete[] OutBuf;
	OutBuf=NULL;
}



CString CEncVideoDlg::GetConfTxtPath()
{
	//��ȡconf.txt·��
	TCHAR EXEFilePath[MAX_PATH];
	memset(EXEFilePath, '\0', MAX_PATH);
	GetModuleFileName(NULL,EXEFilePath,MAX_PATH);
	CString CurPath=EXEFilePath;
	int templen=CurPath.GetLength();
	for(int i=templen;i>-1;i--){
		if(CurPath[i]!='\\'){
			CurPath.Delete(i,1);
		}
		else{
			break;
		}
	}
	CString AllPath=CurPath+"conf.txt";
	return AllPath;
}

void CEncVideoDlg::GetEncDataInfo(CString ConfPath,int MBNum)
{
	CString title=_T("");
	CString str=_T("MB");
	
	for(int i=0;i<MBNum;i++)
	{
		title.Format(_T("%d"),i);
		title=str+title;
		Encdata[i].start=GetPrivateProfileInt(title,(CString)"strset",0,ConfPath);
		Encdata[i].length=GetPrivateProfileInt(title,(CString)"strlen",0,ConfPath);
		title=_T("");
	}
}
EncInfo *CEncVideoDlg::insert_MBsort(EncInfo array[],int len)
{
	int i,j;
	EncInfo key;
	for(i=1;i<len;i++)
	{
		key=array[i];
		//WAY 1
		for(j=i-1;j>=0;j-- )
		{
			if(array[j].start>key.start)
			{
				array[j+1]=array[j];
				array[j]=key;	
			}
		}
	}
	return array;
}

CString CEncVideoDlg::Rnd(int ByteNum)
{
    CString r = _T("");
    int i;
    srand(time(NULL));
    for(i=0;i<ByteNum;i++)
    {
        r = r + char(rand()%10+'0');
    }
    return r;
}

void CEncVideoDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(true);
	UpdateData(false);
}
