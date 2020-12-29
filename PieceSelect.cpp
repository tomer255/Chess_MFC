// PieceSelect.cpp : implementation file
//

#include "pch.h"
#include "MFCchass.h"
#include "PieceSelect.h"
#include "afxdialogex.h"



// PieceSelect dialog

IMPLEMENT_DYNAMIC(PieceSelect, CDialogEx)

PieceSelect::PieceSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

PieceSelect::~PieceSelect()
{
}

void PieceSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PieceSelect, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PieceSelect::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &PieceSelect::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &PieceSelect::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PieceSelect::OnBnClickedButton4)
END_MESSAGE_MAP()


// PieceSelect message handlers


void PieceSelect::OnBnClickedButton1()
{
	Select = 3;
	this->EndDialog(0);
}

void PieceSelect::OnBnClickedButton2()
{
	Select = 0;
	this->EndDialog(0);
}


void PieceSelect::OnBnClickedButton3()
{
	Select = 1;
	this->EndDialog(0);
}


void PieceSelect::OnBnClickedButton4()
{
	Select = 1;
	this->EndDialog(0);
}
