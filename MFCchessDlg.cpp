
// MFCchassDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCchess.h"
#include "MFCchessDlg.h"
#include "afxdialogex.h"
#include "board.h"
#include "Helper.h"
#include "PieceSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCchessDlg dialog

Board board;
COORD from;
COORD to;

CMFCchessDlg::CMFCchessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHASS_DIALOG, pParent)
	, turnDS(_T("לבן"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isPressed = false;

}

void CMFCchessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, turnDS);
}

BEGIN_MESSAGE_MAP(CMFCchessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCchessDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCchessDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCchessDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCchessDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCchessDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCchessDlg message handlers

BOOL CMFCchessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


double blocks;
void CMFCchessDlg::OnPaint()
{
	double blocks_size = 0;
	double piece_size = 0;
	double piece_center = 0;
	GetDesktopResolution(blocks, blocks_size, piece_size, piece_center);
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CFont font;
	//font.CreatePointFont(BLOKS*BLOKS_SIZE, _T("MS Gothic"));
	font.CreatePointFont(blocks*blocks_size, _T("MS Gothic"));
	CFont *oldFont = dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	CString string;
	
	string = _T("■");

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			//Sleep(100);
			dc.SetTextColor((i + j) % 2 ? RGB(130, 70, 0) : RGB(220, 169, 40));
			//dc.SetTextColor((i + j) % 2 ? RGB(255, 255, 255) : RGB(0, 0, 0));
			dc.DrawText(string, &rect,DT_VCENTER/* DT_CALCRECT*/);
			//rect.OffsetRect(BLOKS, 0);
			rect.OffsetRect(blocks, 0);

		}
		rect.OffsetRect(-8* blocks, blocks);
	}
	GetClientRect(&rect);
	rect.OffsetRect(blocks / piece_center, blocks / piece_center);
	font.DeleteObject();
	font.CreatePointFont(blocks*piece_size, _T("MS Gothic"));
	dc.SelectObject(&font);
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			COORD loc = { (SHORT)i,(SHORT)j };
			//board[loc] != nullptr ? Sleep(100) : Sleep(0);
			wchar_t s = board[loc] != nullptr ? board[loc]->getIcon() + 6 : L' ';
			string = s;
			int p = board[loc] != nullptr ? board[loc]->getPlayer() : 0;
			dc.SetTextColor(p ? RGB(255, 255, 255) : RGB(0, 0, 0));
			dc.DrawText(string, &rect, DT_VCENTER);
			string = board[loc] != nullptr ? board[loc]->getIcon() : L' ';
			dc.SetTextColor(p ? RGB(0, 0, 0) : RGB(255, 255, 255));
			dc.DrawText(string, &rect, DT_VCENTER);
			rect.OffsetRect(blocks, 0);
			//---------
			//string = board[loc] != nullptr ? board[loc]->getIcon() : L' ';
			//int p = board[loc] != nullptr ? board[loc]->getPlayer() : 0;
			//dc.SetTextColor(p ? RGB(255, 255, 255) : RGB(0, 0, 0));
			//dc.DrawText(string, &rect, DT_VCENTER);
			//rect.OffsetRect(BLOKS, 0);
		}
		rect.OffsetRect(-8 * blocks, blocks);
	}

	dc.SelectObject(oldFont);
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCchessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCchessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	startP = point;
	isPressed = true;
	CDialog::OnLButtonDown(nFlags, point);
	from = ConvLoc({ (SHORT)startP.x,(SHORT)startP.y },blocks );

}
void CMFCchessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isPressed)
	{
		endP = point;
		isPressed = false;
	}
	CDialog::OnLButtonUp(nFlags, point);
	to = ConvLoc({ (SHORT)endP.x,(SHORT)endP.y },blocks );
	if ((board[from] != nullptr && board[from]->getPlayer() == board.getTurn()))
	{
		if (validLoc(to) && validLoc(from)) {
			if (board.MovePiece(from, to)) {
				if (((to.Y == 0 && board.getTurn() == 1)||(to.Y == 7 && board.getTurn() == 0)) && board[to]->getIcon() == IPawn)
				{
					PieceSelect dlg;
					dlg.DoModal();
					board.ChangePiece(to, dlg.Select);
				}
				board.getTurn() = (board.getTurn() + 1) % 2;
				Invalidate();
				turnDS = board.getTurn() ? L"לבן" : L"שחור";
				UpdateData(false);
			}
			from = { -1,-1 };
			to = { -1,-1 };
		}
	}
}
void CMFCchessDlg::OnMouseMove(UINT nFlags, CPoint point)
{

}

void CMFCchessDlg::OnBnClickedButton1()
{
	CFile file;
	file.Open(L"boardInfo.chs", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	board.Serialize(ar);
	ar.Close();
}


void CMFCchessDlg::OnBnClickedButton2()
{
	CFile file;
	file.Open(L"boardInfo.chs", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	board.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
	turnDS = board.getTurn() ? L"לבן" : L"שחור";
	UpdateData(false);
}


void CMFCchessDlg::OnEnChangeEdit1()
{
}


void CMFCchessDlg::OnBnClickedButton3()
{
	board.CleanBoard();
	board.setNewBoard();
	board.getTurn() = 1;
	turnDS = L"לבן";
	Invalidate();
	UpdateData(false);
}


void CMFCchessDlg::OnBnClickedButton5()
{
	switch (MessageBox(L"האם לשמור לפני יציאה ?", L"יצאה", MB_YESNOCANCEL | MB_ICONQUESTION))
	{
	case IDYES: this->OnBnClickedButton1();
	case IDNO: this->EndDialog(0);
	default:
		break;
	}
}
