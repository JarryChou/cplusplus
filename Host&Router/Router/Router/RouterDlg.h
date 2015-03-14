
// RouterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Setting.h"
#include <WinSock2.h>
#include "afxwin.h"

// CRouterDlg �Ի���
class CRouterDlg : public CDialogEx
{
// ����
public:
	CRouterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROUTER_DIALOG };

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
	void InitUI();
	void InitEnvironment();
	CListCtrl m_table;

	Setting* setting;
	SOCKET m_sock;
	struct sockaddr_in m_desAddr;
	CEdit m_message;
};
