#include "cfilebrowser.h"

CFileBrowser::CFileBrowser(QWidget *parent) :
    QListView(parent)
{
    //init
    init();

    //config
    config();
}

void CFileBrowser::changePath()
{
    QModelIndex currIndex = currentIndex();
    if (currIndex.isValid())
    {
        if (mFileModel->isDir(currIndex))
        {
            //currentPath += "/";
            //currentPath += mFileModel->fileName(currIndex);
            mCurrentPath = mFileModel->fileInfo(currIndex).filePath();

            //setModel(mFileModel);
            setRootIndex(mFileModel->setRootPath(mCurrentPath));
        }
    }
}

void CFileBrowser::contextMenuEvent(QContextMenuEvent *e)
{
	menu->exec(QCursor::pos());
    QModelIndex currIndex = currentIndex();
    if (currIndex.isValid())
    {
		
        //if (mFileModel->isDir(currIndex))
        //{
        //    //Item_Menu->exec(e->globalPos());
        //}
        //else
        //{

        //    QVariant x = mFileModel->data(currIndex);
        //}
    }
}

void CFileBrowser::config()
{
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setUniformItemSizes(true);
    //setDragEnabled(false);
    setGridSize(QSize(64,64));
    setMovement(QListView::Snap);
    //setFixedSize(400,400);
}

void CFileBrowser::init()
{
    mFileModel = new QFileSystemModel();
    mFileModel->setIconProvider(new ThumbnailIconProvider());

    mCurrentPath = qApp->applicationFilePath();

    setModel(mFileModel);
    setRootIndex(mFileModel->setRootPath(mCurrentPath));

    //conncet
    connect(this,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(changePath()));
}

void CFileBrowser::createMenu( QString type )
{
	mType = type;

	CRepositoryManager repMan;

	menu = new QMenu;
	QList<menuInfo> info = repMan.getMenuesInfo(type);
	QSignalMapper *mapper = new QSignalMapper(this);
	if (info.size() > 0)
	{
		for (int i =0 ; i< info.size() ; i++)
		{
			menu_act = new QAction(QIcon(info[i].iconPath),info[i].name,this);
			menu_act->setData(info[i].name);
			menu->addAction(menu_act);
			mapper->setMapping(menu_act, info[i].name);
			connect(menu_act, SIGNAL(triggered()), mapper, SLOT(map()));
		}

		
		connect(mapper, SIGNAL(mapped(QString)), this, SLOT(actionTriggered(QString)));
	}
	
}

void CFileBrowser::actionTriggered(QString name)
{
	QStringList args;
	args << mType;
	args << name;
	QModelIndex currIndex = currentIndex();
	if (currIndex.isValid())
	{
		args << mFileModel->fileInfo(currIndex).filePath();
	}
	else
	{
		args << mCurrentPath;
	}

	emit sendCommand(args);
}

void CFileBrowser::setCurrenyPath( QString path )
{
	mCurrentPath = path;

	setRootIndex(mFileModel->setRootPath(mCurrentPath));
}
