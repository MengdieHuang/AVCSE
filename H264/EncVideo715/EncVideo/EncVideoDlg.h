
// EncVideoDlg.h : 头文件
//

#pragma once

typedef struct EncInfo
{
	int start;
	int length;
}EncDataInfo;

// CEncVideoDlg 对话框
class CEncVideoDlg : public CDialogEx
{

private:
	CString CEncVideoDlg::GetConfTxtPath();
	void CEncVideoDlg::GetEncDataInfo(CString ConfPath,int MBNum);
	EncInfo *CEncVideoDlg::insert_MBsort(EncInfo array[],int len);
	CString CEncVideoDlg::Rnd(int ByteNum);
// 构造
public:
	CEncVideoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ENCVIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString PlainPath;
	CString CipherPath;
	afx_msg void OnBnClickedButton1Readfile();
	CString PlainName;
	CString PlainExt;
	afx_msg void OnBnClickedButton2Writefile();
	afx_msg void OnBnClickedButton3Encrypt();
	EncInfo Encdata[524];
	
	afx_msg void OnEnChangeEdit1();
	//int EncMBNum;
};
