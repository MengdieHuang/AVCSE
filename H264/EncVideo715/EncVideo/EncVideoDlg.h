
// EncVideoDlg.h : ͷ�ļ�
//

#pragma once

typedef struct EncInfo
{
	int start;
	int length;
}EncDataInfo;

// CEncVideoDlg �Ի���
class CEncVideoDlg : public CDialogEx
{

private:
	CString CEncVideoDlg::GetConfTxtPath();
	void CEncVideoDlg::GetEncDataInfo(CString ConfPath,int MBNum);
	EncInfo *CEncVideoDlg::insert_MBsort(EncInfo array[],int len);
	CString CEncVideoDlg::Rnd(int ByteNum);
// ����
public:
	CEncVideoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ENCVIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
