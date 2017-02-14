#include "editor.hpp"
#include <QBoxLayout>
#include <QStatusBar>
#include <QMenuBar>
#include <QFileDialog>
#include <QContextMenuEvent>
#include <QSplitter>
#include <QPixmap>

Editor::Editor(QWidget* parent)
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	//CONTENT 
	QSplitter *splitter = new QSplitter(parent);
	QTreeView *treeview = new QTreeView;
    QWidget* content = new QWidget;
	m_content = new QStackedLayout;
	m_texteditor = new QTextEdit;
	m_imageviewer = new QLabel;
	m_modelviewer = new QOpenGLWidget;
	m_content->addWidget(m_texteditor);
	m_content->addWidget(m_imageviewer);
	m_content->addWidget(m_modelviewer);
	content->setLayout(m_content);

	//TREEVIEW
	m_model = new QStandardItemModel;
	treeview->setSelectionMode(QAbstractItemView::SingleSelection);
	treeview->setModel(m_model);
	
	splitter->addWidget(treeview);
	splitter->addWidget(content);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);
	layout->addWidget(splitter);
	widget->setLayout(layout);

	createActions();
	createMenus();
	connect(treeview->selectionModel(),
	SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)), 
	this, SLOT(treeChanged(const QItemSelection&,const QItemSelection&)));
	
	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);

	setMinimumSize(300, 200);

}

void Editor::treeChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	QModelIndexList indices = selected.indexes();
	if (indices.size() > 0)
	{
		QVariant data = indices.front().data();
		QString entry = data.toString();
		QString extension = entry.split('.').back();
		if(extension=="ini"||extension=="inc"||extension=="txt")
		{
			m_content->setCurrentWidget(m_texteditor);
			std::string content = m_archive.GetText(entry.toStdString());
			m_texteditor->setText(QString(content.c_str()));
		}
		else if(extension=="jpg"||extension=="tga"||extension=="dds"||extension=="png")
		{
			m_content->setCurrentWidget(m_imageviewer);
			uint32_t size = 0;
			uint8_t* content = m_archive.GetBinary(entry.toStdString(),size);
			QPixmap pixmap;
			bool result = pixmap.loadFromData(content,size);
			m_imageviewer->setPixmap(pixmap);
		}
	}
	
}

Editor::~Editor()
{
}

void Editor::Load(const std::string & archive)
{

}

struct Directory
{

};

void Editor::PopulateTree()
{
	//get root of the tree
	m_model->clear();
	QStandardItem *item = m_model->invisibleRootItem();
	for(const auto& entry : m_archive.ListEntries())
	{
		QString name(entry.c_str());
		QStandardItem* child = new QStandardItem(name);
		child->setData(QVariant(name));
		item->appendRow(child);
	}
}

void Editor::createActions()
{
	//FILE ACTIONS
	auto createAction = [this](QAction*& action, QKeySequence::StandardKey key, const char* name, const char* description, auto&& cb)
	{
		action = new QAction(tr(name), this);
		action->setShortcuts(key);
		action->setStatusTip(description);
		connect(action, &QAction::triggered, this, cb);
	};
	//NEW
	createAction(newAct, QKeySequence::New, "&New", "Create a new file", &Editor::newFile);
	//OPEN
	createAction(openAct, QKeySequence::Open, "&Open", "Open a new archive", &Editor::open);
	//SAVE
	createAction(saveAct, QKeySequence::Save, "&Save", "Save opened archive", &Editor::save);
	//SAVE AS
	createAction(saveAsAct, QKeySequence::SaveAs, "Save&As", "Save opened archive", &Editor::saveAs);
	//QUIT
	createAction(quitAct, QKeySequence::Quit, "&Quit", "Quit program", &Editor::quit);
	//UNDO
	createAction(undoAct, QKeySequence::Undo, "&Undo", "Undo last action", &Editor::undo);
	//REDO
	createAction(redoAct, QKeySequence::Redo, "&Redo", "Redo last action", &Editor::redo);
	//CUT
	createAction(cutAct, QKeySequence::Cut, "&Cut", "Cut selection", &Editor::cut);
	//COPY
	createAction(copyAct, QKeySequence::Copy, "&Copy", "Copy selection", &Editor::copy);
	//PASTE
	createAction(pasteAct, QKeySequence::Paste, "&Paste", "Paste clipboard", &Editor::paste);
	//ABOUT
	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Info about this program"));
	connect(aboutAct, &QAction::triggered, this, &Editor::about);
	//ABOUT QT
	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Info about Qt"));
	connect(aboutQtAct, &QAction::triggered, this, &Editor::aboutQt);
}

void Editor::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	editMenu->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

#ifndef QT_NO_CONTEXTMENU
void Editor::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);
	menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void Editor::newFile()
{
}

void Editor::open()
{
	auto fileName = QFileDialog::getOpenFileName(this,
    tr("Open Archive"), "", tr("Big Files (*.big)"));
	
	if(m_archive.Load(fileName.toStdString()))
	{
		m_path = fileName;
		PopulateTree();
	}
}

void Editor::save()
{
	auto fileName = QFileDialog::getSaveFileName(this,
    tr("Save Archive"), "", tr("Big Files (*.big)"));
}

void Editor::saveAs()
{
}

void Editor::undo()
{
}

void Editor::redo()
{
}

void Editor::cut()
{
}

void Editor::copy()
{
}

void Editor::paste()
{
}

void Editor::about()
{
}

void Editor::aboutQt()
{
}

void Editor::quit()
{
}
