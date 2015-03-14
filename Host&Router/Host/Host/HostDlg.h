
// Host1Dlg.h : ͷ�ļ�
//

#pragma once
#include "Setting.h"
#include <WinSock2.h>
#include "afxwin.h"

// CHost1Dlg �Ի���
class CHostDlg : public CDialogEx
{
// ����
public:
	CHostDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HOST1_DIALOG };

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
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	void InitUI();

private:
	Setting* setting;

public:
	SOCKET m_sock;
	struct sockaddr_in m_routerAddr;

public:
	void InitEnvironment();
	CEdit m_message;
	afx_msg void OnBnClickedButton1();

	CString m_dataToSend;
};
