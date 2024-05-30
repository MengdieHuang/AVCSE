
// EncVideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncVideo.h"
#include "EncVideoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CEncVideoDlg 对话框



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


// CEncVideoDlg 消息处理程序

BOOL CEncVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEncVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEncVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEncVideoDlg::OnBnClickedButton1Readfile()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	CString CipherName;
	str="(加密)";
	CipherName = str+PlainName;

	CString CipherExtSet=_T("");
	CString CipherExt1,CipherExt2,CipherExt3,CipherExt4;
	CipherExt1=".";
	CipherExt2="(*.";
	CipherExt3=")";
	CipherExtSet=CipherExt1+PlainExt+CipherExt2+PlainExt+CipherExt3;//密文文件格式，与明文保持一致

	CFileDialog CSaveFileDlg(FALSE,NULL,CipherName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,this);
	CSaveFileDlg.m_ofn.lpstrFilter = CipherExtSet;
	CipherExtSet.ReleaseBuffer();
	CSaveFileDlg.m_ofn.lpstrTitle = _T("加密后的文件另存为");
	
	if(CSaveFileDlg.DoModal() == IDOK)
	{
		CipherPath=CSaveFileDlg.GetPathName();
		UpdateData(false);
	}

}



void CEncVideoDlg::OnBnClickedButton3Encrypt()
{
	// TODO: 在此添加控件通知处理程序代码
	
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

	//先把原文件复制一遍到密文中
	PlainFile.Read(ReceBuf,PlainLen);
	CipherFile.Write(ReceBuf,PlainLen);
	CipherFile.Flush();
	PlainFile.Close();
	memset(ReceBuf,0x00,PlainLen);
	
	//EncMBNum=49;
	for(int j=0;j<EncMBNum;j++)
	{
		int len=Encdata[j].length;
		//从密文中读取一定长度的码流存在ReceBuf，加密后存在OutBUf，重写进密文
		CipherFile.SeekToBegin();	//密文文件指针回到文件首
		CipherFile.Seek(Encdata[j].start,CFile::begin);	//从MB[0]的起始位开始读
		CipherFile.Read(ReceBuf,len);		//读MB[0]的字节长度

		//生成等长的随机数
		CString RndStr=Rnd(Encdata[j].length);
		int RndStrLen=WideCharToMultiByte(CP_ACP,0,RndStr,RndStr.GetLength(),NULL,0,NULL,NULL);
		char* RndChar=new char[RndStrLen+1];
		memset(RndChar,0x00,RndStrLen+1);
		WideCharToMultiByte(CP_ACP,0,RndStr,RndStr.GetLength(),RndChar,RndStrLen,NULL,NULL);

		//ReceBuf与RndChar异或
		
		for(int i=0;i<len;i++)
		{
			OutBuf[i]=ReceBuf[i] ^ RndChar[i];
		}

		//将OutBuf写入Cipher
		CipherFile.Seek(Encdata[j].start,CFile::begin);
		CipherFile.Write(OutBuf,len);
		CipherFile.Flush();
		delete[] RndChar;
		RndChar=NULL;
	}

	/*TRACE("%d位随机数：%s",SortedEncData[0].length,str);*/
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
	//获取conf.txt路径
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(true);
	UpdateData(false);
}
