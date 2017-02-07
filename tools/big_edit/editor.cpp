#include "editor.hpp"
#include <QBoxLayout>
#include <QStatusBar>
#include <QMenuBar>
#include <QContextMenuEvent>

Editor::Editor(QWidget* parent)
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);
	layout->addWidget(topFiller);
	layout->addWidget(bottomFiller);
	widget->setLayout(layout);

	createActions();
	createMenus();

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);

	setMinimumSize(160, 160);

}

Editor::~Editor()
{
}

void Editor::Load(const std::string & archive)
{

}

void Editor::createActions()
{
	//FILE ACTIONS
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &Editor::newFile);

	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open a new archive"));
	connect(openAct, &QAction::triggered, this, &Editor::open);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save opened archive"));
	connect(saveAct, &QAction::triggered, this, &Editor::save);

	saveAsAct = new QAction(tr("Save&As"), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save opened archive"));
	connect(saveAsAct, &QAction::triggered, this, &Editor::saveAs);

	exitAct = new QAction(tr("&Exit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit program"));
	connect(exitAct, &QAction::triggered, this, &Editor::exit);
	//EDIT ACTIONS
	undoAct = new QAction(tr("&Undo"), this);
	undoAct->setShortcuts(QKeySequence::Undo);
	undoAct->setStatusTip(tr("Undo last action"));
	connect(undoAct, &QAction::triggered, this, &Editor::undo);

	redoAct = new QAction(tr("&Redo"), this);
	redoAct->setShortcuts(QKeySequence::Redo);
	redoAct->setStatusTip(tr("Redo last action"));
	connect(redoAct, &QAction::triggered, this, &Editor::redo);

	cutAct = new QAction(tr("&Cut"), this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip(tr("Cut selection"));
	connect(cutAct, &QAction::triggered, this, &Editor::cut);

	copyAct = new QAction(tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(tr("Copy selection"));
	connect(copyAct, &QAction::triggered, this, &Editor::copy);

	pasteAct = new QAction(tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip(tr("Paste at cursor"));
	connect(pasteAct, &QAction::triggered, this, &Editor::paste);
	//ABOUT
	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Info about this program"));
	connect(aboutAct, &QAction::triggered, this, &Editor::about);

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
	fileMenu->addAction(exitAct);

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
	
}

void Editor::save()
{
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

void Editor::exit()
{
}
