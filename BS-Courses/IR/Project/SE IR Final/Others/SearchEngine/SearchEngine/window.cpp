#include "window.h"

CWindow::CWindow(QWidget *parent): QWidget(parent)
{
	mMainLayout = new QVBoxLayout(this);
}

CWindow::~CWindow()
{
}
